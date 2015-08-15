#define TSL_FREQ_PIN 2 // output use digital pin2 for interrupt
#define TSL_S0	     5
#define TSL_S1	     6
#define TSL_S2	     7
#define TSL_S3       8

 // 1000ms = 1s
#define READ_TM 1000 

unsigned long pulse_cnt = 0;

 // two variables used to track time
unsigned long cur_tm = millis();
unsigned long pre_tm = cur_tm;

// we'll need to access the amount
// of time passed
unsigned int tm_diff = 0;

// need to measure what to divide freq by
// 1x sensitivity = 10,
// 10x sens       = 100,
// 100x sens      = 1000
int calc_sensitivity = 10;

// set our frequency multiplier to a default of 1
// which maps to output frequency scaling of 100x
int freq_mult = 100;


void setup() {

// attach interrupt to pin2, send output pin of TSL230R to arduino 2
// call handler on each rising pulse

 attachInterrupt(0, add_pulse, RISING);

 pinMode(TSL_FREQ_PIN, INPUT);
 pinMode(TSL_S0, OUTPUT);
 pinMode(TSL_S1, OUTPUT);
 pinMode(TSL_S2, OUTPUT);
 pinMode(TSL_S3, OUTPUT);

 digitalWrite(TSL_S0, HIGH);
 digitalWrite(TSL_S1, LOW);
 digitalWrite(TSL_S2, HIGH);
 digitalWrite(TSL_S3, HIGH);
}

void loop() {

  // check the value of the light sensor every READ_TM ms

    // calculate how much time has passed

 pre_tm   = cur_tm;
 cur_tm   = millis();

 if( cur_tm > pre_tm ) {
	tm_diff += cur_tm - pre_tm;
 }
 else if( cur_tm < pre_tm ) {
           // handle overflow and rollover (Arduino 011)
	tm_diff += ( cur_tm + ( 34359737 - pre_tm ));
 } 

   // if enough time has passed to do a new reading...

 if( tm_diff >= READ_TM ) {

       // re-set the ms counter
   tm_diff = 0;

      // get our current frequency reading
   unsigned long frequency = get_tsl_freq();

      // calculate radiant energy
   float uw_cm2 = calc_uwcm2( frequency );

      // calculate illuminance
   float lux    = calc_lux_single( uw_cm2, 0.175 );
print(lux);
 }

}

void set_scaling ( int what ) {

  // set output frequency scaling
  // adjust frequency multiplier and set proper pin values
  // e.g.:
  // scale = 2 == freq_mult = 2
  // scale = 10 == freq_mult = 10
  // scale = 100 == freq_mult = 100

  int pin_2 = HIGH;
  int pin_3 = HIGH;

  switch( what ) {
    case 2:
      pin_3     = LOW;
      freq_mult = 2;
      break;
    case 10:
      pin_2     = LOW;
      freq_mult = 10;
      break;
    case 100:
      freq_mult = 100;
      break;
    default:
        // don't do anything with levels
        // we don't recognize
      return;
  }

    // set the pins to their appropriate levels

  digitalWrite(TSL_S2, pin_2);
  digitalWrite(TSL_S3, pin_3);

  return;
}

unsigned long get_tsl_freq() {

    // we have to scale out the frequency --
    // Scaling on the TSL230R requires us to multiply by a factor
    // to get actual frequency

  unsigned long freq = pulse_cnt * freq_mult;

    // reset the pulse counter

  pulse_cnt = 0;

  return(freq);
}

void add_pulse() {

  // increase pulse count
 pulse_cnt++;
 return;
}

void sensitivity( bool dir ) {

  // adjust sensitivity in 3 steps of 10x either direction

  int pin_0;
  int pin_1;

  if( dir == true ) {

      // increasing sensitivity

      // -- already as high as we can get
    if( calc_sensitivity == 1000 )
      return;

    if( calc_sensitivity == 100 ) {
        // move up to max sensitivity
      pin_0 = true;
      pin_1 = true;
    }
    else {
        // move up to med. sesitivity
      pin_0 = false;
      pin_1 = true;
    }

      // increase sensitivity divider
    calc_sensitivity *= 10;
  }
  else {
      // reducing sensitivity

      // already at lowest setting

    if( calc_sensitivity == 10 )
      return;

    if( calc_sensitivity == 100 ) {
        // move to lowest setting
      pin_0 = true;
      pin_1 = false;
    }
    else {
        // move to medium sensitivity
      pin_0 = false;
      pin_1 = true;
    }

      // reduce sensitivity divider
    calc_sensitivity = calc_sensitivity / 10;
  }

    // make any necessary changes to pin states

 digitalWrite(TSL_S0, pin_0);
 digitalWrite(TSL_S1, pin_1);

 return;
}

float calc_uwatt_cm2(unsigned long freq) {

  // get uW observed - assume 640nm wavelength
  // calc_sensitivity is our divide-by to map to a given signal strength
  // for a given sensitivity (each level of greater sensitivity reduces the signal
  // (uW) by a factor of 10)

  float uw_cm2 = (float) freq / (float) calc_sensitivity;

    // extrapolate into entire cm2 area

  uw_cm2       *= ( (float) 1 / (float) 0.0136 );

  return(uw_cm2);

}

float calc_lux_single(float uw_cm2, float efficiency) {

    // calculate lux (lm/m^2), using standard formula:
    // Xv = Xl * V(l) * Km
    // Xl is W/m^2 (calculate actual receied uW/cm^2, extrapolate from sensor size (0.0136cm^2)
    // to whole cm size, then convert uW to W)
    // V(l) = efficiency function (provided via argument)
    // Km = constant, lm/W @ 555nm = 683 (555nm has efficiency function of nearly 1.0)
    //
    // Only a single wavelength is calculated - you'd better make sure that your
    // source is of a single wavelength...  Otherwise, you should be using
    // calc_lux_gauss() for multiple wavelengths

      // convert to w_m2
  float w_m2 = (u_cm2 / (float) 1000000) * (float) 100;

      // calculate lux
  float lux  = w_m2 * efficiency * (float) 683;

  return(lux);
}


