/* Parallel Port Drink Machine interface for linux. */
/* 
   As it stands now:
   Major 252, minor 0 is the drink machine. Writing a character of the slot
   you want to drop drops it, reading one character gives a bitmask of the
   slot out indicators.
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/wrapper.h>
#include <linux/parport.h>

#include "drink.h"

/* In 2.2.3 /usr/include/linux/version.h includes 
 * a macro for this, but 2.0.35 doesn't - so I add 
 * it here if necessary. */
#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) ((a)*65536+(b)*256+(c))
#endif

void drink_wait( int interval );

/* Conditional compilation. LINUX_VERSION_CODE is 
 * the code (as per KERNEL_VERSION) of this version. */
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,2,0)
#include <asm/uaccess.h> /* for put_user */
#endif

#define SUCCESS 0


/* Deal with CONFIG_MODVERSIONS */
#if CONFIG_MODVERSIONS==1
#define MODVERSIONS
#include <linux/modversions.h>
#endif


/* Device Declarations **************************** */

/* parport handle */
struct parport *myport = NULL;
struct pardevice *mypdevice = NULL;

/* Is the device open right now? Used to prevent 
 * concurent access into the same device */
static int Device_Open = 0;
/* Minor number of currently open device */
static int Minor;

/* This function is called whenever a process 
 * attempts to open the device file */
static int device_open(struct inode *inode, 
                       struct file *file)
{
  /* We don't want to talk to two processes at the 
   * same time */
  if (Device_Open)
    return -EBUSY;
  if( parport_claim( mypdevice ) ) {
	return -EBUSY;
  }
  Device_Open++;
  Minor = (inode->i_rdev & 0xFF); 
  if( Minor != 0 && Minor != 1 ) /* only one we support right now */
	return -EINVAL;

  /* Make sure that the module isn't removed while 
   * the file is open by incrementing the usage count 
   * (the number of opened references to the module, if 
   * it's not zero rmmod will fail)
   */
  MOD_INC_USE_COUNT;

  return SUCCESS;
}


/* This function is called when a process closes the 
 * device file. It doesn't have a return value in 
 * version 2.0.x because it can't fail (you must ALWAYS
 * be able to close a device). In version 2.2.x it is 
 * allowed to fail - but we won't let it. 
 */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
static int device_release(struct inode *inode, 
                          struct file *file)
#else 
static void device_release(struct inode *inode, 
                           struct file *file)
#endif
{
  parport_release( mypdevice );

  /* We're now ready for our next caller */
  Device_Open --;

  /* Decrement the usage count, otherwise once you 
   * opened the file you'll never get rid of the module.
   */
  MOD_DEC_USE_COUNT;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
  return 0;
#endif
}


/* This function is called whenever a process which 
 * have already opened the device file attempts to 
 * read from it. */


#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
static ssize_t device_read(struct file *file,
    char *buffer,    /* The buffer to fill with data */
    size_t length,   /* The length of the buffer */
    loff_t *offset)  /* Our offset in the file */
#else
static int device_read(struct inode *inode,
                       struct file *file,
    char *buffer,   /* The buffer to fill with 
                     * the data */ 
    int length)     /* The length of the buffer 
                     * (mustn't write beyond that!) */
#endif
{
  static unsigned char mask;
  static unsigned char control;
  if( Minor == 0 ) {
        control = CONTROL_READ_OUT;
  }
  else if( Minor == 1 ) {
        control = CONTROL_READ_PANEL;
  }

  /* Put the parallel port in readback mode, and select the out switches. */
  parport_write_control( myport, control );
  drink_wait( 1 );

  /* Hit the strobe line to read it back */
  parport_write_control( myport, control | CONTROL_STROBE ); 
  drink_wait( 1 );
  mask = parport_read_data( myport );

  parport_write_data( myport, 0x00 );
  parport_write_control( myport, control );
  parport_write_control( myport, CONTROL_CLEAR );
  
  put_user( mask, buffer);
  return 1;
}




/* This function is called when somebody tries to write 
 * into our device file */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
static ssize_t device_write(struct file *file,
    const char *buffer,    /* The buffer */
    size_t length,   /* The length of the buffer */
    loff_t *offset)  /* Our offset in the file */
