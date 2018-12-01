#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
//Global variables 

//Defines
#define SENSOR1 27 //Physical pin 36, wiringpi 27  CENTER
#define SENSOR2 21 //Physical pin 29, wiringpi 21 LEFT
#define SENSOR3 25 //Physical pin 37, wiringpi 25 RIGHT

#define SERVO   23 //wiringPI pin 23, physical pin 33

#define LEFT 89
#define RIGHT 73
#define CENTER 81

//Function declarations
int scan(int sensor);//Depending on the "sensor" number it will activate that sensor 
void move(int direction);

//Driver
int main(void){

	printf("Beginning setup\n");
	//Setup function call that wiringPi library needs
	wiringPiSetup();
	//Sensor setup
	printf("Setting up Sensors as outputs\n");
	pinMode(SENSOR1, INPUT);
	pinMode(SENSOR2, INPUT);
	pinMode(SENSOR3, INPUT);
	//Servo setup
	printf("Setting up Servo as outpus\n");
	pinMode(SERVO, PWM_OUTPUT);
//pinMode(SERVO, OUTPUT);
	pwmSetMode (PWM_MODE_MS);
   	pwmSetRange (2000);
  	pwmSetClock (192);
	//digitalWrite(SERVO, LOW);
	printf("Setup Complete\n");

//	for(int i = 0; i < 100; i++){
//	move(CENTER);
//	}
//  int temp1;
  //int temp2;
  //int temp3;
	//Infinite while loop that will constantly be checking the sensors, getting data, and then moving the servo accordingly
	while(1){
	 // printf("Top of while 1\n");
    
   // temp1 = scan(SENSOR3);
   // temp2 = scan(SENSOR1);
   // temp3 = scan(SENSOR2);
   // printf("Center Sensor: %d",temp1);
   // printf("                                  Left Sensor: %d",temp2);
   // printf("                                                            Right Sensor: %d\n",temp3);
		if(digitalRead(SENSOR3) == LOW && digitalRead(SENSOR1) == 1 && digitalRead(SENSOR2)== 1){//RIGHT  Sensor
		printf("\nMoved Right");
		pwmWrite(SERVO,250);
		}

		else if(digitalRead(SENSOR1)==LOW && digitalRead(SENSOR3)==HIGH && digitalRead(SENSOR2)==HIGH){
		//printf("                       center  Sensor\n");
		pwmWrite(SERVO,150);
		printf("\n              Moved Center");
		}
		else if(digitalRead(SENSOR2)==LOW && digitalRead(SENSOR3)==HIGH && digitalRead(SENSOR1)==HIGH){
		//printf("                       left  Sensor\n");
		pwmWrite(SERVO,50);
		printf("\nMoved Left");
		}
		else {}
	}
	printf("ERROR EXIT INFINITE LOOP");
	return 0;
}
