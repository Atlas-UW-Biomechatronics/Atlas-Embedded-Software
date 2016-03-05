//Signal Processing Algorithm
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

const int SIZE = 65;

void readFile(int data[], istream &intel)
{
	for (int i = 0; i < SIZE; i ++)
	{
		intel >> data[i];
	}
}

void binomialFilter(int initData[], int sigRes[], int kernel[], int kernelSize)
{
	for (int i = 0; i < SIZE; i++)
	{
		sigRes[i] = 0;
        for (int j = 0; j < kernelSize; j++)
        {
            if (i - j > 0)
                sigRes[i] += abs(initData[i-j]*initData[j]);
            else
                sigRes[i] += (initData[abs(i - j)]*initData[j]);
        }
	}
}

int main()
{
	ifstream fin("data2.txt");
	ofstream fout("output3.txt");
	int kernel [2] = {2, 1};
	int kernelSize = sizeof(kernel);
	int dataArray[SIZE];
	int sigResponse[SIZE];

    readFile(dataArray, fin);
	binomialFilter(dataArray, sigResponse, kernel, kernelSize);
	for (int i = 0; i < SIZE; i++)
        fout << sigResponse[i]/5 << endl;
	return 0;
}
