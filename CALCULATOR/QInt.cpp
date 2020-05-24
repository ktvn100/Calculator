#include "pch.h"
#include "QInt.h"
#include <sstream>

// Bang ma Hex
const int HEX_IDX_NUM = 16;				// So luong ki tu trong ban ma hex
const char HEX_CHAR[HEX_IDX_NUM] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };	//Bang ma cac ki tu tong ma  Hex

QInt::QInt()
{
	this->m_bits = new unsigned int[N];
	for (int i = 0; i < N; i++)
		this->m_bits[i] = 0;
}

QInt::QInt(const QInt& a)
{
	this->m_bits = new unsigned int[N];
	for (int i = 0; i < N; i++)
		this->m_bits[i] = a.m_bits[i];
}

QInt::QInt(int x)
{
	this->m_bits = new unsigned int[N];
	for (int i = 0; i < N; i++)
		this->m_bits[i] = 0;
	this->m_bits[N - 1] = abs(x);
	if (x < 0)
		*this = ~(*this) + 1;
}

QInt::QInt(string x)
{
	this->m_bits = new unsigned int[N];
	for (int i = 0; i < N; i++)
		this->m_bits[i] = 0;
	bool flag = false;
	if (x[0] == '-')
	{
		flag = true;
		x.erase(0, 1);
	}
	int len = x.length();
	for (int i = 0; i < len; i++)
	{
		*this = (*this) * QInt(10);
		*this = (*this) + QInt(x[i] - '0');
	}
	if (flag) *this = ~(*this) + 1;
}

QInt::~QInt()
{
	delete[] this->m_bits;
	this->m_bits = NULL;
}

void QInt::setBitAt(int k)
{
	int i = k / LENGTH;
	int j = k % LENGTH;
	this->m_bits[i] |= (1 << (LENGTH - j - 1));
}

bool QInt::getBitAt(int k)
{
	int i = k / LENGTH;
	int j = k % LENGTH;
	return (this->m_bits[i] >> (LENGTH - j - 1)) & 1;
}

void QInt::turnBitAt(int k)
{
	int i = k / LENGTH;
	int j = k % LENGTH;
	this->m_bits[i] = this->m_bits[i] ^ (1 << (LENGTH - j - 1));
}

string QInt::toString()
{
	if (*this < QInt(0))
	{
		QInt a = ~(*this - QInt(1));
		return "-" + a.toString();
	}
	const int MOD = int(1e9);
	int res[N + 1], p2[N + 1];
	for (int i = 0; i <= N; i++) res[i] = p2[i] = 0;
	p2[0] = 1;
	for (int i = TOTAL_LENGTH - 1; i > 0; i--)
	{
		int tmp = 0;
		if (this->getBitAt(i))
		{
			for (int k = 0; k <= N; k++)
			{
				res[k] = res[k] + p2[k] + tmp;
				tmp = res[k] / MOD;
				res[k] %= MOD;
			}
		}
		tmp = 0;
		for (int k = 0; k <= N; k++)
		{
			p2[k] = p2[k] * 2 + tmp;
			tmp = p2[k] / MOD;
			p2[k] %= MOD;
		}
	}
	string ans = "";
	for (int i = N; i >= 0; i--)
	{
		stringstream buf;
		buf << res[i];
		string tmp = buf.str();
		while (tmp.length() < 9) tmp = "0" + tmp;
		ans = ans + tmp;
	}
	while (ans[0] == '0' && ans.length() > 1) ans.erase(0, 1);
	return ans;
}

istream& operator >>(istream& fi, QInt& a)
{
	string buf = "";
	fi >> buf;
	a = QInt(buf);
	return fi;
}

ostream& operator <<(ostream& fo, QInt a)
{
	fo << a.toString();
	return fo;
}

QInt QInt::operator &(QInt a)
{
	for (int i = 0; i < N; i++)
		a.m_bits[i] &= this->m_bits[i];
	return a;
}

QInt QInt::operator |(QInt a)
{
	for (int i = 0; i < N; i++)
		a.m_bits[i] |= this->m_bits[i];
	return a;
}

QInt QInt::operator ^(QInt a)
{
	for (int i = 0; i < N; i++)
		a.m_bits[i] ^= this->m_bits[i];
	return a;
}

QInt QInt::operator ~()
{
	for (int i = 0; i < N; i++)
		this->m_bits[i] = ~this->m_bits[i];
	return *this;
}

int QInt::toInt()
{
	return this->m_bits[N - 1];
}

void QInt::printData()
{
	for (int i = 0; i < N; i++)
		cout << this->m_bits[i] << " ";
	cout << endl;
}

