import RPi.GPIO as GPIO
import time

# 물리적 핀 번호를 정의
IN1 = 15  # PIN 15 (GPIO 22)
IN2 = 16  # PIN 16 (GPIO 23)
IN3 = 18  # PIN 18 (GPIO 24)
IN4 = 22  # PIN 22 (GPIO 25)

# 스텝 변수 초기화
Steps = 0               # 현재 스텝
steps_left = 4095       # 한 바퀴 (스텝 수)
Direction = True        # 회전 방향 (True: 정방향, False: 역방향)
last_time = 0           # 마지막 시간 기록
currentMillis = 0
time_elapsed = 0

def setup():
    GPIO.setmode(GPIO.BOARD)  # 물리적 핀 번호 방식 사용
    GPIO.setup(IN1, GPIO.OUT)  # IN1 핀을 출력으로 설정
    GPIO.setup(IN2, GPIO.OUT)  # IN2 핀을 출력으로 설정
    GPIO.setup(IN3, GPIO.OUT)  # IN3 핀을 출력으로 설정
    GPIO.setup(IN4, GPIO.OUT)  # IN4 핀을 출력으로 설정

def stepper(xw):
    global Steps
    for _ in range(xw):
        if Steps == 0:
            runStep(GPIO.LOW, GPIO.LOW, GPIO.LOW, GPIO.HIGH)
        elif Steps == 1:
            runStep(GPIO.LOW, GPIO.LOW, GPIO.HIGH, GPIO.HIGH)
        elif Steps == 2:
            runStep(GPIO.LOW, GPIO.LOW, GPIO.HIGH, GPIO.LOW)
        elif Steps == 3:
            runStep(GPIO.LOW, GPIO.HIGH, GPIO.HIGH, GPIO.LOW)
        elif Steps == 4:
            runStep(GPIO.LOW, GPIO.HIGH, GPIO.LOW, GPIO.LOW)
        elif Steps == 5:
            runStep(GPIO.HIGH, GPIO.HIGH, GPIO.LOW, GPIO.LOW)
        elif Steps == 6:
            runStep(GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.LOW)
        elif Steps == 7:
            runStep(GPIO.HIGH, GPIO.LOW, GPIO.LOW, GPIO.HIGH)
        SetDirection()

def runStep(value1, value2, value3, value4):
    GPIO.output(IN1, value1)  # IN1 핀에 값 출력
    GPIO.output(IN2, value2)  # IN2 핀에 값 출력
    GPIO.output(IN3, value3)  # IN3 핀에 값 출력
    GPIO.output(IN4, value4)  # IN4 핀에 값 출력

def SetDirection():
    global Steps
    if Direction:
        Steps += 1  # 정방향으로 스텝 증가
    else:
        Steps -= 1  # 역방향으로 스텝 감소
    if Steps > 7:
        Steps = 0  # 7을 초과하면 첫 번째 스텝으로 돌아감
    if Steps < 0:
        Steps = 7  # 0 미만이면 마지막 스텝으로 돌아감

def main():
    global steps_left, last_time, currentMillis, time_elapsed, Direction

    setup()

    while True:
        # 정방향 회전
        while steps_left > 0:
            currentMillis = time.time() * 1000000  # 현재 시간 (마이크로초 단위)
            if currentMillis - last_time >= 1000:
                stepper(1)
                time_elapsed += (currentMillis - last_time) / 1000000  # 경과 시간 계산
                last_time = currentMillis
                steps_left -= 1  # 남은 스텝 수 감소

        # 3시간 대기 (10,800,000 밀리초)
        print("3시간 대기 중...")
        time.sleep(3 * 60 * 60)  # 3시간 대기
        Direction = not Direction  # 회전 방향 반전
        steps_left = 4095  # 스텝 수 초기화

        # 역방향 회전
        while steps_left > 0:
            currentMillis = time.time() * 1000000  # 현재 시간 (마이크로초 단위)
            if currentMillis - last_time >= 1000:
                stepper(1)
                time_elapsed += (currentMillis - last_time) / 1000000  # 경과 시간 계산
                last_time = currentMillis
                steps_left -= 1  # 남은 스텝 수 감소

        # 3시간 대기 (10,800,000 밀리초)
        print("3시간 대기 중...")
        time.sleep(3 * 60 * 60)  # 3시간 대기
        Direction = not Direction  # 회전 방향 반전
        steps_left = 4095  # 스텝 수 초기화

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        GPIO.cleanup()  # 종료 시 GPIO 클린업
