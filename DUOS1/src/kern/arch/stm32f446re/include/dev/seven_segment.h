#ifndef __SEVEN_SEGMENT_H
#define __SEVEN_SEGMENT_H

#include <gpio.h>
#include <stdint.h>


struct LED_PIN_INFO {
    GPIO_TypeDef* gpio;
    uint16_t pin;
};

static struct LED_PIN_INFO pin_info_table[7] = {
    {GPIOA,5}, //a
    {GPIOA,6}, //b
    {GPIOA,7}, //c
    {GPIOA,8}, //d
    {GPIOA,9}, //e
    {GPIOA,10}, //f
    {GPIOB,1}, //g
};

static uint8_t digit_arr[10][7] = {
    // a  b  c  d  e  f  g
    { 1, 1, 1, 1, 1, 1, 0 }, // 0
    { 0, 1, 1, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1 }, // 2
    { 1, 1, 1, 1, 0, 0, 1 }, // 3
    { 0, 1, 1, 0, 0, 1, 1 }, // 4
    { 1, 0, 1, 1, 0, 1, 1 }, // 5
    { 1, 0, 1, 1, 1, 1, 1 }, // 6
    { 1, 1, 1, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1 }, // 8
    { 1, 1, 1, 1, 0, 1, 1 }  // 9
};

uint32_t module_init(void);
void module_exit(void);
void print_digit(uint8_t digit);

#endif