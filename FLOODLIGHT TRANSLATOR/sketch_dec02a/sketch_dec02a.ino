int intensity[28];

void setup(){
  pinMode(13,OUTPUT);
  Serial2.begin(250000);
  Serial3.begin(57600);
}

void loop(){
  if (Serial2.available() >= 28) {
    for (int i = 0; i<28; i++){
      intensity[i] = Serial2.read();
      Serial3.print(intensity[i]);
      
    }
    
    analogWrite(13,intensity[0]);
  }}
