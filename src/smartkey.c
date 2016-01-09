/* 
 *Smartkey Locker, a ARM2440 based key-lock simulate program.
 *Copyright (C) 2016 by THE KEY team
 *
 *
 *This program is under developing and only work on ARM2440 Development Board
 *This is a test project
 */


#include <stdio.h>
#include "buzzer_ctrl.h"
#include "led_ctrl.h"




extern void delayms(int z);

extern void buzzer_incorrectAlert(int count);
extern void buzzer_correctAlert();


/* Define all variable */
char passwd[50]="paul";
char input_passwd[50];




static int password_check(unsigned char *cur_passwd,unsigned char *corr_passwd)
{
	int flag;
	if(strcmp(input_passwd,passwd)==0)
	{
		flag=1;
	}
	else
	{
		flag=0;
	}
	
	return flag;
}

/*main function*/
int main(void)
{
	int incorrect_count=0;
	int password_correct=0;

	
	//passwd="paul";
	

	Input_password:	
	printf("Welcome, Please input your password\n");
	gets(input_passwd);

	password_correct=password_check(input_passwd,passwd);

	if(password_correct)
	{
		printf("Welcome!\n");
		led_Indicate_correct();
		buzzer_correctAlert();
		incorrect_count=0;
	}
	
	else
	{
		printf("Password incorrect, Please try again\n");
		incorrect_count++;
		buzzer_incorrectAlert(3);
		if(incorrect_count<3)
		{
			goto Input_password;
		}
		else
		{
			printf("You have input incorrect password for 3 times. The keyboard will remain lock.\n");
			led_indicate_incorrect();//LED2 blink more slower for 5 times.
			//function for keyboard lock-down
			goto Input_password;
		}
	}
}



