   
  
    /*************************************************************************************************************************
    Author: Ruslan Masinjila
    
    The following code measures the width, in microseconds, of a HIGH RC pulse and displays the value on the screen
    Use this code to record the followings RC pulse widths:
         1. When a control stick is in the middle (Middle Value)
         2. When the control stick is all the way forward (Max. Forward Value)
         3. When the control stick is all the way back (Max. Reverse Value) 
    Repeat this process for all channels
    After recording these values, proceed with conversion of RC to PWM  (rcToPWM.ino)
    **************************************************************************************************************************/
    
    
    //Connect the Signal Pin from an RC receiver to Digital Pin 52 of the Arduino Mega
    #define RC_PIN 52
    
    //Holds the pulse width in microseconds
    int pulseWidth=0;
    
    void setup() 
    
    {
 
    pinMode(RC_PIN, INPUT);
  
    Serial.begin(9600);
   
    }
  

  
  void loop() 
  
  {
    
    //Read the HIGH pulse from the receiver
    pulseWidth = pulseIn(RC_PIN, HIGH);
    
    //Print the Value to Serial Output (Screen)
    Serial.println("Pulse Width: "+String(pulseWidth));
    
    
    
    //RECORD VALUES FOR ALL THREE POSITIONS OF THE CONTROL STICK
    
    
    

  
  }
  