void QInt::printBits()
{
	for (int i = 0; i < QInt::TOTAL_LENGTH; i++)
		cout << this->getBitAt(i);
	cout << endl;
}

// *********************************************************************
// by Vu

// Ham chuyen doi tu so QInt dang thap phan sang dang nhi phan
// Dau vao la so QInt dang thap phan
bool* QInt::DecToBin(QInt x)
{
	bool* BinQIint = new bool[TOTAL_LENGTH];	//Day so QInt dang nhi phan
	for (int i = 0; i < TOTAL_LENGTH; i++) {
		BinQIint[i] = x.getBitAt(i);
	}
	return BinQIint;
}

// Ham chuyen doi tu so QInt dang nhi phan sang dang thap phan
// Dau vao la so QInt dang nhi phan bieu dien bang mang bool: bit
QInt QInt::BinToDec(bool* bit)
{
	QInt DecQInt;								//Day so QInt duoi dang thap phan; Khoi tao bang dau gom 4 byte 0
	for (int i = 0; i < TOTAL_LENGTH; i++) {
		if (bit[i]) {
			DecQInt.setBitAt(i);
		}
	}
	return DecQInt;
}

// Ham chuyen doi tu QInt dang thap phan sang dang thap luc phan
// Dau vao la so QInt dang thap phan bieu dien bang kieu QInt
string QInt::DecToHex(QInt x)
{
	// Ham hoat dong bang cach truyen thong - chuyen tung bo 4 bit sang ki tu hex
	string QIntHex = "";	//Day so QInt duoi dang thap luc phan; la mot kieu string gom 32 ki tu;
	int HexIdx = 0;			//Chi so cua tung ki tu trong chuoi thap luc phan

	for (int i = 0; i < TOTAL_LENGTH; i += 4) {
		HexIdx = 0;
		for (int j = 0; j < 4; j++) {
			if (x.getBitAt(i + j)) {
				HexIdx |= (1 << (4 - j - 1));
			}
		}
		QIntHex += HEX_CHAR[HexIdx];
	}

	//Bo so 0 o dau chuoi
	while (QIntHex[0] == '0')
	{
		QIntHex.erase(0, 1);
	}

	return QIntHex;
}

// Ham chuyen doi tu QInt dang thap luc phan sang dang thap phan
// Dao vao la so QInt dang thap luc phan bieu dien bang kieu string: x
QInt QInt::HexToDec(string x)
{
	QInt QIntDec;				//Day so QInt duoi dang thap phan; Khoi tao bang dau gom 4 byte 0
	int xLength = x.length();	//Chieu dai cua chuoi x

	// Them so 0 vao dau chuoi de tien cho viec tinh toan
	while (xLength < TOTAL_LENGTH / 4)
	{
		xLength++;
		x = '0' + x;
	}

	for (int i = 0; i < xLength; i++) {
		int idxChar = 0;		//Bien lay ma dec cua ki tu thu i
		while (idxChar < HEX_IDX_NUM)
		{
			if (HEX_CHAR[idxChar] == x[i]) {
				break;
			}
			idxChar++;
		}

		for (int j = 0; j < 4; j++) {
			if ((idxChar >> j) & 1) {
				int idxDec = i * 4 + (4 - j - 1);
				QIntDec.setBitAt(idxDec);
			}
		}
	}

	return QIntDec;
}



// Ham chuyen doi tu QInt dang nhi phan sang dang thap luc phan
// Dau bao la so QInt dang nhi phan bieu dien bang mang bool: bit
string QInt::BinToHex(bool* bit)
{
	/*// Ham hoat dong bang cach truyen thong - chuyen tung bo 4 bit sang ki tu hex
	string QIntHex = "";	//Day so QInt duoi dang thap luc phan; la mot kieu string gom 32 ki tu;
	int HexIdx = 0;			//Chi so cua tung ki tu trong chuoi thap luc phan



	for (int i = 0; i < TOTAL_LENGTH; i += 4) {
		HexIdx = 0;
		for (int j = 0; j < 4; j++) {
			if (bit[i + j]) {
				HexIdx |= (1 << (4 - j - 1));
			}
		}
		QIntHex += HEX_CHAR[HexIdx];
	}
	return QIntHex;*/

	// Hoat dong bang cach goi cac ham khac de chuyen doi bin -> dec -> hex
	string QIntHex = "";	//Day so QInt duoi dang thap luc phan; la mot kieu string gom 32 ki tu;

	QInt temp = QInt::BinToDec(bit);
	QIntHex = QInt::DecToHex(temp);

	return QIntHex;
}

