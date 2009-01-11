/*
 *  Hamlib Lowe backend - main header
 *  Copyright (c) 2003 by Stephane Fillod
 *
 *	$Id: lowe.h,v 1.1 2003/06/22 19:36:37 fillods Exp $
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

#ifndef _LOWE_H
#define _LOWE_H 1

#include <hamlib/rig.h>


int lowe_set_freq(RIG *rig, vfo_t vfo, freq_t freq);
int lowe_get_freq(RIG *rig, vfo_t vfo, freq_t *freq);
int lowe_set_mode(RIG *rig, vfo_t vfo, rmode_t mode, pbwidth_t width);
int lowe_get_mode(RIG *rig, vfo_t vfo, rmode_t *mode, pbwidth_t *width);
int lowe_get_level(RIG *rig, vfo_t vfo, setting_t level, value_t *val);
int lowe_reset(RIG *rig, reset_t reset);
const char *lowe_get_info(RIG *rig);

extern const struct rig_caps hf235_caps;

#endif /* _LOWE_H */
