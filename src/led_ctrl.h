#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>



extern int dim_all(void);
extern void led_Indicate_correct(void);
extern void led_indicate_incorrect(void);


int led_ctrl(int led_no,int led_flag);
