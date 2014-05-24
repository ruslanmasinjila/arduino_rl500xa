   
  
    /*************************************************************************************************************************
    Author: Ruslan Masinjila
    
    The following code converts the RC signal to corresponding PWM value on the scale from 0-254
    Use values recorded by pulseReader to set the FORWARD_MAX, FORWARD_MIN, REVERSE_MAX and REVERSE_MIN
    WARNING: The code assumes that the RC transmitter is always ON
    **************************************************************************************************************************/
    
    
    //Connect the Signal Pin from an RC receiver to Digital Pin 52 of the Arduino Mega
    #define RC_PIN 52
    
    //*****************REPLACE THESE VALUES WITH YOUR OWN*********************
    #define FORWARD_MAX 1800
    #define FORWARD_MIN 1500
    #define REVERSE_MAX 1000
    #define REVERSE_MIN 1300
    #define PWM_MIN 0
    #define PWM_MAX 254
    
    
    //Holds the pulse width in microseconds
    int pulseWidth=0;
    int pwmValue=0;
    int direction=0;    //0=STOP, 1=FORWARD, -1=REVERSE
    
    void setup() 
    
    {
 
    pinMode(RC_PIN, INPUT);
  
    Serial.begin(9600);
   
    }
  

  
  void loop() 
  
  {
      readPulse();
      rcToPWM();
  
  }
  
  void readPulse()
  {
    
    //Read the HIGH pulse from the receiver
    pulseWidth = pulseIn(RC_PIN, HIGH);
    
    //Print the Value to Serial Output (Screen)
    Serial.print("Pulse Width: "+String(pulseWidth)+" ");
    
  }
  
  void rcToPWM()
  {
    //If moving Forward
    if(pulseWidth>FORWARD_MIN)
    {

      //Set anything higher than FORWARD_MAX to FORWARD_MAX
      if(pulseWidth>FORWARD_MAX)
      {
       pulseWidth=FORWARD_MAX; 
      }
      
      //Map the RC to PWM using the arduino map() function
      pwmValue=map(pulseWidth, FORWARD_MIN , FORWARD_MAX, PWM_MIN, PWM_MAX);
      direction=1;
      
    }
    
    //If moving in reverse
    else if(pulseWidth<REVERSE_MIN)
    {

      //Set anything lower than REVERSE_MAX to REVERSE_MAX
      if(pulseWidth<REVERSE_MAX)
      {
       pulseWidth=REVERSE_MAX; 
      }
      
      pwmValue=map(pulseWidth, REVERSE_MIN, REVERSE_MAX, PWM_MIN, PWM_MAX);
      direction=-1;
      
    }
    
    
    //Set PWM to ZERO for all remaining RC widths
    else
    {
     pwmValue=0; 
     direction=0;
    }
    
    Serial.print("PWM Value: "+String(pwmValue)+" DIRECTION: ");
    
    
    if(direction==0)
    {
     Serial.println("STOPPED"); 
    }
    else if(direction==-1)
    {
      Serial.println("REVERSE");
    }
    else
    {
     Serial.println("FORWARD"); 
    }
    
    
    
    
    
  }
  

