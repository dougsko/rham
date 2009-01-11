/*
 *  Hamlib Interface - debug
 *  Copyright (c) 2000-2006 by Stephane Fillod
 *
 *	$Id: debug.c,v 1.4 2006/10/15 00:27:51 aa6e Exp $
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

/**
 * \addtogroup rig_internal
 * @{
 */

/**
 * \file debug.c
 * \brief control hamlib debugging functions
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <sys/types.h>
#include <unistd.h>

#include <hamlib/rig.h>

#include "misc.h"

static int rig_debug_level = RIG_DEBUG_TRACE;
static FILE *rig_debug_stream;
static vprintf_cb_t rig_vprintf_cb;
static rig_ptr_t rig_vprintf_arg;


#define DUMP_HEX_WIDTH 16
/**
 * \param ptr Pointer to memory area
 * \param size Number of chars to words to dump
 * \brief Do a hex dump of the unsigned char array.
 */
void dump_hex(const unsigned char ptr[], size_t size)
{
  int i;
  char buf[DUMP_HEX_WIDTH+1];

  if (!rig_need_debug(RIG_DEBUG_TRACE))
		  return;

  buf[DUMP_HEX_WIDTH] = '\0';

  for(i=0; i<size; i++) {
    if (i % DUMP_HEX_WIDTH == 0)
      rig_debug(RIG_DEBUG_TRACE,"%.4x\t",i);

    rig_debug(RIG_DEBUG_TRACE," %.2x", ptr[i]);

	if (ptr[i] >= ' ' && ptr[i] < 0x7f)
		buf[i%DUMP_HEX_WIDTH] = ptr[i];
	else
		buf[i%DUMP_HEX_WIDTH] = '.';

    if (i % DUMP_HEX_WIDTH == DUMP_HEX_WIDTH-1)
      rig_debug(RIG_DEBUG_TRACE,"\t%s\n",buf);
  }

  /* Add some spaces in order to align right ASCII dump column */
  if ((i / DUMP_HEX_WIDTH) > 0) {
    int j;
    for (j = i % DUMP_HEX_WIDTH; j < DUMP_HEX_WIDTH; j++)
      rig_debug(RIG_DEBUG_TRACE,"   ");
  }

  if (i % DUMP_HEX_WIDTH != DUMP_HEX_WIDTH-1) {
  	buf[i % DUMP_HEX_WIDTH] = '\0';
    rig_debug(RIG_DEBUG_TRACE,"\t%s\n",buf);
  }

} 


/**
 * \param debug_level
 * \brief Change the current debug level
 */
void HAMLIB_API rig_set_debug(enum rig_debug_level_e debug_level)
{
	rig_debug_level = debug_level;
}

/**
 * \param debug_level
 * \brief Useful for dump_hex, etc.
 */
int HAMLIB_API rig_need_debug(enum rig_debug_level_e debug_level)
{
	return (debug_level <= rig_debug_level);
}

/**
 * \param debug_level
 * \param fmt
 * \brief Default is debugging messages are done through stderr
 */
void HAMLIB_API rig_debug(enum rig_debug_level_e debug_level, const char *fmt, ...)
{
	va_list ap;

	if (!rig_need_debug(debug_level))
		return;


	va_start(ap, fmt);

	if (rig_vprintf_cb) {

		rig_vprintf_cb(debug_level, rig_vprintf_arg, fmt, ap);

	} else {
		if (!rig_debug_stream)
			rig_debug_stream = stderr;

		vfprintf (rig_debug_stream, fmt, ap);
	}

	va_end(ap);
}

/**
 * \brief set callback to handle debug messages
 * \param cb    The callback to install
 * \param arg   A Pointer to some private data to pass later on to the callback
 *
 *  Install a callback for \a rig_debug messages.
\code
int
rig_message_cb   (enum rig_debug_level_e debug_level,
		  rig_ptr_t user_data,
		  const char *fmt,
		  va_list ap)
{
	char buf[1024];

	sprintf (buf, "Message(%s) ", (char*)user_data);
	syslog (LOG_USER, buf);
	vsprintf (buf, fmt, ap);
	syslog (LOG_USER, buf);

	return RIG_OK;
}

	. . .

	char *cookie = "Foo";
	rig_set_debug_callback (rig_message_cb, (rig_ptr_t)cookie);
\endcode
 *
 * \return RIG_OK if the operation has been sucessful, otherwise
 * a negative value if an error occured (in which case, cause
 * is set appropriately).
 *
 * \sa rig_debug()
 */
vprintf_cb_t HAMLIB_API rig_set_debug_callback(vprintf_cb_t cb, rig_ptr_t arg)
{
	vprintf_cb_t prev_cb = rig_vprintf_cb;

	rig_vprintf_cb = cb;
	rig_vprintf_arg = arg;

	return prev_cb;
}

/**
 * \brief change stderr to some different output
 * \param stream The stream to set output to
 */
FILE* HAMLIB_API rig_set_debug_file(FILE *stream)
{
	FILE *prev_stream = rig_debug_stream;

	rig_debug_stream = stream;

	return prev_stream;
}

/** @} */
