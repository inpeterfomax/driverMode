#include<linux/fb.h>
#include<sys/mman.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<errno.h>

struct fb_var_screeninfo vinfo;

static void fb_update(int fbfd, struct fb_var_screeninfo *vi)
{
	vi->yoffset = 1;
	ioctl(fbfd, FBIOPUT_VSCREENINFO,vi);
	vi->yoffset = 0;
	ioctl(fbfd, FBIOPUT_VSCREENINFO,vi);
}

int main (int argc, char* argv[])
{
	int fbfd = 0;
	struct fb_var_screeninfo *vinfo;
	unsigned long screensize = 0;
	unsigned int *fbp = 0;
	int argb;
	int x = 0, y = 0;

	char file_name[50]={0};
	if (2 == argc)
		sprintf(file_name, "%s%d", "/dev/graphics/fb", atio(argv[1]));
	
	fbfd =  open(file_name, O_RDWR);
	if (!fbfd) {
		printf("Error: can not open framebuffer device.\n");
		exit(-1);	
	}

	printf("The framebuffer device was opened successfully.\n");

	if(ioctl(fbfd, FBIOGET_VSCREENINFO,&vinfo)) {
		printf ("Error reading variable information. \n");
		exit (1);
	}

	printf("%dx%d, %dbpp\n",vinfo.xres,vinfo.yres,vinfo.bits_per_pixel);
	if(vinfo.bits_per_pixel != 32) {
		printf ("Error: not supported bits_per_pixel, it only supports 32 bit color\n");
	}

	screensize = vinfo.xre * vinfo.yres * 4;

	fbp = mmap(0,screensize, PROT_READ | PORT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)fbp == -1) {
		printf("Error: failed tomap framebuffer device to memory.\n");
		exit(4);
	}

	printf("The framebuffer device was mapped to meory successfully.\n");

	for(y = 0; y < vinfo.yres; y++)
	{
		for (x = 0; x < vinfo.xres; x++)
		{
			argb = (0xff << 24) | (0x00 << 16) | (0x00 << 8) | 0xff;
			*(fbp + y * vinfo.xres +x) = argb;
		}

	}

	fb_update(fbfd, &vinfo);
	while (1);
	munmap (fbp, screensize);
	close(fbfd);

	return 0;
}
