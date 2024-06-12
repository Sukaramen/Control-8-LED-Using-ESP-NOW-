#include <esp_now.h>
#include <WiFi.h>

const int buttonsPins[] = {4, 5, 6, 7, 8, 9, 10, 11};
uint8_t broadcastAddress[] = {}; //isi mac address pada esp32 penerima

typedef struct struct_message{
  bool ledState[8];
}struct_message;

struct_message myData;

void onSent (const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.print("\r\nStatus Pengiriman Paket Data: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Berhasil Terkirim!" : "Gagal Terkirim!");
} 

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println("ESP-NOW Sender");
  for(int i = 0; i < 8; i++){
    pinMode(buttonsPins[i], INPUT_PULLUP);
  }
  if(esp_now_init() != ESP_OK){
    Serial.println("Error melakukan inisialisasi ESP-NOW");
    return;
  }
}

void loop() {
  bool anyButtonPressed = false;

  for(int i; i < 8; i++){
    if (digitalRead(buttonsPins[i]) == LOW){
      myData.ledState[i] = !myData.ledState[i];
      anyButtonPressed = true;
    }
  }
  if (anyButtonPressed){
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if(result == ESP_OK){
      Serial.println("Berhasil Terkirim Data!");
    } else {
      Serial.println("Gagal Mengirim Data!");
    }
    delay(500);
  }
}
