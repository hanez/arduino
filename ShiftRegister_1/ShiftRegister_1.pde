
int pin_led_clock=2;
int pin_led_latch=3;
int pin_led_data=4;

void setup() {
  Serial.begin(9600); //start serial
  pinMode(pin_led_data, OUTPUT);
  pinMode(pin_led_latch, OUTPUT); 
  pinMode(pin_led_clock, OUTPUT);
}

void loop() {
  set_led_states(LOW);
  delay(500);
  set_led_states(HIGH);
  delay(500);
}

void set_led_states(int CMD){
  for (int n=0; n<8; n++) {
    digitalWrite(pin_led_data, CMD); // turn the 'current' led on
    pulse_pin(pin_led_clock); // address the next bit slot
   }
  pulse_pin(pin_led_latch); // when the latch goes from low to high, the data that's been stored to the register's memory gets sent to its output pins
}
 
// Set a pin to low, then high
void pulse_pin(int pin_number){
 digitalWrite(pin_number,LOW);
 digitalWrite(pin_number,HIGH);
}
