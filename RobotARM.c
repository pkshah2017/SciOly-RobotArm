#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     GrabEndpoint,   sensorTouch)
#pragma config(Motor,  motorA,          Mimic1,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          Mimic2,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          Grabber,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Arm1,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Arm2,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Base,          tmotorTetrix, openLoop)

#include "JoystickDriver.c"
#include "drivers/hitechnic-sensormux.h"

int Arm1MimicValue;
int Arm2MimicValue;
bool lastGrabberStatus;
bool grabberStatus;

task main()
{
	nNoMessageCounterLimit = 150;
	int y1Val,y2Val;

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
	}
}

void getMimicValues()
{
	Arm1MimicValue = nMotorEncoder[Mimic1];
	Arm2MimicValue = nMotorEncoder[Mimic2];
	lastGrabberStatus = grabberStatus;
	grabberStatus = SensorValue[GrabEndpoint] == 1;
}
