/*
Author : Ahmad Bakri
 This code moves the servos to the positions that were sent from the PC using python code
 HPV6
*/

//define Yaw and Pitch servo IDs
#define YAW_ser    1
#define PITCH_ser   2
#define ROLL_ser   3

//Include necessary Libraries to drive the DYNAMIXEL servos  
#include <ax12.h>
#include <BioloidController.h>

int Yaw = 512 ;    //wanted position of the Yaw servo
int Pitch = 512 ;   //wanted position of the Pitch servo  
int Roll = 512;    //wanted position of the roll servo
int tempYaw;  //current position of the Yaw servo
int tempPitch ; //current position of the Pitch servo 
int Recievedata;
char buff ;
bool valid = false;
bool execute = false;

void setup()
{
  pinMode(0,OUTPUT);     // setup user LED
  digitalWrite(0, HIGH); // turn user LED on to show the program is running
  Serial.begin(115200);
}

void loop()
{
  
  RecData ();
  if (execute)
  {
    SetServo (Recievedata);
  }
}

//This function receives the data from the PC   
void RecData ()
{
  bool done = false;
  while (!done)
  {
    if (Serial.available() > 0)
    {
      buff = Serial.read();
      //Starting from the header of the message
      if (buff == '$')
      {
         valid = true;
         execute = false;
         Recievedata = 0;
      }
      //getting the actual message
      if (valid)
      {
         if (buff != '!')
         {
           if (buff != '$')
           {
             Recievedata*=10;
             Recievedata+=(int(buff)-int('0'));
             delay(1);
           }
         }
         //The end of message
         if (buff == '!')
         {
           execute = true;
           done = true;
           valid = false;
           return;
         }
       }
    }
  }
}  

//This function is for processing the message and seperating it to Yaw , pitch , Roll
void SetServo (int Recievedata)
{
   int upper_byte;
   int lower_byte;
   int Ser = Recievedata / 1000;              //first bit is the wanted axis
   int Position = Recievedata % 1000;    //The last three bits is the position of the servos
   int Real_Position;
   switch (Ser)
   {
   //Yaw
   case 1:
     SetPosition(YAW_ser,Position);
     break;
   //Pitch
   case 2:
     SetPosition(PITCH_ser,Position);
     break;
   //Roll
   case 3:
     SetPosition(ROLL_ser,Position);
     break;
   //Check current position
   case 9:
     int Ser_id = Position/100;
     Real_Position = ax12GetRegister(Ser_id,36,2);
     upper_byte = Real_Position/256;
     lower_byte = Real_Position%256;
     Serial.write(upper_byte);
     Serial.write(lower_byte);
     break;
   }
   return;
}

