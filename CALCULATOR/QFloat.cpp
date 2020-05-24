#include "pch.h"
#include "QFloat.h"

#include <sstream>

// So luong bit 3 phan: bit dau, bit mu, bit tri
// Luu theo tong cong don
const int BITS[4] = { 0, 1, 16, QFloat::TOTAL_LENGTH };



// Lay do dai bit chinh xac moi phan
int getBitLength(int x)
{
	return BITS[x] - BITS[x - 1];
}

//số mũ tối đa
const QInt MAX_EX = (QInt(1) << getBitLength(2)) - QInt(1);

// Bias
const int BIAS_KEY = (1 << (getBitLength(2) - 1)) - 1;		// Kieu int
const QInt BIAS_EX = (QInt(1) << (getBitLength(2) - 1)) - QInt(1); // Kieu QInt

//số 1 ngầm định của phần trị
const QInt ONE_PLUS = QInt(1) << getBitLength(3);

QFloat::QFloat()
{
	this->m_bits = new unsigned int[QFloat::N];
	for (int i = 0; i < QFloat::N; i++)
		this->m_bits[i] = 0;
}

QFloat::QFloat(const QFloat& a)
{
	this->m_bits = new unsigned int[QFloat::N];
	for (int i = 0; i < QFloat::N; i++)
		this->m_bits[i] = a.m_bits[i];
}

QFloat::QFloat(int x)
{
	// Khoi tao = 0
	this->m_bits = new unsigned int[QFloat::N];
	for (int i = 0; i < QFloat::N; i++)
		this->m_bits[i] = 0;

	if (x == 0) return;

	bool sign = x < 0;							// Bit dau

	x = abs(x);									// Chuyen ve so duong
	int len = sizeof(x) * 8;					// Do dai cua mot so int
	bool* bits = new bool[len];					// Khoi tao mang bit
	int pos = len - 1;								// Vi tri bit 1 dau tien trong mang bit
	for (int i = len - 1; i >= 0; i--)
	{
		if (x == 1) pos = i;					// x = 1 nghia la bit 1 do la bit dau tien
		bits[i] = x & 1;						// Lay bit cuoi cua x ra
		x = x >> 1;								// Dich phai x de tiep tuc xu ly
	}
	for (int i = pos + 1; i < len; i++)
		if (bits[i])
			this->setBitAt(3, i - pos - 1);		// Gan tung bit vao phan tri cua QFloat

	// Gan phan mu
	x = len - pos - 1 + BIAS_KEY;							// x bay gio la gia tri phan mu (2^x)
	len = getBitLength(2);						// len la do dai phan mu
	for (int i = len - 1; i >= 0; i--)
	{
		bits[i] = x & 1;
		x = x >> 1;
	}
	for (int i = 0; i < len; i++)
		if (bits[i])
			this->setBitAt(2, i);

	if (sign) this->setBitAt(1, 0);				// Bat bit dau neu la so am
	delete[] bits;
	bits = NULL;
}

QFloat::QFloat(float x)
{
	// Khoi tao = 0
	this->m_bits = new unsigned int[QFloat::N];
	for (int i = 0; i < QFloat::N; i++)
		this->m_bits[i] = 0;
	if (x == 0) return;

	if (x < 0)
	{
		this->setBitAt(1, 0);
		x = -x;
	}
	int a = int(x);		// Phan nguyen cua x
	x = x - float(a);		// Phan thap phan cua x

	bool* bits = QInt::DecToBin(QInt(a));
	int len = QInt::TOTAL_LENGTH;
	int pos = len - 1;
	for (int i = 0; i < len; i++)
		if (bits[i])
		{
			pos = i;
			break;
		}
	for (int i = pos + 1; i < len; i++)
		if (bits[i])
			this->setBitAt(3, i - pos - 1);
	delete[] bits;

	int ex = len - pos - 1 + BIAS_KEY;	// Phan mu
	this->setExponent(QInt(ex));

	for (int i = len - pos - 1; i < getBitLength(3); i++)
	{
		x = x * 2;
		if (x >= 1)
		{
			this->setBitAt(3, i);
			x = x - 1;
		}
	}
}

