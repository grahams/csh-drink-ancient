#ifndef DRINK_H
#define DRINK_H

#include <linux/ioctl.h>

#define DEVICE_MAJOR 252
#define DEVICE_NAME "drink"

/* Bitmasks for the control lines */
#define CONTROL_CLEAR      0x00  /* No activity */
#define CONTROL_STROBE     0x01  /* Strobe line */
#define CONTROL_DROP_SET   0x0e  /* Set the drop bitmask register */
#define CONTROL_DROP_RUN   0x08  /* Activate the drop register */
#define CONTROL_PANEL_SET  0x0a  /* Set the front panel LED's */
#define CONTROL_READ_OUT   0x22  /* Read back the out switches. */
#define CONTROL_READ_PANEL 0x26 /* Read back the panel switches */
#endif
