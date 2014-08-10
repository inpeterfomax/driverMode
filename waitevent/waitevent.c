/********************************
cription:a code template for linux kernel 2.6
author:Lee Chong()
last modified:12.1,2009
********************************/
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>

#define DEBUG
#define DEVICE_NAME "waitevent_device"
#define DEVICE_CLASS_NAME "waitevent_class"

static int major_number=0;
static int minor_number=0;
static dev_t dev_number;

struct template_dev
{
	char buff[256];
	struct semaphore sem;
	struct cdev this_dev;
	struct class *dev_class;
	struct device *dev_device;
}dev_waitevent;

static int template_open(struct inode *inode,struct file *filp)
{	
	filp->private_data = &dev_waitevent;
	return 0; 
}
static int template_release(struct inode *inode,struct file *filp)
{
	struct template_dev * tmpdev;
	tmpdev = filp->private_data;
	kfree(tmpdev);
	filp->private_data = NULL;

	return 0;
}


static ssize_t template_read(struct file *filp,char __user *buf,size_t count, loff_t *ppos)
{
	sema_init(&dev_waitevent.sem,1);   //it equals sema_init(&sem,1);
	down_interruptible(&dev_waitevent.sem);
		if( strlen(dev_waitevent.buff))
			copy_to_user(buf,dev_waitevent.buff,sizeof(dev_waitevent.buff));	
	up(&dev_waitevent.sem);

	return 0; 
}
static ssize_t template_write(struct file *filp, const char __user *buf,size_t count, loff_t *ppos)
{
	down_interruptible(&dev_waitevent.sem);
		copy_from_user(buf,dev_waitevent.buff,count);
	up(&dev_waitevent.sem);

	return 0;
}

static const struct file_operations template_fp =
{
	.owner 	= THIS_MODULE,
	.open	= template_open,
	.release = template_release,
	.read 	= template_read,
	.write 	= template_write,
};


static int __init template_init(){
	int result;
	int err_number=0;
	
	dev_number = MKDEV(major_number,minor_number);

	if(major_number)
	{
	   result = register_chrdev_region(dev_number,1,DEVICE_NAME);
#ifdef DEBUG
printk("register_chardev_region result:%d \n",result);
#endif
	}else{
	   result = alloc_chrdev_region(&dev_number,0,1,DEVICE_NAME);
	   
	   major_number=MAJOR(dev_number);
	   minor_number=MINOR(dev_number);
#ifdef DEBUG
printk("alloc_chrdev_region result:%d \n",result);
#endif
	}
		cdev_init(&dev_waitevent.this_dev,&template_fp);
		dev_waitevent.this_dev.owner = THIS_MODULE;
		dev_waitevent.this_dev.ops = &template_fp;	
#ifdef DEBUG
	printk("after register device number:%d \n",dev_number);
#endif
		err_number = cdev_add(&dev_waitevent.this_dev,dev_number,1);
		if(err_number!=0){
	   		printk("add device failed!Error number is%d \n",err_number); 
		}
	
	dev_waitevent.dev_class = class_create(THIS_MODULE,DEVICE_CLASS_NAME);
    if (IS_ERR(dev_waitevent.dev_class))
    {
    	printk(KERN_WARNING "Unable to create waitevent class; errno = %ld\n",
                              PTR_ERR(dev_waitevent.dev_class));
            result = PTR_ERR(dev_waitevent.dev_class);
            goto out;
    }
#if 1
    dev_waitevent.dev_device = device_create(dev_waitevent.dev_class,NULL, dev_number,&dev_waitevent, DEVICE_NAME);
    if (IS_ERR(dev_waitevent.dev_device)) {
              printk(KERN_WARNING "Unable to create waitevent device; errno = %ld\n",
                              PTR_ERR(dev_waitevent.dev_device));
              result = PTR_ERR(dev_waitevent.dev_device);
              goto unregister;
    }
#endif
unregister:
	unregister_chrdev_region(MKDEV(major_number,minor_number),1);
out:
	return 0;
}

static void __exit template_exit(){
	device_destroy(dev_waitevent.dev_device,MKDEV(major_number,minor_number));
	class_destroy(dev_waitevent.dev_class);
	unregister_chrdev_region(MKDEV(major_number,minor_number),1);
	cdev_del(&dev_waitevent.this_dev);
}

module_init(template_init);
module_exit(template_exit);

MODULE_AUTHOR("peter.gu");
MODULE_DESCRIPTION("module template");
MODULE_LICENSE("Dual BSD/GPL");

