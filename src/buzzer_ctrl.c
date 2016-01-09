/*Smartkey Locker, a ARM2440 based key-lock simulate program.
 *Copyright (C) 2016 by THE KEY team
 *
 *buzzer_ctrl.c 
 *buzzer_ctrl: the Buzzer control module for Smartkey Lock, to control the frequency of buzzer.
 *
 *This program is under developing and only work on ARM2440 Development Board
 *This is a test project
 */






#include "buzzer_ctrl.h"

#define PWM_IOCTL_SET_FREQ		1
#define PWM_IOCTL_STOP			0
static int fd = -1;

static void open_buzzer(void);
static void close_buzzer(void);
static void set_buzzer_freq(int freq);
static void stop_buzzer(void);



/* External Function */

extern void  buzzer_incorrectAlert(int count)
{
	int i=0;
	int h_freq=1;
	open_buzzer();
	for(i=0;i<=count*2;i++)
	{
		if(h_freq==1)	//µÎ
		{
			set_buzzer_freq(2500);
			delayms(500);
			h_freq=0;
		}
		else if(h_freq==0)	//à½
		{
			set_buzzer_freq(2000);
			delayms(500);
			h_freq=1;
		}
	}
	stop_buzzer();
}

extern void buzzer_correctAlert()
{
	int ba=0;
	for(ba=0;ba<=2;ba++)
	{
		open_buzzer();
		set_buzzer_freq(2500);
		delayms(150);
		close_buzzer();
		delayms(30);
	}

	delayms(150);
	open_buzzer();
	set_buzzer_freq(2500);
	delayms(100);
	close_buzzer();
	delayms(100);
}

extern void delayms(int z)
{
	int aa,ab;
	for(aa=0;aa<=z;aa++)
		for(ab=0;ab<=20000;ab++);
}

/* External Function End */


/* Internal(Static) Function */
static void open_buzzer(void)
{
	fd = open("/dev/pwm", 0);
	if (fd < 0) {
		perror("open pwm_buzzer device");
		exit(1);
	}

	// any function exit call will stop the buzzer
	atexit(close_buzzer);
}

static void close_buzzer(void)
{
	if (fd >= 0) {
		ioctl(fd, PWM_IOCTL_STOP);
		close(fd);
		fd = -1;
	}
}

static void set_buzzer_freq(int freq)
{
	// this IOCTL command is the key to set frequency
	int ret = ioctl(fd, PWM_IOCTL_SET_FREQ, freq);
	if(ret < 0) {
		perror("set the frequency of the buzzer");
		exit(1);
	}
}
static void stop_buzzer(void)
{
	int ret = ioctl(fd, PWM_IOCTL_STOP);
	if(ret < 0) {
		perror("stop the buzzer");
		exit(1);
	}
}



		
	
	

/*int main(int argc, char **argv)
{
	buzzer_correctAlert();
	delayms(1000);
	//buzzer_incorrectAlert(10);
	int freq = 1000 ;
	
	open_buzzer();
	
	while( 1 )
	{
		set_buzzer_freq(freq);
		stop_buzzer();
		exit(0);
	}
}*/
