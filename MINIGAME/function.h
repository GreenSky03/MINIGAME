#pragma once
#include "pch.h"
#include "img.h"

int WORD_NUM = 64; // text - 1���� �ܾ� ����
int GAMEOVER_COUNT = 5; // ���ӿ��� Ƚ��
int CLEAR_NUM = 10; // Ŭ���� ���� Ƚ��
const int timeLimitSeconds = 7; // ���ѽð�

//���� �ܾ� �޾ƿ���
string get_word() {
    string str;
    ifstream inword("word_list.txt");

    if (!inword) {
        cout << "���� ���� �Ұ�";
        exit(-1);
    }

    srand(time(NULL));

    int rannum = rand() % WORD_NUM;
    int curnum = 0;


    while (getline(inword, str)) {
        if (rannum == curnum) {
            break;
        }
        curnum++;
    }
    return str;
}

//�ܾ� ���
void word_prn(string str, int miss_count, int clear_count) {
    GAMEMAIN_IMG();
    gotoxy(34, 11); line();
    gotoxy(34, 13); cout << "     HP     : ";

    setColor(RED);
    for (int a = GAMEOVER_COUNT - miss_count; a > 0; a--) cout << heart; //��� GAMEOVER_COUNT�� ���� �� Ʋ���� ����� -1�ϰ� ���� ������ �ִ� ��� ���
    for (int b = miss_count; b > 0; b--) cout << loseheart;
    setColor(WHITE);
    cout << endl;

    gotoxy(34, 14); line();
    gotoxy(34, 16); cout << " ���� ����  : ";
    setColor(YELLOW);
    for (int b = clear_count; b > 0; b--) cout << box;
    for (int a = CLEAR_NUM - clear_count; a > 0; a--) cout << empty_box;
    setColor(WHITE);
    cout << endl;
    gotoxy(34, 17); line();



    gotoxy(46, 19); cout << str << endl;
    gotoxy(34, 20); line();

    gotoxy(46, 23);
    setColor(GREEN);
    for (int i = 0; i < str.length(); i++) cout << "_";
    for (int i = 0; i < str.length(); i++) cout << "\b";
    setColor(WHITE);
}

// ����� �ܾ� �Է�
string input_asw(clock_t st, string str,  int miss_count) { //����� �ܾ��Է�
    string gameover = "gameover";
    int key = 0;
    string curstr, asw;
    while (true)
    {   
        clock_t check_time = clock();
        
        int time = (check_time - st) / CLOCKS_PER_SEC; // ����� �ð�
        
        
        if ((time) < timeLimitSeconds) {
            gotoxy(35, 10);
            cout << " �����ð�   : ";
            setColor(BLUE);
            for (int a = timeLimitSeconds - time; a > 0; a--) cout << box;
            for (int b = time; b > 0; b--) cout << empty_box;
            setColor(WHITE);
        }
        if (time >= timeLimitSeconds)
        {
            return gameover;
        }
        if (_kbhit() != 0)
        {
            key = _getch();    //Ű �Է� �޴� �Լ�
            if (key == ENTER)
            {
                asw = curstr;
                return curstr;
            }
            else if (key == BACKSPACE)
            {
                if (curstr.size() != 0)
                {
                    setColor(GREEN);
                    gotoxy(46 + curstr.length(), 23);
                    cout << "\b";
                    cout << "_";
                    setColor(WHITE);
                    curstr.pop_back();
                   
                    gotoxy(46, 23);
                    
                    cout << curstr;
                }
            }
            else
            {
                if (curstr.length() < str.length())
                {
                    curstr += key;
                    gotoxy(46, 23);
                    cout << curstr;
                }
            }
        }
    }
}

class Sound
{
public:
    Sound(string input)
    {
        if (input == "GameBGM")      //�ΰ��� BGM. ���� �̸� GameBGM.wav�� ������ ��
            PlaySound(TEXT("GameBGM.wav"), NULL, SND_ASYNC || SND_LOOP);

        if (input == "Clear")       //���� Ŭ���� �� ������ ȿ���� / ���� �̸� Gameclear.wav�� �����ϰ� ���̴� 3�� �̳��� �� ��
            PlaySound(TEXT("Gameclear.wav"), NULL, SND_ASYNC);

        if (input == "Gameover")    //���� ���� �� ������  ȿ���� / ���� �̸� Gameover.wav�� �����ϰ� ���̴� 3�� �̳��� �� ��
            PlaySound(TEXT("Gameover.wav"), NULL, SND_ASYNC);

        if (input == "Correct")     //���ڰ� �¾��� �� ������ ȿ���� / ������ 0.6��
        {
            Beep(260, 100);
            Beep(330, 100);
            Beep(380, 100);
        }
        if (input == "Wrong")       //���ڰ� Ʋ���� �� ������ ȿ���� / ������ 0.3��
        {
            Beep(330, 100);
            Beep(330, 100);
        }
        if (input == "Stop")        //BGM�� ���ߴ� ��ɾ�
            PlaySound(NULL, 0, 0);
    }
};