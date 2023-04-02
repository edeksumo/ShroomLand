#include "DataMenager.h"

int DataMenager::RNG(int a_seed, int a_numbers[], unsigned int a_sizeOfArr)
{
    auto a = a_sizeOfArr - 1;
    auto b = a_seed % a_sizeOfArr;
    if (b > a)
        b = a;
    if (b < 0)
        b = 0;
    return a_numbers[b];
}
