#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <thread>


#define MAX_LINE  200 
#pragma warning(disable:4996)
using namespace std;
class parsing
{
public:
	parsing();
	void find_word_inline(string& line, char word[100], short& z, bool& findbool);
	void write(int &dat_name_number, string Path_to_data1, string Path_to_data2);
	~parsing();
};

