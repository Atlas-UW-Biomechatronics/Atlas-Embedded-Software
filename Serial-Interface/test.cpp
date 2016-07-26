#include "raspberryspi.h"
#include "regset.h"
#include <iostream>
#include <unistd.h>
#include <bitset>
#include <stdint.h>

#define TEST 0x20000000

using namespace std;

void print(off_t test)
{
    cout << test << endl;
}

uint32_t SetBit(uint32_t* reg, uint8_t pos)
{
    *reg = *reg | (0x01<<pos);
    return *reg;
}

int main()
{
    uint8_t tes = 213;
    uint8_t* test = &tes;
    cout << bitset<8>(*test) << endl;
    SETREGA(test, 1, 7, BLEN_3);
    cout << bitset<8>(*test) << endl;
    return 0;
}

