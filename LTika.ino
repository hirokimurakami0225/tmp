int led = 2;
const int PIN_DIGITAL_OUTPUT3 = 32;

void setup() {
  
  pinMode(PIN_DIGITAL_OUTPUT3, OUTPUT);
  pinMode(led, OUTPUT);

   Serial.begin(9600);
     Serial.println( "start" );  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);

  char key;     // 受信データを格納するchar型の変数
  if ( Serial.available() ) {       // 受信データがあるか？
    key = Serial.read();            // 1文字だけ読み込む
    if (key == 'a')
    {
      Serial.println( "reset!");  
      delay(1000);
      digitalWrite(PIN_DIGITAL_OUTPUT3, LOW);
      delay(3000);
      digitalWrite(PIN_DIGITAL_OUTPUT3, HIGH);//esp32の再起動
      delay(3000);

    }
  }

}
