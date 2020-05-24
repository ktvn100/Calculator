
// CALCULATORDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CALCULATOR.h"
#include "CALCULATORDlg.h"
#include "afxdialogex.h"
#include "CalCore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCALCULATORDlg dialog



CCALCULATORDlg::CCALCULATORDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, m_output(_T(""))
	
	, m_reOutput(_T(""))
	, m_codeMode(_T("DEC"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME); 
}

void CCALCULATORDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_output);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Text(pDX, IDC_EDIT_HISTORY, m_reOutput);
	DDX_Control(pDX, IDC_EDIT_HISTORY, m_editHistory);
	DDX_Text(pDX, IDC_EDIT_CODE_MODE, m_codeMode);
	DDX_Control(pDX, IDC_EDIT_CODE_MODE, m_editMode);
}

BEGIN_MESSAGE_MAP(CCALCULATORDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_0, &CCALCULATORDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCALCULATORDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCALCULATORDlg::OnBnClickedButto2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCALCULATORDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCALCULATORDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCALCULATORDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCALCULATORDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCALCULATORDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCALCULATORDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCALCULATORDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_DOT, &CCALCULATORDlg::OnBnClickedButtonDot)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCALCULATORDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCALCULATORDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCALCULATORDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CCALCULATORDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, &CCALCULATORDlg::OnBnClickedButtonErase)
	ON_BN_CLICKED(IDC_BUTTON_ERASE_ALL, &CCALCULATORDlg::OnBnClickedButtonEraseAll)
	ON_BN_CLICKED(IDC_BUTTON_A, &CCALCULATORDlg::OnBnClickedButtonA)
	ON_BN_CLICKED(IDC_BUTTON_B, &CCALCULATORDlg::OnBnClickedButtonB)
	ON_BN_CLICKED(IDC_BUTTON_C, &CCALCULATORDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_D, &CCALCULATORDlg::OnBnClickedButtonD)
	ON_BN_CLICKED(IDC_BUTTON_E, &CCALCULATORDlg::OnBnClickedButtonE)
	ON_BN_CLICKED(IDC_BUTTON_F, &CCALCULATORDlg::OnBnClickedButtonF)
	ON_BN_CLICKED(IDC_BUTTON_SHIFT_LEFT, &CCALCULATORDlg::OnBnClickedButtonShiftLeft)
	ON_BN_CLICKED(IDC_BUTTON_SHIFT_RIGHT, &CCALCULATORDlg::OnBnClickedButtonShiftRight)
	ON_BN_CLICKED(IDC_BUTTON_NOT, &CCALCULATORDlg::OnBnClickedButtonNot)
	ON_BN_CLICKED(IDC_BUTTON_OR, &CCALCULATORDlg::OnBnClickedButtonOr)
	ON_BN_CLICKED(IDC_BUTTON_AND, &CCALCULATORDlg::OnBnClickedButtonAnd)
	ON_BN_CLICKED(IDC_BUTTON_XOR, &CCALCULATORDlg::OnBnClickedButtonXor)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CCALCULATORDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_BIN, &CCALCULATORDlg::OnBnClickedButtonBin)
	ON_BN_CLICKED(IDC_BUTTON_HEX, &CCALCULATORDlg::OnBnClickedButtonHex)
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CCALCULATORDlg::OnBnClickedButtonDec)
	ON_BN_CLICKED(IDC_BUTTON_ROL, &CCALCULATORDlg::OnBnClickedButtonRol)
	ON_BN_CLICKED(IDC_BUTTON_ROR, &CCALCULATORDlg::OnBnClickedButtonRor)
END_MESSAGE_MAP()


// CCALCULATORDlg message handlers

BOOL CCALCULATORDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// **** test 

	

	//*****

	// Font and change font
	m_outputFont.CreateFont(48, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));

	m_reOutputFont.CreateFont(36, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, 0, _T("Microsoft Sans Serif"));

	m_editResult.SetFont(&m_outputFont);

	m_editHistory.SetFont(&m_reOutputFont);

	

	// disable some button
	disableHexChar();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCALCULATORDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCALCULATORDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCALCULATORDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Them mot ki tu vao day ki tu tren man hinh hien thi
void CCALCULATORDlg::addChar(char character)
{
	// khoa tat ca dau khi da su dung (tru dau am)
	if (isOperator(character)) {
		disableAllOperatorButton();
	}

	if (m_output.GetLength() >= 2 && character == '-' && isOperator(m_output[m_output.GetLength() - 2]))
		disableNega();

	if (m_output.GetLength() >= 2 &&
		m_output[m_output.GetLength() - 2] == '-' &&
		m_output[m_output.GetLength() - 1] == ' ' &&
		!isOperator(character))
		disableNega();

	m_output += character;

	//****


	//****

	UpdateData(FALSE);

	int nLength = m_editResult.GetWindowTextLength();
	// put the selection at the end of text
	m_editResult.SetSel(nLength, nLength);
	// replace the selection
	//m_editResult.ReplaceSel(m_output);

}

