int encoderPin1 = 2;
int encoderPin2 = 3;

int x=0;

int v=10;
int i=0;
int c = 0;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

int grados;

void setup() {
  Serial.begin (9600);

  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Started Time,Grados,PWM");
  Serial.println("RESETTIMER");

  pinMode(encoderPin1, INPUT_PULLUP); 
  pinMode(encoderPin2, INPUT_PULLUP);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop(){
Serial.print("DATA,TIME,TIMER,");
Serial.print(grados);
Serial.print(",");
Serial.println(x);   
  if(i==0){
    analogWrite(10,v);
    //c++;
      v=v+1;
    delay(1000);
  }
  x = digitalRead(7);
  if(v==21){
    analogWrite(10,v);
    i=1;
  }
  //Serial.println(grados);
}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time

  grados = (encoderValue*360)/1260;
}
