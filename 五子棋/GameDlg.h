
// GameDlg.h : ͷ�ļ�
//

#pragma once


// CGameDlg �Ի���
class CGameDlg : public CDialogEx
{
// ����
public:
	CGameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CPoint m_centPoint;
	int m_bOrder=1;  //�ո�˭�¹���
	int m_igameRule[14][14] = { 0 };
	int m_igameVictoryList[4] = { 0 };
	
	CUIntArray m_igameList;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	BOOL HelpRect(COLORREF);
	void Flag(COLORREF);
	bool m_bIsRule(int player);//���˭ʤ����



	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT, CPoint);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg void OnBnClickedCancel();
};
