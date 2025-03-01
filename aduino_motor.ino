#define MOTOR1_IN1 11
#define MOTOR1_IN2 12
#define MOTOR2_IN1 5
#define MOTOR2_IN2 6

void setup() {
    pinMode(MOTOR1_IN1, OUTPUT);
    pinMode(MOTOR1_IN2, OUTPUT);
    pinMode(MOTOR2_IN1, OUTPUT);
    pinMode(MOTOR2_IN2, OUTPUT);
    
    Serial.begin(9600);
}

void motor1Forward() {
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
}

void motor1Backward() {
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);
}

void motor2Forward() {
    digitalWrite(MOTOR2_IN1, HIGH);
    digitalWrite(MOTOR2_IN2, LOW);
}

void motor2Backward() {
    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, HIGH);
}

void stopMotors() {
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, LOW);
    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, LOW);
}

void loop() {
    Serial.println("forward");
    motor1Forward();
    motor2Forward();
    delay(1000); // 1s

    Serial.println("stop");
    stopMotors();
    delay(3*60*60*1000); // 3*60*60*1000s

    Serial.println("backward");
    motor1Backward();
    motor2Backward();
    delay(1000); // 1s

    Serial.println("stop");
    stopMotors();
    delay(3*60*60*1000); // 3*60*60*1000s
}
