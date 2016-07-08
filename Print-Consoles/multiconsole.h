#ifndef MULTICONSOLE
#define MULTICONSOLE
#include <iostream>
#include <fstream>
#include <thread>
#include <time.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

/* Returns today's date; used for logs.
 *
 * @return  string  output
 *
 */
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d, %X", &tstruct);

    return buf;
}

/* Output passed in string to the passed in log file; prints to console.
 *
 * @param  string|ofstream  output|console
 *
 * @return void (but reference of ofstream passed in to take affect)
 *
 */
void printToConsole(string output, ofstream& console) {
    console << "\t" << output << endl;
    return;
}

/* Setup all instances of console to be used.
 *
 * @param  ofstream|int|string  console|#ofConsoles|terminalApp
 *
 * @return void (but reference of ofstream is setup)
 *
 */
void setupConsoles(ofstream* console, int console_num, string terminal) {
    string command[console_num];
    for (int i = 0; i < console_num; i++) {
        command[i] = terminal + " -e \"tail -q -f printConsole" + to_string(i) + ".txt\"";
        // if you want to close the consoles at end of program
        // command[i] = terminal + " -e \"tail -q -f printConsole" + to_string(i) + ".txt --pid=\"" + to_string(PID);
        console[i].open("printConsole" + to_string(i) + ".txt", ios_base::app);
        console[i] << "Logged at: " << currentDateTime() << ":\n" << endl;
        system(command[i].c_str());
    }
}
#endif

// Zain Zulfiqar
// July 4, 2016
