#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN D5  // Chân kết nối cảm biến DHT11
#define DHTTYPE DHT11  // Loại cảm biến là DHT11
DHT dht(DHTPIN, DHTTYPE);  // Khởi tạo đối tượng cho cảm biến DHT11

#define MQ135 A0///chân A0 cảm biến nối với A0 esp8266
#define BLYNK_AUTH_TOKEN "JBs27nC_1pCJAeoiOCiAl0JCLksVA5Kn"
char ssid[] = "YourNetworkSSID";  // Tên mạng WiFi
char pass[] = "YourNetworkPassword";  // Mật khẩu mạng WiFi

/*BLYNK_WRITE(V3) {
  chedo = param.asInt();  // Nhận giá trị được set từ widget Set trên Blynk
}*/
void setup() {
  Serial.begin(9600);  // Bắt đầu kết nối Serial
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"mppt-tqh.ddns.net",8080);  // Bắt đầu kết nối Blynk
  dht.begin();  // Bắt đầu kết nối cảm biến DHT11
  Blynk.run();  // Chạy Blynk
  delay(1000);
}

void loop() {
  Blynk.run();  // Chạy Blynk
  float temperature = dht.readTemperature();  // Đọc nhiệt độ từ cảm biến DHT11
  float humidity = dht.readHumidity();  // Đọc độ ẩm từ cảm biến DHT11
  int val1 = analogRead(MQ135);//0-1023
  Blynk.virtualWrite(V0, temperature);  // Gửi giá trị nhiệt độ lên Blynk
  Blynk.virtualWrite(V1, humidity);  // Gửi giá trị nhiệt độ lên Blynk
  Blynk.virtualWrite(V2, val1);  // Gửi giá trị nhiệt độ lên Blynk
  delay(500);
}