// Ham chuyen doi tu QInt dang thap luc phan sang dang nhi phan
// Dau vao la so QInt dang thap luc phan
bool* QInt::HexToBin(string x)
{
	// Hoat dong dua tren cac ham khac de chuyen doi hex -> dec -> bin
	QInt temp = QInt::HexToDec(x);
	bool* QIntBin = QInt::DecToBin(temp);
	return QIntBin;
}

//************************************************************************************************
QInt& QInt::operator =(const QInt& a)
{
	// Lay tung block cua this = a, do khong thay doi kich thuoc
	// va int ban than co phep gan = nen khoi delete cap bo nho lai
	for (int i = 0; i < N; i++)
		this->m_bits[i] = a.m_bits[i];
	return *this;
}

QInt QInt::operator +(QInt a)
{
	QInt mask;
	QInt result = *this;

	// Nếu a chưa bằng 0 thì lặp
	while (!(a == QInt(0)))
	{
		// Tạo một cái mask để nhớ các phép tính có nhớ (nơi mà số ở trên là 1, số dưới cũng 1)
		mask = result & a;
		//cộng lại không cần nhớ gì cả
		result = result ^ a;
		//dịch cái mask tượng trưng cho phép nhớ của bit kế tiếp
		a = mask << 1;
		//lặp lại đến khi nào cái mask rỗng, tức là không còn nhớ nữa thì thôi
		//do dùng cách làm bù 2 nên không quan tâm tràn số (thực ra cái này catch sau)
	}

	return result;
}

QInt QInt::operator -(QInt a)
{
	//tao so bu 2
	QInt tmp = ~a;
	tmp = tmp + QInt(1);
	//cong lai
	return *this + tmp;

}

QInt QInt::operator *(QInt a)
{
	QInt result;
	QInt tmp = *this;
	bool isNegative = false;
	//xét xem 2 số có trái dấu không
	if ((tmp < QInt(0) && a > QInt(0)) || (tmp > QInt(0) && a < QInt(0)))
	{
		isNegative = true;
	}

	//Nếu có âm thì đổi dấu 2 số thành số dương
	if (tmp < QInt(0))
	{
		tmp = ~tmp + QInt(1);
	}

	if (a < QInt(0))
	{
		a = ~a + QInt(1);
	}

	//Nhân 2 số không âm 
	//nếu a==0 hay tmp==0 thì dừng
	while ((!(a == QInt(0))) && (!(tmp == QInt(0))))
	{
		//nếu a là số lẻ thì cộng thêm 1*a vào kết quả
		//do khi chia a cho 2 thì nếu a lẻ sẽ bị thiếu 1, do đó cộng 1 lần a vào
		if (((a.m_bits[N - 1] & 1) - 1) == 0)
		{
			result = result + tmp;
		}
		//không lẻ thì thôi
		tmp = tmp << 1;
		a = a >> 1;
	}
	//kiểm tra có âm không
	if (isNegative)
	{
		result = ~result + QInt(1);
	}

	return result;
}

QInt QInt::operator /(QInt a)
{
	QInt tmp = *this;
	QInt result;
	bool isNegative = false;

	//xét trái dấu
	if ((tmp < QInt(0) && a > QInt(0)) || (tmp > QInt(0) && a < QInt(0)))
	{
		isNegative = true;
	}

	//chuyển về dương
	if (tmp < QInt(0))
	{
		tmp = ~tmp + QInt(1);
	}

	if (a < QInt(0))
	{
		a = ~a + QInt(1);
	}

	//Xét trường hợp = 0 và số bị chia < số chia thì trả về 0
	if ((tmp == QInt(0)) || (a == QInt(0)) || (tmp < a))
	{
		return result;
	}

	//chia cho 1
	if (a == QInt(1))
	{
		result = tmp;
	}
	else
		//chia cho chính nó
		if (a == tmp)
		{
			result = QInt(1);
		}
		else
		{
			int k = LENGTH * N;
			QInt divisor;
			while (k > 0)
			{
				divisor = divisor << 1;
				divisor.m_bits[N - 1] = divisor.m_bits[N - 1] | (int)(tmp.getBitAt(N * LENGTH - k));
				result = result << 1;
				if (divisor >= a)
				{
					divisor = divisor - a;
					result = result | QInt(1);
				}
				k--;
			}
		}

	//xét ngược dấu
	if (isNegative)
	{
		result = ~result + QInt(1);
	}

	return result;
}

