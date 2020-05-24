#pragma once
#include "pch.h"

#include "QInt.h"

class QFloat
{
public:
	static const bool FLAG = false;
	static const int N = 4;										// So luong int
	static const int LENGTH = sizeof(int) * 8;					// Do dai 1 int
	static const int TOTAL_LENGTH = N * LENGTH;					// Tong do dai bit

private:
	unsigned int* m_bits;

public:
	QFloat();
	QFloat(int x);		// Khoi tao QFloat tu mot so nguyen
	QFloat(float x);
	QFloat(const QFloat& a);
	QFloat(string x);	// Khoi tao QFloat tu mot so thap phan duoc luu bang chuoi
	QFloat(QInt x);		// Khoi tao QFloat tu mot so QInt
	~QFloat();

private:
	string toString();

public:
	// 128 bit duoc luu trong 4 int
	// Duoc chia lam 3 phan: phan dau (1 bit), phan mu (15 bit), phan tri (112 bit)
	// Cac phan duoc danh dau tu 1. Voi moi phan, bit bat dau duoc tinh la bit 0
	bool getBitAt(int p, int k);
	void setBitAt(int p, int k);
	void turnBitAt(int p, int k);

	void setBitAt(int k);	//Doi bit thu k thanh bit 1
	bool getBitAt(int k);	//Lay bit thu k
	void turnBitAt(int k);	//Dao bit thu k

	bool getSign();	//lấy dấu
	QInt getExponent();	//lấy mũ
	QInt getSignificant();	//lấy trị
	void setExponent(QInt a);	//sửa mũ
	void setSignificant(QInt a);	//sửa trị

public:
	QFloat& operator =(const QFloat& a);
	bool operator ==(QFloat a);
	friend istream& operator >>(istream& fi, QFloat& a);
	friend ostream& operator <<(ostream& fo, QFloat a);

public:// Cac toan tu
	QFloat operator+(QFloat a);
	QFloat operator-(QFloat a);
	QFloat operator*(QFloat a);
	QFloat operator/(QFloat a);

//*****************************************************************
	// by Vu
public:// Cac ham chuyen doi
	// Ham chuyen doi tu QFloat dec -> bin
	static bool* DecToBin(QFloat x);

	// Ham chuyen doi tu QFloat bin -> dec
	static QFloat BinToDec(bool* bit);

public:	// Ham phu de kiem tra 1 so dieu kien
	bool isZero();
	bool isNaN();
	bool isInf();
	bool isDeN();

public:
	QInt multiBooth(const QInt& s1, const QInt& s2);
	QInt divisBooth(const QInt& s1, const QInt& s2);

public:
	void printExponent();
	void printSignificant();
	void printBits();

public:
	// Cac ham duoi day chi de cho chuong trinh chay duoc
	static string DecToHex(QFloat x) { return ""; }
	static QFloat HexToDec(string x) { return QFloat(0); }
	static string BinToHex(bool* bit) { return ""; }
	static bool* HexToBin(string x) { return NULL; }
	QFloat operator &(QFloat a) { return *this; }
	QFloat operator |(QFloat a) { return *this; }
	QFloat operator ^(QFloat a) { return *this; }
	QFloat operator ~() { return *this; }
	QFloat operator <<(const int& num) { return *this; }
	QFloat operator >>(const int& num) { return *this; }
	QFloat rol() { return *this; }
	QFloat ror() { return *this; }
	int toInt() { return 0; }
};