QFloat::QFloat(QInt a)
{
	// Khoi tao = 0
	this->m_bits = new unsigned int[QFloat::N];
	for (int i = 0; i < QFloat::N; i++)
		this->m_bits[i] = 0;

	if (a == QInt(0)) return;
	if (a.getBitAt(0))
	{
		this->setBitAt(1, 0);
		a = ~a + QInt(1);
	}

	//Gan phan tri
	bool* bits = QInt::DecToBin(a);
	int len = QInt::TOTAL_LENGTH;
	int pos = len - 1;
	for (int i = 0; i < len; i++)
		if (bits[i])
		{
			pos = i;
			break;
		}
	if (len - pos > getBitLength(3)) len -= (len - pos - getBitLength(3));
	for (int i = pos + 1; i < len; i++)
		if (bits[i])
			this->setBitAt(3, i - pos - 1);		// Gan tung bit vao phan tri cua QFloat

	// Gan phan mu
	int x = len - pos - 1 + BIAS_KEY;			// x bay gio la gia tri phan mu (2^x)
	len = getBitLength(2);
	for (int i = len - 1; i >= 0; i--)
	{
		bits[i] = x & 1;
		x = x >> 1;
	}
	for (int i = 0; i < len; i++)
		if (bits[i])
			this->setBitAt(2, i);

	delete[] bits;
	bits = NULL;
}

QFloat::QFloat(string x)
{
	// Khoi tao = 0
	this->m_bits = new unsigned int[QFloat::N];
	for (int i = 0; i < QFloat::N; i++)
		this->m_bits[i] = 0;

	// Phan bao loi
	if (x == "Zero") {
		for (int i = 0; i < QFloat::N; i++)
			this->m_bits[i] = 0;
		return;
	}
	else if (x == "-Inf" || x == "+Inf") {
		for (int i = BITS[1]; i < BITS[2]; i++)
			this->m_bits[i] = 1;
		for (int i = BITS[2]; i < BITS[3]; i++)
			this->m_bits[i] = 0;
		if (x[0] == '-') this->m_bits[0] = 1;
		else this->m_bits[0] = 0;
		return;
	}
	else if (x == "NaN") {
		for (int i = BITS[1]; i < BITS[2]; i++)
			this->m_bits[i] = 1;
		for (int i = BITS[2]; i < BITS[3]; i++)
			this->m_bits[i] = 1;
		return;
	}

	// Bien so x thanh dang a*10^(-b) voi a la so nguyen
	// Dau tien dua a vao bo nho
	bool flag = false;
	if (x[0] == '-')
	{
		flag = true;
		x.erase(0, 1);
	}
	int pos = x.length() - 1;			// Vi tri dau cham thap phan trong chuoi
	int t = 0;
	string t1 = "1";
	string t2 = "";
	for (int i = 0; i < x.length(); i++)
		if (x[i] == '.')
			pos = i;
		else
		{
			t++;
			t1 += "0";
			t2 += x[i];
			if (t == 30 || i == x.length() - 1)
			{
				*this = (*this) * QFloat(QInt(t1)) + QFloat(QInt(t2));	// a(b) = a * 10^p + b
				t = 0;
				t1 = "1";
				t2 = "";
			}
			//cout << *this << endl;
		}

	// Sau do dem chia cho 10^b
	for (int i = 1; i <= x.length() - pos - 1; i++)
	{
		t++;
		t1 += "0";
		if (t == 30 || i == x.length() - pos - 1)
		{
			*this = (*this) / QFloat(QInt(t1));
			t = 0;
			t1 = "1";
		}
	}
	if (flag) this->setBitAt(1, 0);
}

QFloat::~QFloat()
{
	delete[] this->m_bits;
	this->m_bits = NULL;
}

