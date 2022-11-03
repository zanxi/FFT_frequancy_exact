// ConsoleApplication_FFT_frequancy.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <sstream>

using namespace std;
using namespace std::this_thread;

#include <iostream>
#include "Fourier.h"

int InputData(std::string fname, float data[NumData])
{
	ifstream input;
	size_t k = 0;
	string line;
	cout << " !!!! START READING INPUT file: " << fname << endl;
	input.open(fname);
	if (input.is_open())
	{
		while (getline(input, line))
		{
			data[k] = atof(line.c_str());
			k++;
		}

	}
	input.close();
	cout << " !!!! FINISHED READING INPUT file: " << fname << endl;
	return k;
}



int main()
{
	CFourier fft;
	long sample_rate = 4 * 8192;
	long captured_samples = 2000;
	int frequency = 150;
	float data[NumData];

	for(int i=0; i<captured_samples; i++)
	{
			double temp=(double)(2*fft.pi*frequency*((float)i/sample_rate))+
				(double)(2 * fft.pi * 2*frequency * ((float)i / sample_rate));
			data[i]=((double)30*sin(temp));
	}
		
	fft._FFT(data, captured_samples, sample_rate, 1);
	cout << " Test frequncy:  " << fft.fundamental_frequency << endl;

	float data2[NumData];
	int numD = InputData("signal.txt", data2);
	fft._FFT(data2, captured_samples, sample_rate, 1);
	
	cout << "Work frequncy:  "<< fft.fundamental_frequency << "  !!!!!!!!!!!!!" << endl;

	system("pause");
    
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
