const int PIN_LED = 2;
const int PIN_WD  = 4;

void setup() {
  
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_WD, OUTPUT);

  Serial.begin(9600);
  Serial.println( "start" );  
}

void loop()
 {

  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_WD, HIGH);
  delay(1000);
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_WD, LOW);
  delay(1000);
}
