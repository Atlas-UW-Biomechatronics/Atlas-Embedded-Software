#include "RaspberrySPi.h"
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
    uint8_t  pos  = 0;
    uint32_t test = 0x56872244;
    uint32_t* reg = &test;
    uint32_t mask = 0x01 << pos;
    /*
    cout << "SetBit: " << endl;
    cout << bitset<32>(test) << endl;
    cout << bitset<32>(mask) << endl;
    SETBIT(reg, pos);
    cout << bitset<32>(*reg) << endl;
    cout << "ClrBit: " << endl;
    cout << bitset<32>(test) << endl;
    cout << bitset<32>(~mask) << endl;
    CLRBIT(reg, pos);
    cout << bitset<32>(*reg) << endl;
    */
    cout << "ReadBit: " << endl;
    if (READBIT(reg, pos))
        cout << "one" << endl;
    else if (!READBIT(reg, pos))
        cout << "zero" << endl;
    return 0;
}

