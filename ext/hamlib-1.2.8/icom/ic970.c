/*
 *  Hamlib CI-V backend - description of IC-970 and variations
 *  Copyright (c) 2000-2003 by Stephane Fillod
 *
 *	$Id: ic970.c,v 1.6 2005/04/03 19:53:51 fillods Exp $
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License for more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include <hamlib/rig.h>
#include "icom.h"


#define IC970_MODES (RIG_MODE_CW|RIG_MODE_SSB|RIG_MODE_FM)

#define IC970_VFO_ALL (RIG_VFO_A|RIG_VFO_B)

#define IC970_VFO_OPS (RIG_OP_FROM_VFO|RIG_OP_TO_VFO)

#define IC970_STR_CAL { 0, { } }

/*
 * FIXME: this appears to be the IC-970A/E
 * what about the IC-970H ? please give it a fix. --SF
 */
static const struct icom_priv_caps ic970_priv_caps = { 
		0x2e,	/* default address */
		0,		/* 731 mode */
		ic737_ts_sc_list
};

const struct rig_caps ic970_caps = {
.rig_model =  RIG_MODEL_IC970,
.model_name = "IC-970", 
.mfg_name =  "Icom", 
.version =  BACKEND_VER, 
.copyright =  "LGPL",
.status =  RIG_STATUS_UNTESTED,
.rig_type =  RIG_TYPE_TRANSCEIVER,
.ptt_type =  RIG_PTT_NONE,
.dcd_type =  RIG_DCD_NONE,
.port_type =  RIG_PORT_SERIAL,
.serial_rate_min =  1200,
.serial_rate_max =  19200,
.serial_data_bits =  8,
.serial_stop_bits =  1,
.serial_parity =  RIG_PARITY_NONE,
.serial_handshake =  RIG_HANDSHAKE_NONE, 
.write_delay =  0,
.post_write_delay =  0,
.timeout =  200,
.retry =  3, 
.has_get_func =  RIG_FUNC_NONE,
.has_set_func =  RIG_FUNC_NONE, 
.has_get_level =  RIG_LEVEL_NONE,
.has_set_level =  RIG_LEVEL_NONE,
.has_get_parm =  RIG_PARM_NONE,
.has_set_parm =  RIG_PARM_NONE,
.level_gran =  {},
.parm_gran =  {},
.ctcss_list =  NULL,
.dcs_list =  NULL,
.preamp =   { RIG_DBLST_END, },
.attenuator =   { RIG_DBLST_END, },
.max_rit =  Hz(0),
.max_xit =  Hz(0),
.max_ifshift =  Hz(0),
.targetable_vfo =  0,
.vfo_ops =  IC970_VFO_OPS,
.scan_ops =  RIG_SCAN_NONE,
.transceive =  RIG_TRN_RIG,
.bank_qty =   0,
.chan_desc_sz =  0,

.chan_list =  {
		   {   1,  99, RIG_MTYPE_MEM  },
		   { 100, 101, RIG_MTYPE_EDGE },
		   { 102, 102, RIG_MTYPE_CALL },
		   RIG_CHAN_END,
		},

.rx_range_list1 =   { 
	{MHz(144),MHz(146),IC970_MODES,-1,-1,IC970_VFO_ALL},
	{MHz(430),MHz(440),IC970_MODES,-1,-1,IC970_VFO_ALL},
/* 1200MHz band module is optional */
//	{MHz(1240),MHz(1300),IC970_MODES,-1,-1,IC970_VFO_ALL},
	RIG_FRNG_END, },
.tx_range_list1 =  {
	{MHz(144),MHz(146),IC970_MODES,W(3.5),W(25),IC970_VFO_ALL},
	{MHz(430),MHz(440),IC970_MODES,W(3.5),W(25),IC970_VFO_ALL},
//	{MHz(1240),MHz(1300),IC970_MODES,W(1),W(10),IC970_VFO_ALL},
	RIG_FRNG_END, },

.rx_range_list2 =   {
	{MHz(144),MHz(150),IC970_MODES,-1,-1,IC970_VFO_ALL},
	{MHz(430),MHz(450),IC970_MODES,-1,-1,IC970_VFO_ALL},
/* 1200MHz band module is optional */
//	{MHz(1240),MHz(1300),IC970_MODES,-1,-1,IC970_VFO_ALL},
	RIG_FRNG_END, },
.tx_range_list2 =  {
	{MHz(144),MHz(150),IC970_MODES,W(3.5),W(25),IC970_VFO_ALL},
	{MHz(430),MHz(450),IC970_MODES,W(3.5),W(25),IC970_VFO_ALL},
//	{MHz(1240),MHz(1300),IC970_MODES,W(1),W(10),IC970_VFO_ALL},
	RIG_FRNG_END, },

.tuning_steps = 	{
	 {IC970_MODES,10},	/* TBC: does this rig supports settin tuning step? */
	 RIG_TS_END,
	},
	/* mode/filter list, remember: order matters! */
.filters = 	{
		{RIG_MODE_SSB|RIG_MODE_CW, kHz(2.3)},
	//	{RIG_MODE_FM, Hz(500)},		/* optional CW NARROW FILTER */
		{RIG_MODE_FM, kHz(15)},
		RIG_FLT_END,
	},

.cfgparams =  icom_cfg_params,
.set_conf =  icom_set_conf,
.get_conf =  icom_get_conf,

.priv =  (void*)&ic970_priv_caps,
.rig_init =   icom_init,
.rig_cleanup =   icom_cleanup,
.rig_open =  NULL,
.rig_close =  NULL,

.set_freq =  icom_set_freq,
.get_freq =  icom_get_freq,
.set_mode =  icom_set_mode,
.get_mode =  icom_get_mode,
.set_vfo =  icom_set_vfo,

.decode_event =  icom_decode_event,
.set_mem =  icom_set_mem,
.vfo_op =  icom_vfo_op,

};

