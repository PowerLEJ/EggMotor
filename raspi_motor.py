import RPi.GPIO as GPIO
import time

# Physical (BOARD)
MOTOR1_IN1 = 11  # PIN 11 (GPIO 17)
MOTOR1_IN2 = 12  # PIN 12 (GPIO 18)
MOTOR2_IN1 = 15  # PIN 15 (GPIO 22)
MOTOR2_IN2 = 16  # PIN 16 (GPIO 23)

# GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(MOTOR1_IN1, GPIO.OUT)
GPIO.setup(MOTOR1_IN2, GPIO.OUT)
GPIO.setup(MOTOR2_IN1, GPIO.OUT)
GPIO.setup(MOTOR2_IN2, GPIO.OUT)

def motor1_forward():
    GPIO.output(MOTOR1_IN1, GPIO.HIGH)
    GPIO.output(MOTOR1_IN2, GPIO.LOW)

def motor1_backward():
    GPIO.output(MOTOR1_IN1, GPIO.LOW)
    GPIO.output(MOTOR1_IN2, GPIO.HIGH)

def motor2_forward():
    GPIO.output(MOTOR2_IN1, GPIO.HIGH)
    GPIO.output(MOTOR2_IN2, GPIO.LOW)

def motor2_backward():
    GPIO.output(MOTOR2_IN1, GPIO.LOW)
    GPIO.output(MOTOR2_IN2, GPIO.HIGH)

def stop_motors():
    GPIO.output(MOTOR1_IN1, GPIO.LOW)
    GPIO.output(MOTOR1_IN2, GPIO.LOW)
    GPIO.output(MOTOR2_IN1, GPIO.LOW)
    GPIO.output(MOTOR2_IN2, GPIO.LOW)

try:
    while True:
        print("forward")
        motor1_forward()
        motor2_forward()
        time.sleep(1) # 1s

        print("stop")
        stop_motors()
        time.sleep(3*60*60) # 3*60*60s

        print("backward")
        motor1_backward()
        motor2_backward()
        time.sleep(1) # 1s

        print("stop")
        stop_motors()
        time.sleep(3*60*60) # 3*60*60s

except KeyboardInterrupt:
    print("exit")
    stop_motors()
    GPIO.cleanup()
