#pragma once
#include "pch.h"

#include "CalCore.h"

//*****************
#include "QInt.h"
#include "QFloat.h"

#include <string>
#include <sstream>

using namespace std;

bool isNum(string x)
{
	return ((x[0] >= '0' && x[0] <= '9') || (x[0] >= 'A' && x[0] <= 'F') || x.length() > 1 && x[0] == '-');
}

template <class T>
void readFromBin(T& a, string x)
{
	int len = x.length();
	bool* bits = new bool[T::TOTAL_LENGTH];
	for (int i = 0; i < T::TOTAL_LENGTH; i++) bits[i] = 0;
	for (int i = 0; i < len; i++) bits[T::TOTAL_LENGTH - len + i] = x[i] - '0';
	a = T::BinToDec(bits);
	delete[] bits;
}

template <class T>
void readFromHex(T& a, string x)
{
	a = T::HexToDec(x);
}

template <class T>
void readFromDec(T& a, string x)
{
	a = T(x);
}

template <class T>
string toString(string base, T x)
{
	string tmp = "";
	if (base[0] == '2')
	{
		bool* a = T::DecToBin(x);
		bool flag = T::FLAG;
		for (int i = 0; i < T::TOTAL_LENGTH; i++)
			if (a[i] || !flag)
			{
				flag = false;
				tmp += char(a[i] + '0');
			}
		delete[] a;
	}
	else if (base[1] == '6')
		tmp = T::DecToHex(x);
	else
	{
		stringstream buf;
		buf << x;
		tmp = buf.str();
	}
	return tmp;
}

template <class T>
string baseChange(T type, string* par)
{
	T x;
	if (par[0][0] == '2')
		readFromBin(x, par[2]);
	else if (par[0][1] == '0')
		readFromDec(x, par[2]);
	else
		readFromHex(x, par[2]);

	return toString(par[1], x);
}

template <class T>
string cal1(T type, string* par)
{
	T x, y;
	if (par[0][0] == '2')
	{
		readFromBin(x, par[1]);
		readFromBin(y, par[3]);
	}
	else if (par[0][1] == '0')
	{
		readFromDec(x, par[1]);
		readFromDec(y, par[3]);
	}
	else
	{
		readFromHex(x, par[1]);
		readFromHex(y, par[3]);
	}

	T res;
	if (par[2][0] == '+') res = x + y; else
		if (par[2][0] == '-') res = x - y; else
			if (par[2][0] == '*') res = x * y; else
				if (par[2][0] == '/') res = x / y; else
					if (par[2][0] == '&') res = x & y; else
						if (par[2][0] == '|') res = x | y; else
							if (par[2][0] == '^') res = x ^ y; else
								if (par[2][0] == '<') res = (x << y.toInt()); else
									if (par[2][0] == '>') res = (x >> y.toInt());

	return toString(par[0], res);
}

template <class T>
string cal2(T type, string* par)
{
	T x;
	if (par[0][0] == '2')
		readFromBin(x, par[2]);
	else if (par[0][1] == '0')
		readFromDec(x, par[2]);
	else
		readFromHex(x, par[2]);

	T res;
	if (par[1][0] == '~') res = ~x; else
		if (par[1][2] == 'l') res = x.rol(); else
			if (par[1][2] == 'r') res = x.ror();

	return toString(par[0], res);
}

template <class T>
string process(T type, string pt)
{
	string* par = new string[4];
	pt = pt + " ";
	int s = 0;
	int i = 0;
	int p = pt.find(" ", s);
	while (p != string::npos)
	{
		par[i++] = pt.substr(s, p - s);
		s = p + 1;
		p = pt.find(" ", s);
	}
	string tmp = "";
	if (!isNum(par[1]))
		tmp = cal2(type, par);
	else if (!isNum(par[2]))
		tmp = cal1(type, par);
	else
		tmp = baseChange(type, par);
	delete[] par;
	return tmp;
}
//*****************
