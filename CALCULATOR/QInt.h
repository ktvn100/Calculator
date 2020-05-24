#pragma once
#include "pch.h"

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class QInt
{
public:
	static const bool FLAG = true;
	static const int N = 4;							// So luong day bit
	static const int LENGTH = sizeof(int) * 8;		// Chieu dai mot day bit
	static const int TOTAL_LENGTH = LENGTH * N;		// Tong chieu dai day bit cua so QInt

private:
	unsigned int* m_bits;
	//4 day bit, moi day 32 bit, danh so tu 0-31, tu ben trai qua

public:
	QInt();
	QInt(const QInt& a);

	//Chuyen tu mot so int sang QInt
	QInt(int x);

	//Chuyen tu day so dec sang QInt
	QInt(string x);
	~QInt();

public:
	//k tinh tu trai qua

	//Doi bit thu k thanh bit 1
	void setBitAt(int k);

	//Lay bit thu k
	bool getBitAt(int k);

	//Dao bit thu k
	void turnBitAt(int k);

public:
	friend istream& operator >>(istream& fi, QInt& a);
	friend ostream& operator <<(ostream& fi, QInt a);
	QInt& operator =(const QInt& a);
	int toInt();

private:
	//Chuyen QInt thanh day so
	string toString();

public:
	// Ham chuyen doi tu QInt dec sang bin
	static bool* DecToBin(QInt x);

	// Ham chuyen doi tu QInt bin -> dec
	static QInt BinToDec(bool* bit);

	// Ham chuyen doi tu QInt dec -> hex
	static string DecToHex(QInt x);

	// Ham chuyen doi tu QInt hex -> dec
	static QInt HexToDec(string x);

	// Ham chuyen doi tu QInt bin -> hex
	static string BinToHex(bool* bit);

	// Ham chuyen doi tu QInt hex -> bin
	static bool* HexToBin(string x);

public:
	//dung de debug
	void printData();
	void printBits();

public:	// Cac toan tu so sanh
	bool operator >(QInt a);
	bool operator <(QInt a);
	bool operator ==(QInt a);
	bool operator >=(QInt a);
	bool operator <=(QInt a);

public:	// Cac toan tu phep tinh
	QInt operator +(QInt a);
	QInt operator -(QInt a);
	QInt operator *(QInt a);
	QInt operator /(QInt a);

public:	// Cac toan tu xu ly bit
	QInt operator &(QInt a);
	QInt operator |(QInt a);
	QInt operator ^(QInt a);
	QInt operator ~();
	QInt operator <<(const int& num);
	QInt operator >>(const int& num);
	QInt rol();
	QInt ror();
};