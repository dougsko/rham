/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpcrig.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif
/*
 *  Hamlib Interface - RPC definitions
 *  Copyright (c) 2000-2002 by Stephane Fillod and Frank Singleton
 *
 *	$Id: rpcrig.x,v 1.11 2006/01/09 21:41:39 fillods Exp $
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
#if __APPLE__
static int _rpcsvcdirty;
#endif

void
rigprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		freq_arg setfreq_1_arg;
		vfo_x getfreq_1_arg;
		mode_arg setmode_1_arg;
		vfo_x getmode_1_arg;
		vfo_x setvfo_1_arg;
		vfo_x getvfo_1_arg;
		freq_arg setsplitfreq_1_arg;
		vfo_x getsplitfreq_1_arg;
		mode_arg setsplitmode_1_arg;
		vfo_x getsplitmode_1_arg;
		split_arg setsplitvfo_1_arg;
		vfo_x getsplitvfo_1_arg;
		ptt_arg setptt_1_arg;
		vfo_x getptt_1_arg;
		vfo_x getdcd_1_arg;
		setting_arg setfunc_1_arg;
		setting_arg getfunc_1_arg;
		setting_arg setlevel_1_arg;
		setting_arg getlevel_1_arg;
		setting_arg setparm_1_arg;
		setting_arg getparm_1_arg;
		vfo_op_arg vfoop_1_arg;
		rptrshift_arg setrptrshift_1_arg;
		vfo_x getrptrshift_1_arg;
		shortfreq_arg setrptroffs_1_arg;
		vfo_x getrptroffs_1_arg;
		tone_arg setctcsstone_1_arg;
		vfo_x getctcsstone_1_arg;
		tone_arg setctcsssql_1_arg;
		vfo_x getctcsssql_1_arg;
		tone_arg setdcscode_1_arg;
		vfo_x getdcscode_1_arg;
		tone_arg setdcssql_1_arg;
		vfo_x getdcssql_1_arg;
		shortfreq_arg setrit_1_arg;
		vfo_x getrit_1_arg;
		shortfreq_arg setxit_1_arg;
		vfo_x getxit_1_arg;
		shortfreq_arg setts_1_arg;
		vfo_x getts_1_arg;
		scan_arg scan_1_arg;
		reset_x reset_1_arg;
		ch_arg setmem_1_arg;
		vfo_x getmem_1_arg;
		ant_arg setant_1_arg;
		vfo_x getant_1_arg;
		ch_arg setbank_1_arg;
		powerstat_x setpowerstat_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case GETMODEL:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_model_x;
		local = (char *(*)(char *, struct svc_req *)) getmodel_1_svc;
		break;

	case GETRIGSTATE:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_rigstate_res;
		local = (char *(*)(char *, struct svc_req *)) getrigstate_1_svc;
		break;

	case SETFREQ:
		_xdr_argument = (xdrproc_t) xdr_freq_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setfreq_1_svc;
		break;

	case GETFREQ:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_freq_res;
		local = (char *(*)(char *, struct svc_req *)) getfreq_1_svc;
		break;

	case SETMODE:
		_xdr_argument = (xdrproc_t) xdr_mode_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setmode_1_svc;
		break;

	case GETMODE:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_mode_res;
		local = (char *(*)(char *, struct svc_req *)) getmode_1_svc;
		break;

	case SETVFO:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setvfo_1_svc;
		break;

	case GETVFO:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_vfo_res;
		local = (char *(*)(char *, struct svc_req *)) getvfo_1_svc;
		break;

	case SETSPLITFREQ:
		_xdr_argument = (xdrproc_t) xdr_freq_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setsplitfreq_1_svc;
		break;

	case GETSPLITFREQ:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_freq_res;
		local = (char *(*)(char *, struct svc_req *)) getsplitfreq_1_svc;
		break;

	case SETSPLITMODE:
		_xdr_argument = (xdrproc_t) xdr_mode_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setsplitmode_1_svc;
		break;

	case GETSPLITMODE:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_mode_res;
		local = (char *(*)(char *, struct svc_req *)) getsplitmode_1_svc;
		break;

	case SETSPLITVFO:
		_xdr_argument = (xdrproc_t) xdr_split_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setsplitvfo_1_svc;
		break;

	case GETSPLITVFO:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_split_res;
		local = (char *(*)(char *, struct svc_req *)) getsplitvfo_1_svc;
		break;

	case SETPTT:
		_xdr_argument = (xdrproc_t) xdr_ptt_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setptt_1_svc;
		break;

	case GETPTT:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_ptt_res;
		local = (char *(*)(char *, struct svc_req *)) getptt_1_svc;
		break;

	case GETDCD:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_dcd_res;
		local = (char *(*)(char *, struct svc_req *)) getdcd_1_svc;
		break;

	case SETFUNC:
		_xdr_argument = (xdrproc_t) xdr_setting_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setfunc_1_svc;
		break;

	case GETFUNC:
		_xdr_argument = (xdrproc_t) xdr_setting_arg;
		_xdr_result = (xdrproc_t) xdr_val_res;
		local = (char *(*)(char *, struct svc_req *)) getfunc_1_svc;
		break;

	case SETLEVEL:
		_xdr_argument = (xdrproc_t) xdr_setting_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setlevel_1_svc;
		break;

	case GETLEVEL:
		_xdr_argument = (xdrproc_t) xdr_setting_arg;
		_xdr_result = (xdrproc_t) xdr_val_res;
		local = (char *(*)(char *, struct svc_req *)) getlevel_1_svc;
		break;

	case SETPARM:
		_xdr_argument = (xdrproc_t) xdr_setting_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setparm_1_svc;
		break;

	case GETPARM:
		_xdr_argument = (xdrproc_t) xdr_setting_arg;
		_xdr_result = (xdrproc_t) xdr_val_res;
		local = (char *(*)(char *, struct svc_req *)) getparm_1_svc;
		break;

	case VFOOP:
		_xdr_argument = (xdrproc_t) xdr_vfo_op_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) vfoop_1_svc;
		break;

	case SETRPTRSHIFT:
		_xdr_argument = (xdrproc_t) xdr_rptrshift_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setrptrshift_1_svc;
		break;

	case GETRPTRSHIFT:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_rptrshift_res;
		local = (char *(*)(char *, struct svc_req *)) getrptrshift_1_svc;
		break;

	case SETRPTROFFS:
		_xdr_argument = (xdrproc_t) xdr_shortfreq_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setrptroffs_1_svc;
		break;

	case GETRPTROFFS:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_shortfreq_res;
		local = (char *(*)(char *, struct svc_req *)) getrptroffs_1_svc;
		break;

	case SETCTCSSTONE:
		_xdr_argument = (xdrproc_t) xdr_tone_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setctcsstone_1_svc;
		break;

	case GETCTCSSTONE:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_tone_res;
		local = (char *(*)(char *, struct svc_req *)) getctcsstone_1_svc;
		break;

	case SETCTCSSSQL:
		_xdr_argument = (xdrproc_t) xdr_tone_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setctcsssql_1_svc;
		break;

	case GETCTCSSSQL:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_tone_res;
		local = (char *(*)(char *, struct svc_req *)) getctcsssql_1_svc;
		break;

	case SETDCSCODE:
		_xdr_argument = (xdrproc_t) xdr_tone_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setdcscode_1_svc;
		break;

	case GETDCSCODE:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_tone_res;
		local = (char *(*)(char *, struct svc_req *)) getdcscode_1_svc;
		break;

	case SETDCSSQL:
		_xdr_argument = (xdrproc_t) xdr_tone_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setdcssql_1_svc;
		break;

	case GETDCSSQL:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_tone_res;
		local = (char *(*)(char *, struct svc_req *)) getdcssql_1_svc;
		break;

	case SETRIT:
		_xdr_argument = (xdrproc_t) xdr_shortfreq_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setrit_1_svc;
		break;

	case GETRIT:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_shortfreq_res;
		local = (char *(*)(char *, struct svc_req *)) getrit_1_svc;
		break;

	case SETXIT:
		_xdr_argument = (xdrproc_t) xdr_shortfreq_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setxit_1_svc;
		break;

	case GETXIT:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_shortfreq_res;
		local = (char *(*)(char *, struct svc_req *)) getxit_1_svc;
		break;

	case SETTS:
		_xdr_argument = (xdrproc_t) xdr_shortfreq_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setts_1_svc;
		break;

	case GETTS:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_shortfreq_res;
		local = (char *(*)(char *, struct svc_req *)) getts_1_svc;
		break;

	case SCAN:
		_xdr_argument = (xdrproc_t) xdr_scan_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) scan_1_svc;
		break;

	case RESET:
		_xdr_argument = (xdrproc_t) xdr_reset_x;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) reset_1_svc;
		break;

	case SETMEM:
		_xdr_argument = (xdrproc_t) xdr_ch_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setmem_1_svc;
		break;

	case GETMEM:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_ch_res;
		local = (char *(*)(char *, struct svc_req *)) getmem_1_svc;
		break;

	case SETANT:
		_xdr_argument = (xdrproc_t) xdr_ant_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setant_1_svc;
		break;

	case GETANT:
		_xdr_argument = (xdrproc_t) xdr_vfo_x;
		_xdr_result = (xdrproc_t) xdr_ant_res;
		local = (char *(*)(char *, struct svc_req *)) getant_1_svc;
		break;

	case SETBANK:
		_xdr_argument = (xdrproc_t) xdr_ch_arg;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setbank_1_svc;
		break;

	case SETPOWERSTAT:
		_xdr_argument = (xdrproc_t) xdr_powerstat_x;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) setpowerstat_1_svc;
		break;

	case GETPOWERSTAT:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_powerstat_res;
		local = (char *(*)(char *, struct svc_req *)) getpowerstat_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}
