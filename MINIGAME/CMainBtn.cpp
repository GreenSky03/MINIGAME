#include "pch.h"
#include "CMainBtn.h"


CMainBtn::CMainBtn()
	: bSelect(false)
	, tType(MENU_TYPE::END)
{
}

CMainBtn::~CMainBtn()
{
}

void CMainBtn::Render()
{
	if (bSelect)
		setColor(COLOR::BLUE);
	switch (tType)
	{
	case MENU_TYPE::PLAY:
		cout << "[ ���� �÷��� ]";
		break;
	case MENU_TYPE::LOGIN:
		cout << "[    �α���   ]";
		break;
	case MENU_TYPE::SIGNIN:
		cout << "[   ȸ������  ]";
		break;
	case MENU_TYPE::SCORE:
		cout << "[ ���� ���ھ� ]";
		break;
	case MENU_TYPE::DEV:
		cout << "[    ������   ]";
		break;
	case MENU_TYPE::QUIT:
		cout << "[    �� ��    ]";
		break;
	case MENU_TYPE::MINESWEEPER:
		cout << "[   ����ã��  ]";
		break;
	case MENU_TYPE::TYPINGGAME:
		cout << "[   Ÿ�ڿ���  ]";
		break;
	case MENU_TYPE::BACK:
		cout << "[   �ڷΰ���  ]";
		break;
	default:
		break;
	}
	setColor(COLOR::WHITE);
}