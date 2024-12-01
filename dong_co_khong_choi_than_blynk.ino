#define BLYNK_TEMPLATE_ID "TMPL6yThZT0VK"
#define BLYNK_TEMPLATE_NAME "IOT NHIET DO DO AM"
#define BLYNK_AUTH_TOKEN "aXcHfrJxggNp9bvdpPvPZTs8f3svlQ_v"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
char ssid[] = "Thu Thao";  // Tên mạng WiFi
char pass[] = "12052002";  // Mật khẩu mạng WiFi

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Địa chỉ I2C của LCD 1602

BlynkTimer timer;

int setTemp = 36;  // Giá trị nhiệt độ được set mặc định
int coi = D8; // Chân kết nối của còi báo
int led = D7;
#include <Servo.h>
Servo dongco;
BLYNK_WRITE(V2) {
  setTemp = param.asInt();  // Nhận giá trị được set từ widget Set trên Blynk
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dongco.attach(D6);
  pinMode(coi, OUTPUT);
  pinMode(led, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.run();
  delay(100);
  Blynk.virtualWrite(V2, setTemp);  // Gửi giá trị nhiệt độ lên Blynk
}

void sendSensor() {
  int val = analogRead(A0);
  Blynk.virtualWrite(V0, val);  // Gửi giá trị nhiệt độ lên Blynk
  dongco.write(setTemp);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Val: ");
  lcd.print(val);
  lcd.setCursor(0, 1);
  lcd.print("Set: ");
  lcd.print(setTemp);

}

void loop() {
  Blynk.run();
  timer.run();
}
