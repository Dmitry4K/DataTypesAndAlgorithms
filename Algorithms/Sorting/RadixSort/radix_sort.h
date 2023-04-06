#pragma once
#include<cmath>
const unsigned int BIT_SIZE = sizeof(int) * 8;//32 бита
const unsigned int PART_SIZE = (unsigned int)log2(BIT_SIZE);//5 бит
const unsigned int PART_COUNT = BIT_SIZE / PART_SIZE;//6 штук
const unsigned int PART_MASK = (unsigned int)pow(2, PART_SIZE);

void counting_sort_bit(unsigned int* a, int size, int point);

void radixSort(unsigned int* arr, int size);
