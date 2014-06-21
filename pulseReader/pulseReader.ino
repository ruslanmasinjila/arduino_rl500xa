   
  
    /*************************************************************************************************************************
    Author: Ruslan Masinjila
    
    The following code measures the width, in microseconds, of a HIGH RC pulse and displays the value on the screen
    Use this code to record the followings RC pulse widths:
         1. When the control stick of Channel 2 is in the middle (STOP)
         2. When the control stick of Channel 2 is all the way forward (FORWARD_MAX)
         3. When the control stick of Channel 2 is all the way back (REVERSE_MAX) 
         4. When the control stick of Channel 4 is in the middle (STRAIGHT)
         5. When the control stick of Channel 4 is all the way left (LEFT_MAX)
         6. When the control stick of Channel 4 is all the way right (RIGHT_MAX)

    After recording these values, change the following values in RC_control.ino
    int FORWARD_MIN=<???>;                
    int FORWARD_MAX=<???>;              
    int REVERSE_MIN=<???>;                
    int REVERSE_MAX=<???>;  
    
    int LEFT_MIN=<???>;                
    int LEFT_MAX=<???>;              
    int RIGHT_MIN=<???>;                
    int RIGHT_MAX=<???>; 
    
    For more information, visit this link <https://sites.google.com/site/ruslanmasinjila/rl_500_xa#pulseReader>
    **************************************************************************************************************************/
    
    
    //Connect the Signal Pin from an RC receiver to Digital Pin 52 of the Arduino Mega
    #define CH2_PIN 52
    #define CH4_PIN 53
    
    //Holds the pulse width in microseconds
    int pulseWidthCH2=0;
    int pulseWidthCH4=0;
    
    void setup() 
    
    {
 
    pinMode(CH2_PIN, INPUT);
    pinMode(CH4_PIN, INPUT);
  
    Serial.begin(9600);
   
    }
  

  
  void loop() 
  
  {
    
    //Read the HIGH pulse from the receiver
    pulseWidthCH2 = pulseIn(CH2_PIN, HIGH);
    pulseWidthCH4 = pulseIn(CH4_PIN, HIGH);
    
    //Print the Value to Serial Output (Screen)
    Serial.println("Pulse Width CH2: "+String(pulseWidthCH2));   
    Serial.println("Pulse Width CH4: "+String(pulseWidthCH4));  
    delay(1000); 
    
    //RECORD VALUES FOR ALL THREE POSITIONS OF THE CONTROL STICKS (FORWARD/REVERSE + LEFT/RIGHT)
     
  }
  

