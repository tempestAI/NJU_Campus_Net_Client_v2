// InputInfo_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NJU.h"
#include "InputInfo_Dlg.h"
#include "NJUDlg.h"
#include "afxdialogex.h"
#include "Wait.h"

extern char new_username[MAX_ID_LENGTH];
extern char new_password[MAX_PASSWORD_LENGTH];
extern int now_status; 
extern status *new_status;
extern char *info_file_loc;
extern char *user_file_loc;
extern char *pw_file_loc;
// InputInfo_Dlg �Ի���

IMPLEMENT_DYNAMIC(InputInfo_Dlg, CDialogEx)

InputInfo_Dlg::InputInfo_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

InputInfo_Dlg::~InputInfo_Dlg()
{
}

void InputInfo_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputInfo_Dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputInfo_Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &InputInfo_Dlg::OnEnChangeEdit2)
	ON_COMMAND(ID_32784, &InputInfo_Dlg::On32784)
END_MESSAGE_MAP()


// InputInfo_Dlg ��Ϣ�������

//��ȡ�༭�����ݣ�����¼
void InputInfo_Dlg::OnBnClickedOk()
{
	CString strTemp;
	GetDlgItemText(IDC_EDIT1, strTemp);
	char szTemp[128];
	memset(szTemp, 0, sizeof(szTemp));
	strcpy(szTemp, (char *)(strTemp.GetBuffer(strTemp.GetLength())));
	CString strTemp2;
	GetDlgItemText(IDC_EDIT2, strTemp2);
	char szTemp2[128];
	memset(szTemp2, 0, sizeof(szTemp2));
	strcpy(szTemp2, (char *)(strTemp2.GetBuffer(strTemp2.GetLength())));

	if (strTemp.IsEmpty() || strTemp2.IsEmpty())
	{
		AfxMessageBox(_T("�û���������Ϊ�գ�"));
		return;
	}

	Wait* Msgdlg = new Wait;
	Msgdlg->Create(IDD_DIALOG2, this);
	Msgdlg->UpdateData(FALSE);
	Msgdlg->ShowWindow(SW_SHOW);
	Msgdlg->RedrawWindow();
	logout();

	now_status = 0;
	strcpy(new_username, "\0");
	strcpy(new_password, "\0");
	strcpy(new_username, szTemp);
	strcpy(new_password, szTemp2);
	save_user();
	login();	
	Msgdlg->DestroyWindow();
	
	read_status(new_status);
	if (new_status->successful == 0)
	{
		CString s_fail(_T("��¼ʧ�ܣ�"));
		now_status = 0;
		CEdit *p_fail = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT3);
		p_fail->SetWindowText((LPCTSTR)s_fail);
		GetParent()->GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT5)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
		GetParent()->GetDlgItem(IDC_EDIT7)->SetWindowText(_T(""));
	}
	else
	{
		now_status = 1;
		//AfxMessageBox(_T("123"));
		CString s_succ(_T("��¼�ɹ���"));
		CEdit *p_succ = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT3);
		p_succ->SetWindowText((LPCTSTR)s_succ);
		CString s_username(new_status->username);
		CEdit *p_name = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT4);
		p_name->SetWindowText((LPCTSTR)s_username);
		CString s_num;
		s_num.Format(_T("%d"), new_status->device_amounts);
		CEdit *p_num = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT7);
		p_num->SetWindowText((LPCTSTR)s_num);
		CString s_rest;
		s_rest.Format(_T("%.2fԪ"), new_status->account_balance);
		CEdit *p_rest = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT5);
		p_rest->SetWindowText((LPCTSTR)s_rest);
		CString s_time;
		s_time.Format(_T("%dСʱ%d����"), new_status->hours, new_status->mins);
		CEdit *p_time = (CEdit*)GetParent()->GetDlgItem(IDC_EDIT6);
		p_time->SetWindowText((LPCTSTR)s_time);
	}
	CString s_butt;
	if (now_status == 0)
		s_butt.Format(_T("���µ�¼"));
	else
		s_butt.Format(_T("�ǳ�"));
	CEdit *p_butt = (CEdit*)GetParent()->GetDlgItem(IDC_BUTTON3);
	p_butt->SetWindowText((LPCTSTR)s_butt);

	EndDialog(0);
}


void InputInfo_Dlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void InputInfo_Dlg::On32784()
{
	// TODO: �ڴ���������������
	InputInfo_Dlg *p = new InputInfo_Dlg;
	p->Create(IDD_DIALOG1, this);
	p->ShowWindow(SW_SHOW);
}
