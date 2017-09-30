
// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "������.h"
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
// CGameDlg �Ի���



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


// CGameDlg ��Ϣ�������

BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE


	
}



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameDlg::OnPaint()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	printf("==========>\n");
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();
	}

	//��������
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	//2���м�㿪ʼ���������µ�λ��
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
	
	//����������
	if ((point.x > 35 && point.y > 35) && (point.x < 765 && point.y < 765))
	{
		this->HelpRect(GetSysColor(COLOR_3DFACE));
		//1��ȡ���Ľ����λ�� �㷨
		//Sleep(200);
		
		
		int zhengchuX = point.x / 50;
		int zhengchuy = point.y / 50;
		if (point.x % 50 > 25)//����������ĵ�x��Χ
		{
			this->m_centPoint.x = 50 * (zhengchuX + 1);
		}
		else 
		{
			this->m_centPoint.x = 50 * (zhengchuX);
		}

		if (point.y % 50 > 25)//����������ĵ�y��Χ
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
		AfxMessageBox(L"��λ���Ѿ������ˣ�");
		return;
	}
	if (m_bOrder == 2)//�췽
	{
		this->Flag(RGB(255, 0, 0));
		m_bOrder = 1;
	}
	else
	{//��������
		this->Flag(RGB(0, 0, 255));
		m_bOrder = 2;
	}
	//��Ϸ�����߼�
	int x = m_centPoint.x / 50;
	int y = m_centPoint.y / 50;
	if (m_igameRule[x - 1][y - 1] != 0)
	{
		AfxMessageBox(L"��λ���Ѿ������ˣ�");
		return;
	}
	m_igameRule[x - 1][y - 1] = m_bOrder;


	//��Ϸʤ������߼�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitProcess(0);
}
