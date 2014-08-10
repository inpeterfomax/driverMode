#include <linux/modules.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <asm/semaphore.h>
#include <linux/errno.h>
#include "simple.h"

static int simple_major = simple_MAJOR; //default in simple.h
MODULE_PARM(simple_major,int,0666);
static int simple_minor = simple_MINOR;
MODULE_PARM(simple_minor,int,0666);
static int simple_num   = simple_NUM;
MODULE_PARM(simple_num,int,0666);

static	dev_t dev;
static struct simple_dev mydev;

static int simple_open(struct inode *inode,struct file *filp)
{
	struct simple_dev *dev;
	dev = container_of(inode->i_cdev,struct simple_dev,cdev);
	flip->private_data = dev;
	
	if( (flip->f_flags & O_ACCMODE) == O_WRONLY)
		printk("just to write\n");	
	return 0;
}

static int simple_release(struct inode *inode,struct file *filp){
	return 0;
}
static ssize_t simple_read(struct file *filp,char __user *buf,size_t count,loff_t *f_pos)
{
	static int retval;
	return retval;
}
static int simple_write(struct file *filp,const char __user *buf,size_t count,loff_t *f_pos)
{
	ssize_t retval = -ENOMEN;
	return retval;
}
static int simple_ioctl(struct file*filp ,const int cmd,unsigned long *arg)
{
	return 0;
}

//device operations
static struct file_operation simple_fops = {
	.owner  = THIS_MODULE,
//	.llseek = simple_llseek,
	.read   = simple_read,
	.write  = simple_write,
	.ioctl  = simple_ioctl,
	.open   = simple_open,
	.release = simple_release,
};

//set cdev
static void simple_setup_cdev(struct simple_dev *dev,int index){
	int err;
	int devno = MKDEV(simple_major,simple_monit+index);
	
	cdev_init(&dev->cdev,&simple_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdv.ops = simple_fops;
	err = cdev_add(&dev->cdev,devno,1);
	
	if(err)
		printk(KERN "add dev failed\n");
}
//register the device id ,pass simple_major,simple_minor
static int register_dev_id(int major,int minor,int num)
{
	int result;

	if(major){
		dev = MKDEV(major,minor);
		result = register_chrdev_region(dev,num,simple_NAME);
	}else{
		result = alloc_chrdev_region(&dev,minor,num,simple_NAME);
		simple_major = MAJOR(dev);  //this is global param
	}
	if(result < 0){
		printk(KERN_WARNING "simple : can't get major %d\n",simple_major);
		return result;
	}
	return 0;
}

static int __init fun_init(){
	int retval;
	simple_set_cdev(&mydev,0);
	
	retval = register_dev_id(simple_major,simple_minor,simple_num);
	if( ret)
		printk(KERN_WARNING"%s\n",__func__);
}

static void __exit fun_exit(){
	int retval;
	retval = unregister_chrdev_region(dev,1); 
	if(retval)
		printk(KERN_WARNNING "unregister_chrdev_region failed\n");

	cdev_del(&mydev.cdev);
} 

module_init(fun_init);
module_exit(fun_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple is a driver for a partof memory in linux kernel\
					time: 2013-11-18");