string QFloat::toString()
{
	if (this->isZero()) return "0";
	if (this->isInf()) return "Inf";
	if (this->isNaN()) return "NaN";
	// dec = tri * 2^e = (...) * 2^(e - 112)
	// tri = 1 + 2^... = 2^-112 * (2^112 + 2^...)
	QInt a = this->getSignificant();	// Phan tri * 2^(-112)
	if (!(this->getExponent() == QInt(0)))
		a.setBitAt(BITS[2] - 1);		// Lay so 1 (hoac 0 neu la so khong chuan)

	int p2 = -getBitLength(3) + this->getExponent().toInt() - BIAS_KEY;	// 2^p2 (p2 = e - 112)
	int p10 = 0;	// 10^p10
	if (p2 < 0)				// p2 < 0 nghia la chia 2^p2
	{
		p2 = -p2;
		a = a * QInt(1000);		// 1000~2^10
		p10 -= 3;
		while (p2 >= 30)
		{
			// Lien tuc chia cho 2^30 roi nhan cho 1e9
			// Khi nhan cho 1e9 thi phan mu 10 giam 9
			a = a >> 30;
			a = a * QInt(int(1e9));
			p10 -= 9;
			p2 -= 30;
		}
		a = a >> p2;
	}
	else if (p2 > 0)		// p2 > 0 nghia la nhan 2^p2
	{
		while (p2 >= 30)
		{
			// Uu tien chia 1e9 truoc roi nhan 2^30
			// Chia 1e9 thi phan mu 10 tang 9
			a = a / QInt(int(1e9));
			a = a << 30;
			p10 += 9;
			p2 -= 30;
		}
		a = a / QInt(int(1e9));
		p10 += 9;
		a = a << p2;
	}

	// Dua ve chuoi, them dau . vao
	stringstream buf;
	buf << a;
	string tmp = buf.str();
	int d = (tmp[10] >= '5');
	for (int i = 10; i < tmp.length(); i++) tmp[i] = '0';
	tmp = "0" + tmp;
	for (int i = 10; i > -1; i--)
		if (tmp[i] + d > '9')
			tmp[i] = '0';
		else
		{
			tmp[i] += d;
			d = 0;
		}
	while (tmp[0] == '0' && tmp[1] != '.') tmp.erase(0, 1);
	p10 += (tmp.length() - 1);
	tmp = tmp[0] + tmp;
	tmp[1] = '.';
	if (p10 > 0 && p10 <= 10)
	{
		tmp = tmp + "0000000000";
		int i = 1;
		while (p10 > 0)
		{
			tmp[i] = tmp[i + 1];
			tmp[i + 1] = '.';
			i++;
			p10--;
		}
	}
	else if (p10 < 0 && p10 >= -10)
	{
		tmp = "0000000000" + tmp;
		int i = 11;
		while (p10 < 0)
		{
			tmp[i] = tmp[i - 1];
			tmp[i - 1] = '.';
			i--;
			p10++;
		}
		while (tmp[1] != '.') tmp.erase(0, 1);
	}
	while (tmp[tmp.length() - 1] == '0') tmp.erase(tmp.length() - 1, 1);
	if (tmp[tmp.length() - 1] == '.')
		if (p10 == 0)
			tmp.erase(tmp.length() - 1, 1);
		else
			tmp = tmp + "0";
	// Them phan mu 10 vao
	stringstream buff;
	if (this->getBitAt(1, 0)) buff << "-";
	buff << tmp;
	if (p10 < 0)
		buff << "e" << p10;
	else if (p10 > 0)
		buff << "e+" << p10;
	return buff.str();
}

bool QFloat::getBitAt(int p, int k)
{
	int x = BITS[p - 1] + k;
	int i = x / LENGTH;
	int j = x % LENGTH;
	return (this->m_bits[i] >> (LENGTH - j - 1)) & 1;
}

void QFloat::setBitAt(int p, int k)
{
	int x = BITS[p - 1] + k;
	int i = x / LENGTH;
	int j = x % LENGTH;
	this->m_bits[i] |= (1 << (LENGTH - j - 1));
}

