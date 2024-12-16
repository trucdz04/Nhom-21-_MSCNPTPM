#include <Adafruit_LiquidCrystal.h>

int soil_sensor = 0;
int level = 0;  // Biến lưu trữ mức độ khô của đất
Adafruit_LiquidCrystal lcd_1(0);

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);  // Điều khiển bơm tưới
  pinMode(8, OUTPUT);  // Đèn báo tưới cây
  pinMode(9, OUTPUT);  // Đèn báo ngưng tưới
  
  lcd_1.begin(16, 2);
}

void loop() {
  soil_sensor = analogRead(A0);  // Đọc giá trị từ cảm biến độ ẩm đất
  Serial.println(soil_sensor);   // Hiển thị giá trị trên Serial Monitor

  // Xác định mức độ khô của đất dựa trên giá trị đo được từ 0 tới 876
  if (soil_sensor <= 218) {
    level = 1;  // Mức 1: đất rất khô
  } else if (soil_sensor <= 437) {
    level = 2;  // Mức 2: đất khô
  } else if (soil_sensor <= 656) {
    level = 3;  // Mức 3: đất ẩm
  } else {
    level = 4;  // Mức 4: đất rất ẩm
  }

  // Hiển thị mức độ khô của đất trên LCD
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("Do am: Muc ");
  lcd_1.print(level);

  // Điều khiển bơm tưới và hiển thị trạng thái tưới cây
  if (level == 1 || level == 2) {  // Đất khô hoặc rất khô -> bật bơm
    digitalWrite(7, HIGH);  // Bật bơm
    digitalWrite(8, HIGH);  // Bật đèn báo tưới
    digitalWrite(9, LOW);   // Tắt đèn báo ngưng tưới
    lcd_1.setCursor(0, 1);
    lcd_1.print("Dang tuoi cay");
  } else {  // Đất ẩm hoặc rất ẩm -> tắt bơm
    digitalWrite(7, LOW);  // Tắt bơm
    digitalWrite(8, LOW);  // Tắt đèn báo tưới
    digitalWrite(9, HIGH); // Bật đèn báo ngưng tưới
    lcd_1.setCursor(0, 1);
    lcd_1.print("Tat tuoi cay");
  }

  delay(1000);  // Chờ 1 giây trước khi cập nhật lại
}
