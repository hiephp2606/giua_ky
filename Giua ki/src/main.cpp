#include <Arduino.h>

#include <DHT.h>
#include <Adafruit_Sensor.h>

// Định nghĩa các chân kết nối
#define BUZZER_PIN 32
#define DHT_PIN 27
#define DHT_TYPE DHT11
#define MQ2_PIN 35

// Khởi tạo cảm biến
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  
  // Khởi tạo cảm biến DHT
  dht.begin();
  
  // Khởi tạo Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Khởi tạo MQ2
  pinMode(MQ2_PIN, INPUT);
  
  Serial.println("Hệ thống đã sẵn sàng!");
}

void loop() {
  // Đọc dữ liệu từ DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Không đọc được dữ liệu từ DHT11");
  } else {
    Serial.print("Nhiệt độ: ");
    Serial.print(temperature);
    Serial.print(" *C, Độ ẩm: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  
  // Đọc dữ liệu từ MQ2
  int mq2Value = analogRead(MQ2_PIN);
  Serial.print("Giá trị MQ2: ");
  Serial.println(mq2Value);

  // Điều kiện bật buzzer
  if (temperature > 30 || mq2Value > 600) {
    digitalWrite(BUZZER_PIN, HIGH);  // Bật Buzzer
    Serial.println("Cảnh báo! Nhiệt độ hoặc khí gas vượt ngưỡng!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Tắt Buzzer
  }
  
  delay(2000); // Chờ 2 giây trước khi đọc lại
}

