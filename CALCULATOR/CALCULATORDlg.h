
// CALCULATORDlg.h : header file
//

#pragma once

// CCALCULATORDlg dialog
class CCALCULATORDlg : public CDialogEx
{
// Construction
public:
	CCALCULATORDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// ham them ki tu tu  ban phim ao
	void addChar(char character);

	// ham xoa ki tu tu  ban phim ao
	void delChar();

	// ham xoa tat ca ki tu tu  ban phim ao
	void delAllChar();

	// ham in ket qua
	void printResult(int typeR);

	// font moi 
	CFont m_outputFont;
	CFont m_reOutputFont;	

	// output on the screen after pushing the button
	CString m_output;

	CEdit m_editResult;

	// hien thi lai input khi in result ra man hinh
	CString m_reOutput;

	CEdit m_editHistory;

private: // mod cho dang tinh toan va hien thi hien tai
	bool m_DEC = 1;
	bool m_BIN = 0;
	bool m_HEX = 0;
	int m_TypeIF = 0; // 0-Int; >0-Float 

public:
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButto2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();

	afx_msg void OnBnClickedButtonDot();

	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivide();

	afx_msg void OnBnClickedButtonErase();
	afx_msg void OnBnClickedButtonEraseAll();

	afx_msg void OnBnClickedButtonA();
	afx_msg void OnBnClickedButtonB();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonD();
	afx_msg void OnBnClickedButtonE();
	afx_msg void OnBnClickedButtonF();

	afx_msg void OnBnClickedButtonShiftLeft();
	afx_msg void OnBnClickedButtonShiftRight();

	afx_msg void OnBnClickedButtonNot();
	afx_msg void OnBnClickedButtonOr();
	afx_msg void OnBnClickedButtonAnd();
	afx_msg void OnBnClickedButtonXor();

	afx_msg void OnBnClickedButtonEqual();

	afx_msg void OnBnClickedButtonBin();
	afx_msg void OnBnClickedButtonHex();
	afx_msg void OnBnClickedButtonDec();

	afx_msg void OnBnClickedButtonRol();
	afx_msg void OnBnClickedButtonRor();

private:// code hien thi BIN DEC HEX
	CString m_codeMode;

	void changeMode(int newMode);

private: // mot so ham check
	bool isOperator(char character);

private: // disabel and enable some buttons
	// Operator button
	void disableAllOperatorButton();
	void enableAllOperatorButton();
	// HEX char button
	void disableHexChar();
	void enableHexChar();
	// DEC number button
	void disableDecNum();
	void enableDecNum();
	// DOT button
	void disableDot();
	void enableDot();
	// Nega
	void disableNega();
	void enableNega();

	CEdit m_editMode;
};