QInt QInt::operator <<(const int& num)
{
	//kết quả
	QInt result;
	QInt a = *this;
	int x = num;
	//bit dấu
	//int signBit;
	//dịch trái không ảnh hưởng sự dịch của block cuối
	while (x > 31)
	{
		for (int i = 0; i < N - 1; i++)
			a.m_bits[i] = a.m_bits[i + 1];
		a.m_bits[N - 1] = 0;
		x -= 32;
	}
	result.m_bits[N - 1] = a.m_bits[N - 1] << x;
	//lấy bit dấu
	//signBit = this->getBitAt(0);

	//đưa bit tràn qua mấy cái block ở trên
	for (int i = N - 2; i > -1; i--)
	{
		for (int j = 0; j < x; j++)
		{
			unsigned int tmp = (a.m_bits[i + 1] >> (LENGTH - x))& (1 << j);
			result.m_bits[i] = result.m_bits[i] | tmp;
		}
		//dịch cáu=i block phía trước rồi cộng vô
		unsigned int tmp = a.m_bits[i] << x;

		result.m_bits[i] = result.m_bits[i] | tmp;
	}
	//lấy lại bit dấu
	//result.setBitAt(0);
	//result.turnBitAt(0);
	//result.m_bits[0] = result.m_bits[0] | signBit;

	return result;
}

QInt QInt::operator >>(const int& num)
{
	//kết quả
	QInt result;
	QInt a = *this;
	int x = num;
	//bit dấu
	//int signBit;
	//dịch cái block 4byte đầu tiên, do nó không ảnh hưởng gì từ việc dịch phải
	while (x > 31)
	{
		for (int i = N - 1; i > 0; i--)
			a.m_bits[i] = a.m_bits[i - 1];
		a.m_bits[0] = 0;
		x -= 32;
	}
	result.m_bits[0] = a.m_bits[0] >> num;
	//lấy bit dấu
	//signBit = this->getBitAt(0);

	//đưa bit bị tràn qua các block 4 byte phía sau
	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < num; j++)
		{
			//lấy những bit bị dịch ở cuối block trước đưa cho đầu block sau
			result.m_bits[i] = result.m_bits[i] | (((1 << j) & (a.m_bits[i - 1])) << (LENGTH - x));
		}
		//dịch cái block phía sau
		unsigned int tmp = a.m_bits[i] >> x;
		//cộng vào
		result.m_bits[i] = result.m_bits[i] | tmp;
	}
	//lấy lại bit dấu
	//result.setBitAt(0);
	//result.turnBitAt(0);
	//result.m_bits[0] = result.m_bits[0] | signBit;
	return result;
}

QInt QInt::rol()
{
	int tmp;
	QInt result;
	//lấy bit đầu ra
	tmp = (1 << (LENGTH - 1) & this->m_bits[0]);
	//dịch qua trái 1 bit
	result = *this << 1;
	//chèn bit đầu lúc nãy vào cuối
	result.m_bits[N - 1] = result.m_bits[N - 1] | (tmp >> (LENGTH - 1));

	return result;
}

QInt QInt::ror()
{
	QInt result;
	int tmp;
	//lấy bit cuối ra
	tmp = 1 & this->m_bits[N - 1];
	//dịch phải 1 bit
	result = *this >> 1;
	//chèn bit tmp lên đầu
	result.m_bits[0] = result.m_bits[0] | (tmp << (LENGTH - 1));

	return result;
}

bool QInt::operator>(QInt a)
{
	bool sign_this = this->getBitAt(0);
	bool sign_a = a.getBitAt(0);

	if (sign_this == sign_a)
	{
		//nếu block càng gần phía trên lớn thì lớn
		for (int i = 0; i < N; i++)
		{
			if (this->m_bits[i] > a.m_bits[i])
				return true;
			else
				if (this->m_bits[i] < a.m_bits[i])
					return false;
		}
		return false;
	}
	else
		if (sign_this == 1 && sign_a == 0)
			return false;
		else
			if (sign_this == 0 && sign_a == 1)
				return true;
}

bool QInt::operator<(QInt a)
{
	//hông >, hông = thì bé 
	if (*this > a || *this == a)
		return false;
	return true;
}

bool QInt::operator==(QInt a)
{
	//từng block đều bằng nhau
	for (int i = 0; i < N; i++)
	{
		if (this->m_bits[i] != a.m_bits[i])
			return false;
	}
	return true;
}

bool QInt::operator>=(QInt a)
{
	//hông bé thì <=
	if (*this < a)
		return false;
	return true;
}

bool QInt::operator<=(QInt a)
{
	//hông lớn thì <=
	if (*this > a)
		return false;
	return true;
}