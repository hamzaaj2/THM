#define RELAY_PIN 3
int ledPin1 = 11;
int ledPin2 = 12;
char data;
double finalmax;
double max1;
double max2;
double max3;
double finallow;
double low1;
double low2;
double low3;
double finalpers;
int intfinalpers;
unsigned long timee;
unsigned long pretimee;
double reading1;
double prereading1;
double reading2;
double prereading2;
double reading3;
double prereading3;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT); 
  digitalWrite(RELAY_PIN,LOW);
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT); 
  timee = millis();
  max1 = 0;
  max2 = 0;
  max3 = 0;
  low1 = 0;
  low2 = 0;
  low3 = 0;
}

void loop() {
  while (Serial.available()){
     data = Serial.read();
  }
  if ( data == 'v' ){
         data = 'z';
         while(true){
           while (Serial.available()){
           data = Serial.read();
           }
           if ( data == 's') {
             data = 'z';
             check(max1 , reading1 , prereading1 , low1);
           }
           else if ( data == 'd') {
             data = 'z';
             check(max2 , reading2 , prereading2 , low2);
           }
           else if ( data == 'o') {
             data = 'z';
             check(max3 , reading3 , prereading3 , low3);
           }
           }
         finalmax = max1 + max2 + max3;
         finallow = low1 + low2 + low3;
         finalmax = finalmax / 3;
         finallow = finallow / 3;
         finallow = abs (finallow);
         finalmax = finalmax / 510;
         finallow = finallow / 510;  
         finalpers = finalmax + finallow;
         finalpers = finalpers*100/2;
         intfinalpers = finalpers;
         if ( intfinalpers >= 100 ){
          intfinalpers = 100;
         }
         Serial.println(intfinalpers);
         low1 = 0;
         low2 = 0;
         low3 = 0;
         max1 = 0;
         max2 = 0;
         max3 = 0;
         finalmax = 0;
         finallow = 0;
         finalpers = 0;
         intfinalpers = 0;
       }
       else if(data=='a'){
         data = 'z'; 
         while(true){
         treat();
         if (data == 'x'){
         break;
         }
         treat();
           if (data == 'x'){
         break;
         }
         treat();
           if (data == 'x'){
         break;
         }
         data = 'z';
         break;
       }
       }
}
void check(double &max0 , double &reading0 , double &prereading0 , double &low0){
    delay(1000);
    timee = millis();
    pretimee = timee + 6000;
    while (timee <= pretimee){
      digitalWrite(ledPin1, HIGH);
      timee = millis();
      prereading0 = analogRead(A0);
      reading0 = prereading0 - 510.5;
      if ( reading0 > max0 ){
        max0 = reading0;
      }
      if ( reading0 < low0){
        low0 = reading0;
      }
      timee = millis();
    }
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    delay(800);
    digitalWrite(ledPin2, LOW); 
}
  void treat(){
   for (int i=0; i <= 10; i++){
      if (Serial.available()){
        data = Serial.read();
      }
        digitalWrite(RELAY_PIN,HIGH);
        delay(600);
        digitalWrite(RELAY_PIN,LOW);
        delay(600);
      if (data == 'x'){
        break;
      }
      } 
  }








