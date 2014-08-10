#ifndef __SCULL_H
#define __SCULL_H

#define SCULL_MAJOR 0
#define SCULL_MINOR 0
#define SCULL_NUM 	1
#define SCULL_NAME "sculldev"
//my device struct
struct scull_dev{
	struct scull_qset *data ;//first quant set
	int quantum; //size of quant
	int qset;	//size of arry
	unsigned long size; //all data
	unsigned int access_key;
	struct semaphore sem;
	struct cdev cdev;
}
struct scull_qset{
	void **data;
	struct scull_qset *next;
}


// ioctl commands definition
#define SCULL_IOC_MAGIC 'k'
#define SCULL_IOCRESET _IO(SCULL_IOC_MAGIC,0)
#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC,1,int)
#define SCULL_IOCSQSET _IOW(SCULL_IOC_MAGIC,2,int)
#define SCULL_IOCHQSET _IO(SCULL_IOC_MAGIC,12)
#endif
