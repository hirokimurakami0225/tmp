const int PIN_LED  = 2;
const int PIN_RY   = 13;
const int PIN_WDIN = 4;

int g_iCount = 0;

void setup() {
  
  g_iCount = 0;

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_RY, OUTPUT);
  pinMode(PIN_WDIN, INPUT);

  Serial.begin(9600);
  Serial.println( "start" );  
}



void loop() 
{

  int iWd = digitalRead(PIN_WDIN); 
  if ( iWd == 1)
  {
    digitalWrite(PIN_LED, HIGH);
    g_iCount = 0;
  }
  else
  { 
    digitalWrite(PIN_LED, LOW);
    g_iCount++;
  }

  if ( g_iCount > 100)
  {
    digitalWrite(PIN_RY, HIGH);
    delay(2000);
    digitalWrite(PIN_RY, LOW);
    delay(2000);

    g_iCount = 0;
    delay(5000);
  }

  Serial.println(g_iCount);
  delay(100);
}
