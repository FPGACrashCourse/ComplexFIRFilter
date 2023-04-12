/**
 * @file complexFIR.h
 * @author Alex Stepko (axstepko.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INCLUDES
#define INCLUDES
#include <stdio.h>


#endif // INCLUDES

#ifndef DEFINES
#define DEFINES

void fpga417_fir(int* data, int* filter, int length);
void fir(int input, int filter[3], int *output);

#endif // DEFINES
