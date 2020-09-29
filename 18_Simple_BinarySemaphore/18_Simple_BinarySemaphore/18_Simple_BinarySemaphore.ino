#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED     6
#define YELLOW  7
#define BLUE    8

typedef int TaskProfiler; 
TaskProfiler RedTaskProfiler,BlueTaskProfiler, YellowTaskProfiler;

TaskHandle_t blue_Handle, red_Handle,yellow_Handle;

SemaphoreHandle_t xBinarySemaphore; 

void setup() {
  Serial.begin(9600); 
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(redLedControllerTask, 
              "Red Led Task",
              100, 
              NULL,
              1, 
              NULL); 

  xTaskCreate(blueLedControllerTask, 
              "Blue Led Task",
              100, 
              NULL,
              1, 
              NULL);

  xTaskCreate(yellowLedControllerTask, 
              "Yello Led Task",
              100, 
              NULL,
              1, 
              NULL);
}

void redLedControllerTask(void *pvParameters)
{
  pinMode(RED, OUTPUT); 
  xSemaphoreGive(xBinarySemaphore);
  while(1) {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("This is Red Task"); 
    xSemaphoreGive(xBinarySemaphore); 
    vTaskDelay(1);
  }
}

void blueLedControllerTask(void *pvParameters)
{
  pinMode(BLUE, OUTPUT); 
  while(1) {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("This is Blue Task");
    xSemaphoreGive(xBinarySemaphore); 
    vTaskDelay(1);
  }
}

void yellowLedControllerTask(void *pvParameters)
{
  pinMode(YELLOW, OUTPUT); 
  while(1) {
    xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
    Serial.println("This is Yellow Task");
    xSemaphoreGive(xBinarySemaphore); 
    vTaskDelay(1);
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
