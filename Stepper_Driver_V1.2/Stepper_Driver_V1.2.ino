// Stepper motor driver by Serial Terminal
//
// Send an INTEGER value through Serial Terminal
// to the arduino to parse and execute a number of
// steps.
//
// 2/25/2020
// V1.2
 
 
//We want:
// - Directional control
// - A "sine" movement
// - "Absolute" step control/location
 
bool activation = false;
 
#define STEP_PIN     2 //by pulse
#define DIR_PIN      3
#define SLEEP_PIN    4
#define ENABLE_PIN   5
 
#define S_MODE_M0_PIN 6
#define S_MODE_M1_PIN 7
 
#define STEP_DELAY 50 //Used in step function. Change as needed
static int step_delay = 50; //Used in step function. Change as needed
static bool step_direction = true; //Used for direction of stepper
 
 
typedef enum
{
  no_case, step, dir, sine, speed
} command_options;
 
 
 
void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(9600);
  Serial.println("Initialize the stepper");
 
  //Enable
  // LOW = ENABLE
  // HIGH = DISABLE (Bruh)
  //disable the stepper driver during initialization.
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);
  Serial.println("Enable done");
  //step mode
  //00 Full-step
  //01 1/2 step
  //10 8 microstep
  //11 16 microstep
  pinMode(S_MODE_M0_PIN, OUTPUT);
  pinMode(S_MODE_M1_PIN, OUTPUT);
 
  //Set to mode: FULL_STEP (0,0);
  digitalWrite(S_MODE_M0_PIN, LOW);
  digitalWrite(S_MODE_M1_PIN, LOW);
  //digitalWrite(S_MODE_M0_PIN, HIGH);
  //digitalWrite(S_MODE_M1_PIN, LOW);
 
  Serial.println("Step mode done");
 
 
  //Direction (Step Mode M0/M1)
  // Clockwise = HIGH
  // CCWise    = LOW
  //Set the stepper driver to clockwise rotation.
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, HIGH);
  Serial.println("Direction done");
 
  //Sleep (NSLEEP)
  // LOW = SLEEP
  //Bring stepper driver out of "sleep" state if present
  pinMode(SLEEP_PIN, OUTPUT);
  digitalWrite(SLEEP_PIN, LOW);
  Serial.println("Sleep done");
 
  //Step pulse by pulse
  //NULL
  //Initialize step pin.
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);
  Serial.println("Step done");
 
  //System is now initialized (hopefully)
 
  Serial.flush();
  activation = true;
}
 
void loop() {
  // put your main code here, to run repeatedly:
  static int stepNumber = 0;
  if (activation)
  {
    if (Serial.available() > 0)
    {
      String incomingData = Serial.readString();
 
      int index_of_firstDelim = incomingData.indexOf(',');
      String commandParam = incomingData.substring(0, index_of_firstDelim);
      commandParam.trim();
      Serial.println(commandParam);
 
 
 
 
 
      switch (castCommand(commandParam))
      {
        //{"step",13_int}
        case step:
        digitalWrite(SLEEP_PIN, HIGH);
        Serial.println("Sleeping");
          //commandParam = incomingData.substring(index_of_firstDelim + 1);
          //commandParam = command
          //commandParam.trim();
          //Serial.println(commandParam);
          stepNumber = (incomingData.substring(index_of_firstDelim + 1)).toInt();
          Serial.println(stepNumber);
          Serial.print("NUM of Steps requested: ");
          Serial.println(stepNumber);
          //should check if the incoming value is
          // ACTUALLY an integer of the correct type!
          stepSteps(stepNumber);
          digitalWrite(SLEEP_PIN, LOW);
          Serial.println("Not Sleeping");
          break;
          
 
        //{"dir","ccw"}
        case dir:
          typedef enum {ccw, cw} directions;
          commandParam = incomingData.substring(index_of_firstDelim + 1);
          Serial.println("Command Parameter: " + commandParam);
          commandParam.trim();
 
          //Direction (Step Mode M0/M1)
          // Clockwise = HIGH
          // CCWise    = LOW
          //bool direction_option = true; //true is CW
          if (commandParam.equalsIgnoreCase("ccw"))
          {
            digitalWrite(DIR_PIN, LOW);
            Serial.println("Direction: Counter Clock Wise");
          }
          else if (commandParam.equalsIgnoreCase("cw"))
          {
            digitalWrite(DIR_PIN, HIGH);
            Serial.println("Direction: Clock Wise");
          }
          else
          {
            Serial.println("ERROR: Unknown direction. Check spell/case/word?");
          }
 
          break;
 
        //{"sine","yes",startPosition_int}
        case sine:
 
          break;
 
        //{"speed", 32_int}s
        case speed:
          int thisSpeed = (incomingData.substring(index_of_firstDelim + 1)).toInt();
          Serial.print("New speed is: ");
          Serial.println(thisSpeed);
          step_delay = thisSpeed;
          break;
      }
 
 
    }
  }
 
}
 
 
/*
typedef enum
{
  no_case, step, dir, sine, speed
} command_options;
*/
 
command_options castCommand(String command)
{
  command_options returnValue;
 
  if(command.equalsIgnoreCase("step")) {returnValue = step;}
  else if(command.equalsIgnoreCase("dir")) {returnValue = dir;}
  else if(command.equalsIgnoreCase("sine")) {returnValue = sine;}
  else if(command.equalsIgnoreCase("speed")) {returnValue = speed;}
  else {returnValue = no_case;}
 
  return returnValue;
}
 
//Sends the number of steps at a #defined delay. Up to numSteps.
void stepSteps(int numSteps)
{
  //only called after initialization or undefined behavior.
  if (numSteps > 0)
  {
    for (int i = 1; i <= numSteps; i++)
    {
      digitalWrite(STEP_PIN, HIGH);
      //delay(STEP_DELAY);
      delay(step_delay);
      digitalWrite(STEP_PIN, LOW);
      //delay(STEP_DELAY);
      delay(step_delay);
 
      Serial.print("Step #: ");
      Serial.println(i);
    }
  }
  else
  {
  }
 
  return;
}