#else
static int device_write(struct inode *inode,
                        struct file *file,
                        const char *buffer,
                        int length)
#endif
{
  static time_t lastdrop = 0;
  unsigned char mask;

  switch( Minor ) {
      case 0: /* Main drink interface to the slots. */
        /* Put a slight delay in to allow the slots to cycle correctly */
        if( ( CURRENT_TIME - lastdrop ) < 10 ) {
            printk( "drink: Delaying drop.\n" );
            drink_wait( (CURRENT_TIME - lastdrop) * 3000 );
        }
        lastdrop = CURRENT_TIME;

  	#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0) 
     	  get_user( mask, buffer );
  	#else
     	  mask = get_user( buffer );
  	#endif
         if( mask > 6 ) {
             printk( "drink: invalid slot number: %d\n", mask );
             return -EINVAL;
         }
         mask = 1 << mask;
          /* Set the bitmask we want to drop onto the bus, then strobe the 
             register to hold it. */
	  parport_write_control( myport, CONTROL_DROP_SET ); 
  	  parport_write_data( myport, mask ); 
          parport_write_control( myport, CONTROL_DROP_SET | CONTROL_STROBE );
	  parport_write_control( myport, CONTROL_DROP_SET );
	  parport_write_control( myport, CONTROL_DROP_RUN );
          /* Select the output_enable on the drop register, then strobe it. */
          parport_write_control( myport, CONTROL_DROP_RUN | CONTROL_STROBE );
 
          /* Wait about a half second, then turn the register back off. */
          drink_wait( 500 );
          parport_write_control( myport, CONTROL_DROP_RUN );

 	return 1;
        break;   
      case 1: /* Set the front panel lights */
	 #if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
          get_user( mask, buffer );
        #else
          mask = get_user( buffer );
        #endif
	parport_write_control( myport, CONTROL_PANEL_SET );
	/* We need to invert the mask here because of a fuck-up on the
	   hardware. */
	parport_write_data( myport, (mask ^ 0xff) );
	parport_write_control( myport, CONTROL_PANEL_SET | CONTROL_STROBE );
	parport_write_control( myport, CONTROL_PANEL_SET );
 	parport_write_control( myport, CONTROL_CLEAR );
	parport_write_data( myport, 0x00 );
	return 1;
 	break;
      default:

         return -EINVAL;  /* Any others we just return an error. */
  }
}

/* Module Declarations ***************************** */

struct file_operations Fops = {
  NULL,   /* seek */
  device_read, 
  device_write,
  NULL,   /* readdir */
  NULL,   /* select */
  NULL,   /* ioctl  */ 
  NULL,   /* mmap */
  device_open,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,2,0)
  NULL,   /* flush */
#endif
  device_release  /* a.k.a. close */
};

static int Major;

/* Initialize the module - Register the character device */
int init_module()
{
  /* Register the character device (atleast try) */
  Major = module_register_chrdev(DEVICE_MAJOR, 
                                 DEVICE_NAME,
                                 &Fops);

  /* Negative values signify an error */
  if (Major < 0) {
    printk ("%s device failed with %d\n",
            "Sorry, registering the character",
            Major);
    return Major;
  }

  myport = parport_enumerate();
  if( myport == NULL ) {
	printk( "drink couldn't get a parallel port\n" );
	return -1;
  }
 
  mypdevice = parport_register_device( myport, DEVICE_NAME, NULL, NULL, NULL, 0,
	NULL );
  if( mypdevice == NULL ) {
	printk( "drink couldn't grab a pardevice\n" );
	return -1;
  }
  printk ("drink registerd on major device number %d, parallel port at 0x%x\n",
          DEVICE_MAJOR, (unsigned int)myport->base);
 
  return 0;
}


/* Cleanup - unregister the appropriate file from /proc */
void cleanup_module()
{
  int ret;
  
  if( mypdevice ) {
	parport_unregister_device( mypdevice );
  }

  /* Unregister the device */
  ret = module_unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
 
  /* If there's an error, report it */ 
  if (ret < 0)
    printk("Error in unregister_chrdev: %d\n", ret);
}

void drink_wait( int interval ) {
          current->state = TASK_INTERRUPTIBLE;
          schedule_timeout((interval * HZ + 1000 - HZ) / 1000);
          current->state = TASK_RUNNING;
}
