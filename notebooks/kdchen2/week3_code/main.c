#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"

//LED stuff
#include <driver/ledc.h>

//ADC stuff
#include "driver/adc.h"
#include "esp_adc_cal.h"


//LED defines
#define LED_PIN 5           // LED connected to GPIO 5
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES LEDC_TIMER_10_BIT // 10-bit resolution (0-1023)
#define LEDC_FREQUENCY 1000             // 1 kHz PWM frequency

//General
#define DELAY_MS        30


void app_main(void)
{
    

    //configure adc
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

    esp_adc_cal_characteristics_t adc1_chars;//calibration
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);

    int adc_value =  adc1_get_raw(ADC1_CHANNEL_0);//set initial value
    uint32_t mV = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_0), &adc1_chars);

    // Configure LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_DUTY_RES,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY
    };
    ledc_timer_config(&ledc_timer);

    // Configure LEDC channel
    ledc_channel_config_t ledc_channel = {
        .gpio_num = LED_PIN,
        .speed_mode = LEDC_MODE,
        .channel = LEDC_CHANNEL,
        .timer_sel = LEDC_TIMER,
        .duty = 0
    };
    ledc_channel_config(&ledc_channel);


    while (1) {
        adc_value = adc1_get_raw(ADC1_CHANNEL_0);
        mV = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_0), &adc1_chars);

        // // Fade in
        // for (int duty = 0; duty <= 1023; duty += 10) {
        //     ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
        //     ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        //     vTaskDelay(50 / portTICK_PERIOD_MS);
        //     //printf("LED duty cycle: %d\n", duty);
        // }
        // // Fade out
        // for (int duty = 1023; duty >= 0; duty -= 10) {
        //     ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
        //     ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        //     vTaskDelay(50 / portTICK_PERIOD_MS);
        //     //printf("LED duty cycle: %d\n", duty);
        // }


        int duty = (int)((1023*adc_value)/4096);
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);

        printf("adc_value: %d, mV: %ld, duty: %d\n", adc_value, mV, duty);

    }
}
