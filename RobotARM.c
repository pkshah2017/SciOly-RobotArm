#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          Rotate,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          Claw,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          Flipper,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Arm1,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Arm2,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     Base,          tmotorTetrix, openLoop)

#include "JoystickDriver.c"
#include "drivers/hitechnic-sensormux.h"

task main()
{
	nNoMessageCounterLimit = 150;
	int y1Val,y2Val;
	int tophatjoy1 = joystick.joy1_TopHat;
	int tophatjoy2 = joystick.joy2_TopHat;
	nMotorEncoder[Claw] = 0;
	nMotorEncoder[Rotate] = 0;
	nMotorEncoderTarget[Rotate] = 720;
	motor[Rotate] = 30;
	wait10Msec(100);
	while (true)
	{
		getJoystickSettings(joystick);

		y1Val = joystick.joy1_y1;
		y2Val = joystick.joy1_y2;

		if(abs(y1Val)> 10)
		{
			if(y1Val > 10)
				motor[Arm1]=(y1Val/10);
			if(y1Val <-10)
				motor[Arm1]=(y1Val/10);
		}
		else
		{
			motor[Arm1]=0;
		}

		if(abs(y2Val)> 10)
		{
			if(y2Val > 10)
				motor[Arm2]=-(y2Val/10);
			if(y2Val <-10)
				motor[Arm2]=-(y2Val/10);
		}
		else
		{
			motor[Arm2]=0;
		}

		if(joy1Btn(7))
		{
			motor[Base] = 5;
		}
		else if(joy1Btn(8))
		{
			motor[Base] = -5;
		}
		else
		{
			motor[Base] = 0;
		}

		if(joy1Btn(4))
		{
			nMotorEncoderTarget[Claw] = 60;
			motor[Claw] = 30;
			wait10Msec(100);
		}
		else if(joy1Btn(2))
		{
			nMotorEncoderTarget[Claw] = -60;
			motor[Claw] = -30;
			wait10Msec(100);
		}
		else
		{
			motor[Claw] = 0;
		}

		if(joy1Btn(6))
		{
			motor[Rotate] = 30;
		}
		else if(joy1Btn(5))
		{
			motor[Rotate] = -30;
		}
		else
		{
			motor[Rotate] = 0;
		}

		if(joy1Btn(1))
		{
			motor[Flipper] = 60;
		}
		else if(joy1Btn(3))
		{
			motor[Flipper] = -60;
		}
		else
		{
			motor[Flipper] = 0;
		}
	}
}
