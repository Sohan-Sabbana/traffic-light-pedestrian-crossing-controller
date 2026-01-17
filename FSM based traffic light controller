const int red1    = 3;
const int yellow1 = 4;
const int green1  = 5;

const int red2    = 8;
const int green2  = 9;

const int pushButton = 13;

const unsigned long green_time  = 10000;
const unsigned long yellow_time = 3000;
const unsigned long red_time    = 10000;

enum TrafficState {
  road1_green,
  road1_yellow,
  all_red,
  road2_green,
  road2_yellow
};

TrafficState currentState = road1_green;

unsigned long state_startTime = 0;
volatile bool pedestrianReq = false;

void pedestrianISR() {
  pedestrianReq = true;
}

void setup() {
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);

  pinMode(pushButton, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(pushButton),
    pedestrianISR,
    FALLING
  );

  Serial.begin(9600);
  state_startTime = millis();
}

void setLights(bool r1r, bool r1y, bool r1g,
               bool r2r, bool r2g) {
  digitalWrite(red1, r1r);
  digitalWrite(yellow1, r1y);
  digitalWrite(green1, r1g);
  digitalWrite(red2, r2r);
  digitalWrite(green2, r2g);
}

void loop() {
  unsigned long now = millis();

  switch (currentState) {

    case road1_green:
      setLights(LOW, LOW, HIGH, HIGH, LOW);
      if ((now - state_startTime >= green_time) || pedestrianReq) {
        pedestrianReq = false;
        currentState = road1_yellow;
        state_startTime = now;
        Serial.println("Road1 -> Yellow");
      }
      break;

    case road1_yellow:
      setLights(LOW, HIGH, LOW, HIGH, LOW);
      if (now - state_startTime >= yellow_time) {
        currentState = all_red;
        state_startTime = now;
        Serial.println("All Red");
      }
      break;

    case all_red:
      setLights(HIGH, LOW, LOW, HIGH, LOW);
      if (now - state_startTime >= red_time) {
        currentState = road2_green;
        state_startTime = now;
        Serial.println("Road2 -> Green");
      }
      break;

    case road2_green:
      setLights(HIGH, LOW, LOW, LOW, HIGH);
      if (now - state_startTime >= green_time) {
        currentState = road2_yellow;
        state_startTime = now;
        Serial.println("Road2 -> Yellow");
      }
      break;

    case road2_yellow:
      setLights(HIGH, HIGH, LOW, HIGH, LOW);
      if (now - state_startTime >= yellow_time) {
        currentState = road1_green;
        state_startTime = now;
        Serial.println("Road1 -> Green");
      }
      break;
  }
}
