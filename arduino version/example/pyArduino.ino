
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Arduino IDE
 * @brief   pyArduino (.ino) 
*/

/*
#### NOTE ####
Before using this example you need to download and install the PWM library written by Sam Knight.
Link: https://github.com/terryjmyers/PWM

Then copy the ardCd folder to the Arduino libraries path.

######
*/


#include "ardCd.hpp"
#include <Servo.h>
#include "PWM.h"

#define MAX_FRQ     2000000UL

#define is_adc_pin(idx)   (((idx) >= 0) && ((idx) <= 7)) 

#define is_8_bit_tim(idx) (((idx) == 3) || \
                          ((idx) == 5)  || \
                          ((idx) == 6)  || \
                          ((idx) == 11))  
                          
#define is_pwm_pin(idx) (((idx) == 3)   || \
                         ((idx) == 9)   || \
                         ((idx) == 10))

#define is_servo_pin(idx) (((idx) == 9) || \
                           ((idx) == 10))                             

enum commands{
    out,
    in,
    pwmfre,
    pwm,
    servo,
    adc
};
typedef enum commands  cmds;

enum erros{
    badCmd,
    idxNF,
    assgnmentNF,
    valOF,
    notNum,
    idxF,
    assgnmentF
};
typedef enum erros  err;

void error(const err& e);
bool l1_errors();
bool l2_errors();

const String baseCmd_1[] = {"out", "in", "pwmfre", "pwm", "servo", "adc"};
const String baseCmd_2[] = {".0", ".1", ".2", ".3", ".4", ".5",".6", ".7", ".8", ".9",".10", ".11", ".12", ".13",
														".14", ".15", ".16", ".17", ".18", ".19"};


ardCd<2, 1> pyArduino;
Servo servoMotor;

String inputStr;
int cmd;
int idx;
int val;
int cmdHis = ardCd<2, 1> :: NP;
int idxHis = ardCd<2, 1> :: NP;
bool success;
bool isMemGood;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println(pyArduino.addBaseCmd(baseCmd_1, 6, 0));
  delay(1000);
  Serial.println(pyArduino.addBaseCmd(baseCmd_2, 20, 1));
  delay(1000);
  if(pyArduino.memStatus() == false)
  {
    while(1)
    {
      Serial.println("Memory allocation failed!");
      delay(1000);
    }
  }
}

void loop() {

  while(!Serial.available());
  inputStr = Serial.readString();
  pyArduino.decode(inputStr);
  cmd = pyArduino.getCmd(0);
  if(cmd == ardCd<2, 1> :: NP)
    error(badCmd);

  else
  {
    idx = pyArduino.getCmd(1);
    val = pyArduino.getNum(0);
  
    switch(cmd)
    { 
      case out:

        if(!(l1_errors()))
          break;

        if(val > 1 || val < 0)
        {
          error(valOF); 
          break;
        }
        if(!(cmdHis == cmd && idxHis == idx))
          pinMode(idx, OUTPUT);
        
        digitalWrite(idx, val);
        Serial.println("OK");

      break;

      case in: 

        if(!(l2_errors()))
          break;

        if(!(cmdHis == cmd && idxHis == idx))
          pinMode(idx, INPUT);
  
        Serial.println(digitalRead(idx));
      break;

      case pwmfre: 

        if(!(l1_errors()))
          break;

        if(val > MAX_FRQ || val < 1)
        {
          error(valOF); 
          break;
        }

        if(is_8_bit_tim(idx) == 1 && val < 31)
        {
          Serial.println("8 bit timers frequency range: 31Hz - 2 MHz!");
          break;
        }

        if(is_pwm_pin(idx) == 0)
        {
          Serial.println("this pin is not pwm!");
          break;
        }  

        InitTimersSafe(); 
        success = SetPinFrequencySafe(idx, val);
        if(!success)
        {
          Serial.println("unable to Initialize timers!"); 
          break;
        } 
        Serial.println("OK");
      break;

      case pwm: 

        if(!(l1_errors()))
          break;

        if(val > 100 || val < 0)
        {
          error(valOF); 
          break;
        }
        if(is_pwm_pin(idx) == 0)
        {
          Serial.println("this pin is not pwm!");
          break;
        }  
        val = map(val, 0, 100, 0, 65535);
        pwmWriteHR(idx, val);

        Serial.println("OK");
      break;

      case servo: 

        if(!(l1_errors()))
          break;

        if(val > 180 || val < 0)
        {
          error(valOF); 
          break;
        }
        if(is_servo_pin(idx) == 0)
        {
          Serial.println("this pin is not for servo!");
          break;
        }  
        if(!(cmdHis == cmd && idxHis == idx))
          servoMotor.attach(idx);
        
        servoMotor.write(val); 
        Serial.println("OK");
      break;

      case adc: 

        if(!(l2_errors()))
          break;
        
        if(is_adc_pin(idx) == 0)
        {
          Serial.println("this pin is not analog!");
          break;
        } 
        Serial.println(analogRead((idx + 14)));
      break;

      defalut:
        Serial.println("unknown!");
      break;
    } 
  }
  cmdHis = cmd;
  idxHis = idx;
}

void error(const err& e)
{
  switch(e)
  {
    case badCmd:
      Serial.println("Bad command!");
    break;

    case idxNF: 
      Serial.println("Bad index!");
    break;

    case idxF:
      Serial.println("This command must not get an index!");
    break;

    case valOF:
      Serial.println("out of range!");
    break;

    case notNum:
      Serial.println("not numeric value!");
    break;

    case assgnmentNF:
      Serial.println("This command must get a value!");
    break;

    case assgnmentF:
      Serial.println("This command must not get a value!");
    break;

    default:
    break;
  }
}

bool l1_errors()
{
bool status = true;

  if(idx == ardCd<2, 1> :: NP){ error(idxNF); status = false; } 

  else if(val == ardCd<2, 1> :: NP){ error(assgnmentNF); status = false; }

  else if(val == ardCd<2, 1> :: NaN){ error(notNum); status = false; }

  return status;

}

bool l2_errors()
{
bool status = true;

  if(idx == ardCd<2, 1> :: NP){ error(idxNF); status = false; } 

  else if(val != ardCd<2, 1> :: NP){ error(assgnmentF); status = false; }

  return status;
}

