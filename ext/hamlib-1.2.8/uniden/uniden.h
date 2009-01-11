/*
 *  Hamlib Uniden backend - main header
 *  Copyright (c) 2001-2008 by Stephane Fillod
 *
 *	$Id: uniden.h,v 1.9 2008/10/07 18:58:08 fillods Exp $
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

#ifndef _UNIDEN_H
#define _UNIDEN_H 1

#include <hamlib/rig.h>
#include <cal.h>

#define BACKEND_VER	"0.3"

/* TODO: Trunk, Delay, Recording
 *
 * .channel_desc=1 is only on BC780 BC250 BC785
 * .ctcss_sql=1,
 * .dcs_sql=1,
 */
#define UNIDEN_CHANNEL_CAPS \
	.freq=1,\
	.levels=RIG_LEVEL_ATT,\
	.flags=1, /* L/O */ 

/* Calibration, actually from the BC785D */
#define UNIDEN_STR_CAL { 8, \
        { \
		{   0, -54 }, \
		{ 134, -20 }, /* < 0.50uV */ \
		{ 157, -12 }, \
		{ 173,  -9 }, \
		{ 189,  -5 }, \
		{ 204,  -1 }, \
		{ 221,   4 }, /* < 7.50uV */ \
		{ 255,  60 }, \
	} }

extern const tone_t uniden_ctcss_list[];
extern const tone_t uniden_dcs_list[];

int uniden_transaction (RIG *rig, const char *cmdstr, int cmd_len,
		const char *replystr, char *data, size_t *datasize);
int uniden_set_freq(RIG *rig, vfo_t vfo, freq_t freq);
int uniden_get_freq(RIG *rig, vfo_t vfo, freq_t *freq);
int uniden_set_mode(RIG *rig, vfo_t vfo, rmode_t mode, pbwidth_t width);
int uniden_get_mode(RIG *rig, vfo_t vfo, rmode_t *mode, pbwidth_t *width);
int uniden_set_mem(RIG *rig, vfo_t vfo, int ch);
int uniden_get_mem(RIG *rig, vfo_t vfo, int *ch);
int uniden_get_dcd(RIG *rig, vfo_t vfo, dcd_t *dcd);
int uniden_set_level(RIG *rig, vfo_t vfo, setting_t level, value_t val);
int uniden_get_level(RIG *rig, vfo_t vfo, setting_t level, value_t *val);
int uniden_get_channel(RIG *rig, channel_t *chan);
int uniden_set_channel(RIG *rig, const channel_t *chan);
const char* uniden_get_info(RIG *rig);

extern const struct rig_caps bc895_caps;
extern const struct rig_caps bc245_caps;
extern const struct rig_caps bc780_caps;
extern const struct rig_caps bc250_caps;
extern const struct rig_caps pro2052_caps;

extern const struct rig_caps bcd396t_caps;
extern const struct rig_caps bcd996t_caps;

#endif /* _UNIDEN_H */