void QFloat::turnBitAt(int p, int k)
{
	int x = BITS[p - 1] + k;
	int i = x / LENGTH;
	int j = x % LENGTH;
	this->m_bits[i] = this->m_bits[i] ^ (1 << (LENGTH - j - 1));
}

void QFloat::setBitAt(int k)
{
	int i = k / LENGTH;
	int j = k % LENGTH;
	this->m_bits[i] |= (1 << (LENGTH - j - 1));
}

bool QFloat::getBitAt(int k)
{
	int i = k / LENGTH;
	int j = k % LENGTH;
	return (this->m_bits[i] >> (LENGTH - j - 1)) & 1;
}

void QFloat::turnBitAt(int k)
{
	int i = k / LENGTH;
	int j = k % LENGTH;
	this->m_bits[i] = this->m_bits[i] ^ (1 << (LENGTH - j - 1));
}

bool QFloat::getSign()
{
	return this->getBitAt(1, 0);
}

QInt QFloat::getExponent()
{
	QInt ex;
	for (int i = 0; i < getBitLength(2); i++)
	{
		if (this->getBitAt(2, i) == 1)
			ex.setBitAt(TOTAL_LENGTH - getBitLength(2) + i);
	}
	return ex;
}

QInt QFloat::getSignificant()
{
	QInt sig;
	for (int i = 0; i < getBitLength(3); i++)
	{
		if (this->getBitAt(3, i) == 1)
			sig.setBitAt(BITS[2] + i);
	}
	return sig;
}

void QFloat::setExponent(QInt a)
{
	for (int i = 0; i < getBitLength(2); i++)
	{
		if (a.getBitAt(TOTAL_LENGTH - getBitLength(2) + i) != this->getBitAt(2, i))
			this->turnBitAt(2, i);
	}
}

void QFloat::setSignificant(QInt a)
{
	for (int i = 0; i < getBitLength(3); i++)
	{
		if (a.getBitAt(BITS[2] + i) != this->getBitAt(3, i))
			this->turnBitAt(3, i);
	}
}

QFloat& QFloat::operator =(const QFloat& a)
{
	for (int i = 0; i < N; i++)
		this->m_bits[i] = a.m_bits[i];
	return *this;
}

bool QFloat::operator ==(QFloat a)
{
	for (int i = 1; i <= 3; i++)
		for (int k = 0; k < getBitLength(i); k++)
			if (this->getBitAt(i, k) != a.getBitAt(i, k))
				return false;
	return true;
}

istream& operator >>(istream& fi, QFloat& a)
{
	string buf;
	fi >> buf;
	a = QFloat(buf);
	return fi;
}

ostream& operator <<(ostream& fo, QFloat a)
{
	fo << a.toString();
	return fo;
}

void QFloat::printExponent()
{
	bool* bits = QInt::DecToBin(this->getExponent());
	string tmp = "";
	for (int i = 0; i < QInt::TOTAL_LENGTH; i++) tmp = tmp + char(bits[i] + '0');
	while (tmp[0] == '0' && tmp.length() > 15) tmp.erase(0, 1);
	cout << tmp << endl;
	delete[] bits;
}

void QFloat::printSignificant()
{
	bool* bits = QInt::DecToBin(this->getSignificant());
	string tmp = "";
	for (int i = 0; i < QInt::TOTAL_LENGTH; i++) tmp = tmp + char(bits[i] + '0');
	while (tmp[0] == '0' && tmp.length() > 112) tmp.erase(0, 1);
	cout << tmp << endl;
	delete[] bits;
}

