#include "raspberryspi.h"
#include "regset.h"
#include <iostream>
#include <unistd.h>
#include <bitset>
#include <stdint.h>

#define TEST 0x20000000

using namespace std;

void print32(uint32_t reg)
{
    cout << "33222222222211111111110000000000" << endl;
    cout << "10987654321098765432109876543210" << endl;
    cout << bitset<32>(reg) << endl;
    cout << "--------------------------------" << endl;
}
int main()
{
    uint32_t test32 = 0x8571235;
    print32(test32);
    cout << (READREGV(test32, 9 , BLEN_2)) << endl;;
    return 0;
}

