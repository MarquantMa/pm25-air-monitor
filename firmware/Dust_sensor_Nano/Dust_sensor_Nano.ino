// ====================================================================
// 夏普 GP2Y1010AU0F PM2.5 粉尘传感器测试程序 (Arduino Nano 适用)
// ====================================================================

const int dustPin = A0;   // 传感器第5脚 Vo -> 接 Nano 的 A0 引脚
const int ledPower = 2;   // 传感器第3脚 LED -> 接 Nano 的 D2 引脚

// 夏普官方手册规定的脉冲时间参数（单位：微秒）
const int samplingTime = 280; // 开启LED后，等待280微秒再采样
const int deltaTime = 40;     // 采样持续40微秒
const int sleepTime = 9680;   // 剩下的等待时间 (10000 - 280 - 40)

void setup() {
  Serial.begin(9600);         // 初始化串口监视器，波特率 9600
  pinMode(ledPower, OUTPUT);  // 设置 D2 为输出模式
}

void loop() {
  // 1. 点亮传感器内部的红外 LED (低电平点亮)
  digitalWrite(ledPower, LOW); 
  delayMicroseconds(samplingTime);

  // 2. 读取 A0 引脚的模拟电压信号 (0 ~ 1023)
  float rawSignal = analogRead(dustPin);

  delayMicroseconds(deltaTime);
  // 3. 关闭红外 LED (高电平熄灭)
  digitalWrite(ledPower, HIGH); 
  delayMicroseconds(sleepTime);

  // 4. 计算实际电压值 (Nano工作电压为 5V，ADC为 10位)
  float voltage = rawSignal * (5.0 / 1023.0);
  
  // 5. 使用经典线性公式计算粉尘浓度 (单位: mg/m3)
  // 公式源于夏普官方曲线图：浓度 = 0.172 * 电压 - 0.1
  float dustDensity = 0.172 * voltage - 0.1;
  
  // 修正校准：空气极好时，算法可能算负数，将其归零
  if (dustDensity < 0) {
    dustDensity = 0; 
  }

  // 6. 转换为更直观的 ug/m3（微克/立方米）并输出
  float ugM3 = dustDensity * 1000;

  Serial.print("传感器电压: ");
  Serial.print(voltage, 3); // 保留3位小数
  Serial.print(" V  |  PM2.5 浓度: ");
  Serial.print(ugM3, 1);    // 保留1位小数
  Serial.println(" ug/m3");

  delay(500); // 每隔 1 秒刷新一次数据
}