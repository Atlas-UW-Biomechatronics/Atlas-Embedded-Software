#include "multiconsole.h"
using namespace std;

int main () {

    // ------------------------ Framework setup -------------------------------

    //define preferences here
    string terminal = "xfce4-terminal";                 //terminal inside OS
    int console_num = 4;                                //num of outputs

    //initialize consoles setup
    int PID = getpid();
    ofstream console[console_num];                      //output file streams
    setupConsoles(console, console_num, terminal);      //framework setup

    // ------------------------ Framework setup -------------------------------

    //Your code START ...

    printToConsole("This is console 0", console[0]);
    printToConsole("This is console 1", console[1]);
    printToConsole("This is console 2", console[2]);
    printToConsole("This is console 3", console[3]);

    //Your code END ...

    // remember to close all file streams defined by framework
    for (int i = 0; i < console_num; i++) {
        console[i] << "" << endl;
        console[i].close();
    }
    return 0;   //exit program
}