void CCALCULATORDlg::delChar()
{
	while (m_output.GetLength() && m_output[m_output.GetLength() - 1] == ' ')
	{
		m_output.Delete(m_output.GetLength() - 1, 1);
	}

	if (m_output.GetLength() && m_output[m_output.GetLength() - 1] == '.') m_TypeIF -= 1;

	if (m_output.GetLength() && isOperator(m_output[m_output.GetLength() - 1]))
		if (m_output.GetLength() >= 3 &&
			(m_output[m_output.GetLength() - 1] == '-' ) &&
			isOperator(m_output[m_output.GetLength() - 3])) enableNega();
		else enableAllOperatorButton();

	if (m_output.GetLength() >= 3 &&
		!isOperator(m_output[m_output.GetLength() - 1]) &&
		isOperator(m_output[m_output.GetLength() - 3])) enableNega();

	if (m_output.GetLength()) m_output.Delete(m_output.GetLength() - 1, 1);

	while (m_output.GetLength() && m_output[m_output.GetLength() - 1] == ' ' &&
		((m_output.GetLength() >= 2 && !isOperator(m_output[m_output.GetLength() - 2])) || m_output.GetLength()==1))
	{
		m_output.Delete(m_output.GetLength() - 1, 1);
	}

	UpdateData(FALSE);
}

void CCALCULATORDlg::delAllChar()
{
	m_output.Delete(0, m_output.GetLength());
	m_reOutput.Delete(0, m_reOutput.GetLength());

	m_TypeIF = 0;

	enableAllOperatorButton();

	UpdateData(FALSE);
}

void CCALCULATORDlg::printResult(int typeR)
{
	if (!m_output.GetLength()) return;

	m_reOutput = m_output;

	string pt = "";

	bool checkOp = 0;

	switch (typeR)
	{
	case 0: // dau = 
		if (m_BIN) pt = "2 ";
		else if (m_DEC) pt = "10 ";
		else pt = "16 ";

		//Check nhap 1 so khong phep toan
		
		for (int i = 0; i < m_output.GetLength(); i++)
			if (isOperator(m_output[i]) && !(i==0 && m_output[i]=='-')) {
				checkOp = 1;
				if (m_output[i] == '/') m_TypeIF = 1;
				break;
			}
		if (!checkOp) pt += "0 + ";

		break;

	case 1: // Doi sang BIN
		if (m_BIN) return;
		else if (m_DEC) pt = "10 2 ";
		else pt = "16 2 ";

		break;

	case 2: // Doi sang DEC
		if (m_BIN) pt = "2 10 ";
		else if (m_DEC) return;
		else pt = "16 10 ";

		break;

	case 3: // Doi sang HEX
		if (m_BIN) pt = "2 16 ";
		else if (m_DEC) pt = "10 16 ";
		else return;

		break;

	default:
		pt = "ERROR!";
		break;
	}

	for (int i = 0; i < m_output.GetLength(); i++)
		pt += m_output[i];

	// ham tinh se dat cho nay
	string tmp = "";

	if (m_TypeIF == 0)
		tmp = process(QInt(0), pt);
	else
		tmp = process(QFloat(0), pt);

	m_output = tmp.c_str();

	UpdateData(FALSE);

	m_reOutput = m_reOutput + " = " + m_output;

	if (typeR == 0) m_output = "";

	if (typeR == 0) m_TypeIF = 0;

	enableAllOperatorButton();
}


// Cac ham click

void CCALCULATORDlg::OnBnClickedButton0()
{
	addChar('0');
}


void CCALCULATORDlg::OnBnClickedButton1()
{
	addChar('1');
}


void CCALCULATORDlg::OnBnClickedButto2()
{
	addChar('2');
}


void CCALCULATORDlg::OnBnClickedButton3()
{
	addChar('3');
}


void CCALCULATORDlg::OnBnClickedButton4()
{
	addChar('4');
}


void CCALCULATORDlg::OnBnClickedButton5()
{
	addChar('5');
}


void CCALCULATORDlg::OnBnClickedButton6()
{
	addChar('6');
}


void CCALCULATORDlg::OnBnClickedButton7()
{
	addChar('7');
}


void CCALCULATORDlg::OnBnClickedButton8()
{
	addChar('8');
}


void CCALCULATORDlg::OnBnClickedButton9()
{
	addChar('9');
}


void CCALCULATORDlg::OnBnClickedButtonDot()
{
	addChar('.');
	m_TypeIF += 1;
}


