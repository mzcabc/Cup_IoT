# 继电器

此继电器为`低电平触发`，`正极`接到`公共端`
- `IN`输入`低电平`时, `长闭端`接通`公共端`
- `IN`输入`高电平`时, `长开端`接通`公共端`

code:
```cpp
void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  analogWrite(6, 80); //低亮度 避免LED烧坏
  digitalWrite(7, HIGH);
  Serial.println("7 HIGH");
  delay(2000);
  digitalWrite(7, LOW);
  Serial.println("7 LOW");
  delay(2000);
}
```
