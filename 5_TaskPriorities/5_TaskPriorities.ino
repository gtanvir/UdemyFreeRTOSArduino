#include <Arduino_FreeRTOS.h>

#define RED     6
#define BLUE    8
#define YELLOW  7

typedef int TaskProfiler;

TaskProfiler RedLEDProfiler;
TaskProfiler YellowLEDProfiler;
TaskProfiler BlueLEDProfiler;

TaskHandle_t red_Handle, blue_Handle, yellow_Handle;

void setup()
{
  xTaskCreate(redLedControllerTask,"RED LED Task",100,NULL,3,&red_Handle);
  xTaskCreate(blueLedControllerTask,"BLUE LED Task", 100, NULL,3,&blue_Handle);
  xTaskCreate(yellowLedControllerTask,"YELLOW LED Task", 100, NULL,3,&yellow_Handle);  
}


void redLedControllerTask(void *pvParameters)
{
  pinMode(RED,OUTPUT);
  while(1)
  {
   digitalWrite(RED,digitalRead(RED)^1);
   delay(50);  
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE,OUTPUT);
  while(1)
  {
   digitalWrite(BLUE,digitalRead(BLUE)^1); 
   delay(50); 
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW,OUTPUT);
  while(1)
  {
    digitalWrite(YELLOW,digitalRead(YELLOW)^1);
    delay(50); 
    vTaskPrioritySet(red_Handle,2); 
  }
}

void loop(){}