void CCALCULATORDlg::OnBnClickedButtonPlus()
{
	addChar(' ');
	addChar('+');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonMinus()
{
	if (m_output.GetLength() == 0) {
		addChar('-');
	}
	else if ((m_output[m_output.GetLength() - 1] >= '0' && m_output[m_output.GetLength() - 1] <= '9') ||
		(m_output[m_output.GetLength() - 1] >= 'A' && m_output[m_output.GetLength() - 1] <= 'F')) {
		addChar(' ');
		addChar('-');
		addChar(' ');
	}
	else {
		addChar('-');
	}
}


void CCALCULATORDlg::OnBnClickedButtonMultiply()
{
	addChar(' ');
	addChar('*');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonDivide()
{ 
	addChar(' ');
	addChar('/');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonErase()
{
	delChar();
}


void CCALCULATORDlg::OnBnClickedButtonEraseAll()
{
	delAllChar();
}


void CCALCULATORDlg::OnBnClickedButtonA()
{
	addChar('A');
}


void CCALCULATORDlg::OnBnClickedButtonB()
{
	addChar('B');
}


void CCALCULATORDlg::OnBnClickedButtonC()
{
	addChar('C');
}


void CCALCULATORDlg::OnBnClickedButtonD()
{
	addChar('D');
}


void CCALCULATORDlg::OnBnClickedButtonE()
{
	addChar('E');
}


void CCALCULATORDlg::OnBnClickedButtonF()
{
	addChar('F');
}


void CCALCULATORDlg::OnBnClickedButtonShiftLeft()
{
	addChar(' ');
	addChar('<');
	addChar('<');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonShiftRight()
{
	addChar(' ');
	addChar('>');
	addChar('>');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonNot()
{
	addChar('~');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonOr()
{
	addChar(' ');
	addChar('|');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonAnd()
{
	addChar(' ');
	addChar('&');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonXor()
{
	addChar(' ');
	addChar('^');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonEqual()
{
	printResult(0);
}


void CCALCULATORDlg::OnBnClickedButtonBin()
{
	// them ham tinh vao day

	printResult(1);

	changeMode(1);

	disableHexChar();
	disableDecNum();
	disableDot();
}


void CCALCULATORDlg::OnBnClickedButtonHex()
{
	// them ham tinh vao day

	printResult(3);

	changeMode(3);

	enableHexChar();
	enableDecNum();
	disableDot();
}


void CCALCULATORDlg::OnBnClickedButtonDec()
{
	// them ham tinh vao day

	printResult(2);

	changeMode(2);

	disableHexChar();
	enableDecNum();
	enableDot();
}


void CCALCULATORDlg::OnBnClickedButtonRol()
{
	//addChar(' ');
	addChar('r');
	addChar('o');
	addChar('l');
	addChar(' ');
}


void CCALCULATORDlg::OnBnClickedButtonRor()
{
	//addChar(' ');
	addChar('r');
	addChar('o');
	addChar('r');
	addChar(' ');
}

void CCALCULATORDlg::changeMode(int newMode) // 1-BIN; 2-DEC; 3-HEX
{
	m_BIN = m_DEC = m_HEX = 0;
	switch (newMode)
	{
	case 1:
		m_BIN = 1;
		m_codeMode = _T("BIN");
		break;

	case 2:
		m_DEC = 1;
		m_codeMode = _T("DEC");
		break;

	case 3:
		m_HEX = 1;
		m_codeMode = _T("HEX");
		break;

	default:
		m_DEC = 1;
		m_codeMode = _T("DEC");
		break;
	}

	UpdateData(FALSE);
	//m_editMode.UpdateData(FALSE);
}

bool CCALCULATORDlg::isOperator(char character)
{
	if (!((character >= '0' && character <= '9') ||
		(character >= 'A' && character <= 'F') ||
		(character == '.') || (character == ' ') || 
		(m_output.GetLength() == 0 && character == '-'))) {
		return true;
	}
	return false;
}

void CCALCULATORDlg::disableAllOperatorButton()
{
	GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_MULTIPLY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DIVIDE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_AND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_OR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_XOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_NOT)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_SHIFT_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SHIFT_RIGHT)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_ROL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ROR)->EnableWindow(FALSE);
}

void CCALCULATORDlg::enableAllOperatorButton()
{
	GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_MULTIPLY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DIVIDE)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_AND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_OR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_XOR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_NOT)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_SHIFT_LEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SHIFT_RIGHT)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_ROL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ROR)->EnableWindow(TRUE);

}

void CCALCULATORDlg::disableHexChar()
{
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_D)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_E)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_F)->EnableWindow(FALSE);
}

void CCALCULATORDlg::enableHexChar()
{
	GetDlgItem(IDC_BUTTON_A)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_B)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_C)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_D)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_E)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_F)->EnableWindow(TRUE);
}

void CCALCULATORDlg::disableDecNum()
{
	GetDlgItem(IDC_BUTTON_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_5)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_6)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_8)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_9)->EnableWindow(FALSE);
}

void CCALCULATORDlg::enableDecNum()
{
	GetDlgItem(IDC_BUTTON_2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_5)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_6)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_7)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_8)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_9)->EnableWindow(TRUE);
}

void CCALCULATORDlg::disableDot()
{
	GetDlgItem(IDC_BUTTON_DOT)->EnableWindow(FALSE);
}

void CCALCULATORDlg::enableDot()
{
	GetDlgItem(IDC_BUTTON_DOT)->EnableWindow(TRUE);
}

void CCALCULATORDlg::disableNega()
{
	GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
}

void CCALCULATORDlg::enableNega()
{
	GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
}
