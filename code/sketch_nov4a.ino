#include "Wire.h"
#include "Adafruit_TCS34725.h"

const int pot0_pin = 8;//j7 far pot
const int pot1_pin = 9;//j6 middle pot
const int mode_sw = 10; //j3 switch gpio 10
// const float SENSOR_TOLERANCE = 0.2;
// const float LED_PWM_TOLERANCE = 0.05;
const int I2C_SCL = 17;//22 //17
const int I2C_SDA = 21;//21

float SENSOR_TOLERANCE = 0.05;
float LED_PWM_TOLERANCE = 0.02;
float adj_tolerance = 0.02;

int target_lux = 0;
int target_temp = 0;


const int adc0_pin = 4;//36
int lux_adc_val = 0;
int tuned_lux = 0;

float temp_val = 0;

const int led0_pin = 18;//5
float led0_duty = 0;

const int led1_pin = 5;//18
float led1_duty = 0;

int output_val0 = 1200;
int output_val1 = 1200;

int counter = 0;
const int sample_sz = 15;
float lux_data_arr[sample_sz] = {250,250,250,250,250,250,250,250,250,250,250,250,250,250,250};//roughly ambient room light
float temp_data_arr[sample_sz] = {2048,2048,2048,20480,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048,2048};//roughly ambient room light


float led0_duty_arr[sample_sz] = {400,400,400,400,400,400,400,400,400,400,400,400,400,4004,400};
float led1_duty_arr[sample_sz] = {400,400,400,400,400,400,400,400,400,400,400,400,400,4004,400};


/* Initialise with specific int time and gain values */
TwoWire I2CTCS = TwoWire(0);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_180MS, TCS34725_GAIN_1X);

//right shift values in data array by 1; replace 1st value
void update_arr(float input_arr[], int length, float new_val) {
  for (byte i = 0; i < length-1; i++) {
    input_arr[i + 1] = input_arr[i];
  }
  if (new_val < 20){
    new_val = 20;
  }
  input_arr[0] = new_val;
}

