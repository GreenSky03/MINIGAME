#include "pch.h"
#include "CMain.h"
#include "CMainBtn.h"

CMain::CMain()
    : iSelect(0)
    , tCurMenu(MENU_TYPE::END)
    , sCurId(" ")
    , bMsg(false)
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
    case MENU_TYPE::LOGIN: //�Ϸ�
        LOGIN();
        tCurMenu = MENU_TYPE::END;
        Init();
        break;
    case MENU_TYPE::SIGNIN: //�Ϸ�
        SIGN_UP();
        tCurMenu = MENU_TYPE::END;
        Init();
        break;
    case MENU_TYPE::SCORE:
        Check_Score();
        tCurMenu = MENU_TYPE::END;
        Init();
        break;
    case MENU_TYPE::DEV:
        devsINFO();
        tCurMenu = MENU_TYPE::END;
        Init();
        break;
    case MENU_TYPE::QUIT: //�Ϸ�
        END();
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
        static time_t tMsgTimer = 0;
        if ((clock() - tMsgTimer) / CLOCKS_PER_SEC > 0.5 && bMsg) {
            tMsgTimer = 0;
            bMsg = false;
            break;
        }
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
                else if ((vMainBtnArr[iSelect]->GetType() == MENU_TYPE::PLAY || vMainBtnArr[iSelect]->GetType() == MENU_TYPE::SCORE)&& sCurId == " ") {
                    bMsg = true;
                    tMsgTimer = clock();
                }
                else {
                    tCurMenu = vMainBtnArr[iSelect]->GetType();
                    bMsg = false;
                    tMsgTimer = 0;
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
    system("cls");
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
    gotoxy(0, 18);
    if (bMsg) cout << "                                       �α����� �ʿ��մϴ�!                       ";
    gotoxy(0, 21);
    for (int i = 0; i < vMainBtnArr.size(); i++) {
        gotoxy(RESOLUTION.x / 2 - 8, i + 20);
        vMainBtnArr[i]->Render();
    }
}

