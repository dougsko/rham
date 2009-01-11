/*
 *  Hamlib KIT backend - Universal Software Radio Peripheral
 *  Copyright (c) 2005 by Stephane Fillod
 *
 *	$Id: usrp_impl.h,v 1.1 2005/11/01 23:12:11 fillods Exp $
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public
 *   License along with this library; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef _USRP_IMPL_H
#define _USRP_IMPL_H 1

#include <hamlib/rig.h>
#include <token.h>

__BEGIN_DECLS

#define TOK_IFMIXFREQ TOKEN_BACKEND(2)


int usrp_init(RIG *rig);
int usrp_cleanup(RIG *rig);
int usrp_open(RIG *rig);
int usrp_close(RIG *rig);
int usrp_set_freq(RIG *rig, vfo_t vfo, freq_t freq);
int usrp_get_freq(RIG *rig, vfo_t vfo, freq_t *freq);
int usrp_set_conf(RIG *rig, token_t token, const char *val);
int usrp_get_conf(RIG *rig, token_t token, char *val);

const char * usrp_get_info(RIG *rig);

extern const struct rig_caps usrp0_caps;
extern const struct rig_caps usrp_caps;

__END_DECLS

#endif	/* _USRP_IMPL_H */
