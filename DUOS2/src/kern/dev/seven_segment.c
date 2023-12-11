#include "seven_segment.h"
#include "gpio.h"
#include <kstdio.h>
void test()
{
      GPIO_InitTypeDef GpioInit;
      GpioInit.Pin = GPIO_PIN_0;
      GpioInit.Mode = GPIO_MODE_OUTPUT_PP;
      GpioInit.Speed = GPIO_SPEED_FREQ_HIGH;
      GPIO_Init(GPIOA, &GpioInit);
      GpioInit.Pin = GPIO_PIN_1;
      GPIO_Init(GPIOA, &GpioInit);
      GpioInit.Pin = GPIO_PIN_4;
      GPIO_Init(GPIOA, &GpioInit);
      GpioInit.Pin = GPIO_PIN_5;
      GPIO_Init(GPIOA, &GpioInit);
      GpioInit.Pin = GPIO_PIN_6;
      GPIO_Init(GPIOA, &GpioInit);
      GpioInit.Pin = GPIO_PIN_7;
      GPIO_Init(GPIOA, &GpioInit);
      GpioInit.Pin = GPIO_PIN_8;
      GPIO_Init(GPIOA, &GpioInit);
      GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
      GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
      GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
      GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
      GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
      GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
      GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
}
void reset()
{

      GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
      GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
      GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
      GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
      GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
      GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}
void LedMatrix(int num)
{
      test();
      reset();
      if (num == 1)
      {
            int n[3][3] = {
                {0, 0, 1},
                {0, 0, 0},
                {0, 0, 1}};
            ledArray(n);
      }
      else if (num == 2)
      {
            int n[3][3] = {
                {0, 1, 1},
                {0, 1, 0},
                {1, 1, 0}};
            ledArray(n);
      }
      else if (num == 3)
      {
            int n[3][3] = {
                {0, 1, 1},
                {0, 1, 0},
                {0, 1, 1}};
            ledArray(n);
      }
      else if (num == 4)
      {
            int n[3][3] = {
                {1, 0, 1},
                {0, 1, 0},
                {0, 0, 1}};
            ledArray(n);
      }
      else if (num == 5)
      {
            int n[3][3] = {
                {1, 1, 0},
                {0, 1, 0},
                {0, 1, 1}};
            ledArray(n);
      }
      else if (num == 6)
      {
            int n[3][3] = {
                {1, 1, 0},
                {0, 1, 0},
                {1, 1, 1}};
            ledArray(n);
      }
      else if (num == 7)
      {
            int n[3][3] = {
                {0, 1, 1},
                {0, 0, 0},
                {0, 0, 1}};
            ledArray(n);
      }
      else if (num == 8)
      {
            int n[3][3] = {
                {1, 1, 1},
                {0, 1, 0},
                {1, 1, 1}};
            ledArray(n);
      }
      else if (num == 9)
      {
            int n[3][3] = {
                {1, 1, 1},
                {0, 1, 0},
                {0, 1, 1}};
            ledArray(n);
      }
      else if (num == 0)
      {
            int n[3][3] = {
                {1, 1, 1},
                {0, 0, 0},
                {1, 1, 1}};
            ledArray(n);
      }
      else
            return;
}

void ledArray(int n[3][3])
{
      for (int i = 0; i < 3; i++)
      {
            for (int j = 0; j < 3; j++)
            {
                  if (n[i][j] == 1)
                  {
                        if (i == 0 && j == 0)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
                        }
                        else if (i == 0 && j == 1)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
                        }
                        else if (i == 0 && j == 2)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
                        }

                        else if (i == 1 && j == 1)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
                        }

                        else if (i == 2 && j == 0)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
                        }

                        else if (i == 2 && j == 1)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
                        }

                        else if (i == 2 && j == 2)
                        {

                              GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
                        }
                  }
            }
      }
}