QFloat QFloat::operator+(QFloat a)
{
	QFloat result;

	QInt ex_this = this->getExponent(); //phần mũ của this
	QInt sig_this = this->getSignificant() + ONE_PLUS; //phần trị của this
	QInt ex_a = a.getExponent(); //phần mũ của a
	QInt sig_a = a.getSignificant() + ONE_PLUS; //phần trị của a

	//nếu là số không chuẩn thì không có ngầm định 1
	if (ex_this == QInt(0))
		sig_this = sig_this - ONE_PLUS;
	if (ex_a == QInt(0))
		sig_a = sig_a - ONE_PLUS;

	//số infinity và không xác định thì báo lỗi
	if (ex_this >= MAX_EX || ex_a >= MAX_EX)
		return result;

	bool isNegative = false;
	bool bitOne_this = false; //bit lấy lại dấu của dịch logic
	bool bitOne_a = false; //bit lấy lại dấu của dịch logic
	//nếu cả 2 đều âm thì bật cờ
	if ((this->getSign() == a.getSign()) && (a.getSign() == 1))
		isNegative = true;
	else
		//nếu riêng lẻ từng cái âm thì chuyển đổi phần trị sang bù 2
		if (this->getSign() == 1)
		{
			sig_this = ~sig_this + QInt(1);
			bitOne_this = true;
		}
		else
			if (a.getSign() == 1)
			{
				sig_a = ~sig_a + QInt(1);
				bitOne_a = true;
			}

	//nếu this = 0 thì return a
	if (*this == QFloat(0))
		return a;
	else
		//nếu a = 0 thì return this
		if (a == QFloat(0))
			return *this;



	QInt range;


	// nếu mũ a > mũ this
	if (ex_a > ex_this)
	{
		//tính độ chênh lệch mũ
		range = ex_a - ex_this;
		//đưa mũ của this về = mũ của a
		while (range > QInt(0))
		{
			//nếu phần trị bị underflow thì xem nó = 0 luôn
			if (sig_this == QInt(0))
				return a;
			//tăng mũ của this lên
			ex_this = ex_this + QInt(1);
			//dịch phải phần trị
			sig_this = sig_this >> 1;
			if (bitOne_this == true)
				sig_this.setBitAt(0);
			range = range - QInt(1);
		}
	}
	else
		//cái này tương tự phần trên, dùng cho mũ của a < mũ của this
		if (ex_a < ex_this)
		{
			range = ex_this - ex_a;
			while (range > QInt(0))
			{
				if (sig_a == QInt(0))
					return *this;
				//tăng mũ của a lên
				ex_a = ex_a + QInt(1);
				//dịch phải phần trị
				sig_a = sig_a >> 1;
				if (bitOne_a == true)
					sig_a.setBitAt(0);
				range = range - QInt(1);
			}
		}



	//cộng phần trị lại
	QInt sig = sig_this + sig_a;

	QInt ex = ex_a;


	//nếu cộng lại = 0 thì bằng 0
	if (sig == QInt(0))
		return QFloat(0);

	//nếu phần trị bị tràn thì dịch phải
	if (sig >= ONE_PLUS)
	{
		sig = sig >> 1;
		ex = ex + QInt(1);
		//cái này dùng để báo lỗi tràn mũ
		if (ex >= MAX_EX)
			return result;
	}

	//nếu cộng lại mà âm thì đổi phần trị thành dương, bật cờ isNegative
	if (sig < QInt(0))
	{
		sig = ~sig + QInt(1);
		isNegative = true;
	}

	//Kiểm tra xem chuẩn hóa chưa
	while (sig < ONE_PLUS)
	{
		//cái này là dành số dạng không chuẩn
		if (ex == QInt(0))
		{
			result.setExponent(ex);
			result.setSignificant(sig);
			if (isNegative)
				result.setBitAt(1, 0);
			return result;
		}
		//dịch sig qua trái và giảm mũ
		sig = sig << 1;
		ex = ex - QInt(1);
	}

	result.setExponent(ex);
	result.setSignificant(sig);
	if (isNegative)
		result.setBitAt(1, 0);
	return result;
}

QFloat QFloat::operator-(QFloat a)
{
	//đổi dấu của a
	a.turnBitAt(1, 0);
	return (*this + a);
}

