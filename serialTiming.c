#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>
//Global variables 
int counterold = 0;
int counter = 0;
//Defines
#define CSENSOR 27 //Physical pin 36, wiringpi 27  CENTER
#define LSENSOR 21 //Physical pin 29, wiringpi 21 LEFT
#define RSENSOR 25 //Physical pin 37, wiringpi 25 RIGHT

#define SERVO   23 //wiringPI pin 23, physical pin 33

#define LEFT 89
#define RIGHT 73
#define CENTER 81

//Function declarations
int scan(char sensor);//Depending on the "sensor" number it will activate that sensor 
void move(char direction);//Will move to the desired location
int setUp(void);
//Driver
int main(void){
	//Setup IO
	setUp();
	//END Setup
	long measurements[20];
	int active1 = 0;
	int active2 = 0;
	int active3 = 0;
	//Infinite while loop that will constantly be checking the sensors, getting data, and then moving the servo accordingly
	while(1){
		clock_t timeM = clock();//Used for performance metrics
		active1 = leftSensor();
		active2 = centerSensor();
		active3 = rightSensor();
		calculate(active1);
		calculate(active2);
		calculate(active3);
		timeM = clock() - timeM;
		double timetaken = ((double)timeM)/CLOCKS_PER_SEC;
   	 	printf("TOOK TIME: %f",timetaken);
		if(counter < 20){
			measurements[counter] = timetaken;
			//counterold = counter;
		}
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
uint_t leftSensor(){
	if(digitalRead(LSENSOR) == LOW){
		counter++;
		return 1;
	}
	else return 0;
}
uint_t centerSensor(){
	if(digitalRead(CSENSOR) == LOW){
		counter++;
		return 2;
	}
	else return 0;
}
uint_t rightSensor(){
	if(digitalRead(RSENSOR) ==  LOW){
		counter++;
		return 3;
	}
	else return 0;
}
int calculate(uint_t movement){
	//Does the actual moving
	if(movement == 1){//LEFT
		pwmWrite(SERVO,50);
		return 1;
	}
	else if(movement == 2){//CENTER
		pwmWrite(SERVO,150);
		return 1;
	}
	else if(movement == 3){//RIGHT
		pwmWrite(SERVO,250);
		return 1;
	}
	else return 0;
}

/* if(digitalRead(RSENSOR) == LOW && digitalRead(CSENSOR) == 1 && digitalRead(LSENSOR)== 1){
		//printf("\nMoved Right");
		pwmWrite(SERVO,250);
		}

		else if(digitalRead(CSENSOR)==LOW && digitalRead(RSENSOR)==HIGH && digitalRead(LSENSOR)==HIGH){
		pwmWrite(SERVO,150);
		//printf("\n              Moved Center");
		}
		else if(digitalRead(LSENSOR)==LOW && digitalRead(RSENSOR)==HIGH && digitalRead(CSENSOR)==HIGH){
		pwmWrite(SERVO,50);
		//printf("\nMoved Left");
		}
		else {} */