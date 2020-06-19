  #include <Stepper.h>

//----------------------------------Motor Pins---------------------------------------------// 
#define in1 4 //Motor 1
#define in2 5
#define in3 6 //Motor 2
#define in4 7
#define in5 8 //Motor 3
#define in6 9
#define in7 10 //Motor 4
#define in8 11

//int i;
int M1,M2,M3,M4;

//------------------------------------Instances for stepper motor------------------------------//

const int STEPS_PER_REV = 150;
Stepper stepper_NEMA17_2(STEPS_PER_REV, 30, 32, 34, 36); //forward m2
Stepper stepper_NEMA17_2_b(STEPS_PER_REV, 32, 30, 36, 34); //backword m2
Stepper stepper_NEMA17_1(STEPS_PER_REV, 22, 24, 26, 28); //forward m1
Stepper stepper_NEMA17_1_b(STEPS_PER_REV, 24, 22, 28, 26); //backward m2

//-------------------------Water Pump-------------------------------------//
const int S = 12; 

//------------------Serial receive----------------------//
String incomingByte = " ";
int i =0;
 
void setup() 
{
//-----------------------Motor Movement setup--------------//

//------------------------Set the pins for output---------------------------//
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(in5, OUTPUT);
pinMode(in6, OUTPUT);
pinMode(in7, OUTPUT);
pinMode(in8, OUTPUT);

pinMode(3,OUTPUT);
pinMode(2,OUTPUT);

//-----------------------set the pins low - this will keep the motor from moving-------------------------------//
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
digitalWrite(in5, LOW);
digitalWrite(in6, LOW);
digitalWrite(in7, LOW);
digitalWrite(in8, LOW);

digitalWrite(3, HIGH);
digitalWrite(2, LOW);
 
//----------------------------Serial Communication---------------------------//
Serial.begin(9600);
Serial2.begin(9600);

//-------------------------Water Pump-------------------------------------//
pinMode(S, OUTPUT);
pinMode(13,OUTPUT);

}

void loop() 
{
     
  while(Serial2.available())
  {
    //----------------------------------------receive the command---------------------------------------//
    incomingByte = Serial2.readString();
    Serial.println(incomingByte);
    Serial.println(incomingByte.length());
    //--------------------------------------------------------------------------------------------------//
   
    //-------------------------------------Blink the LED to acknowledge the command--------------------//
    digitalWrite(13,HIGH);
    delay(500);   
    digitalWrite(13,LOW);
    delay(500);
   //-------------------------------------------------------------------------------------------------//
  }  
   if (incomingByte.equals("Forward"))
    {
      Serial.println("Start Forward");
      //------------------------------------move forward-----------------------------//
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      digitalWrite(in5, HIGH);
      digitalWrite(in6, LOW);
      digitalWrite(in7, HIGH);
      digitalWrite(in8, LOW);
      
      //---------------------------------------------------------------------------//
      //-------------------------------Move plough and pour seeds---------------------------------//
      stepper_NEMA17_1.setSpeed(120);
      for( i =0; i <=10;i++)
      {
      stepper_NEMA17_1.step(STEPS_PER_REV);
      delay(1000);
      stepper_NEMA17_1.step(-STEPS_PER_REV);
      delay(1000); 
      stepper_NEMA17_2.setSpeed(120);
      stepper_NEMA17_2.step(STEPS_PER_REV);
      delay(1000);
      stepper_NEMA17_1.step(-STEPS_PER_REV);
     
      }// stepper_NEMA17_1_b.setSpeed(120);
     // stepper_NEMA17_1_b.step(STEPS_PER_REV);
      //---------------------------------------------------------------------------//
      
      //--------------------------pour the water------------------------------//
      delay(1000);
      digitalWrite(S, HIGH);
      delay(5000);
      digitalWrite(S, LOW);
      delay(5000);
      //----------------------------------------------------------------------//
      
      Serial.println("End Forward");
    }
    else if (incomingByte.equals("Back"))
    {
      Serial.println("Start Back");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      digitalWrite(in5, LOW);
      digitalWrite(in6, HIGH);
      digitalWrite(in7, LOW);
      digitalWrite(in8, HIGH);
      
      Serial.println("End Back");
      
    }
    else if (incomingByte.equals("Left"))
    {
      Serial.println("Start Left");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in5, HIGH);
      digitalWrite(in6, LOW);
      digitalWrite(in7, LOW);
      digitalWrite(in8, LOW);
      Serial.println("End Left");
      
    }
    else 
    if (incomingByte.equals("Right"))
    {
      Serial.println("Start Right");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      digitalWrite(in5, LOW);
      digitalWrite(in6, LOW);
      digitalWrite(in7, HIGH);
      digitalWrite(in8, LOW);
      Serial.println("End Right");    
    }
    else
        if (incomingByte.equals("Stop"))
    {
      Serial.println("Begin Stop");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      digitalWrite(in5, LOW);
      digitalWrite(in6, LOW);
      digitalWrite(in7, LOW);
      digitalWrite(in8, LOW);
      Serial.println("End Stop");
         
    }
 // }
  }
