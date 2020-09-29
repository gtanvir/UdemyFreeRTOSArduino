#include <Arduino_FreeRTOS.h>
#include "semphr.h"

#define RED 6
#define YELLOW 7
#define BLUE 8

SemaphoreHandle_t xCountingSemaphore; 

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);

  Serial.begin(9600);

  xCountingSemaphore = xSemaphoreCreateCounting(1,0);

  xTaskCreate(redLedControllerTask, "RED", 100, NULL, 1, NULL);
  xTaskCreate(yellowLedControllerTask, "YELLOW", 100, NULL, 1, NULL);
  xTaskCreate(blueLedControllerTask, "BLUE", 100, NULL, 1, NULL);

  xSemaphoreGive(xCountingSemaphore);
}

void redLedControllerTask() {
  while(1) {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(RED, digitalRead(RED)^1);
    Serial.println("Red Task: "); 
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);    
  }
}

void yellowLedControllerTask() {
  while(1) {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);
    Serial.println("Yellow Task: ");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);          
  }
}

void blueLedControllerTask() {
  while(1) {
    xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    Serial.println("Blue Task: ");
    xSemaphoreGive(xCountingSemaphore);
    vTaskDelay(1);   
  }
}


void loop() {
  // put your main code here, to run repeatedly:

}
