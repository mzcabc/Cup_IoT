# 基础

在Arduino中, 标准的程序入口main函数在内部被定义, 用户只需要关心以下两个函数:
- `void setup()`:用于初始化,一般放在程序开头, 用于设置一些引脚的输出/输入模式, 初始化串口通讯等类似工作
- `void loop()`:用于执行,函数中的代码将被循环执行, 例如: 读入引脚状态, 设置引脚输出状态等.

简单程序:
```cpp
int onBoardLedPin = 13;//13为板载LED灯的引脚编号，
int testPin = 7;//声明一个要使用的引脚

// the setup function runs once when you press reset or power the board 初始化
void setup() {
  Serial.begin(9600);
  pinMode(onBoardLedPin, OUTPUT);//设置引脚状态为OUTOUT模式
  pinMode(testPin, INPUT);
}

// the loop function runs over and over again forever 主循环
void loop() {
  if (digitalRead(testPin) == 1 ) {
    digitalWrite(onBoardLedPin, HIGH); //写入引脚电平
    Serial.println("HIGH");
  } else {
    digitalWrite(onBoardLedPin, LOW);
    Serial.println("LOW");
  }
}


```

# 串口

函数:

```cpp
Serial.begin(); //开启串口, 初始化并设置串口波特率
Serial.end(); //关闭串口
Serial.available(); //判断串口缓冲器是否有数据装入
Serial.read(); //读取串口数据
Serial.peek(); //返回下一个字节（字符）输入数据，但不删除它
Serial.flush(); //清空串口缓存
Serial.print(); //写入字符串数据到串口
Serial.println(); //写入字符串数据带换行到串口
Serial.write(); //写入二进制数据到串口
Serial.SerialEvent(); //read时触发的事件函数
Serial.readBytes(buffer, length); //读取固定长度的二进制流
```

[官方例子][1]
```cpp
int incomingByte = 0;   // for incoming serial data

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC); // 打印接到数据十进制表示的ascii码
  }
}
```

[官方例子 Fade][2]
```cpp
/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */

int led = 9;           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
```





[1]:https://www.arduino.cc/en/Serial/Available
[2]:https://www.arduino.cc/en/Tutorial/Fade
