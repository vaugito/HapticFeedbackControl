/*
  Title: ProstheticFeedbackControl
  Author: Justin Clark
  General Description: A prosthetic feedback control system
  Detailed Description: Control the ouptut of the gripper based on the input of the glove.
                        Based on the sensor input of the gripper, send feedback to the glove.
  Notes For Improvement: * Using a for loop in moveMotor() takes up more memory than the 29672 bytes allocated
                         * Gripper has gear slippage that can affect grip readings {HARDWARE}
*/
#include <Servo.h>
int vibrator_pin, feedback_pin, servo_gripper_pin, stretch_analog_pin, servo_vibrator_pin, stretch_value, touch_analog_pin, touch_value, stretch_analog_pin_1, stretch_analog_pin_2, stretch_analog_pin_3, stretch_analog_pin_4, stretch_analog_pin_5;
float stretch_voltage_1, stretch_voltage_2, stretch_voltage_3, stretch_voltage_4, stretch_voltage_5, touch_voltage, output, input, inputt, vibrator_voltage, inputt_feedback, stretch_max, stretch_min;
Servo gripper, vibrator;
String stretch_string, stretch_string_2, stretch_string_3, stretch_string_4, stretch_string_5,touch_string, out_string, stretch_input_pin, touch_input_pin;

void setup() {
  pinMode(10, OUTPUT);
  //pinMode(3, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  stretch_analog_pin_1 = 1; //Analog pin A1
  stretch_analog_pin_2 = 2; //Analog pin A2
  stretch_analog_pin_3 = 3; //Analog pin A3  
  stretch_analog_pin_4 = 4; //Analog pin A4
  stretch_analog_pin_5 = 5; //Analog pin A5

  stretch_string = "\nfinger 1 voltage: ";
  stretch_string_2 = " finger 2 voltage: ";
  stretch_string_3 = " finger 3 voltage: ";
  stretch_string_4 = " finger 4 voltage: ";
  stretch_string_5 = " finger 5 voltage: ";
  touch_string = " touch voltage: ";
  stretch_max = 1.9; //[V]
  stretch_min = 1.5; //[V]
  
}

void moveMotor(float input) {
  servo_gripper_pin = 10; //Servo PWM pin 10
  gripper.attach(servo_gripper_pin); //information voltage pin 
  inputt = map(input, stretch_min, stretch_max, 0, 180); // scale it to use it with the servo (value between 0 and 180)

}

void feedback(float touch_feedback) {  //lack of for loop saves memory for some reason? Need to explore...
  servo_vibrator_pin = 8; // PWM pin 3
  vibrator.attach(servo_vibrator_pin); 
  int speed = map(touch_feedback, 3.46, 3.90, 0, 180); 
 if (touch_feedback < 2.4)
  { vibrator.write(0);
    delay(1);
    vibrator.write(360);}
    else if (touch_feedback < 2.6)
    {vibrator.write(0); 
    delay(10);
    vibrator.write(360);}
    else if (touch_feedback < 3.0)
    {vibrator.write(0); 
    delay(30);
    vibrator.write(360);}
    else if (touch_feedback < 3.4)
    {vibrator.write(0); 
    delay(50);
    vibrator.write(360);}
    else if (touch_feedback < 3.6)
    {vibrator.write(0); 
    delay(100);
    vibrator.write(360);}
   else if (touch_feedback < 4.0)
    {vibrator.write(0); 
    delay(150);
    vibrator.write(360);}
    else if (touch_feedback < 4.3)
    {vibrator.write(0); 
    delay(175);
    vibrator.write(360);}
    else if (touch_feedback < 4.5)
    {vibrator.write(0); 
    delay(200);
    vibrator.write(360);}
    else if (touch_feedback < 4.7)
    {vibrator.write(0); 
    delay(256);
    vibrator.write(360);}
      else if (touch_feedback < 4.9)
      {vibrator.write(360);    
       delay(300);
       vibrator.write(0);}
       else{
        delay(500);
       }
  delay(15);
}
void loop() {
  int conversion_voltage = (5.0 / 1023.0);
  int stretch_value_1 = analogRead(stretch_analog_pin_1);
  int stretch_value_2 = analogRead(stretch_analog_pin_2);
  int stretch_value_3 = analogRead(stretch_analog_pin_3);
  int stretch_value_4 = analogRead(stretch_analog_pin_4);
  int stretch_value_5 = analogRead(stretch_analog_pin_5);
  touch_value = analogRead(touch_analog_pin);
  stretch_voltage_1 = stretch_value_1 * 5.0 / 1023.0; //Converts: 0-1024 bit range to 0-5[V] scale
  stretch_voltage_2 = stretch_value_2 * 5.0 / 1023.0;
  stretch_voltage_3 = stretch_value_3 * 5.0 / 1023.0;
  stretch_voltage_4 = stretch_value_4 * 5.0 / 1023.0;
  stretch_voltage_5 = stretch_value_5 * 5.0 / 1023.0;
  touch_voltage = touch_value * 5.0 / 1023.0;

  Serial.println(stretch_string + stretch_voltage_1 + stretch_string_2 + stretch_voltage_2 + stretch_string_3  + stretch_voltage_3 + stretch_string_4 + stretch_voltage_4 + stretch_string_5 + stretch_voltage_5);
  delay(500);
}
