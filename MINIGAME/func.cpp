#include "pch.h"
#include "CGameMgr.h"
#include "CMain.h"

MYSQL Conn;                              // MySQL ���� ���� ����ü
MYSQL* ConnPtr = NULL;                  // MySQL �ڵ�
MYSQL_RES* Result;                      // ���� ������ ����� ��� ����ü ������
MYSQL_ROW Row;                  // ���� ������ ����� ���� ���� ������ ��� ����ü



void setColor(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursor() { //Ŀ�� �Ⱥ��̰�
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCusor;
	ConsoleCusor.bVisible = false;
	ConsoleCusor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCusor);
}

void MineSweeper() {
	CGameMgr::GetInst()->Init();
	while (true)
	{
		CGameMgr::GetInst()->Render();
		CGameMgr::GetInst()->Update();
		if (CGameMgr::GetInst()->Quit()) break;
	}
}

void SIGN_UP()
{

	///////////////////////////SQL ���� Ȯ��///////////////////////////

	MYSQL mysql;
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "34.64.226.23", "root", "", "MINIGAME", 3306, NULL, 0)) {
		cout << "error\n";
	}
	else {
		cout << "success\n";
	}

	mysql_init(&Conn); // MySQL ���� �ʱ�ȭ  

	///////////////////////////SQL ���� ����///////////////////////////

	ConnPtr = mysql_real_connect(&Conn, "34.64.226.23", "root", "", "MINIGAME", 3306, (char*)NULL, 0);

	// ���� ��� Ȯ��. null�� ��� ����
	if (ConnPtr == NULL) {
		fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
		return ;
	}

	///////////////////////////ȸ������///////////////////////////

	string UserName, UserId, UserPw;


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// �ϴ� ���� ���
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	std::cout << "\n\n\n";
	cout << "                ## ##     ####    ## ##   ###  ##           ##  ###  ### ##   \n";
	cout << "               ##   ##     ##    ##   ##    ## ##           ##   ##   ##  ##  \n";
	cout << "               ####        ##    ##        # ## #           ##   ##   ##  ##  \n";
	cout << "                #####      ##    ##  ###   ## ##            ##   ##   ##  ##  \n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << "                   ###     ##    ##   ##   ##  ##           ##   ##   ## ##   \n";
	cout << "               ##   ##     ##    ##   ##   ##  ##           ##   ##   ##      \n";
	cout << "                ## ##     ####    ## ##   ###  ##            ## ##   ####     \n";
	cout << "\n\n\n\n";
	// ������� �����Ͽ� ���� ����� ������� ��Ÿ������ ��
	SetConsoleTextAttribute(hConsole, 15);


	cout << "�̸��� �Է����ּ��� >> ";
	cin >> UserName;
	while (1) {
		cout << "���̵� �Է����ּ��� >> ";
		cin >> UserId;
		////���̵� �ߺ� Ȯ��

		// ID �ߺ� üũ�� ���� SQL ���� ����
		string idCheckQuery = "SELECT ID FROM customer_table WHERE ID = '" + UserId + "'";

		// SQL ���� ����
		mysql_query(&Conn, idCheckQuery.c_str());

		// ����� ����
		MYSQL_RES* idCheckResult = mysql_store_result(&Conn);

		// ��� ���� ������ Ȯ���Ͽ� �ߺ� ���θ� �Ǵ�
		if (mysql_num_rows(idCheckResult) == 0) {
			// ��� ��Ʈ ����
			mysql_free_result(idCheckResult);

			// �ߺ��� ������ �ݺ��� ����
			break;
		}

		cout << "�̹� �����ϴ� ���̵� �Դϴ�!\n";
		mysql_free_result(idCheckResult);
	}

	cout << "��й�ȣ�� �Է����ּ���.";
	cin >> UserPw;

	cout << "������ �������� ȯ���մϴ�!!!\n";
	Sleep(3000);

	//���� �ο� �Ǻ� �� No�� ����
	int No = 0; // ������ ȸ���� ��ϵǸ� NO(ȸ����ȣ)�� ȸ���� �ľ�


	// �� ���̺��� ���ڵ� ������ �������� ���� SQL ���� ����
	string AccountCountQuery = "SELECT COUNT(*) FROM customer_table";
	//�� ���̺� �ִ� ��� Į���� �˻����ּ���

	// SQL ���� ����
	if (mysql_query(&Conn, AccountCountQuery.c_str()) != 0) {
		// SQL ���� ���� �� ���� �߻� �� ���� �޽��� ���
		fprintf(stderr, "SQL �� ���� ����: %s\n", mysql_error(&Conn));
	}
	else {
		// SQL ���� ������ ������ ��� ����� ��������
		MYSQL_RES* result = mysql_use_result(&Conn);

		// ��� �� ��������
		MYSQL_ROW row = mysql_fetch_row(result);

		// ��� ���� �����ϴ� ���
		if (row != NULL) {
			// ���ڵ� ������ ������ ��ȯ�Ͽ� No ������ ����
			No = atoi(row[0]); //atoi()���� ������ ��ȯ

			// ��� ��Ʈ ����
			mysql_free_result(result);
		}
	}
	//���� �ο� +1 =No   ex) �����̺� 5���� ���� �����ϸ� ���� ȸ�����ʹ� NO.6 ����
	No += 1;

	// ȸ�� ������ �����ͺ��̽��� �����ϱ� ���� SQL ���� ���� �� ����
	string insertQuery = "INSERT INTO `MINIGAME`.`customer_table` (`No`, `ID`, `Name`, `Password`) VALUES ('" + to_string(No) + "','" + UserId + "', '" + UserName + "', '" + UserPw + "')";

	if (mysql_query(&Conn, insertQuery.c_str()) != 0) {
		fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
	}
}

