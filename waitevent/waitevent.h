#ifndef _WAITEVENT_H
#define _WAITEVENT_H

#include<linux/modules.h>
#include<linux/errno.h>
#include<linux/semaphore.h>
#include<linux/cdev.h>

struct spimple_dev{
	char *name;
	struct cdev cdev;
	struct semaphore sem;
}
#define DEVNAME 	"simple"
#endif

