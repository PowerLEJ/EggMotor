#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

int Steps = 0;              // 현재 스텝
int num_revolutions = 2;    // 회전할 바퀴 수
int steps_per_revolution = 4095;  // 한 바퀴에 필요한 스텝 수
int steps_left = steps_per_revolution * num_revolutions;  // 전체 스텝 수
boolean Direction = true;   // 회전 방향 (true: 정방향, false: 역방향)
unsigned long last_time;    // 마지막 시간 기록
unsigned long currentMillis;
long time;

void setup() {
    Serial.begin(115200);    // 시리얼 통신 초기화
    pinMode(IN1, OUTPUT);    // IN1 핀을 출력으로 설정
    pinMode(IN2, OUTPUT);    // IN2 핀을 출력으로 설정
    pinMode(IN3, OUTPUT);    // IN3 핀을 출력으로 설정
    pinMode(IN4, OUTPUT);    // IN4 핀을 출력으로 설정

    delay(5000); // 5초 후에 시작
}

void loop() {

    // 정방향 회전
    while(steps_left > 0) {
        currentMillis = micros();  // 현재 시간 (마이크로초 단위) 기록
        if (currentMillis - last_time >= 1000) {  // 1000 마이크로초가 경과했으면
            stepper(1); 
            time = time + micros() - last_time;  // 경과 시간 계산
            last_time = micros();  // 마지막 시간 갱신
            steps_left--;  // 남은 스텝 수 감소
        }
    }

    // 1시간 대기
    Serial.println("1시간 대기 중...");
    delay(1000*1*60*60); 
    Direction = !Direction;  // 회전 방향 반전
    steps_left = steps_per_revolution * num_revolutions;  // 스텝 수 초기화
    
    // 역방향 회전
    while(steps_left > 0) {
        currentMillis = micros();  // 현재 시간 (마이크로초 단위) 기록
        if (currentMillis - last_time >= 1000) {  // 1000 마이크로초가 경과했으면
            stepper(1); 
            time = time + micros() - last_time;  // 경과 시간 계산
            last_time = micros();  // 마지막 시간 갱신
            steps_left--;  // 남은 스텝 수 감소
        }
    }

    // 1시간 대기
    Serial.println("1시간 대기 중...");
    delay(1000*1*60*60); 
    Direction = !Direction;  // 회전 방향 반전
    steps_left = steps_per_revolution * num_revolutions;  // 스텝 수 초기화
}

void stepper(int xw) {
    for (int x = 0; x < xw; x++) {
        switch(Steps) {
            case 0:  runStep(LOW, LOW, LOW, HIGH);   break; 
            case 1:  runStep(LOW, LOW, HIGH, HIGH);   break; 
            case 2:  runStep(LOW, LOW, HIGH, LOW);    break; 
            case 3:  runStep(LOW, HIGH, HIGH, LOW);   break; 
            case 4:  runStep(LOW, HIGH, LOW, LOW);    break; 
            case 5:  runStep(HIGH, HIGH, LOW, LOW);   break; 
            case 6:  runStep(HIGH, LOW, LOW, LOW);    break; 
            case 7:  runStep(HIGH, LOW, LOW, HIGH);   break;     
            default: runStep(LOW, LOW, LOW, LOW);     break; 
        }
        SetDirection();  // 다음 스텝의 방향을 설정
    }
}

void runStep(int value1, int value2, int value3, int value4) {
    digitalWrite(IN1, value1);  // IN1 핀에 value1 값 출력
    digitalWrite(IN2, value2);  // IN2 핀에 value2 값 출력
    digitalWrite(IN3, value3);  // IN3 핀에 value3 값 출력
    digitalWrite(IN4, value4);  // IN4 핀에 value4 값 출력
}

void SetDirection() {
    if (Direction == true) { 
        Steps++;  // 정방향으로 스텝 증가
    }
    if (Direction == false) { 
        Steps--;  // 역방향으로 스텝 감소
    }
    if (Steps > 7) { 
        Steps = 0;  // 7을 초과하면 첫 번째 스텝으로 돌아감
    }
    if (Steps < 0) { 
        Steps = 7;  // 0 미만이면 마지막 스텝으로 돌아감
    }
}
