
#define VERSION "V1.0.0"

#define MORSE_CW_SPEED 20
#define TX_DELAY 500

#define GPIO_SQL   2
#define GPIO_PTT   7
#define GPIO_PWM  11
#define GPIO_LED  12

/** FSM states */
#define IDLE            0
#define WAIT_SQL_OFF    1
#define SEND_ID         2
#define WAIT_ID_PERIOD  3

/** FSM  struct */
typedef struct {
  byte  output;
  byte  next[2];
  unsigned long wait;
} fsm_t;

/** FSM */
const fsm_t FSM[] = {
  { 0, {           IDLE,   WAIT_SQL_OFF },       2000 }, // IDLE
  { 0, {        SEND_ID,   WAIT_SQL_OFF },        200 }, // WAIT_SQL_OFF
  { 1, { WAIT_ID_PERIOD, WAIT_ID_PERIOD },        300 }, // SEND_ID
  { 0, {           IDLE,   WAIT_SQL_OFF },     600000 }  // WAIT_ID_PERIOD
};
