#pragma once

class CMainBtn;

class CMain
{
	vector<CMainBtn*> vMainBtnArr;
	int iSelect;
	MENU_TYPE tCurMenu;
	string sCurId;
	bool bMsg;
public:
	void Init();
	void Update();
	void Render();
	MENU_TYPE GetCurMenu() {return tCurMenu;}
	void SetID(string _ID) { sCurId = _ID; }
	string GetID() { return sCurId; }


// ===== �̱��� =====
public:
	static CMain* GetInst()
	{
		static CMain mgr;
		return &mgr;
	}


private:
	CMain();
	~CMain();
// ==================
};

