/*
 * dumpcaps.c - Copyright (C) 2000-2008 Stephane Fillod
 * This programs dumps the capabilities of a backend rig.
 *
 *
 *    $Id: dumpcaps.c,v 1.48 2008/09/21 19:10:59 fillods Exp $  
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <hamlib/rig.h>
#include "misc.h"

#include "sprintflst.h"
#include "rigctl_parse.h"

static int print_ext(RIG *rig, const struct confparams *cfp, rig_ptr_t ptr);
int range_sanity_check(const struct freq_range_list range_list[], int rx);
int ts_sanity_check(const struct tuning_step_list tuning_step[]);
static void dump_chan_caps(const channel_cap_t *chan, FILE *fout);

/*
 * the rig may be in rig_init state, but not openned
 */
int dumpcaps (RIG* rig, FILE *fout)
{ 
	const struct rig_caps *caps;
	int status,i;
	int can_esplit,can_echannel;
	char freqbuf[20];
	int backend_warnings=0;
	static char prntbuf[1024];	/* a malloc would be better.. */

	if (!rig || !rig->caps)
		return -RIG_EINVAL;

	caps = rig->caps;

	fprintf(fout, "Caps dump for model %d\n",caps->rig_model);
	fprintf(fout, "Model name:\t%s\n",caps->model_name);
	fprintf(fout, "Mfg name:\t%s\n",caps->mfg_name);
	fprintf(fout, "Backend version:\t%s\n",caps->version);
	fprintf(fout, "Backend copyright:\t%s\n",caps->copyright);
	fprintf(fout, "Backend status:\t%s\n", rig_strstatus(caps->status));
	fprintf(fout, "Rig type:\t");
	switch (caps->rig_type & RIG_TYPE_MASK) {
	case RIG_TYPE_TRANSCEIVER:
			fprintf(fout, "Transceiver\n");
			break;
	case RIG_TYPE_HANDHELD:
			fprintf(fout, "Handheld\n");
			break;
	case RIG_TYPE_MOBILE:
			fprintf(fout, "Mobile\n");
			break;
	case RIG_TYPE_RECEIVER:
			fprintf(fout, "Receiver\n");
			break;
	case RIG_TYPE_PCRECEIVER:
			fprintf(fout, "PC Receiver\n");
			break;
	case RIG_TYPE_SCANNER:
			fprintf(fout, "Scanner\n");
			break;
	case RIG_TYPE_TRUNKSCANNER:
			fprintf(fout, "Trunking scanner\n");
			break;
	case RIG_TYPE_COMPUTER:
			fprintf(fout, "Computer\n");
			break;
	case RIG_TYPE_TUNER:
			fprintf(fout, "Tuner\n");
			break;
	case RIG_TYPE_OTHER:
			fprintf(fout, "Other\n");
			break;
	default:
			fprintf(fout, "Unknown\n");
			backend_warnings++;
	}

	fprintf(fout, "PTT type:\t");
	switch (caps->ptt_type) {
	case RIG_PTT_RIG:
			fprintf(fout, "rig capable\n");
			break;
	case RIG_PTT_PARALLEL:
			fprintf(fout, "thru parallel port (DATA0)\n");
			break;
	case RIG_PTT_SERIAL_RTS:
			fprintf(fout, "thru serial port (CTS/RTS)\n");
			break;
	case RIG_PTT_SERIAL_DTR:
			fprintf(fout, "thru serial port (DTR/DSR)\n");
			break;
	case RIG_PTT_NONE:
			fprintf(fout, "None\n");
			break;
	default:
			fprintf(fout, "Unknown\n");
			backend_warnings++;
	}

	fprintf(fout, "DCD type:\t");
	switch (caps->dcd_type) {
	case RIG_DCD_RIG:
			fprintf(fout, "rig capable\n");
			break;
	case RIG_DCD_PARALLEL:
			fprintf(fout, "thru parallel port (DATA1? STROBE?)\n");
			break;
	case RIG_DCD_SERIAL_CTS:
			fprintf(fout, "thru serial port (CTS/RTS)\n");
			break;
	case RIG_DCD_SERIAL_DSR:
			fprintf(fout, "thru serial port (DTR/DSR)\n");
			break;
	case RIG_DCD_SERIAL_CAR:
			fprintf(fout, "thru serial port (CD)\n");
			break;
	case RIG_DCD_NONE:
			fprintf(fout, "None\n");
			break;
	default:
			fprintf(fout, "Unknown\n");
			backend_warnings++;
	}

	fprintf(fout, "Port type:\t");
	switch (caps->port_type) {
	case RIG_PORT_SERIAL:
			fprintf(fout, "RS-232\n");
			break;
	case RIG_PORT_PARALLEL:
			fprintf(fout, "Parallel\n");
			break;
	case RIG_PORT_DEVICE:
			fprintf(fout, "device driver\n");
			break;
	case RIG_PORT_USB:
			fprintf(fout, "USB\n");
			break;
	case RIG_PORT_NETWORK:
			fprintf(fout, "network link\n");
			break;
	case RIG_PORT_NONE:
			fprintf(fout, "None\n");
			break;
	default:
			fprintf(fout, "Unknown\n");
			backend_warnings++;
	}

	fprintf(fout, "Serial speed: %d..%d bauds, %d%c%d %s\n", caps->serial_rate_min,
					caps->serial_rate_max,caps->serial_data_bits,
					caps->serial_parity==RIG_PARITY_NONE?'N':
					(caps->serial_parity==RIG_PARITY_ODD?'O':'E'),
					caps->serial_stop_bits,
					caps->serial_handshake==RIG_HANDSHAKE_NONE?"":
					(caps->serial_handshake==RIG_HANDSHAKE_XONXOFF?"XONXOFF":"CTS/RTS")
					);

	fprintf(fout, "Write delay %dms, timeout %dms, %d retry\n",
					caps->write_delay,caps->timeout,caps->retry);
	fprintf(fout, "Post Write delay %dms\n",
					caps->post_write_delay);

	fprintf(fout, "Has targetable VFO: %s\n",
					caps->targetable_vfo?"yes":"no");

	fprintf(fout, "Has transceive: %s\n",
					caps->transceive?"yes":"no");

	fprintf(fout, "Announce: 0x%x\n", caps->announces);
	fprintf(fout, "Max RIT: -%ld.%ldkHz/+%ld.%ldkHz\n", 
					caps->max_rit/1000, caps->max_rit%1000,
					caps->max_rit/1000, caps->max_rit%1000);

	fprintf(fout, "Max XIT: -%ld.%ldkHz/+%ld.%ldkHz\n", 
					caps->max_xit/1000, caps->max_xit%1000,
					caps->max_xit/1000, caps->max_xit%1000);

	fprintf(fout, "Max IF-SHIFT: -%ld.%ldkHz/+%ld.%ldkHz\n", 
					caps->max_ifshift/1000, caps->max_ifshift%1000,
					caps->max_ifshift/1000, caps->max_ifshift%1000);

	fprintf(fout, "Preamp:");
	for(i=0; i<MAXDBLSTSIZ && caps->preamp[i] != 0; i++)
			fprintf(fout, " %ddB", caps->preamp[i]);
	if (i == 0)
		fprintf(fout, " none");
	fprintf(fout, "\n");
	fprintf(fout, "Attenuator:");
	for(i=0; i<MAXDBLSTSIZ && caps->attenuator[i] != 0; i++)
			fprintf(fout, " %ddB",caps->attenuator[i]);
	if (i == 0)
		fprintf(fout, " none");
	fprintf(fout, "\n");

	sprintf_func(prntbuf, caps->has_get_func);
	fprintf(fout, "Get functions: %s\n", prntbuf);

	sprintf_func(prntbuf, caps->has_set_func);
	fprintf(fout, "Set functions: %s\n", prntbuf);

	sprintf_level_gran(prntbuf, caps->has_get_level, caps->level_gran);
	fprintf(fout, "Get level: %s\n", prntbuf);

	if ((caps->has_get_level&RIG_LEVEL_SQLSTAT)) {
			fprintf(fout, "Warning: backend uses deprecated SQLSTAT level!\n");
			backend_warnings++;
	}

	if ((caps->has_get_level&RIG_LEVEL_RAWSTR) &&
				caps->str_cal.size == 0) {
			fprintf(fout, "Warning: backend has get RAWSTR, but not calibration data\n");
			backend_warnings++;
	}

	sprintf_level_gran(prntbuf, caps->has_set_level, caps->level_gran);
	fprintf(fout, "Set level: %s\n", prntbuf);
	if (caps->has_set_level&RIG_LEVEL_READONLY_LIST) {
			fprintf(fout, "Warning: backend can set readonly levels!\n");
			backend_warnings++;
	}
	fprintf(fout, "Extra levels:");
	rig_ext_level_foreach(rig, print_ext, NULL);
	fprintf(fout, "\n");

	sprintf_parm_gran(prntbuf, caps->has_get_parm, caps->parm_gran);
	fprintf(fout, "Get parameters: %s\n", prntbuf);

	sprintf_parm_gran(prntbuf, caps->has_set_parm, caps->parm_gran);
	fprintf(fout, "Set parameters: %s\n", prntbuf);
	if (caps->has_set_parm&RIG_PARM_READONLY_LIST) {
			fprintf(fout, "Warning: backend can set readonly parms!\n");
			backend_warnings++;
	}
	fprintf(fout, "Extra parameters:");
	rig_ext_parm_foreach(rig, print_ext, fout);
	fprintf(fout, "\n");


	if (rig->state.vfo_list!=0)
		sprintf_vfo(prntbuf, rig->state.vfo_list);
	else
		strcpy(prntbuf," none! This backend might be bogus!\n");
	fprintf(fout, "VFO list: %s\n", prntbuf);

	sprintf_vfop(prntbuf, caps->vfo_ops);
	fprintf(fout, "VFO Ops: %s\n", prntbuf);

	sprintf_scan(prntbuf, caps->scan_ops);
	fprintf(fout, "Scan Ops: %s\n", prntbuf);

	fprintf(fout, "Number of banks:\t%d\n", caps->bank_qty);
	fprintf(fout, "Memory name desc size:\t%d\n", caps->chan_desc_sz);

	fprintf(fout, "Memories:");
	for (i=0; i<CHANLSTSIZ && caps->chan_list[i].type; i++) {
		fprintf(fout, "\n\t%d..%d:   \t%s", caps->chan_list[i].start,
						caps->chan_list[i].end,
						rig_strmtype(caps->chan_list[i].type));
		fprintf(fout, "\n\t  mem caps: ");
		dump_chan_caps(&caps->chan_list[i].mem_caps, fout);
	}
	if (i == 0)
		fprintf(fout, " none");
	fprintf(fout, "\n");

/* TODO: print rx/tx ranges here */
	status = range_sanity_check(caps->tx_range_list1,0);
	fprintf(fout, "TX ranges status, region 1:\t%s (%d)\n",status?"Bad":"OK",status);
	if (status) backend_warnings++;
	status = range_sanity_check(caps->rx_range_list1,1);
	fprintf(fout, "RX ranges status, region 1:\t%s (%d)\n",status?"Bad":"OK",status);
	if (status) backend_warnings++;

	status = range_sanity_check(caps->tx_range_list2,0);
	fprintf(fout, "TX ranges status, region 2:\t%s (%d)\n",status?"Bad":"OK",status);
	if (status) backend_warnings++;
	status = range_sanity_check(caps->rx_range_list2,1);
	fprintf(fout, "RX ranges status, region 2:\t%s (%d)\n",status?"Bad":"OK",status);
	if (status) backend_warnings++;

	fprintf(fout, "Tuning steps:");
	for (i=0; i<TSLSTSIZ && !RIG_IS_TS_END(caps->tuning_steps[i]); i++) {
		if (caps->tuning_steps[i].ts == RIG_TS_ANY)
			strcpy(freqbuf, "ANY");
		else
			sprintf_freq(freqbuf,caps->tuning_steps[i].ts);
		sprintf_mode(prntbuf,caps->tuning_steps[i].modes);
		fprintf(fout, "\n\t%s:   \t%s", freqbuf, prntbuf);
	}
	if (i==0) {
			fprintf(fout, " none! This backend might be bogus!");
			backend_warnings++;
	}
	fprintf(fout, "\n");
	status = ts_sanity_check(caps->tuning_steps);
	fprintf(fout, "Tuning steps status:\t%s (%d)\n",status?"Bad":"OK",status);
	if (status) backend_warnings++;

	fprintf(fout, "Filters:");
	for (i=0; i<FLTLSTSIZ && !RIG_IS_FLT_END(caps->filters[i]); i++) {
		if (caps->filters[i].width == RIG_FLT_ANY)
			strcpy(freqbuf, "ANY");
		else
			sprintf_freq(freqbuf,caps->filters[i].width);
		sprintf_mode(prntbuf,caps->filters[i].modes);
		fprintf(fout, "\n\t%s:   \t%s", freqbuf, prntbuf);
	}
	if (i==0) {
			fprintf(fout, " none! This backend might be bogus!");
			backend_warnings++;
	}
	fprintf(fout, "\n");

        fprintf(fout, "Bandwidths:");
	for (i=1; i < 1<<10; i<<=1) {
		pbwidth_t pbnorm = rig_passband_normal(rig, i);

		if (pbnorm == 0)
			continue;

		sprintf_freq(freqbuf, pbnorm);
		fprintf(fout, "\n\t%s\tnormal: %s,\t", rig_strrmode(i), freqbuf);

		sprintf_freq(freqbuf, rig_passband_narrow(rig, i));
		fprintf(fout, "narrow: %s,\t", freqbuf);

		sprintf_freq(freqbuf, rig_passband_wide(rig, i));
		fprintf(fout, "wide: %s", freqbuf);
	}
	fprintf(fout, "\n");

	fprintf(fout, "Has priv data:\t%c\n",caps->priv!=NULL?'Y':'N');
	/*
	 * Status is either 'Y'es, 'E'mulated, 'N'o
	 *
	 * TODO: keep me up-to-date with API call list!
	 */
	fprintf(fout, "Has init:\t%c\n",caps->rig_init!=NULL?'Y':'N');
	fprintf(fout, "Has cleanup:\t%c\n",caps->rig_cleanup!=NULL?'Y':'N');
	fprintf(fout, "Has open:\t%c\n",caps->rig_open!=NULL?'Y':'N');
	fprintf(fout, "Has close:\t%c\n",caps->rig_close!=NULL?'Y':'N');
	fprintf(fout, "Can set conf:\t%c\n",caps->set_conf!=NULL?'Y':'N');
	fprintf(fout, "Can get conf:\t%c\n",caps->get_conf!=NULL?'Y':'N');
	fprintf(fout, "Can set frequency:\t%c\n",caps->set_freq!=NULL?'Y':'N');
	fprintf(fout, "Can get frequency:\t%c\n",caps->get_freq!=NULL?'Y':'N');
	fprintf(fout, "Can set mode:\t%c\n",caps->set_mode!=NULL?'Y':'N');
	fprintf(fout, "Can get mode:\t%c\n",caps->get_mode!=NULL?'Y':'N');
	fprintf(fout, "Can set vfo:\t%c\n",caps->set_vfo!=NULL?'Y':'N');
	fprintf(fout, "Can get vfo:\t%c\n",caps->get_vfo!=NULL?'Y':'N');
	fprintf(fout, "Can set ptt:\t%c\n",caps->set_ptt!=NULL?'Y':'N');
	fprintf(fout, "Can get ptt:\t%c\n",caps->get_ptt!=NULL?'Y':'N');
	fprintf(fout, "Can get dcd:\t%c\n",caps->get_dcd!=NULL?'Y':'N');
	fprintf(fout, "Can set repeater duplex:\t%c\n",caps->set_rptr_shift!=NULL?'Y':'N');
	fprintf(fout, "Can get repeater duplex:\t%c\n",caps->get_rptr_shift!=NULL?'Y':'N');
	fprintf(fout, "Can set repeater offset:\t%c\n",caps->set_rptr_offs!=NULL?'Y':'N');
	fprintf(fout, "Can get repeater offset:\t%c\n",caps->get_rptr_offs!=NULL?'Y':'N');

	can_esplit = caps->set_vfo || 
		(rig_has_vfo_op(rig, RIG_OP_TOGGLE) && caps->vfo_op);
	fprintf(fout, "Can set split freq:\t%c\n",caps->set_split_freq!=NULL?'Y':
			(can_esplit&&caps->set_freq?'E':'N'));
	fprintf(fout, "Can get split freq:\t%c\n",caps->get_split_freq!=NULL?'Y':
			(can_esplit&&caps->get_freq?'E':'N'));
	fprintf(fout, "Can set split mode:\t%c\n",caps->set_split_mode!=NULL?'Y':
			(can_esplit&&caps->set_mode?'E':'N'));
	fprintf(fout, "Can get split mode:\t%c\n",caps->get_split_mode!=NULL?'Y':
			(can_esplit&&caps->get_mode?'E':'N'));

	fprintf(fout, "Can set split vfo:\t%c\n",caps->set_split_vfo!=NULL?'Y':'N');
	fprintf(fout, "Can get split vfo:\t%c\n",caps->get_split_vfo!=NULL?'Y':'N');
	fprintf(fout, "Can set tuning step:\t%c\n",caps->set_ts!=NULL?'Y':'N');
	fprintf(fout, "Can get tuning step:\t%c\n",caps->get_ts!=NULL?'Y':'N');
	fprintf(fout, "Can set RIT:\t%c\n",caps->set_rit!=NULL?'Y':'N');
	fprintf(fout, "Can get RIT:\t%c\n",caps->get_rit!=NULL?'Y':'N');
	fprintf(fout, "Can set XIT:\t%c\n",caps->set_xit!=NULL?'Y':'N');
	fprintf(fout, "Can get XIT:\t%c\n",caps->get_xit!=NULL?'Y':'N');
	fprintf(fout, "Can set CTCSS:\t%c\n",caps->set_ctcss_tone!=NULL?'Y':'N');
	fprintf(fout, "Can get CTCSS:\t%c\n",caps->get_ctcss_tone!=NULL?'Y':'N');
	fprintf(fout, "Can set DCS:\t%c\n",caps->set_dcs_code!=NULL?'Y':'N');
	fprintf(fout, "Can get DCS:\t%c\n",caps->get_dcs_code!=NULL?'Y':'N');
	fprintf(fout, "Can set CTCSS squelch:\t%c\n",caps->set_ctcss_sql!=NULL?'Y':'N');
	fprintf(fout, "Can get CTCSS squelch:\t%c\n",caps->get_ctcss_sql!=NULL?'Y':'N');
	fprintf(fout, "Can set DCS squelch:\t%c\n",caps->set_dcs_sql!=NULL?'Y':'N');
	fprintf(fout, "Can get DCS squelch:\t%c\n",caps->get_dcs_sql!=NULL?'Y':'N');
	fprintf(fout, "Can set power stat:\t%c\n",caps->set_powerstat!=NULL?'Y':'N');
	fprintf(fout, "Can get power stat:\t%c\n",caps->get_powerstat!=NULL?'Y':'N');
	fprintf(fout, "Can reset:\t%c\n",caps->reset!=NULL?'Y':'N');
	fprintf(fout, "Can get ant:\t%c\n",caps->get_ant!=NULL?'Y':'N');
	fprintf(fout, "Can set ant:\t%c\n",caps->set_ant!=NULL?'Y':'N');
	fprintf(fout, "Can set transceive:\t%c\n",caps->set_trn!=NULL?'Y':'N');
	fprintf(fout, "Can get transceive:\t%c\n",caps->get_trn!=NULL?'Y':'N');
	fprintf(fout, "Can set func:\t%c\n",caps->set_func!=NULL?'Y':'N');
	fprintf(fout, "Can get func:\t%c\n",caps->get_func!=NULL?'Y':'N');
	fprintf(fout, "Can set level:\t%c\n",caps->set_level!=NULL?'Y':'N');
	fprintf(fout, "Can get level:\t%c\n",caps->get_level!=NULL?'Y':'N');
	fprintf(fout, "Can set param:\t%c\n",caps->set_parm!=NULL?'Y':'N');
	fprintf(fout, "Can get param:\t%c\n",caps->get_parm!=NULL?'Y':'N');
	fprintf(fout, "Can send DTMF:\t%c\n",caps->send_dtmf!=NULL?'Y':'N');
	fprintf(fout, "Can recv DTMF:\t%c\n",caps->recv_dtmf!=NULL?'Y':'N');
	fprintf(fout, "Can send Morse:\t%c\n",caps->send_morse!=NULL?'Y':'N');
	fprintf(fout, "Can decode events:\t%c\n",caps->decode_event!=NULL?'Y':'N');
	fprintf(fout, "Can set bank:\t%c\n",caps->set_bank!=NULL?'Y':'N');
	fprintf(fout, "Can set mem:\t%c\n",caps->set_mem!=NULL?'Y':'N');
	fprintf(fout, "Can get mem:\t%c\n",caps->get_mem!=NULL?'Y':'N');

	can_echannel = caps->set_mem && caps->set_vfo;
	fprintf(fout, "Can set channel:\t%c\n",caps->set_channel!=NULL?'Y':
			(can_echannel?'E':'N'));
	fprintf(fout, "Can get channel:\t%c\n",caps->get_channel!=NULL?'Y':
			(can_echannel?'E':'N'));

	fprintf(fout, "Can ctl mem/vfo:\t%c\n",caps->vfo_op!=NULL?'Y':'N');
	fprintf(fout, "Can scan:\t%c\n",caps->scan!=NULL?'Y':'N');
	fprintf(fout, "Can get info:\t%c\n",caps->get_info!=NULL?'Y':'N');
	

	fprintf(fout, "\nOverall backend warnings: %d\n", backend_warnings);

	return backend_warnings;
}


