
// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "五子棋.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include <afxwin.h>
#include <Gdiplus.h>
#include <stdio.h>
#include <consoleapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define player1 1
#define player2 2
// CGameDlg 对话框



CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);



}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGameDlg::OnBnClickedOk)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCANCEL, &CGameDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE


	
}



// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameDlg::OnPaint()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	printf("==========>\n");
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();
	}

	//绘制棋盘
	CClientDC cliendc(this);
	for (int i = 1; i < 16; i++)
	{

		cliendc.MoveTo(50, 50 * i);
		cliendc.LineTo(750, 50 * i);
	}
	for (int i = 1; i < 16; i++)
	{
		cliendc.MoveTo(50 * i, 50);
		cliendc.LineTo(50 * i, 750);
	}


	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CGameDlg::OnBnClickedOk()
{
	CClientDC cclientdc(this);
	//cclientdc.getp
}

BOOL CGameDlg::HelpRect(COLORREF color)
{
	//2从中间点开始画旗子落下的位置
	CPen pen(PS_SOLID, 1, color);
	CClientDC cclientdc(this);
	CPen *pOldPen = cclientdc.SelectObject(&pen);

	cclientdc.MoveTo(m_centPoint.x - 15, m_centPoint.y - 15);
	cclientdc.LineTo(m_centPoint.x - 10, m_centPoint.y - 15);

	cclientdc.MoveTo(m_centPoint.x + 10, m_centPoint.y - 15);
	cclientdc.LineTo(m_centPoint.x + 15, m_centPoint.y - 15);

	cclientdc.MoveTo(m_centPoint.x - 15, m_centPoint.y - 15);
	cclientdc.LineTo(m_centPoint.x - 15, m_centPoint.y - 10);

	cclientdc.MoveTo(m_centPoint.x - 15, m_centPoint.y + 10);
	cclientdc.LineTo(m_centPoint.x - 15, m_centPoint.y + 15);
	//============
	cclientdc.MoveTo(m_centPoint.x + 15, m_centPoint.y + 15);
	cclientdc.LineTo(m_centPoint.x + 10, m_centPoint.y + 15);

	cclientdc.MoveTo(m_centPoint.x + 15, m_centPoint.y + 15);
	cclientdc.LineTo(m_centPoint.x + 15, m_centPoint.y + 10);
	cclientdc.MoveTo(m_centPoint.x - 15, m_centPoint.y + 15);
	cclientdc.LineTo(m_centPoint.x - 10, m_centPoint.y + 15);

	cclientdc.MoveTo(m_centPoint.x + 15, m_centPoint.y - 15);
	cclientdc.LineTo(m_centPoint.x + 15, m_centPoint.y - 10);
	cclientdc.SelectObject(pOldPen);
	return 1;
}

void CGameDlg::Flag(COLORREF color)
{
	CClientDC dc(this);
	CBrush brush, *oldbrush;
	brush.CreateSolidBrush(color);
	oldbrush = dc.SelectObject(&brush);
	dc.Ellipse(m_centPoint.x - 15, m_centPoint.y - 15, m_centPoint.x + 15, m_centPoint.y + 15);
	dc.SelectObject(oldbrush);
}

bool CGameDlg::m_bIsRule(int player)
{
	int isok = false;
	for (int zz = 0; zz < 5; zz++)
	{
		if (m_igameVictoryList[zz] != player)
		{
			isok = false;
			//memset(&m_igameVictoryList, 0, 5);
			break;
		}
		else
		{
			isok = true;
		}
	}
	return isok;
}

void CGameDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	
	//锁定棋盘内
	if ((point.x > 35 && point.y > 35) && (point.x < 765 && point.y < 765))
	{
		this->HelpRect(GetSysColor(COLOR_3DFACE));
		//1获取中心交叉点位置 算法
		//Sleep(200);
		
		
		int zhengchuX = point.x / 50;
		int zhengchuy = point.y / 50;
		if (point.x % 50 > 25)//如果超过中心点x范围
		{
			this->m_centPoint.x = 50 * (zhengchuX + 1);
		}
		else 
		{
			this->m_centPoint.x = 50 * (zhengchuX);
		}

		if (point.y % 50 > 25)//如果超过中心点y范围
		{
			this->m_centPoint.y = 50 * (zhengchuy + 1);
		}
		else
		{
			this->m_centPoint.y = 50 * (zhengchuy);
		}
		system("cls");
		printf("%d  %d oldX:%d,oldy:%d    x:%d    y:%d------------%d\n", zhengchuX, zhengchuy, point.x, point.y, this->m_centPoint.x, this->m_centPoint.y, nFlags);
		this->HelpRect(RGB(33, 33, 33));
	
	}
}

void CGameDlg::OnLButtonDown(UINT, CPoint)
{
	CClientDC cdc(this);
	COLORREF color=GetPixel(cdc, m_centPoint.x, m_centPoint.y);
	if (color == RGB(255, 0, 0) || color == RGB(0, 0, 255))
	{
		AfxMessageBox(L"该位置已经有子了！");
		return;
	}
	if (m_bOrder == 2)//红方
	{
		this->Flag(RGB(255, 0, 0));
		m_bOrder = 1;
	}
	else
	{//蓝方先行
		this->Flag(RGB(0, 0, 255));
		m_bOrder = 2;
	}
	//游戏下字逻辑
	int x = m_centPoint.x / 50;
	int y = m_centPoint.y / 50;
	if (m_igameRule[x - 1][y - 1] != 0)
	{
		AfxMessageBox(L"该位置已经有子了！");
		return;
	}
	m_igameRule[x - 1][y - 1] = m_bOrder;


	//游戏胜负检测逻辑
	memset(&m_igameList, 0, m_igameList.GetCount());

	int z = 0;
	//
	int zs = 0;
	int arr[5] = {0};

		for (; zs<5; zs++)
		{
			if ((y - 1 - z) >= 0)
			{
				for (int ss=4;ss>=0;ss--)
				{
					arr[ss] = m_igameRule[x - 1][y - 1 - z];
					z++;
				}
				for (int ii = 0; ii < 5; ii++)
				{
					m_igameList.Add(arr[ii]);
				}

			}
		}
		

		for (z=0; z < 5; z++)
		{
			if ((y - 1 + z) < 15)
			{

				m_igameList.Add(m_igameRule[x - 1][y - 1 + z+1]);

			}
		}


		int rulenumber = 0;
		int s=2;
		for (int zzz=0;zzz<m_igameList.GetCount();zzz++)
		{
			if (s = m_igameList.GetAt(zzz))
			{
				rulenumber++;
				if (rulenumber==5)
				{
					AfxMessageBox(L"2ok");
				}
				else
				{
					rulenumber = 0;
				}
			}
			

		}

		return;
/*
	if (y - 1 - 0 >= 4)
	{
		for (; z < 5; z++)
		{
			m_igameList.Add(m_igameRule[x - 1][y - 1 - z]);
		}
	}*/

}


void CGameDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitProcess(0);
}