// *********************************************************************
// by Vu

// Ham chuyen doi tu so QFloat dang thap phan sang dang nhi phan
// Dau vao la so QFloat dang thap phan
bool* QFloat::DecToBin(QFloat x)
{
	bool* BinQIint = new bool[TOTAL_LENGTH];	//Day so QInt dang nhi phan
	for (int i = 0; i < TOTAL_LENGTH; i++) {
		BinQIint[i] = x.getBitAt(i);
	}
	return BinQIint;
}

// Ham chuyen doi tu so QFloat dang nhi phan sang dang thap phan
// Dau vao la so QFloat dang nhi phan bieu dien bang mang bool: bit
QFloat QFloat::BinToDec(bool* bit)
{
	QFloat DecQInt;								//Day so QInt duoi dang thap phan; Khoi tao bang dau gom 4 byte 0
	for (int i = 0; i < TOTAL_LENGTH; i++) {
		if (bit[i]) {
			DecQInt.setBitAt(i);
		}
	}
	return DecQInt;
}

bool QFloat::isZero()
{
	for (int i = BITS[1]; i < BITS[3]; i++) {
		if (this->getBitAt(i) == 1) return false;
	}
	return true;
}

bool QFloat::isNaN()
{
	for (int i = BITS[1]; i < BITS[2]; i++) {
		if (this->getBitAt(i) == 0) return false;
	}
	for (int i = BITS[2]; i < BITS[3]; i++) {
		if (this->getBitAt(i) == 1) return true;
	}
	return false;
}

bool QFloat::isInf()
{
	for (int i = BITS[1]; i < BITS[2]; i++) {
		if (this->getBitAt(i) == 0) return false;
	}
	for (int i = BITS[2]; i < BITS[3]; i++) {
		if (this->getBitAt(i) == 1) return false;
	}
	return true;
}

bool QFloat::isDeN()
{
	for (int i = BITS[1]; i < BITS[2]; i++) {
		if (this->getBitAt(i) == 1) return false;
	}
	for (int i = BITS[2]; i < BITS[3]; i++) {
		if (this->getBitAt(i) == 1) return true;
	}
	return false;
}

QInt QFloat::multiBooth(const QInt& s1, const QInt& s2)
{
	QInt A;
	QInt Q = s1;
	QInt M = s2;

	for (int i = BITS[2] - 1; i < BITS[3]; i++) {
		if (M.getBitAt(i)) {
			A = A + Q;
		}

		Q = Q >> 1;
	}
	return A;
}

QFloat QFloat::operator*(QFloat a)
{
	// Kiem tra * 0
	if (this->isZero() || a.isZero()) {
		return QFloat("Zero");
	}

	// Kiem tra dang loi NaN
	if (this->isNaN() || a.isNaN()) {
		return QFloat("NaN");
	}

	// Kiem tra dang vo cuc
	if (this->isInf() || a.isInf()) {
		if (this->getBitAt(0) ^ a.getBitAt(0)) return QFloat("-Inf");
		else return QFloat("+Inf");
	}

	QFloat result;

	QInt ex_this = this->getExponent(); //phần mũ của this
	QInt sig_this = this->getSignificant() + ONE_PLUS; //phần trị của this
	QInt ex_a = a.getExponent(); //phần mũ của a
	QInt sig_a = a.getSignificant() + ONE_PLUS; //phần trị của a

	//nếu là số không chuẩn thì không có ngầm định 1
	if (this->isDeN())
		sig_this = sig_this - ONE_PLUS;
	if (a.isDeN())
		sig_a = sig_a - ONE_PLUS;

	QInt ex_res = ex_this + ex_a - BIAS_EX;

	QInt sig_res = multiBooth(sig_this, sig_a);

	// Chuan hoa phan thap phan
	// tang so mu
	for (int i = BITS[0]; i < BITS[2] - 1; i++)
		if (sig_res.getBitAt(i)) {
			int temp = (BITS[2] - 1) - i;
			sig_res = sig_res >> temp;
			ex_res = ex_res + QInt(temp);
			break;
		}

	// Giam so mu
	while (!sig_res.getBitAt(BITS[2] - 1) && ex_res > QInt(0))
	{
		sig_res = sig_res << 1;
		ex_res = ex_res - QInt(1);
	}

	result.setSignificant(sig_res);
	result.setExponent(ex_res);

	if (this->getBitAt(0) ^ a.getBitAt(0)) result.setBitAt(1, 0);

	return result;
}

