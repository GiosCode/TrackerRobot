#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
//Global variables 
//int counterold = 0;
//int counter =  0;
//int semaphore = 0;
//int semaphore2 = 0;
//int semaphore3 = 0;
int flag = 0;
clock_t timeM = 0;
int currentPos = 150;

int leftActive = 0;
int rightActive = 0;

//Defines
#define CSENSOR 27 //Physical pin 36, wiringpi 27  CENTER
#define LSENSOR 21 //Physical pin 29, wiringpi 21 LEFT
#define RSENSOR 25 //Physical pin 37, wiringpi 25 RIGHT

#define SERVO   23 //wiringPI pin 23, physical pin 33

#define LEFT 89
#define RIGHT 73
#define CENTER 81

//Function declarations
//int scan(char sensor);//Depending on the "sensor" number it will activate that sensor 
//void move(char direction);//Will move to the desired location
int calculate(int movement);
void setUp(void);
int leftSensor();
int rightSensor();
int centerSensor();
//Driver
int main(void){
	//Setup IO
	setUp();
	//END Setup
	long measurements[20];
	int active1 = 0;
	int active2 = 0;
	int active3 = 0;
	int test = 0;
	int test2 = 0;
	//Infinite while loop that will constantly be checking the sensors, getting data, and then moving the servo accordingly
	while(1){
	delay(5);
		//clock_t timeM = clock();//Used for performance metrics
		// Get 1 or 0 from sensor
		active1 = leftSensor();
		//active2 = centerSensor();
		active3 = rightSensor();
		//active2 = centerSensor();
		// Run servo on triggered sensor
		calculate(active1);
//		delay(500);
		//calculate(active2);
		calculate(active3);
		//calculate(active2);



		if(centerSensor() == 2 && flag == 1){//test!=0||test2!=0
			double timeL = ((double)timeM) / CLOCKS_PER_SEC;
			printf("Loop time: %.11f\n", timeL);
			flag = 0;
			leftActive = 0;
			rightActive = 0;
			timeM = 0;
		}
		//timeM = 0;
	}

	printf("ERROR EXIT INFINITE LOOP");
	return 0;
}
void setUp(void){
	printf("Beginning setup\n");
	//Setup function call that wiringPi library needs
	wiringPiSetup();
	//Sensor setup
	printf("Setting up Sensors as outputs\n");
	pinMode(CSENSOR, INPUT);
	pinMode(LSENSOR, INPUT);
	pinMode(RSENSOR, INPUT);
	//Servo setup
	printf("Setting up Servo as outpus\n");
	pinMode(SERVO, PWM_OUTPUT);
	pwmSetMode (PWM_MODE_MS);
   	pwmSetRange (2000);
  	pwmSetClock (192);
	printf("Setup Complete\n");
	return;
}
int leftSensor(){
	if(digitalRead(LSENSOR) == LOW)
	{
		if(leftActive == 0){
			timeM = clock();
		}
		else {leftActive = 1;}
		//currentPos = currentPos + 1;
		return 1;
	}
	else return 0;
}
int centerSensor(){
	if(digitalRead(CSENSOR) == LOW){
	timeM = clock() - timeM;
	return 2;}
	else return 0;
}
int rightSensor(){
	if(digitalRead(RSENSOR) ==  LOW)
	{
		if(rightActive == 0){
			timeM = clock();
		}
		else {rightActive = 1;}
		return 3;
	}
	else return 0;
}
int calculate(int  movement){
	//Does the actual moving
	if(movement == 1 && digitalRead(CSENSOR) == HIGH){//LEFT
		if (currentPos == 50){
			currentPos = 50;
		}
		else{
			currentPos = currentPos - 1;
		}
		pwmWrite(SERVO,currentPos);//50
//		timeM = clock() - timeM;
		printf("\ncurrentPosition LEFT is %d",currentPos);
		flag = 1;
		return 1;
	}
	//else if(movement == 2){//CENTER
		//pwmWrite(SERVO,150);
		//counter++;
	//	timeM = clock() - timeM;
	//	return 1;
	//}
	else if(movement == 3 && digitalRead(CSENSOR) == HIGH){//RIGHT
		if (currentPos == 250){
			currentPos = 250;
		}
		else{
			currentPos = currentPos + 1;
		}
		pwmWrite(SERVO,currentPos);//250
//		timeM = clock() - timeM;
		printf("\ncurrentPosition RIGHT is %d",currentPos);
		flag = 1;
		return 1;
	}
	else return 0;
}
