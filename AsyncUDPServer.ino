#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "aterm-2feb65-g";
const char * password = "06dd239ee4746";
const IPAddress ip(192,168,3,200);
const IPAddress subnet(255,255,255,0);

AsyncUDP udp;

const int LED_PIN     = 2;
const int SV_PIN      = 13;
const int RST_PIN     = 32;

int m_iCount  = 0;
int m_iCountB = 0;

void Reset()
{
  delay(1000);
  digitalWrite(RST_PIN, LOW);
  delay(3000);
  digitalWrite(RST_PIN, HIGH);//esp32の再起動
  delay(3000);
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(SV_PIN,  OUTPUT);
    pinMode(RST_PIN, OUTPUT);

    Serial.begin(9600);
    Serial.println("Start!"); 

    WiFi.mode(WIFI_STA);                  // WIFI子機モード(ステーション)

    if (!WiFi.config(ip,ip,subnet))
    {
      Serial.println("Failed to configure!");
      delay(5000);
      Reset();
    }

    WiFi.begin(ssid, password);

    int  iCount = 0;
    bool done = true;
    while (done) 
    {
      auto last = millis();
      while (WiFi.status() != WL_CONNECTED && last + 5000 > millis()) 
      {
        delay(500);
      }

      if (WiFi.status() == WL_CONNECTED) 
      {
        done = false;
      } 
      else 
      {
        if ( iCount < 3)
        {
          WiFi.disconnect();
          WiFi.reconnect();
          iCount++;
        }
        else
        {
          Reset();
        }
      }
    }

    if(udp.listen(1234)) 
    {
        udp.onPacket([](AsyncUDPPacket packet) 
        {
          udp.broadcastTo( "PC_UDP_OK",1234, TCPIP_ADAPTER_IF_MAX);
          m_iCount++;
        });
    }
}

// 接続が切れるとリセット
void WifiCheck()
{
  if ((WiFi.status() != WL_CONNECTED)) 
  {
    Reset();
  }
}

// LED点滅
int           m_iLedState    = 0;
unsigned long m_ullLedTimeB  = 0;
void LTika()
{
  unsigned long currentMillis = millis();
  if(currentMillis - m_ullLedTimeB >= 1000)
  {
    if (m_iLedState == 0) 
    {
      digitalWrite(LED_PIN, HIGH);
      m_iLedState = 1;
    }
    else 
    {
      digitalWrite(LED_PIN, LOW);
      m_iLedState = 0;
    }
    m_ullLedTimeB = currentMillis;
  }
}

// ショット
void Shot()
{
  if ( m_iCount != m_iCountB)
  {
      digitalWrite(SV_PIN, HIGH);
      delay(2000);
      digitalWrite(SV_PIN, LOW);
      m_iCountB = m_iCount;
  }
}


void ResetTest()
{
  char key;     // 受信データを格納するchar型の変数
  if ( Serial.available() ) {       // 受信データがあるか？
    key = Serial.read();            // 1文字だけ読み込む
    if (key == 'a')
    {
      Serial.println( "reset!");  
      Reset();
    }
  }
}

void loop()
{
    WifiCheck();
    LTika();
    Shot();
    ResetTest();
}
