#pragma once


// Wait �Ի���

class Wait : public CDialogEx
{
	DECLARE_DYNAMIC(Wait)

public:
	Wait(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Wait();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
