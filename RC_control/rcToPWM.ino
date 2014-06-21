
//********************************************************************
//Converts RC Signals to PWM pulses which are used to diver the motors
//********************************************************************
void rcToPWM()
{
  if(RC_CONNECTION_STATUS==1)
  {

    forwardReversePWM();

    leftRightPWM();

    pwmSteering();

  }

}

void forwardReversePWM()
{


  ch2_rc = pulseIn(CH2_PIN, HIGH);

  //If the Motors are moving in the forward Direction
  if(ch2_rc>=FORWARD_MIN )
  {
    if(ch2_rc>=FORWARD_MAX)
    {
      ch2_rc=FORWARD_MAX; 
    }

    fr_pwm = map(ch2_rc, FORWARD_MIN , FORWARD_MAX, PWM_MIN, PWM_MAX);
    yAxisDirection='f';

  }

  //If the Motors are moving in the reverse Direction

  else if(ch2_rc>SIGNAL_THRESHOLD&&ch2_rc<=REVERSE_MIN)
  {
    if(ch2_rc<=REVERSE_MAX)
    {
      ch2_rc=REVERSE_MAX; 
    }
    fr_pwm = map(ch2_rc, REVERSE_MIN, REVERSE_MAX, PWM_MIN, PWM_MAX);
    yAxisDirection='b';

  }


  else
  {
    fr_pwm=0;
    stopDrivingMotors();

  }




}


void leftRightPWM()
{

  ch4_rc = pulseIn(CH4_PIN, HIGH);



  //If the Motors are moving in the left Direction
  if(ch4_rc>=LEFT_MIN )
  {
    if(ch4_rc>=LEFT_MAX)
    {
      ch4_rc=LEFT_MAX; 
    }

    lr_pwm = map(ch4_rc, LEFT_MIN , LEFT_MAX, PWM_MIN, PWM_MAX);
    xAxisDirection='l';

  }

  //If the Motors are moving in the reverse Direction
  //Must be strictly greater than SIGNAL_THRESHOLD (0)
  else if(ch4_rc<=RIGHT_MIN)
  {
    if(ch4_rc<=RIGHT_MAX)
    {
      ch4_rc=RIGHT_MAX; 
    }
    lr_pwm = map(ch4_rc, RIGHT_MIN, RIGHT_MAX, PWM_MIN, PWM_MAX);
    xAxisDirection='r';

  } 
  else
  {
     lr_pwm=0; 
  }
  

}

void pwmSteering()
{
  int pwm_difference=0;
  pwm_difference=pwmDifference(fr_pwm,lr_pwm);
  
  if(yAxisDirection=='f')
  {
    stopReverse();
    
  }
  
  if(yAxisDirection=='b')
  {
    stopFoward();
    
  }

  if(yAxisDirection=='f'&& xAxisDirection=='l')
  {  
    analogWrite(RIGHT_MOTOR_FOWARD_PIN,fr_pwm);
    analogWrite(LEFT_MOTOR_FOWARD_PIN,pwm_difference);
  }

  if(yAxisDirection=='f'&& xAxisDirection=='r')
  {
    analogWrite(LEFT_MOTOR_FOWARD_PIN,fr_pwm);
    analogWrite(RIGHT_MOTOR_FOWARD_PIN,pwm_difference);

  }

  if(yAxisDirection=='b'&& xAxisDirection=='l')
  {
    analogWrite(RIGHT_MOTOR_REVERSE_PIN,fr_pwm);
    analogWrite(LEFT_MOTOR_REVERSE_PIN,pwm_difference);

  }


  if (yAxisDirection=='b'&& xAxisDirection=='r')
  {
    analogWrite(LEFT_MOTOR_REVERSE_PIN,fr_pwm);
    analogWrite(RIGHT_MOTOR_REVERSE_PIN,pwm_difference);
  }

  if(yAxisDirection=='f'&& xAxisDirection=='\0')
  {
    analogWrite(RIGHT_MOTOR_FOWARD_PIN,fr_pwm);
    analogWrite(LEFT_MOTOR_FOWARD_PIN,fr_pwm);

  }


  if (yAxisDirection=='b'&& xAxisDirection=='\0')
  {
    analogWrite(RIGHT_MOTOR_REVERSE_PIN,fr_pwm); 
    analogWrite(LEFT_MOTOR_REVERSE_PIN,fr_pwm);
  }
  
  xAxisDirection='\0';
  
}

int pwmDifference(int fr_pwm, int lr_pwm)
{

  int difference=fr_pwm-lr_pwm;

  if(difference<=0)
  {
    difference=0;
  }
  return difference; 

}


//Stops the driving Motors (Left and Right Wheels) by sending 0 PWM to both Motors.
//First determines the yAxisDirection known direction of the motors, then Applies 0 PWM in that direction
void stopDrivingMotors()
{ 


  stopReverse();  
  stopFoward();
  


}

void stopReverse()
{
    analogWrite(RIGHT_MOTOR_REVERSE_PIN,0);
    analogWrite(LEFT_MOTOR_REVERSE_PIN,0);
  
}

void stopFoward()
{
     analogWrite(RIGHT_MOTOR_FOWARD_PIN,0);
     analogWrite(LEFT_MOTOR_FOWARD_PIN,0);
  
}



