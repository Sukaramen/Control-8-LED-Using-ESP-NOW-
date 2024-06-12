#include <esp_now.h>
#include <WiFi.h>

const int ledPins[8] = {4, 5, 6, 7, 8, 9, 10, 11};

typedef struct struct_message{
  bool ledState[8];
}struct_message;

struct_message myData;

void onReceive(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  for(int i = 0; i < 8; i++){
    Serial.print("Led ");
    Serial.print(i);
    Serial.print(" State: ");
    Serial.println(myData.ledState[i]);
    digitalWrite(ledPins[i], myData.ledState[i] ? HIGH : LOW);
  }
}

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("ESP-NOW Receiver");
  for(int i = 0; i < 8; i++){
    pinMode(ledPins[i], OUTPUT);
  }
  if (esp_now_init() != ESP_OK){
    Serial.println("Error melakukan inisialisasi ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onReceive);
}

void loop(){
  
}
