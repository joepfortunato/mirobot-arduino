#ifndef Mirobot_h
#define Mirobot_h

#include "Arduino.h"
#include "lib/HotStepper.h"
#include "lib/CmdProcessor.h"
#include <EEPROM.h>

#define STEPS_PER_TURN    2048.0

#define CIRCUMFERENCE_MM_V1  251.3
#define WHEEL_DISTANCE_V1    126.0
#define PENUP_DELAY_V1 1200
#define PENDOWN_DELAY_V1 2000

#define CIRCUMFERENCE_MM_V2  256
#define WHEEL_DISTANCE_V2    121.0
#define PENUP_DELAY_V2 2000
#define PENDOWN_DELAY_V2 1000

#define STEPS_PER_MM_V1      STEPS_PER_TURN / CIRCUMFERENCE_MM_V1
#define STEPS_PER_DEGREE_V1  ((WHEEL_DISTANCE_V1 * 3.1416) / 360) * STEPS_PER_MM_V1
#define STEPS_PER_MM_V2      STEPS_PER_TURN / CIRCUMFERENCE_MM_V2
#define STEPS_PER_DEGREE_V2  ((WHEEL_DISTANCE_V2 * 3.1416) / 360) * STEPS_PER_MM_V2

#define STATUS_LED 13

#define MIROBOT_VERSION "2.0.2"

#define MAGIC_BYTE_1 0xF0
#define MAGIC_BYTE_2 0x0D

#define SERVO_PIN 3
#define SERVO_PULSES 15

#define SPEAKER_PIN 9
#define NOTE_C4  262

#define LEFT_LINE_SENSOR  A0
#define RIGHT_LINE_SENSOR A1

#define LEFT_COLLIDE_SENSOR  A3
#define RIGHT_COLLIDE_SENSOR A2

typedef enum {UP, DOWN} penState_t;

typedef enum {NORMAL, RIGHT_REVERSE, RIGHT_TURN, LEFT_REVERSE, LEFT_TURN} collideState_t;

struct HwVersion {
  byte major;
  byte minor;
};

class Mirobot {
  public:
    Mirobot();
    void setup();
    void setup(Stream &s);
    void forward(int distance);
    void back(int distance);
    void right(int angle);
    void left(int angle);
    void penup();
    void pendown();
    void pause();
    void resume();
    void stop();
    void reset();
    void follow();
    int  followState();
    void collide();
    void collideState(char &state);
    void beep(int);
    void setHwVersion(char&);
    boolean ready();
    void process();
    HwVersion hwVersion;
    boolean blocking;
    boolean collideNotify;
    boolean followNotify;
    void version(char);
  private:
    void wait();
    void followHandler();
    void collideHandler();
    void ledHandler();
    void servoHandler();
    void autoHandler();
    void sensorNotifier();
    void checkState();
    void initHwVersion();
    char lastCollideState;
    int lastFollowState;
    collideState_t _collideState;
    unsigned long lastLedChange;
    Mirobot& self() { return *this; }
    penState_t penState;
    void setPenState(penState_t);
    void takeUpSlack(byte, byte);
    unsigned long next_servo_pulse;
    unsigned char servo_pulses_left;
    boolean paused;
    boolean following;
    boolean colliding;
    int steps_per_mm;
    int steps_per_degree;
    int penup_delay;
    int pendown_delay;
    int slackSteps;
    long beepComplete;
};

#endif