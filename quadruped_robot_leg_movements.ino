#include <Servo.h>

Servo servo[12];

const int deg0[12] = {60, 60, 35, 60, 60, 40, 25, 90, 80, 75, 125, 40};
const int dir[12] = {-1, -1, 1, 1, 1, -1, 1, 1, -1, -1, -1, 1};

void setup(){
  for(int i=0; i<12; i++){
    servo[i].attach(i+2);
  }
  Serial.begin(9600);
}

void still(){
  for(int i=0; i<12; i++){
    servo[i].write(deg0[i]);
  }
}

void two_degs(float h, float l, float H, float forward_rate, int motor1, int motor2){
  float t_square = pow(forward_rate, 2)+pow(H, 2);
  float cos_theta2 = (pow(h, 2)+pow(l, 2)-t_square)/(2*h*l);
  float theta2 = acos(cos_theta2);
  float diameter = pow(t_square, 0.5)/sin(theta2);
  float sin_theta_primeprime = l/diameter;
  float theta_primeprime = asin(sin_theta_primeprime);
  float sin_theta_primeprimeprimeprime = abs(forward_rate)/pow(t_square, 0.5);
  float theta_primeprimeprimeprime = asin(sin_theta_primeprimeprimeprime);
  theta_primeprime = degrees(theta_primeprime);
  theta_primeprimeprimeprime = degrees(theta_primeprimeprimeprime);
  int decision = 1;
  if(forward_rate != 0){
    decision = forward_rate/abs(forward_rate);
  }
  float theta1 = 90-theta_primeprimeprimeprime*decision-theta_primeprime;
  theta2 = degrees(theta2);
  Serial.println("===========");
  Serial.println(theta2);
  Serial.println(theta1);
  Serial.println("===========");
  Serial.println(deg0[motor1]-dir[motor1]*theta2-106.26);
  Serial.println(deg0[motor2]-dir[motor2]*theta1-53.13);
  servo[motor1].write(deg0[motor1]-dir[motor1]*theta2-106.26);
  servo[motor2].write(deg0[motor2]-dir[motor2]*theta1-53.13);
}

void motormove(int num, int deg){
  servo[num].write(deg0[num]+dir[num]*deg);
}

void loop(){
  still();
  delay(1000);
  for(int i=0; i<21; i++){
    motormove(2, -i);
    motormove(5, -i);
    motormove(8, i);
    motormove(11, i);
    delay(15);
  }
  delay(1000);
  //two_degs(5, 5, 9, 3, 0, 1);
  //delay(10);
  //two_degs(5, 5, 7, 3, 0, 1);
  //delay(3000);
}
