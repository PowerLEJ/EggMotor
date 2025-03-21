// Forward rotation
#define IN1_1  4
#define IN2_1  5
#define IN3_1  6
#define IN4_1  7
#define IN1_2    8
#define IN2_2    9
#define IN3_2    10
#define IN4_2    11

int Steps = 0;                      // 현재 스텝
float num_revolutions = 0.15;       // 회전할 바퀴 수
int steps_per_revolution = 4095;    // 한 바퀴에 필요한 스텝 수
float steps_left = steps_per_revolution * num_revolutions;  // 전체 스텝 수
unsigned long last_time;            // 마지막 시간 기록
unsigned long currentMillis;
long time;

void setup() {
    Serial.begin(115200);    // 시리얼 통신 초기화
    
    pinMode(IN1_1, OUTPUT);
    pinMode(IN2_1, OUTPUT);
    pinMode(IN3_1, OUTPUT);
    pinMode(IN4_1, OUTPUT);

    pinMode(IN1_2, OUTPUT);    // IN1 핀을 출력으로 설정
    pinMode(IN2_2, OUTPUT);    // IN2 핀을 출력으로 설정
    pinMode(IN3_2, OUTPUT);    // IN3 핀을 출력으로 설정
    pinMode(IN4_2, OUTPUT);    // IN4 핀을 출력으로 설정

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
            steps_left -= 1.0;  // 실수형으로 감소
        }
    }

    // 1시간 대기
    Serial.println("1시간 대기 중...");
    delay(3600000); // 1000 * 1 * 60 * 60
    steps_left = steps_per_revolution * num_revolutions;  // 스텝 수 초기화
}

void stepper(int xw) {
    for (int x = 0; x < xw; x++) {
        switch(Steps) {
            case 0:  runStep(LOW, LOW, LOW, HIGH);   break; 
            case 1:  runStep(LOW, LOW, HIGH, HIGH);  break; 
            case 2:  runStep(LOW, LOW, HIGH, LOW);   break; 
            case 3:  runStep(LOW, HIGH, HIGH, LOW);  break; 
            case 4:  runStep(LOW, HIGH, LOW, LOW);   break; 
            case 5:  runStep(HIGH, HIGH, LOW, LOW);  break; 
            case 6:  runStep(HIGH, LOW, LOW, LOW);   break; 
            case 7:  runStep(HIGH, LOW, LOW, HIGH);  break;     
            default: runStep(LOW, LOW, LOW, LOW);    break; 
        }
        SetDirection();  // 다음 스텝의 방향을 설정
    }
}

void runStep(int value1, int value2, int value3, int value4) {
    digitalWrite(IN1_1, value1);  
    digitalWrite(IN2_1, value2);  
    digitalWrite(IN3_1, value3);  
    digitalWrite(IN4_1, value4);  
    
    digitalWrite(IN1_2, value1);  
    digitalWrite(IN2_2, value2);  
    digitalWrite(IN3_2, value3);  
    digitalWrite(IN4_2, value4);  
}

void SetDirection() {

    Steps++;  // 정방향으로 스텝 증가
    
    if (Steps > 7) { 
        Steps = 0;  // 7을 초과하면 첫 번째 스텝으로 돌아감
    }
    if (Steps < 0) { 
        Steps = 7;  // 0 미만이면 마지막 스텝으로 돌아감
    }
}
