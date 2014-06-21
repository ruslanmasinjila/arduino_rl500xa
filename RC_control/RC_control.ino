/*******************************************************************************************
Author: Ruslan Masinjila

This arduino code is used to control the RL-500-XA robotic platform remotely. 
For more information, visit this link <https://sites.google.com/site/ruslanmasinjila/rl_500_xa>

The code does the following:
1. Read RC signals from the receiver and coverts them to corresponding PWM values.
2. Drives the motors of the wheels using the PWM values.
********************************************************************************************/

//VERSION 3 
//General RC Properties**********************************************************************
int SIGNAL_THRESHOLD=900;             //Channel 2 RC Signal. Signal considered lost below 900
int RC_CONNECTION_STATUS=1;           //0 if signal is lost, 1 if there is connection     


//**********Channel 2 Properties [Y Axis Right Stick: Up=Forward | Down=Reverse]*************
int FORWARD_MIN=1500;                
int FORWARD_MAX=1800;              

int REVERSE_MIN=1300;                
int REVERSE_MAX=1000;   


int CH2_PIN=52;                       //Input Pin. Reads Pulses from channel 2 of RC receiver

int CH4_PIN=53;                       //Input Pin. Reads Pulses from channel  of RC receiver


int ch2_rc;                          //Holds the duration, in microseconds, of the pulse from channel 2 when the signal is HIGH
//Forward: ch2_rc>=1500. Set any value>=1800 to 1800
//Reverse: ch2_rc<=1300. Set any value<=1000 to 1000
//Stop: All remaining ch2_rc values

//**********Channel 4 Properties [X Axis left Stick: left=left | right=right]****************       
int LEFT_MIN=1700;                
int LEFT_MAX=1900;              

int RIGHT_MIN=1500;                
int RIGHT_MAX=1300;   

int ch4_rc;                          //Holds the duration, in microseconds, of the pulse from channel 3 when the signal is HIGH
//Left: ch4_rc>=1700. Set any value>=1900 to 1900
//Right: ch4_rc<=1500. Set any value<=1300 to 1300
//Straight: All remaining ch4_rc values   







//******************Forward/Reverse PWM Properties*******************************************
int fr_pwm=0;                        //Holds the PWM value for forward and reverse
int lr_pwm=0;                        //Holds the PWM value for left and right
int PWM_MIN=0;                       //Minimum Speed
int PWM_MAX=254;                     //Maximum Speed



//*****************Available PWM PINS on MegaMoto: 3,5,6,9,10,11****************************
//Pin 5 drives the LEFT MOTOR in the REVERSE DIRECTION
//Pin 6 drives the LEFT MOTOR in the FORWARD DIRECTION
//Pin 9 drives the RIGHT MOTOR in the FORWARD DIRECTION
//Pin 10 drives the RIGHT MOTOR in the REVERSE DIRECTION
int LEFT_MOTOR_FOWARD_PIN=6;
int LEFT_MOTOR_REVERSE_PIN=5;
int RIGHT_MOTOR_FOWARD_PIN=9;
int RIGHT_MOTOR_REVERSE_PIN=10;


//****************Available ENABLE_PIN Pins on MegaMoto: 8,12,13 and 5V(Always On)**********
//Shields are enabled by HIGH signal on Pin 8, disabled by LOW signal
//Set jumpers on all Shields at D8
int ENABLE_PIN=8;





//******************************************************************************************
int singleChar;
String inputCommand="";          


//Holds the yAxisDirection direction of the motors (Forward='f', Reverse='r')
//Helps in stopping the motors smoothly
char yAxisDirection='\0';
char xAxisDirection='\0';


void setup() {

  pinMode(CH2_PIN, INPUT);
  pinMode(CH4_PIN, INPUT);

  pinMode(ENABLE_PIN,OUTPUT); 
  digitalWrite(ENABLE_PIN,HIGH); 
  Serial.begin(9600);

}

void loop() {

  rcToPWM();

}


