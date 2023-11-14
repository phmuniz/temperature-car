#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15

#define MOTOR1_PINO_POS    D3
#define MOTOR1_PINO_NEG    D1
#define MOTOR2_PINO_POS    D4
#define MOTOR2_PINO_NEG    D5

void setup() {
  pinMode(MOTOR1_PINO_POS,OUTPUT);  
  pinMode(MOTOR1_PINO_NEG,OUTPUT);
  pinMode(MOTOR2_PINO_POS,OUTPUT);
  pinMode(MOTOR2_PINO_NEG,OUTPUT);

  digitalWrite(MOTOR1_PINO_POS,LOW);
  digitalWrite(MOTOR1_PINO_NEG,LOW);
  digitalWrite(MOTOR2_PINO_POS,LOW);
  digitalWrite(MOTOR2_PINO_NEG,LOW);
}

void loop() {
  analogWrite(MOTOR1_PINO_POS,200);
  analogWrite(MOTOR1_PINO_NEG,0);
  analogWrite(MOTOR2_PINO_POS,0);
  analogWrite(MOTOR2_PINO_NEG,200);

}
