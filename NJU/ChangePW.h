#pragma once
#include "NJU.h"

// ChangePW 对话框

class ChangePW : public CDialogEx
{
	DECLARE_DYNAMIC(ChangePW)

public:
	ChangePW(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChangePW();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