//get avg of values in an array
float get_avg(float input_arr[], int length){
  float sum = 0;
  for (byte i = 0; i < length; i++) {
    sum += input_arr[i];
  }
  return sum/length;
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

int limit_output(int input, int limit){
  int rtn_val = input;
  if (input > limit){
    rtn_val = limit;
  }
  return rtn_val;
}

//lux_sensor_val is between 0-4095, 0 = high lux/ bright environment
//limit_coeff becomes larger in brighter environments, it is used to gamma tune adj_increment
//limit_coeff becomes very small in dark environments
//brighter environment -> limit_coeff2 becomes small; both limits become lower

//target_lux affects lux_limit_shift, which is a linear shift in values between 0-4095 in a 1948 wide window
//a smaller target lux makes both the low and high limit higher

void adjust(float target_temp, float target_lux, float temp_sensor_val, float lux_sensor_val, float *curr_output, float tolerance){
  //float feedback = 0;
  
  float lux_limit_shift = 2047*((100+target_lux)/4095);
  float low_limit = lux_limit_shift;
  float high_limit = 2048 + lux_limit_shift;
  float limit_coeff2 = (4095-lux_sensor_val)/4095;
  float limit_coeff = (lux_sensor_val+100)/4095;

  float target_increment = target_temp*tolerance*0.8;
  float adj_increment = limit_coeff*(4095-temp_sensor_val)*tolerance;
  //float adj_increment2 = lux_sensor_val*tolerance;

  

  if ((lux_sensor_val > target_lux - target_lux*tolerance) && ((*curr_output - adj_increment) >= limit_coeff2*low_limit)){//limit_coeff2*
    *curr_output -= adj_increment;
  }
  else if ((lux_sensor_val < target_lux + target_lux*tolerance) && ((*curr_output + adj_increment) < limit_coeff2*high_limit)){//
    *curr_output += adj_increment;
  }
  if ((temp_sensor_val > target_temp - target_increment) && ((*curr_output - adj_increment) >= limit_coeff2*low_limit)){//limit_coeff2*
    *curr_output -= adj_increment;
  }
  else if ((temp_sensor_val < target_temp + target_increment) && ((*curr_output + adj_increment) < limit_coeff2*high_limit)){//limit_coeff2*
    *curr_output += adj_increment;
  }

  // if ((*curr_output + adj_increment) < limit_coeff2*high_limit){
  //   *curr_output += adj_increment;
  // }
  // else if ((*curr_output - adj_increment) >= limit_coeff2*low_limit){
  //   *curr_output -= adj_increment;
  // }

  //*curr_output += feedback;
}

//approximate temperature from RGB, naive implementation
//return a float from 0 to 4095, 0 being cool, 4095 being warm
//less accurate in dim conditions with small rgb values
float get_temp(int r, int g, int b){
  float temp = 2048;
  float offset = 2047*(float)(r-b)/(r+b+1);
  return temp + offset;
}

int tune_lux_OPT(int value){
  float temp_val = (float)value;
  temp_val *= (4095/2875);
  if (temp_val > 4095){
    temp_val = 4095;
  }
  return 4095-(int)temp_val;
}

int tune_lux_PR(int value){
  if (value*2 < 4095){
    value *= 2;
  }
  else if (value*2 >= 4095){
    value = 4095;
  }
  return 4095-value;
}


void setup(void) {
  Serial.begin(921600);
  pinMode(led0_pin, OUTPUT);
  pinMode(led1_pin, OUTPUT);

  I2CTCS.begin(I2C_SDA, I2C_SCL, 100000);
  if (tcs.begin(0x29, &I2CTCS)) {//
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

}

void loop(void) {
  //===============================get sensor data==============================
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  // r = 6600;
  // g = 6600;
  // b = 6600;
  // c = 6600;
  //colorTemp = tcs.calculateColorTemperature(r, g, b);
  // lux = tcs.calculateLux(r, g, b);
  temp_val = get_temp(r, g, b);

  lux_adc_val = analogRead(adc0_pin);
  

  //========================================================================
  //temporarily manually set temp and lux
  if(analogRead(mode_sw) > 1500){
    target_lux = analogRead(pot0_pin);
    target_temp = analogRead(pot1_pin);//middle
  }
  else{
    SENSOR_TOLERANCE = 0.2*(analogRead(pot0_pin)/4095);
    adj_tolerance = 0.05*(analogRead(pot1_pin)/4095);
  }
  
  // target_lux = 4095;
  // target_temp = 2500;


  
  //======================filter sensor data===========================================================
  tuned_lux = tune_lux_PR(lux_adc_val);//tune_lux_OPT
  float new_lux_reading = filter_val(tuned_lux, get_avg(lux_data_arr, sample_sz), SENSOR_TOLERANCE);//0.02
  update_arr(lux_data_arr, sample_sz, new_lux_reading);

  float new_temp_reading = filter_val(temp_val, get_avg(temp_data_arr, sample_sz), 2*SENSOR_TOLERANCE);//0.02
  update_arr(temp_data_arr, sample_sz, new_temp_reading);


  //=========================================set LED PWM=================================
  adjust(4096-(float)target_temp, (float)target_lux, 4096-get_avg(temp_data_arr, sample_sz), get_avg(lux_data_arr, sample_sz), &led0_duty, adj_tolerance);
  adjust((float)target_temp, (float)target_lux, get_avg(temp_data_arr, sample_sz), get_avg(lux_data_arr, sample_sz), &led1_duty, adj_tolerance);

  //===========================================filter and update LED PWM arrays===========================
  float new_led0_duty = filter_val(led0_duty, get_avg(led0_duty_arr, sample_sz), LED_PWM_TOLERANCE);//0.02
  update_arr(led0_duty_arr, sample_sz, new_led0_duty);

  float new_led1_duty = filter_val(led1_duty, get_avg(led1_duty_arr, sample_sz), LED_PWM_TOLERANCE);//0.02
  update_arr(led1_duty_arr, sample_sz, new_led1_duty);

  //===========================================drive LEDs==================================
  analogWrite(led1_pin, limit_output((int)((255*get_avg(led1_duty_arr, sample_sz))/4095), 255));//warm led
  analogWrite(led0_pin, limit_output((int)((255*get_avg(led0_duty_arr, sample_sz))/4095), 255));//cool led

  // analogWrite(led1_pin, 255);//warm led
  // analogWrite(led0_pin, 255);//cool led

  if(counter > 512){
    counter = 0;
  }
  counter += 1;
  if (counter%4 == 0){
    Serial.print("Target Lux: "); Serial.print(target_lux); Serial.print("| Target Temp: "); Serial.print(target_temp);
    Serial.println("");

    Serial.print("lux: "); Serial.print(get_avg(lux_data_arr, sample_sz));
    // for(int i = 0; i < sample_sz; i++)
    // {
    //   Serial.print(lux_data_arr[i]); Serial.print("|");
    // }
    Serial.println("");

    Serial.print("temp: "); Serial.print(get_avg(temp_data_arr, sample_sz));
    // for(int i = 0; i < sample_sz; i++)
    // {
    //   Serial.print(temp_data_arr[i]); Serial.print("|");
    // }
    Serial.println("");
    Serial.print("LED0: "); Serial.print(led0_duty); Serial.print("| LED1: "); Serial.print(led1_duty);
    //Serial.println("Tuned Lux: "); Serial.print(tuned_lux);
    Serial.println("");
    Serial.println("");
  }
  

  

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

  //   Serial.print(led0_duty); Serial.print("| "); Serial.println(lux_adc_val);
  // }

  // Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  // Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  // Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  // Serial.println(" "); Serial.print(led0_duty); Serial.print("| "); Serial.println(lux_adc_val);

  

  //delay(1);
}