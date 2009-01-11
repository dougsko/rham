/*
 *  Hamlib Interface - USB communication low-level support
 *  Copyright (c) 2000-2005 by Stephane Fillod
 *
 *	$Id: usb_port.c,v 1.5 2007/10/07 20:12:36 fillods Exp $
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
 * \brief USB IO
 * \file usb_port.c
 *
 * doc todo: deal with defined(HAVE_LIBUSB)... quashing the doc process.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <hamlib/rig.h>

/*
 * Compile only if libusb is available
 */
#if defined(HAVE_LIBUSB) && defined(HAVE_USB_H)


#include <stdlib.h>
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include <usb.h>
#include "usb_port.h"

/**
 * \brief Find USB device
 * \param port
 * \return usb_device
 */
struct usb_device * find_device(const hamlib_port_t *port)
{
	struct usb_bus *p;
	struct usb_device *q;

  p = usb_get_busses();

  rig_debug(RIG_DEBUG_TRACE, "%s: looking for device %04x:%04x...", __FUNCTION__,
		  port->parm.usb.vid, port->parm.usb.pid);

  while (p != NULL){
    q = p->devices;
    while (q != NULL){
      rig_debug(RIG_DEBUG_TRACE, " %04x:%04x,", q->descriptor.idVendor,
			q->descriptor.idProduct);
      if (q->descriptor.idVendor == port->parm.usb.vid &&
			q->descriptor.idProduct == port->parm.usb.pid) {
      		rig_debug(RIG_DEBUG_TRACE, " -> found\n");
	  	return q;
	  }
      q = q->next;
    }
    p = p->next;
  }
  rig_debug(RIG_DEBUG_TRACE, " -> not found\n");
  return NULL;	/* not found */
}


int usb_port_open(hamlib_port_t *port)
{
	struct usb_dev_handle *udh;
	struct usb_device *dev;


	if (!port->pathname)
		return -RIG_EINVAL;

    usb_init ();	/* usb library init */
    if (usb_find_busses () < 0)
	rig_debug(RIG_DEBUG_ERR, "%s: usb_find_busses failed %s\n",
			__FUNCTION__, usb_strerror());
    if (usb_find_devices() < 0)
	rig_debug(RIG_DEBUG_ERR, "%s: usb_find_devices failed %s\n",
			__FUNCTION__, usb_strerror());

    dev = find_device(port);
    if (dev == 0)
	return -RIG_EIO;

  udh = usb_open (dev);
  if (udh == 0)
	return -RIG_EIO;

#ifdef LIBUSB_HAS_GET_DRIVER_NP
      /* Try to detach ftdi_sio kernel module
       * Returns ENODATA if driver is not loaded
       */
	if (usb_detach_kernel_driver_np(udh, port->parm.usb.iface) != 0 && errno != ENODATA) {
		if (errno == EPERM)
			rig_debug(RIG_DEBUG_ERR, "%s: inappropriate permissions\n", __FUNCTION__);
		usb_close(udh);
		return -RIG_EIO;
	}
#endif

  if (dev != usb_device (udh)){
	rig_debug(RIG_DEBUG_ERR, "%s:%d: internal error!\n", __FILE__, __LINE__);
	usb_close(udh);
	return -RIG_EINTERNAL;
  }

#if 0
  if (usb_set_configuration (udh, port->parm.usb.conf) < 0){
	rig_debug(RIG_DEBUG_ERR, "%s: usb_set_configuration: failed conf %d: %s\n",
			__FUNCTION__,port->parm.usb.conf, usb_strerror());
    usb_close (udh);
    return 0;
  }
#endif

   rig_debug(RIG_DEBUG_VERBOSE, "%s: %d\n", __FUNCTION__, port->parm.usb.iface);

  if (usb_claim_interface (udh, port->parm.usb.iface) < 0){
	rig_debug(RIG_DEBUG_ERR, "%s:usb_claim_interface: failed interface %d: %s\n", 
		    __FUNCTION__,port->parm.usb.iface, usb_strerror());
    usb_close (udh);
    return 0;
  }

#if 0
  if (usb_set_altinterface (udh, port->parm.usb.alt) < 0){
    fprintf (stderr, "%s:usb_set_alt_interface: failed: %s\n", __FUNCTION__,
		   usb_strerror());
    usb_release_interface (udh, port->parm.usb.iface);
    usb_close (udh);
    return 0;
  }
#endif

  port->handle = (void*) udh;

  return RIG_OK;
}

int usb_port_close(hamlib_port_t *port)
{
	struct usb_dev_handle *udh = port->handle;

	/* we're assuming that closing an interface automatically releases it. */
	return usb_close (udh) == 0 ? RIG_OK : -RIG_EIO;
}

#else

int usb_port_open(hamlib_port_t *port)
{
	return -RIG_ENAVAIL;
}

int usb_port_close(hamlib_port_t *port)
{
	return -RIG_ENAVAIL;
}

#endif	/* defined(HAVE_LIBUSB) && defined(HAVE_USB_H) */

/** @} */
