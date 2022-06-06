
#include <Adafruit_CircuitPlayground.h>
#define sensorPin A1
long distance = 0;
long duration = 0;
const int analogOutPin = 10; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int thresh = 1000; //set this based on your readings!
int debounce = 100;

bool on = false;
bool touched = false;

void setup() {
  // put your setup code here, to run once:
  //put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  CircuitPlayground.begin();
  on = false;
  pinMode(sensorPin, INPUT);

}
void read_sensor() {
  duration = pulseIn(sensorPin, HIGH);
  distance = duration / 58;
}
void print_data() {
  Serial.print("distance = ");
  Serial.print(distance);
  Serial.println(" cm");

}


void loop() {
  CircuitPlayground.setBrightness(255);//
  duration = pulseIn(sensorPin, HIGH);//
  distance = duration / 58;
  distance = analogRead(sensorPin);
  outputValue = map(distance, 10, 300 , 10, 255);
  //    Serial.print("outputValue"); Serial.println(outputValue);
  //    print_data();
  //  Serial.println(on);
  int t = CircuitPlayground.readCap(A2);
  if (t > thresh && !touched) {
    touched = true;
    if (on) {
      on = false;
    }
    else {
      on = true;
    }
  } else if ( t <= thresh) {
    touched = false;
  }
  if (on) {
    Serial.println(outputValue);
    CircuitPlayground.setPixelColor(0, outputValue,   outputValue,   outputValue);
  } else {
    CircuitPlayground.clearPixels();
  }
  delay(10);


}
