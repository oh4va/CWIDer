#include <Morse.h>
#include "CWIDer.h"

const char call[] = "DE OH4SSV D";
byte state = IDLE;
char c;
Morse morse(GPIO_PWM, MORSE_CW_SPEED, 1);

void setup() {
  pinMode(GPIO_SQL, INPUT_PULLUP);
  pinMode(GPIO_PTT, OUTPUT);
  pinMode(GPIO_LED, OUTPUT);
  pinMode(GPIO_PWM, OUTPUT);

  analogWrite(GPIO_PWM, 0);
  digitalWrite(GPIO_LED, HIGH);
  digitalWrite(GPIO_PTT, LOW);

  delay(3000);
  digitalWrite(GPIO_LED, LOW);
}

void loop() {

  digitalWrite(GPIO_PTT, FSM[state].output);
  
  switch (state) {
    case IDLE:
      digitalWrite(GPIO_LED, LOW);
      break;
    case WAIT_SQL_OFF:
      digitalWrite(GPIO_LED, !digitalRead(GPIO_LED));
      break;
    case SEND_ID:
      digitalWrite(GPIO_LED, HIGH);
      delay(TX_DELAY);
      for (int i = 0; i < sizeof(call) - 1; i++)
      {
        c = call[i];
        morse.send(c);
      }
      break;
    case WAIT_ID_PERIOD:
      digitalWrite(GPIO_LED, LOW);
      break;
    default:
      break;
  }

  delay(FSM[state].wait);
  state = FSM[state].next[!digitalRead(GPIO_SQL)];
}
