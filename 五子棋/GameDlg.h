
// GameDlg.h : 头文件
//

#pragma once


// CGameDlg 对话框
class CGameDlg : public CDialogEx
{
// 构造
public:
	CGameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CPoint m_centPoint;
	int m_bOrder=1;  //刚刚谁下过了
	int m_igameRule[14][14] = { 0 };
	int m_igameVictoryList[4] = { 0 };
	
	CUIntArray m_igameList;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	BOOL HelpRect(COLORREF);
	void Flag(COLORREF);
	bool m_bIsRule(int player);//检测谁胜利了



	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT, CPoint);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg void OnBnClickedCancel();
};
