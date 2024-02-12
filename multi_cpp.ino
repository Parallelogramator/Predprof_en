const int chipPin = PA0; 
const int redLedPin = PB0; 
const int greenLedPin = PB1;
const int buttonPin = PE13;
const int motorPin = PE14; // PWM pin for the motor
float voltage;
float minVoltage = 3.0; // Минимальное контрольное напряжение
float maxVoltage = 3.6; // Максимальное контрольное напряжение

int motorSpeed;


void setup(){
  pinMode(chipPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(motorPin, OUTPUT);
  motorSpeed = 0;
  Serial.begin(9600); 
}

void loop() {
    // Simple motor test - increase speed, then decrease it.
  for(motorSpeed = 0; motorSpeed <= 100; ++motorSpeed) {
    analogWrite(motorPin, motorSpeed);
    delay(10);
  }
  while(digitalRead(buttonPin) == HIGH){ // Ждём нажатия кнопки
    // Ничего не делаем
  }

  float totalVoltage = 0.0;
  int iterations = 10;

  for(int i=0; i<iterations; ++i) {
    int value = analogRead(chipPin);
    voltage = (value * 5.0) / 4096.0; // Преобразуем значение аналогового чтения в напряжение
    totalVoltage += voltage;
    delay(500);
  }

  voltage = totalVoltage / iterations;
  Serial.print("Average Voltage: ");  
  Serial.println(voltage); 
    for(motorSpeed = 100; motorSpeed >= 0; --motorSpeed) {
    analogWrite(motorPin, motorSpeed);
    delay(10);
    }

  if(voltage < minVoltage || voltage > maxVoltage) { // если напряжение выходит за допустимые пределы 
    digitalWrite(redLedPin, HIGH); 
    digitalWrite(greenLedPin, LOW);
  } else { // если напряжение в допустимых пределах
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
  delay(500);
  
  while(digitalRead(buttonPin) == LOW){ // Ждём отпускания кнопки
     // Ничего не делаем
  }
}
  
