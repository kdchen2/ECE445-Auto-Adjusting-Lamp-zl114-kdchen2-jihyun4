#include "Wire.h"
#include "Adafruit_TCS34725.h"

const int adc0_pin = 36;
int adc0_val = 0;

const int led0_pin = 5;
int led0_duty = 0;

const int led1_pin = 18;
int led1_duty = 0;

int output_val0 = 1200;
int output_val1 = 1200;

//between 0 and 4096
int lux_target0 = 2800;
int lux_target1 = 300;
int temp_target0 = 400;
int temp_target1 = 400;

int counter = 0;
const int sample_sz = 15;
int lux_adc[sample_sz] = {250,250,250,250,250,250,250,250,250,250,250,250,250,250,250};//roughly ambient room light

//value between 0 and 4095 that will be adjusted each loop
float led0_out = 300;
float led1_out = 300;

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_1X);

//right shift values in data array by 1; replace 1st value
void update_arr(int input_arr[], int length, int new_val) {
  for (byte i = 0; i < length-1; i++) {
    input_arr[i + 1] = input_arr[i];
  }
  if (new_val < 100){
    new_val = 100;
  }
  input_arr[0] = new_val;
}

//get avg of values in an array
float get_avg(int input_arr[], int length){
  long sum = 0L;
  for (byte i = 0; i < length; i++) {
    sum += input_arr[i];
  }
  return ((float)sum)/length;
}

//checks if num is within tolerance of an average
//will return num if it is, otherwise the low or high value within tolerance
float filter_val(int num, float avg, float tolerance){
  float rtn_val = (float)num;
  float increment = tolerance*avg;
  float high = avg + increment;
  float low = avg - increment;
  if (num > high){
    rtn_val = high;
  }
  else if (num < low){
    rtn_val = low;
  }

  return rtn_val;
}

void setup(void) {
  Serial.begin(9600);
  pinMode(led0_pin, OUTPUT);
  pinMode(led1_pin, OUTPUT);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  // if(counter > 512){
  //   counter = 0;
  // }
  // counter += 1;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  // lux = tcs.calculateLux(r, g, b);

 


  adc0_val = analogRead(adc0_pin);
  
  if (adc0_val*2 < 4095){
    adc0_val *= 2;
  }
  else if (adc0_val*2 >= 4095){
    adc0_val = 4095;
  }
  //Serial.println(adc0_val);

  

  int new_reading = (int)filter_val(adc0_val, get_avg(lux_adc, sample_sz), 0.02);//0.02
  update_arr(lux_adc, sample_sz, new_reading);
  for(int i = 0; i < sample_sz; i++)
  {
    Serial.print(lux_adc[i]); Serial.print("|");
  }
  Serial.println("");

  
  led0_duty = (int)((255*get_avg(lux_adc, sample_sz))/4095);
  analogWrite(led0_pin, led0_duty);

  led1_duty = (int)((255*get_avg(lux_adc, sample_sz))/4095);
  analogWrite(led1_pin, led1_duty);

  // Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  // Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  // Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.println(" ");
  // if (counter%10 == 0){//print log
  //   //Serial.print("Color Temp: "); Serial.print(colorTemp, DEC);
  //   //Serial.print(" K - ");
  //   //Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  //   // Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //   // Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //   // Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //   // Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  //   Serial.println(" ");

  //   Serial.print(led0_duty); Serial.print("| "); Serial.println(adc0_val);
  // }

  // Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  // Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  // Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.println(" "); Serial.print(led0_duty); Serial.print("| "); Serial.println(adc0_val);

  

  //delay(1);
}