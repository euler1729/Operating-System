#include <seven_segment.h>
#include <gpio.h>
#include <stdint.h>

uint32_t module_init(void){
    GPIO_InitTypeDef gpio_init;
    for(uint8_t i = 0;i < 7;i++){
        gpio_init.Pin = 1 << pin_info_table[i].pin;
        gpio_init.Mode = GPIO_MODE_OUTPUT;
        gpio_init.Speed = 0x3U;
        GPIO_Init(pin_info_table[i].gpio,&gpio_init);
    }
    return 0;
}


void print_digit(uint8_t digit){
    for(uint8_t i = 0;i < 7;i++){
        GPIO_WritePin(pin_info_table[i].gpio,
            pin_info_table[i].pin,digit_arr[digit][i]);
    }
}
