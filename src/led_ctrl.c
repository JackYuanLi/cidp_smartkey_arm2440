/*Smartkey Locker, a ARM2440 based key-lock simulate program.
 *Copyright (C) 2016 by THE KEY team
 *
 *led_ctrl.c 
 *led_ctrl: the LED control module for Smartkey Lock.
 *
 *This program is under developing and only work on ARM2440 Development Board
 *This is a test project
 */






#include "led_ctrl.h"

static void delayms(int z);
static void blink_slow(int led_n2,int count2);
static void blink_fast(int led_n1,int count1);


/* 
 * External function 
 */
 
extern void led_Indicate_correct(void)
{
	dim_all();
	blink_fast(1,5);
}

extern void led_indicate_incorrect(void)
{
	dim_all();
	blink_slow(1,5);	
}

extern int dim_all(void)
{
	led_ctrl(0,0);
	led_ctrl(1,0);
	led_ctrl(2,0);
	led_ctrl(3,0);
}

/* 
 * External function end 
 */




#ifdef LED_Demo
int main(void)
{
	dim_all();
	blink_fast(0,5);
	blink_slow(0,10);
}
#endif
	
/* Internal static function */
static void blink_slow(int led_n1,int count1)
{
	while(count1--)
	{
		led_ctrl(led_n1,0);
		delayms(5000);
		led_ctrl(led_n1,1);
		delayms(5000);
	}
}

static void blink_fast(int led_n2,int count2)
{
	int co2=0;
	for(co2=0;co2<=count2;co2++)
	{
		led_ctrl(led_n2,0);
		delayms(2000);
		led_ctrl(led_n2,1);
		delayms(2000);
	}
}


static void delayms(int z)
{
	int i,j;
	for(i=0;i<=z;i++)
		for(j=0;j<=10000;j++);
}

int led_ctrl(int led_number,int led_flag)
{
	int on;
	int led_no;
	int fd;	

	led_no=led_number;
	on=led_flag;

	if(led_no<0 || led_no>3 || on<0 || on>1)
	{
		fprintf(stderr,"Usage:leds led_no 0|1\n");
		exit(1);
	}
	
	fd=open("/dev/leds0",0);
	if(fd<0)
	{
		fd=open("/dev/leds",0);
	}
	if(fd<0)
	{
		perror("Open LED device failed");
		exit(1);
	}
	
	ioctl(fd,on,led_no);
	close(fd);
	return(0);
}
