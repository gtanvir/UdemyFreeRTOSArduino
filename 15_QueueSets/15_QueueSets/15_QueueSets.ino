#include <Arduino_FreeRTOS.h>
#include "queue.h"

#define RED 6
#define YELLOW 7
#define BLUE 8

QueueHandle_t xQueue1, xQueue2; 
QueueSetHandle_t xQueueSet; 

void setup() {
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);  
  Serial.begin(9600); 
  xQueue1 = xQueueCreate(1, sizeof(char *));
  xQueue2 = xQueueCreate(1, sizeof(char *));

  xQueueSet = xQueueCreateSet(1*2);

  xQueueAddToSet(xQueue1, xQueueSet);
  xQueueAddToSet(xQueue2, xQueueSet);

  xTaskCreate(vSenderTask1, "Sender Task 1", 100, NULL, 1, NULL);
  xTaskCreate(vSenderTask2, "Sender Task 2", 100, NULL, 1, NULL);
  xTaskCreate(vReceiverTask,"Receiver Task", 100, NULL, 2, NULL);
  
}

void vSenderTask1(void *pvParameters) {

  const TickType_t xBlockTime = pdMS_TO_TICKS(100);
  const char * const messageToSend = "Message from Sender 1";

  while(1) {
  vTaskDelay(xBlockTime);
  xQueueSend(xQueue1, &messageToSend, 0);
  digitalWrite(BLUE, HIGH);
  }
}

void vSenderTask2(void *pvParameters) {

  const TickType_t xBlockTime = pdMS_TO_TICKS(200);
  const char * const messageToSend = "Hello from Sender 2";

  while(1){
  vTaskDelay(xBlockTime);
  xQueueSend(xQueue2, &messageToSend, 0);
  digitalWrite(BLUE, HIGH);
  }
}

void vReceiverTask(void *pvParameters) {
  QueueHandle_t xQueueThatContainsData; 
  char *pcReceivedString;

  while(1) {
    xQueueThatContainsData = (QueueHandle_t)xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
    xQueueReceive(xQueueThatContainsData, &pcReceivedString, 0); 
    Serial.println(pcReceivedString);  
    Serial.println((int)xQueueThatContainsData);
    digitalWrite(BLUE, LOW);
    delay(100);
  }
}



void loop() {
  // put your main code here, to run repeatedly:

}