void LOGIN()
{
	string InputId, InputPw;
	int missing = 0;
	string MemberNo = "NULL";


	mysql_init(&Conn); // MySQL ���� �ʱ�ȭ

	// �����ͺ��̽��� ����
	ConnPtr = mysql_real_connect(&Conn, "34.64.226.23", "root", "", "MINIGAME", 3306, (char*)NULL, 0);
	// MySql DB�� �����ϱ� ���� ��
	//  MYSQL ����ü�� ���� �����ͷ� ��, ���� ���� �� ����ü�� �ʱ�ȭ ȣ��Ʈ�� / ����� �̸� / ��й�ȣ / ��Ű�� / ��Ʈ��ȣ / �����Ϳ� ���� 0 ��� C++���� NULL�� �ؼ�

	// ���� ��� Ȯ��. null�� ��� ����
	if (ConnPtr == NULL) {
		fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
		return;
	}

	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//�ϴ� ���� ���
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "\n\n\n";
	cout << "                            ##        ##        ## ##    ####   ###   ##\n";
	cout << "                            ##      ##   ##   ##   ##     ##      ##  ##\n";
	cout << "                            ##      ##   ##   ##          ##     # ## ##\n";
	cout << "                            ##      ##   ##   ##  ###     ##     ## ##\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << "                            ##      ##   ##   ##   ##     ##     ##  ##\n";
	cout << "                            ##       ## ##     ##   ##    ##     ##  ##\n";
	cout << "                            ### ###   ##        ## ##    ####   ###  ##\n";

	SetConsoleTextAttribute(hConsole, 15);
	cout << "\n\n\n\n";


	while (1)
	{
		cout << "\n";
		cout << "���̵� �Է��ϼ��� >> ";
		cin >> InputId;
		cout << "��й�ȣ�� �Է��ϼ��� >> ";
		cin >> InputPw;

		// SQL ���� - customer_table���� ID�� �ִ� ��� Į���� �����ּ���
		string query = "SELECT * FROM customer_table WHERE ID = '" + InputId + "' AND password = '" + InputPw + "'";
		// SQL ������ �����ϰ� ���� ���� Ȯ��
		if (mysql_query(&Conn, query.c_str()) == 0) {
			// ����� ����
			MYSQL_RES* result = mysql_store_result(&Conn);

			// ����� ���� ���
			if (result) {
				// ù ��° ���� ������
				MYSQL_ROW row = mysql_fetch_row(result);

				// ���� �����ϸ� �α��� ����
				if (row) {
					// ��� ��Ʈ ����
					mysql_free_result(result);

					// �α����� ������� ������ �ٽ� �������� SQL ���� ����
					string whoLoginquery = "SELECT Name, NO FROM MINIGAME.customer_table WHERE ID = '" + InputId + "'";

					// SQL ������ �����ϰ� ���� ���� Ȯ��
					if (mysql_query(&Conn, whoLoginquery.c_str()) == 0) {
						// ����� ����
						MYSQL_RES* result = mysql_store_result(&Conn);

						// ����� ���� ���
						if (result != NULL) {
							// ù ��° ���� ������
							MYSQL_ROW row = mysql_fetch_row(result);

							// ���� �����ϸ� ȯ�� �޽��� ���
							if (row != NULL) {
								cout << "ȯ���մϴ�! " << row[0] << "��!\n"; //row[0]���� name�� ����Ǿ� ����
								MemberNo = row[1]; //row[1]���� No�� ����Ǿ� ����

								CMain::GetInst()->SetID(InputId);

								// 5�� ���
								Sleep(5000);

								break;

							}
						}

						// ��� ��Ʈ ����
						mysql_free_result(result);
					}
				}
				else {
					// ��й�ȣ ���� �ִ� 5�� ����
					missing += 1;
					cout << "��й�ȣ�� �����ʽ��ϴ�." << endl;
					cout << "���� ��й�ȣ" << missing << "ȸ �����Դϴ�." << endl;
					if (missing < 5) {
						continue;
					}
					cout << "�α��� 5ȸ ���н� �α����� ���ѵ˴ϴ�." << endl;

					//��� ��Ʈ ��ü
					mysql_free_result(result);

					//���α׷� ����
					cout << "\n";
					cout << "���� : �α��� 5ȸ ����" << endl;
					cout << "\n\n\n\n";
					exit(0);

				}
			}
		}
		else {
			// ���� ������ ���� �߻�
			cout << "SQL query error: " << mysql_error(&Conn);
		}
	}
	cout << "\n";
}

