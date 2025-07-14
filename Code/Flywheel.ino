const int AIN1 = 18;
const int AIN2 = 19;
const int PWMA = 21;

const int BIN1 = 22;
const int BIN2 = 23;
const int PWMB = 25;

const int STBY = 5;
const int joyButton = 15;

bool motorOn = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(joyButton, INPUT_PULLUP);

  digitalWrite(STBY, HIGH); 

  ledcAttach(PWMA, 1000, 8);
  ledcAttach(PWMB, 1000, 8);

  Serial.begin(115200);
}

void loop() {
  bool buttonState = digitalRead(joyButton);

  if (lastButtonState == HIGH && buttonState == LOW) {
    motorOn = !motorOn;

    if (motorOn) {
      runMotors(255); 
      Serial.println("Motors ON");
    } else {
      stopMotors();
      Serial.println("Motors OFF");
    }

    delay(200); 
  }

  lastButtonState = buttonState;
}

void runMotors(int speed) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(PWMA, speed); 
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(PWMB, speed);
}

void stopMotors() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  ledcWrite(PWMA, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  ledcWrite(PWMB, 0);
}
