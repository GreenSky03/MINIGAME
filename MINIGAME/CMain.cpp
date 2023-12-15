#include "pch.h"
#include "CMain.h"
#include "CMainBtn.h"

CMain::CMain()
    : iSelect(0)
    , tCurMenu(MENU_TYPE::END)
{
}

CMain::~CMain()
{
}

void CMain::Init()
{
    system("cls");
    for (int i = 0; i < vMainBtnArr.size(); i++) {
        delete vMainBtnArr[i];
    }
    vMainBtnArr.clear();

    switch (tCurMenu)
    {
    case MENU_TYPE::PLAY:
        for (int i = (int)MENU_TYPE::MINESWEEPER; i <= (int)MENU_TYPE::BACK; i++) {
            CMainBtn* pMainBtnObj = new CMainBtn;
            pMainBtnObj->SetType(static_cast<MENU_TYPE>(i));
            vMainBtnArr.push_back(pMainBtnObj);
        }
        break;
    case MENU_TYPE::LOGIN:
        // TODO : �� ���̽����� ����̳� �Լ��� �ۼ��� �ּ���.
        break;
    case MENU_TYPE::SIGNIN:
        break;
    case MENU_TYPE::SCORE:
        break;
    case MENU_TYPE::DEV:
        break;
    case MENU_TYPE::QUIT:
        exit(0);
        break;
    case MENU_TYPE::MINESWEEPER:
        MineSweeper();
        tCurMenu = MENU_TYPE::PLAY;
        Init();
        PlaySound(TEXT("main.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        break;
    case MENU_TYPE::TYPINGGAME:
        TypingGame();
        tCurMenu = MENU_TYPE::PLAY;
        Init();
        PlaySound(TEXT("main.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        break;
    default:
        for (int i = 0; i <= (int)MENU_TYPE::QUIT; i++) {
            CMainBtn* pMainBtnObj = new CMainBtn;
            pMainBtnObj->SetType(static_cast<MENU_TYPE>(i));
            vMainBtnArr.push_back(pMainBtnObj);
        }
        break;
    }

    // �޴� �۾� �̿Ϸ�� ���� �߻��ϴ� ���� ó���Դϴ�. ���� ������ �Ϸ�Ǹ� ������ ���� �����մϴ�.
    try {
        if (vMainBtnArr.size() == 0) throw 0;
        vMainBtnArr[iSelect]->Select();
    }
    catch(int _) {
        tCurMenu = MENU_TYPE::END;
        Init();
    }
}

void CMain::Update()
{
    char cInput;
    while (true) {
        if (_kbhit()) {
            cInput = _getch();
            if (cInput == -32) {
                cInput = _getch();
                switch (cInput) {
                case RIGHT:
                case DOWN:
                    vMainBtnArr[iSelect]->UnSelect();
                    if (iSelect >= vMainBtnArr.size() - 1)
                        iSelect = 0;
                    else iSelect++;
                    vMainBtnArr[iSelect]->Select();
                    break;
                case LEFT:
                case UP:
                    vMainBtnArr[iSelect]->UnSelect();
                    if (iSelect <= 0)
                        iSelect = vMainBtnArr.size() - 1;
                    else iSelect--;
                    vMainBtnArr[iSelect]->Select();
                    break;
                }
                break;
            }
            else if (cInput == SPACE || cInput == ENTER) {
                if (vMainBtnArr[iSelect]->GetType() == MENU_TYPE::BACK) {
                    tCurMenu = MENU_TYPE::END;
                }
                else {
                    tCurMenu = vMainBtnArr[iSelect]->GetType();
                }
                Init();
                break;
            }
        }
    }
}

void CMain::Render()
{
    // �α���, ȸ������, ���� ���ھ�, ������ ���� ��� ȭ�� �۾� ��
    // �� �Լ� �ȿ��� Switch ���� ����ϴ� ���� �����մϴ�
    gotoxy(0, 0);
    cout << "\n\n\n";
    cout << "            ##   ##   ####    ##   #    ####        ####      ##     ##   ##  ######\n";
    cout << "            # # # #    ##     # #  #     ##        ##  ##    ####    # # # #  #     \n";
    cout << "            # ##  #    ##     # ## #     ##        ##       ##  ##   # # # #  #     \n";
    cout << "            #  #  #    ##     #  # #     ##        ## ###   ######   #  #  #  ####  \n";
    cout << "            #     #    ##     #  # #     ##        ##  ##   ##  ##   #     #  #     \n";
    cout << "            #     #    ##     #   ##     ##        ##  ##   ##  ##   #     #  #     \n";
    cout << "            #     #   ####    #   ##    ####        ####    ##  ##   #     #  ######\n\n\n";
    cout << "                                     2023 NSU COMPUTER SOFTWARE\n";
    cout << "                                              REVERSE\n\n";
    cout << "                                              VER 1.0\n\n\n";
    for (int i = 0; i < vMainBtnArr.size(); i++) {
        gotoxy(RESOLUTION.x / 2 - 8, i + 20);
        vMainBtnArr[i]->Render();
    }
}