static int print_ext(RIG *rig, const struct confparams *cfp, rig_ptr_t ptr)
{
	fprintf((FILE*)ptr, " %s", cfp->name);

	return 1;       /* process them all */
}


/* 
 * check for:
 * - start_freq<end_freq	return_code=-1
 * - modes are not 0		return_code=-2
 * - if(rx), low_power,high_power set to -1		return_code=-3
 *     else, power is >0
 * - array is ended by a {0,0,0,0,0} element (before boundary) rc=-4
 * - ranges with same modes do not overlap		rc=-5
 * ->fprintf(stderr,)!
 *
 * TODO: array is sorted in ascending freq order
 */
int range_sanity_check(const struct freq_range_list range_list[], int rx)
{
	int i;

	for (i=0; i<FRQRANGESIZ; i++) {
			if (range_list[i].start == 0 && range_list[i].end == 0)
					break;
			if (range_list[i].start > range_list[i].end)
					return -1;
			if (range_list[i].modes == 0)
					return -2;
			if (rx) {
				if (range_list[i].low_power > 0 && range_list[i].high_power > 0)
						return -3;
			} else {
				if (!(range_list[i].low_power > 0 && range_list[i].high_power > 0))
						return -3;
				if (range_list[i].low_power > range_list[i].high_power)
						return -3;
			}
	}
	if (i == FRQRANGESIZ)
			return -4;

	return 0;
}

