#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#define MAX_LEN 13
const int daysInMonth [12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int getRandomItem(char * buf)
{
	int wordLen = rand() % MAX_LEN + 1;
	for (int i = 0; i < wordLen; i++)
		buf[i] = 'a' + rand() % 26;
	return wordLen;
}
void getRandomData(char * buf)
{
	int year = 2000 + rand() % 18;
	int month = 1 + rand() % 12;
	int day = 1 + rand() % daysInMonth[month - 1];
	for (int i = 9 ; i >= 0; i--)
	{
		if (i > 7)
		{
			buf[i] = '0' +  day % 10;
			day -= day % 10;
			day /= 10;
		}
		else if (i == 4 || i == 7) buf[i] = '.';
		else if (i < 7 && i > 4)
		{
			buf[i] = '0' + month % 10;
			month -= month % 10;
			month /= 10;
		}
		else if (i < 4)
		{
			buf[i] = '0' + year % 10;
			year -= year % 10;
			year /= 10;
		}
	}
}
int main(int argv, char ** argc)
{
	int amount(10000);
	char * outputFileName = const_cast<char*>("output");
	std :: cout << amount << std :: endl;
        if (argv == 2)
	{
		amount = atoi(argc[1]);
		if (!amount)
		{
			printf("invalid command");
			return -1;
		}
	}
	else if (argv == 3)
	{
		amount = atoi(argc[1]);
		if (!amount)
		{
			printf("invalid command \n");
			return -1;
		}
		outputFileName = argc[2];
	}
	else if (argv > 2)
	{
		printf("too many arguments \n");
		return -1;
	}
	FILE * file = fopen(outputFileName, "w");
	if (!file)
	{
		printf("cannot open file \n");
		return -1;
	}
	srand(time(NULL));
	int user_id(0);
	double price(0);
	char * stringBuf = new char [MAX_LEN];
	char * data = new char [12];
	for (int i = 0; i < amount; i++)
	{
		memset(stringBuf, 0, MAX_LEN);
		memset(data, 0, 12);
		user_id = 1000000 + rand() % 100000000;
		price = (double)(rand() % 1000) + (double)100 / (1 + rand() % 100);
		getRandomItem(stringBuf);
		getRandomData(data);
                if(i != amount - 1)
                    fprintf(file, "%i %s %f %s \n", user_id, stringBuf, price, data);
                else
                    fprintf(file, "%i %s %f %s ", user_id, stringBuf, price, data);
	}
        fclose(file);
	delete [] stringBuf;
	delete [] data;
}
