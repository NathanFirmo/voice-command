#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"  
#include <Tone.h>

VR myVR(2, 3);

/**
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/

uint8_t records[7];
uint8_t buf[64];

int Led = 13;
int Rele1 = 7;
int Rele2 = 6;
int Rele3 = 5;
int Rele4 = 4;

int l1 = 10;
int l2 = 11;
int l3 = 12;
int l4 = A3;
int l5 = A4;
int l6 = A5;

int botao_carregar = A1;
int botao_treinar = A2;
int comando_sequencia_treino;

int ldrPin = A0;
int ldrValor = 0;

#define Comando1    (1)
#define Comando2   (2)
#define Comando3    (3)
#define Comando4   (4)
#define Comando5    (5)
#define Comando6    (6)
#define Comando7    (7)

Tone tone1;

#define OCTAVE_OFFSET 0


int notes[] = { 0,
                NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
                NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
                NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
                NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
              };

char *song1 = "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
char *song2 = "PinkPanther:d=4,o=5,b=160:8d#,8e,2p,8f#,8g,2p,8d#,8e,16p,8f#,8g,16p,8c6,8b,16p,8d#,8e,16p,8b,2a#,2p,16a,16g,16e,16d,2e";
char *song3 = "Coca-cola:d=4,o=5,b=125:8f#6,8f#6,8f#6,8f#6,g6,8f#6,e6,8e6,8a6,f#6,d6,2p";
char *song4 = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";

void printSignature(uint8_t *buf, int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (buf[i] > 0x19 && buf[i] < 0x7F) {
      Serial.write(buf[i]);
    }
    else {
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if (buf[0] == 0xFF) {
    Serial.print("NONE");
  }
  else if (buf[0] & 0x80) {
    Serial.print("UG ");
    Serial.print(buf[0] & (~0x80), DEC);
  }
  else {
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if (buf[3] > 0) {
    printSignature(buf + 4, buf[3]);
  }
  else {
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  tone1.begin(9);

  myVR.begin(9600);
  Serial.begin(115200);

  pinMode(botao_treinar, INPUT_PULLUP);
  pinMode(botao_carregar, INPUT_PULLUP);

  pinMode(Led, OUTPUT);
  pinMode(Rele1, OUTPUT);
  pinMode(Rele2, OUTPUT);
  pinMode(Rele3, OUTPUT);
  pinMode(Rele4, OUTPUT);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(l5, OUTPUT);
  pinMode(l6, OUTPUT);

  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  digitalWrite(l4, LOW);
  digitalWrite(l5, LOW);
  digitalWrite(l6, LOW);

  digitalWrite(Rele1, HIGH);
  digitalWrite(Rele2, HIGH);
  digitalWrite(Rele3, HIGH);
  digitalWrite(Rele4, HIGH);

  if (myVR.clear() == 0) {
    Serial.println("Recognizer cleared.");
  } else {
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while (1);
  }

  if (myVR.load((uint8_t)Comando1) >= 0) {
    Serial.println("Comando1 loaded");
  }

  if (myVR.load((uint8_t)Comando2) >= 0) {
    Serial.println("Comando2 loaded");
  }

  if (myVR.load((uint8_t)Comando3) >= 0) {
    Serial.println("Comando3 loaded");
  }

  if (myVR.load((uint8_t)Comando4) >= 0) {
    Serial.println("Comando4 loaded");
  }

  if (myVR.load((uint8_t)Comando5) >= 0) {
    Serial.println("Comando5 loaded");
  }

  if (myVR.load((uint8_t)Comando6) >= 0) {
    Serial.println("Comando6 loaded");
  }

  if (myVR.load((uint8_t)Comando7) >= 0) {
    Serial.println("Comando7 loaded");
  }
}

#define isdigit(n) (n >= '0' && n <= '9')


void play_rtttl(char *p)
{
  byte default_dur = 4;
  byte default_oct = 6;
  int bpm = 63;
  int num;
  long wholenote;
  long duration;
  byte note;
  byte scale;

  while (*p != ':') p++;
  p++;

  // get default duration
  if (*p == 'd')
  {
    p++; p++;
    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    if (num > 0) default_dur = num;
    p++;
  }

  Serial.print("ddur: "); Serial.println(default_dur, 10);

  if (*p == 'o')
  {
    p++; p++;
    if (num >= 3 && num <= 7) default_oct = num;
    p++;
  }

  Serial.print("doct: "); Serial.println(default_oct, 10);

  // get BPM
  if (*p == 'b')
  {
    p++; p++;
    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }
    bpm = num;
    p++;
  }

  Serial.print("bpm: "); Serial.println(bpm, 10);

  wholenote = (60 * 1000L / bpm) * 4;  

  Serial.print("wn: "); Serial.println(wholenote, 10);


  while (*p)
  {
    num = 0;
    while (isdigit(*p))
    {
      num = (num * 10) + (*p++ - '0');
    }

    if (num) duration = wholenote / num;
    else duration = wholenote / default_dur;

    note = 0;

    switch (*p)
    {
      case 'c':
        note = 1;
        break;
      case 'd':
        note = 3;
        break;
      case 'e':
        note = 5;
        break;
      case 'f':
        note = 6;
        break;
      case 'g':
        note = 8;
        break;
      case 'a':
        note = 10;
        break;
      case 'b':
        note = 12;
        break;
      case 'p':
      default:
        note = 0;
    }
    p++;

    if (*p == '#')
    {
      note++;
      p++;
    }

    if (*p == '.')
    {
      duration += duration / 2;
      p++;
    }

    if (isdigit(*p))
    {
      scale = *p - '0';
      p++;
    }
    else
    {
      scale = default_oct;
    }

    scale += OCTAVE_OFFSET;

    if (*p == ',')
      p++;

    if (note)
    {
      Serial.print("Playing: ");
      Serial.print(scale, 10); Serial.print(' ');
      Serial.print(note, 10); Serial.print(" (");
      Serial.print(notes[(scale - 4) * 12 + note], 10);
      Serial.print(") ");
      Serial.println(duration, 10);
      tone1.play(notes[(scale - 4) * 12 + note]);
      delay(duration);
      tone1.stop();
    }
    else
    {
      Serial.print("Pausing: ");
      Serial.println(duration, 10);
      delay(duration);
    }
  }
}

void loop()
{
  //Alternar e carregar os comandos
  switch (comando_sequencia_treino)
  {
    case 1:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      digitalWrite(l6, HIGH);
      break;
    case 2:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, HIGH);
      digitalWrite(l6, LOW);
      break;
    case 3:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, HIGH);
      digitalWrite(l5, LOW);
      digitalWrite(l6, LOW);
      break;
    case 4:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, HIGH);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      digitalWrite(l6, LOW);
      break;
    case 5:
      digitalWrite(l1, LOW);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      digitalWrite(l6, LOW);
      break;
    case 6:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      digitalWrite(l6, LOW);
      break;
    case 7:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, HIGH);
      digitalWrite(l4, HIGH);
      digitalWrite(l5, HIGH);
      digitalWrite(l6, HIGH);
      break;
  }

  if (digitalRead(botao_carregar) == LOW)
  {
    delay(100);
    if (comando_sequencia_treino < 7) {
      comando_sequencia_treino += 1; ;
    }
    else {
      comando_sequencia_treino = 1;
    }
    Serial.print("Comando_sequencia_treino:");
    Serial.println(comando_sequencia_treino);
    // Carrega os comandos

    if (myVR.clear() == 0) {
      Serial.println("Recognizer cleared.");
    } else {
      Serial.println("Not find VoiceRecognitionModule.");
      Serial.println("Please check connection and restart Arduino.");
      while (1);
    }


    if (myVR.load((uint8_t)Comando1) >= 0) {
      Serial.println("Comando1 loaded");
    }

    if (myVR.load((uint8_t)Comando2) >= 0) {
      Serial.println("Comando2 loaded");
    }

    if (myVR.load((uint8_t)Comando3) >= 0) {
      Serial.println("Comando3 loaded");
    }

    if (myVR.load((uint8_t)Comando4) >= 0) {
      Serial.println("Comando4 loaded");
    }

    if (myVR.load((uint8_t)Comando5) >= 0) {
      Serial.println("Comando5 loaded");
    }

    if (myVR.load((uint8_t)Comando6) >= 0) {
      Serial.println("Comando6 loaded");
    }

    if (myVR.load((uint8_t)Comando7) >= 0) {
      Serial.println("Comando7 loaded");
    }
  }

  // Treinar comando x
  if (digitalRead(botao_treinar) == LOW)
  {
    delay(100);
    switch (comando_sequencia_treino)
    {
      case 1:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x01);
        myVR.write(0x0A);
        break;
      case 2:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x02);
        myVR.write(0x0A);
      case 3:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x03);
        myVR.write(0x0A);
        break;
      case 4:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x04);
        myVR.write(0x0A);
        break;
      case 5:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x05);
        myVR.write(0x0A);
        break;
      case 6:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x06);
        myVR.write(0x0A);
        break;
      case 7:
        myVR.write(0xAA);
        myVR.write(0x03);
        myVR.write(0x20);
        myVR.write(0x07);
        myVR.write(0x0A);
        break;
    }
  }

  // Execução dos comandos
  int ret;
  ret = myVR.recognize(buf, 50);
  if (ret > 0) {
    switch (buf[1]) {
      case Comando1:
        /** turn on LED */
        digitalWrite(Rele1, digitalRead(Rele1) ^ 1);
        break;
      case Comando2:
        /** turn off LED*/
        digitalWrite(Rele2, digitalRead(Rele2) ^ 1);
        break;
      case Comando3:
        /** turn on LED */
        digitalWrite(Rele3, digitalRead(Rele3) ^ 1);
        break;
      case Comando4:
        /** turn off LED*/
        break;
      case Comando5:
        /** turn off LED*/
        digitalWrite(Led, digitalRead(Led) ^ 1);
        break;
      case Comando6:
        /** turn off LED*/
        play_rtttl(song1);
        Serial.println("Done.");
        while (0);
        delay(1000);
        play_rtttl(song2);
        Serial.println("Done.");
        while (0);
        delay(1000);
        play_rtttl(song3);
        Serial.println("Done.");
        while (0);
        delay(1000);
        play_rtttl(song4);
        Serial.println("Done.");
        while (0);
        delay(1000);
        break;
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
  
  ///ler o valor do LDR
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  //se o valor lido for maior que 500, liga o led
  if (ldrValor >= 200) digitalWrite(Rele4, LOW);
  // senão, apaga o led
  else digitalWrite(Rele4, HIGH);

  delay(2);
}
