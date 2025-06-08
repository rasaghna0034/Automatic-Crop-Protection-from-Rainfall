#define IN1 8         // Motor input 1
#define IN2 9         // Motor input 2
#define rainPin 7     // Rain sensor digital pin
#define buzzer 6      // Buzzer connected to D6

bool shelterClosed = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(rainPin, INPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(buzzer, LOW);
  Serial.begin(9600);
}

void loop() {
  int rain = digitalRead(rainPin); // LOW = rain detected

  if (rain == LOW && !shelterClosed) {
    Serial.println("Rain Detected: Closing shelter");
    digitalWrite(buzzer, HIGH);     // Sound buzzer
    closeShelter();
    shelterClosed = true;
    digitalWrite(buzzer, LOW);      // Turn off buzzer
  }
  else if (rain == HIGH && shelterClosed) {
    Serial.println("No Rain: Opening shelter");
    openShelter();
    shelterClosed = false;
  }

  delay(2000);  // Delay for stability
}

void closeShelter() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);  // Motor rotates one way
  delay(5000);              // Adjust based on motor/shelter
  stopMotor();
}

void openShelter() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);   // Reverse motor direction
  delay(5000);
  stopMotor();
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