QInt QFloat::divisBooth(const QInt& s1, const QInt& s2)
{
	QInt A;
	QInt Q = s1;
	QInt M = s2;

	for (int i = BITS[2] - 1; i < BITS[3]; i++) {
		if (Q / M > QInt(0)) {
			A.setBitAt(i);
			Q = Q - M;
			Q = Q << 1;
		}
		else {
			Q = Q << 1;
		}
		if (Q == QInt(0)) break;
	}

	/*
	cout << endl;
	A.printBits();
	Q.printBits();
	M.printBits();
	cout << endl;
	*/

	return A;
}

QFloat QFloat::operator/(QFloat a)
{
	// Kiem tra dang loi NaN
	if (this->isNaN() || a.isNaN()) {
		return QFloat("NaN");
	}

	// Kiem tra 0
	if (this->isZero()) {
		return QFloat("Zero");
	}

	if (a.isZero()) {
		return QFloat("NaN");
	}


	// Kiem tra dang vo cuc
	if (this->isInf() && a.isInf()) {
		return QFloat("NaN");
	}

	if (this->isInf()) {
		if (this->getBitAt(0) ^ a.getBitAt(0)) return QFloat("-Inf");
		else return QFloat("+Inf");
	}

	if (a.isInf()) {
		return QFloat("Zero");
	}


	QFloat result;

	QInt ex_this = this->getExponent(); //phần mũ của this
	QInt sig_this = this->getSignificant() + ONE_PLUS; //phần trị của this
	QInt ex_a = a.getExponent(); //phần mũ của a
	QInt sig_a = a.getSignificant() + ONE_PLUS; //phần trị của a

	//nếu là số không chuẩn thì không có ngầm định 1
	if (this->isDeN())
		sig_this = sig_this - ONE_PLUS;
	if (a.isDeN())
		sig_a = sig_a - ONE_PLUS;

	/*
	cout << endl;
	ex_this.printBits();
	sig_this.printBits();
	ex_a.printBits();
	sig_a.printBits();
	cout << endl;
	*/

	QInt ex_res = ex_this - ex_a + BIAS_EX;

	QInt sig_res = divisBooth(sig_this, sig_a);

	// Chuan hoa phan thap phan
	// tang so mu
	for (int i = BITS[0]; i < BITS[2] - 1; i++)
		if (sig_res.getBitAt(i)) {
			int temp = (BITS[2] - 1) - i;
			sig_res = sig_res >> temp;
			ex_res = ex_res + QInt(temp);
			break;
		}

	// Giam so mu
	while (!sig_res.getBitAt(BITS[2] - 1) && ex_res > QInt(0))
	{
		sig_res = sig_res << 1;
		ex_res = ex_res - QInt(1);
	}

	/*
	cout << endl;
	ex_res.printBits();
	sig_res.printBits();
	cout << endl;
	*/

	result.setSignificant(sig_res);
	result.setExponent(ex_res);

	if (this->getBitAt(0) ^ a.getBitAt(0)) result.setBitAt(1, 0);

	return result;
}

void QFloat::printBits()
{
	bool* bits = QFloat::DecToBin(*this);
	string tmp = "";
	for (int i = 0; i < QInt::TOTAL_LENGTH; i++) tmp = tmp + char(bits[i] + '0');
	while (tmp[0] == '0' && tmp.length() > 112) tmp.erase(0, 1);
	cout << tmp << endl;
	delete[] bits;
}