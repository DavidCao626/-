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
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CRect temprect(0, 0, 800, 825);
	CWnd::SetWindowPos(NULL, 0, 0, temprect.Width(), temprect.Height(), SWP_NOZORDER | SWP_NOMOVE);
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
BOOL CGameDlg::GameInit()
{
	CBitmapButton cbit;
	cbit.LoadBitmaps(IDB_PNG8);

	return 0;
}
void CGameDlg::OnPaint()
{
	#ifdef _DEBUG
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		printf("==========>\n");
	#endif
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
	
	//加载位图  
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

	//选入DC  
	CClientDC cdc(this);
	CDC comdc;
	comdc.CreateCompatibleDC(&cdc);
	comdc.SelectObject(&bitmap);

	//生成BITMAP  
	BITMAP bit;
	bitmap.GetBitmap(&bit);

	//客户区域  
	CRect rect;
	GetClientRect(rect);

	//用客户区的DC绘制所生成的BITMAP，并适应为窗口大小  
	cdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &comdc, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

	if (m_gameStart == 0)
	{
		this->GameInit();
		return;
	}

	//绘制棋盘
	CPen pen(PS_SOLID, 1, RGB(0x00, 0x45, 0x25));

	CClientDC cliendc(this);
	CPen *pOldPen = cliendc.SelectObject(&pen);
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
	cliendc.SelectObject(pOldPen);

}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CGameDlg::OnBnClickedOk()
{
	//
}

BOOL CGameDlg::HelpRect(COLORREF color)
{
	//2从中间点开始画旗子落下的位置
	CPen pen(PS_SOLID, 1, color);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//#
	CClientDC cclientdc(this);
	//CPen *pOldPen = cclientdc.SelectObject(&pen);
	CBrush *pOldPen = cclientdc.SelectObject(pBrush);//#(3)

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
//将png贴图透明
void TransparentPNG(CImage *png)
{
	for (int i = 0; i < png->GetWidth(); i++)
	{
		for (int j = 0; j < png->GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(png->GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
}
void CGameDlg::Flag(int pl)
{
	CClientDC dc(this);
	/*CBrush brush, *oldbrush;
	brush.CreateSolidBrush(color);

	oldbrush = dc.SelectObject(&brush);
	dc.Ellipse(m_centPoint.x - 20, m_centPoint.y - 20, m_centPoint.x + 20, m_centPoint.y + 20);
	dc.SelectObject(oldbrush);*/
	CImage  zi;
	if (pl == player1)
	{
		zi.Load(L"C:\\Users\\Administrator\\Source\\Repos\\-\\Debug\\wat.png");
	}
	else
	{
		zi.Load(L"C:\\Users\\Administrator\\Source\\Repos\\-\\Debug\\bak.png");
	}
	TransparentPNG(&zi);
	zi.Draw(dc, m_centPoint.x - 15, m_centPoint.y - 17, 40, 40);
}
bool CGameDlg::m_bIsRule(int player)
{
	int isok = false;
	return isok;
}
void CGameDlg::OnMouseMove(UINT nFlags, CPoint point)
{

	if (m_gameStart == 0)
	{
		this->GameInit();
		return;
	}
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	//锁定棋盘内
	if ((point.x > 35 && point.y > 35) && (point.x < 765 && point.y < 765))
	{
		CClientDC cdc(this);
		//this->HelpRect(RGB(0x00,0x8d,0x4c));

		//InvalidateRect();
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
		//this->HelpRect(RGB(33, 33, 33));

	}
}
void CGameDlg::OnLButtonDown(UINT, CPoint)
{
	if (m_gameStart == 0)
	{
		this->GameInit();
		return;
	}
	//游戏下字逻辑
	int x = m_centPoint.x / 50 - 1;
	int y = m_centPoint.y / 50 - 1;
	if (m_igameRule[x][y] != 0)
	{
		//AfxMessageBox(L"该位置已经有子了！");
		return;
	}
	if (m_bOrder == 2)//黑方
	{
		this->Flag(2);
		m_bOrder = 1;
	}
	else
	{//白方先行
		this->Flag(1);
		m_bOrder = 2;
	}
	m_igameRule[x][y] = m_bOrder;

	//游戏胜负检测逻辑
	int transverse = 0, zNumber = 0, forwardslash = 0, backslant = 0;//横、纵、正斜向、反斜向检测
	int left = 0, right = 1, top = 0, bottom = 1, upperlef = 0, lowerright = 1, Lowerleft = 0, rightupper = 1;
	while (1)
	{

		if (transverse == 5 || zNumber == 5 || forwardslash == 5 || backslant == 5)
		{
			for (int i1 = 0; i1 <= 14; i1++)
			{
				for (int z1 = 0; z1 <= 14; z1++)
				{
					m_igameRule[i1][z1] = 0;
				}
			}

			if (m_bOrder == 1)
			{
				if (CWnd::MessageBox(L"黑方胜利,再来一把？", L"游戏结束", MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
				{
					InvalidateRect(false);
					return;
				}
				else
				{
					ExitProcess(0);
				}
			}
			else if (m_bOrder == 2)
			{
				if (CWnd::MessageBox(L"白方胜利,再来一把？", L"游戏结束", MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
				{
					InvalidateRect(false);
					return;
				}
				else
				{
					ExitProcess(0);
				}

			}

		}
		//TODO :边界判断 
		if (m_igameRule[x - left][y] == m_bOrder)
		{
			transverse++;
			left++;
		}
		else if (m_igameRule[x + right][y] == m_bOrder)
		{
			transverse++;
			right++;
		}
		else if (m_igameRule[x][y - top] == m_bOrder)
		{
			zNumber++;
			top++;
		}
		else if (m_igameRule[x][y + bottom] == m_bOrder)
		{
			zNumber++;
			bottom++;
		}
		else if (m_igameRule[x - upperlef][y - upperlef] == m_bOrder)
		{
			forwardslash++;
			upperlef++;
		}
		else if (m_igameRule[x + lowerright][y + lowerright] == m_bOrder)
		{
			forwardslash++;
			lowerright++;
		}

		else if (m_igameRule[x + Lowerleft][y - Lowerleft] == m_bOrder)
		{
			backslant++;
			Lowerleft++;
		}
		else if (m_igameRule[x - rightupper][y + rightupper] == m_bOrder)
		{
			backslant++;
			rightupper++;
		}

		else
		{
			break;
		}

	}

}

void CGameDlg::OnBnClickedCancel()
{

	if (m_gameStart == 0)
	{
		this->GameInit();
		return;
	}
	for (int i1 = 0; i1 <= 14; i1++)
	{
		for (int z1 = 0; z1 <= 14; z1++)
		{
			m_igameRule[i1][z1] = 0;
		}
	}
	InvalidateRect(false);
	return;

}