/* 
 * check for:
 * - steps sorted in ascending order return_code=-1
 * - modes are not 0		return_code=-2
 * - array is ended by a {0,0,0,0,0} element (before boundary) rc=-4
 *
 * TODO: array is sorted in ascending freq order
 */
int ts_sanity_check(const struct tuning_step_list tuning_step[])
{
	int i;
	shortfreq_t last_ts;
	rmode_t last_modes;

	last_ts = 0;
	last_modes = RIG_MODE_NONE;
	for (i=0; i<TSLSTSIZ; i++) {
			if (RIG_IS_TS_END(tuning_step[i]))
					break;
			if (tuning_step[i].ts != RIG_TS_ANY && tuning_step[i].ts < last_ts && 
							last_modes == tuning_step[i].modes)
					return -1;
			if (tuning_step[i].modes == 0)
					return -2;
			last_ts = tuning_step[i].ts;
			last_modes = tuning_step[i].modes;
	}
	if (i == TSLSTSIZ)
			return -4;

	return 0;
}


static void dump_chan_caps(const channel_cap_t *chan, FILE *fout)
{
  if (chan->bank_num) fprintf(fout, "BANK ");
  if (chan->ant) fprintf(fout, "ANT ");
  if (chan->freq) fprintf(fout, "FREQ ");
  if (chan->mode) fprintf(fout, "MODE ");
  if (chan->width) fprintf(fout, "WIDTH ");
  if (chan->tx_freq) fprintf(fout, "TXFREQ ");
  if (chan->tx_mode) fprintf(fout, "TXMODE ");
  if (chan->tx_width) fprintf(fout, "TXWIDTH ");
  if (chan->split) fprintf(fout, "SPLIT ");
  if (chan->rptr_shift) fprintf(fout, "RPTRSHIFT ");
  if (chan->rptr_offs) fprintf(fout, "RPTROFS ");
  if (chan->tuning_step) fprintf(fout, "TS ");
  if (chan->rit) fprintf(fout, "RIT ");
  if (chan->xit) fprintf(fout, "XIT ");
  if (chan->funcs) fprintf(fout, "FUNC "); /* TODO: iterate over the list */
  if (chan->levels) fprintf(fout, "LEVEL "); /* TODO: iterate over the list */
  if (chan->ctcss_tone) fprintf(fout, "TONE ");
  if (chan->ctcss_sql) fprintf(fout, "CTCSS ");
  if (chan->dcs_code) fprintf(fout, "DCSCODE ");
  if (chan->dcs_sql) fprintf(fout, "DCSSQL ");
  if (chan->scan_group) fprintf(fout, "SCANGRP ");
  if (chan->flags) fprintf(fout, "FLAG "); /* TODO: iterate over the RIG_CHFLAG's */
  if (chan->channel_desc) fprintf(fout, "NAME ");
  if (chan->ext_levels) fprintf(fout, "EXTLVL ");
}

int dumpconf (RIG* rig, FILE *fout)
{
        rig_token_foreach(rig, print_conf_list, (rig_ptr_t)rig);

	return 0;
}

