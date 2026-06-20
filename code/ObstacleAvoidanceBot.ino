// Define Pin Connections
const int trigPin = 9;
const int echoPin = 10;

// Motor pins
int IN1 = 12;  // Left motors
int IN2 = 2;
int IN3 = 3;  // Right motors
int IN4 = 4;

int enA = 5;  //PWM pin
int enB = 6;  //Pwm pin

// Define variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  analogWrite(enA, 70); // Motor A at partial speed
  analogWrite(enB, 80); // Motor B at partial speed

  // Clear the trigPin by setting it LOW for 2 microseconds
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds to send the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (Speed of sound is 0.034 cm/microsecond)
  distance = duration * 0.034 / 2;
  
  // Print the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 50){
      stopMotors();
      delay(1000);
      right();
      delay(1000);
      stopMotors();
  }
  else{
    forward();
  }
  
  delay(50);
}

void forward() {
  // both sides forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward() {
  // both sides backward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void left() {
  // left side stop, right side forward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  // right side stop, left side forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