void END() 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// �ϴ� ���� ���
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "           #### ##  ###  ##    ##     ###  ##  ##  ###           ##  ##    ## ##   ##  ###\n";
	cout << "           # ## ##   ##  ##     ##      ## ##  ##  ##            ##  ##   ##   ##  ##   ##\n";
	cout << "             ##      ##  ##   ## ##    # ## #  ## ##             ##  ##   ##   ##  ##   ##\n";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << "             ##      ## ###   ##  ##   ## ##   ## ##              ## ##   ##   ##  ##   ##\n";
	cout << "             ##      ##  ##   ## ###   ##  ##  ## ###              ##     ##   ##  ##   ##\n";
	cout << "             ##      ##  ##   ##  ##   ##  ##  ##  ##              ##     ##   ##  ##   ##\n";
	cout << "            ####    ###  ##  ###  ##  ###  ##  ##  ###             ##      ## ##    ## ##\n";
	cout << "\n\n\n\n";
	// ������� �����Ͽ� ���� ����� ������� ��Ÿ������ ��
	SetConsoleTextAttribute(hConsole, 15);
}

/////////////////////////��� �߰�///////////////////////////

void Record(int _score)
{
	int iScore;
	string Player_ID = CMain::GetInst()->GetID();

	iScore = _score;
	int record_No = 0; // ������ ȸ���� ��ϵǸ� NO(ȸ����ȣ)�� ȸ���� �ľ�

	// �� ���̺��� ���ڵ� ������ �������� ���� SQL ���� ����
	string CountQuery;
	switch (CMain::GetInst()->GetCurMenu())
	{
	case MENU_TYPE::MINESWEEPER:
		CountQuery = "SELECT COUNT(*) FROM minesweeper_game";
		break;
	case MENU_TYPE::TYPINGGAME:
		CountQuery = "SELECT COUNT(*) FROM typing_word_game";
		break;
	}
	//�� ���̺� �ִ� ��� Į���� �˻����ּ���

	// SQL ���� ����
	if (mysql_query(&Conn, CountQuery.c_str()) != 0) {
		// SQL ���� ���� �� ���� �߻� �� ���� �޽��� ���
		fprintf(stderr, "SQL �� ���� ����: %s\n", mysql_error(&Conn));
	}
	else {
		// SQL ���� ������ ������ ��� ����� ��������
		MYSQL_RES* result = mysql_use_result(&Conn);

		// ��� �� ��������
		MYSQL_ROW row = mysql_fetch_row(result);

		// ��� ���� �����ϴ� ���
		if (row != NULL) {
			// ���ڵ� ������ ������ ��ȯ�Ͽ� No ������ ����
			record_No = atoi(row[0]); //atoi()���� ������ ��ȯ

			// ��� ��Ʈ ����
			mysql_free_result(result);
		}
	}
	//���� �ο� +1 =No   ex) �����̺� 5���� ���� �����ϸ� ���� ȸ�����ʹ� NO.6 ����
	record_No += 2;

	string insertQuery;

	switch (CMain::GetInst()->GetCurMenu())
	{
	case MENU_TYPE::MINESWEEPER:
		insertQuery = "INSERT INTO `MINIGAME`.`minesweeper_game` (`No`, `Score`, `Player_ID`) VALUES ('" + to_string(record_No) + "','" + to_string(iScore) + "', '" + Player_ID + "')";
		break;
	case MENU_TYPE::TYPINGGAME:
		insertQuery = "INSERT INTO `MINIGAME`.`typing_word_game` (`No`, `Score`, `Player_ID`) VALUES ('" + to_string(record_No) + "','" + to_string(iScore) + "', '" + Player_ID + "')";
	}

	if (mysql_query(&Conn, insertQuery.c_str()) != 0) {
		fprintf(stderr, "Mysql query error:%s", mysql_error(&Conn));
	}

	cout << "\n";
}


