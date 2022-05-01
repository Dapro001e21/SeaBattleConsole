// SeaBattleConsole.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <WinSock2.h>

#include <windows.h>
#include <sstream>

using namespace std;

int GetKEY()
{
	while (true)
	{
		for (int i = 0; i < 256; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				return i;
			}
		}
	}
}

bool Constains(int* massiv, int n, int k)
{
	for (int i = 0; i < n; i++)
	{
		if (massiv[i] == k) {
			return true;
		}
	}

	return false;
}

bool Collision(int* massiv, int b, int xp, int yp, int* map, int mapX)
{
	for (int i = 0; i < b; i++)
	{
		/*if (map[(yp - i) * mapX + xp] == 2 || map[(yp - i - 1) * mapX + xp] == 2 || map[(yp - i) * mapX + (xp + 1)] == 2 || map[(yp - i - 1) * mapX + (xp + 1)] == 2
			|| map[(yp - i) * mapX + (xp - 1)] == 2 || map[(yp - i - 1) * mapX + (xp - 1)] == 2 || map[(yp - i - 2) * mapX + xp] == 2 || map[(yp - i + 1) * mapX + xp] == 2) {
			return true;
		}
		else if (map[(yp - i - 2) * mapX + (xp + 1)] == 2 || map[(yp - i - 2) * mapX + (xp - 1)] == 2 || map[(yp - i + 1) * mapX + (xp + 1)] == 2 || map[(yp - i + 1) * mapX + (xp - 1)] == 2) {
			return true;
		}*/
		if (map[(yp - i) * mapX + xp] == 2 || map[(yp - i - 1) * mapX + xp] == 2 || map[(yp - i + 1) * mapX + xp] == 2 || map[(yp - i) * mapX + (xp - 1)] == 2 || map[(yp - i) * mapX + (xp + 1)] == 2)
		{
			return true;
		}
		else if (map[(yp - i + 1) * mapX + (xp + 1)] == 2 || map[(yp - i + 1) * mapX + (xp - 1)] == 2 || map[(yp - i - 1) * mapX + (xp + 1)] == 2 || map[(yp - i - 1) * mapX + (xp - 1)] == 2) {
			return true;
		}
	}

	return false;

}

void ManualPlacementShip(int& countShip, int yp, int xp, int mapX, int mapY, int maxShip, int b, int* map)
{
	while (countShip < maxShip) {
		int* coard = new int[b + 1];

		for (int i = 0; i < b + 1; i++) {
			coard[i] = (yp - i) * mapX + xp;
		}

		for (int y = 0; y < mapY; y++)
		{
			for (int x = 0; x < mapX; x++)
			{
				if (Constains(coard, b + 1, y * mapX + x))
				{
					printf("\x1B[32m@");
				}
				else {
					if (map[y * mapX + x] == 1) {
						printf("\x1B[31m1");
					}
					else if (map[y * mapX + x] == 2)
					{
						printf("\x1B[33m@");
					}
					else {
						printf("\x1B[34m0");
					}
				}
			}

			printf("\n");
		}

		if (maxShip - countShip > 4) {
			cout << "Осталось раставить: " << maxShip - countShip << " кораблей";
		}
		else if (maxShip - countShip < maxShip && maxShip - countShip > 1) {
			cout << "Осталось раставить: " << maxShip - countShip << " корабля";
		}
		else {
			cout << "Осталось раставить: " << maxShip - countShip << " корабль";
		}

		printf("\n");

		int key = GetKEY();
		switch (key)
		{
		case 87:
			if (yp - b > 1) {
				yp--;
			}
			break;
		case 83:
			if (yp < mapY - 2) {
				yp++;
			}
			break;
		case 65:
			if (xp > 1) {
				xp--;
			}
			break;
		case 68:
			if (xp < mapX - 2) {
				xp++;
			}
			break;
		case 13:
			if (!Collision(coard, b + 1, xp, yp, map, mapX)) {

				for (int i = 0; i < b + 1; i++) {
					map[(yp - i) * mapX + xp] = 2;
				}

				countShip++;

				if (countShip == 4)
				{
					b++;
				}
				else if (countShip == 7)
				{
					b++;
				}
				else if (countShip == 9)
				{
					b++;
				}

				xp = 8;
				yp = 5;
			}
			break;
		default:
			break;
		}

		//update console
		std::system("cls");
		if (countShip == maxShip)
		{
			for (int y = 0; y < mapY; y++)
			{
				for (int x = 0; x < mapX; x++)
				{
					if (map[y * mapX + x] == 1) {
						printf("\x1B[31m1");
					}
					else if (map[y * mapX + x] == 2)
					{
						printf("\x1B[33m@");
					}
					else {
						printf("\x1B[34m0");
					}
				}

				printf("\n");
			}

			std::system("cls");
		}
	}
}

void AutoPlacementShip(int& countShip, int mapX, int mapY, int maxShip, int b, int* map)
{
	while (countShip < maxShip)
	{
		int* coard = new int[b + 1];
		int xp = 1 + rand() % (mapX - 2);
		int yp = (1 + b) + rand() % (mapY - 2 - b);

		while (Collision(coard, b + 1, xp, yp, map, mapX)) {
			xp = 1 + rand() % (mapX - 2);
			yp = (1 + b) + rand() % (mapY - 2 - b);

			for (int i = 0; i < b + 1; i++)
			{
				coard[i] = (yp - i) * mapX + xp;
			}
		}

		for (int i = 0; i < b + 1; i++)
		{
			coard[i] = (yp - i) * mapX + xp;
		}

		for (int i = 0; i < b + 1; i++)
		{
			map[(yp - i) * mapX + xp] = 2;
		}

		countShip++;

		if (countShip == 4)
		{
			b++;
		}
		else if (countShip == 7)
		{
			b++;
		}
		else if (countShip == 9)
		{
			b++;
		}
	}
}

void ShowMapPlayer(int* map, int mapY, int mapX)
{
	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			if (map[y * mapX + x] == 1) {
				printf("\x1B[31m1");
			}
			else if (map[y * mapX + x] == 2)
			{
				printf("\x1B[33m@");
			}
			else {
				printf("\x1B[34m0");
			}
		}

		printf("\n");
	}

	std::system("pause");
	std::system("cls");
}

string GetIP()
{
	char n[256];
	struct hostent* host;
	struct in_addr addr;

	gethostname(n, 255);
	host = gethostbyname(n);
	int i = 0;
	for (int i = 0; host->h_addr_list[i] != 0; i++)
	{
		if (host->h_addr_list[i + 1] == 0)
		{
			addr.s_addr = *(u_long*)host->h_addr_list[i];
			return inet_ntoa(addr);
		}
	}
}

int* MapGenerated(int mapX, int mapY)
{
	int* massiv = new int[mapX * mapY];
	for (int y = 0; y < mapY; y++)
	{
		for (int x = 0; x < mapX; x++)
		{
			if (y == 0 || x == 0 || y == mapY - 1 || x == mapX - 1)
			{
				massiv[y * mapX + x] = 1;
			}
			else {
				massiv[y * mapX + x] = 0;
			}
		}
	}
	return massiv;
}

string Margins(int mapX)
{
	string s = "     ";
	for (int i = 0; i < mapX - 15; i++)
	{
		s += " ";
	}

	return s;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	while (true)
	{
		int xp = 8, yp = 5;
		int xpC = 8, ypC = 5;

		int mapX = 18, mapY = 12, level, motion = 1;
		int countShip = 0, maxShip = 10, b = 0, countShip2 = 0, maxShip2 = 10, b2 = 0;

		char s, v;
		string outStr = "";

		int* map = MapGenerated(mapX, mapY);
		int* mapEnemy = MapGenerated(mapX, mapY);

		/*
		0 - Море
		1 - Границы поля
		2 - Корабль
		3 - Мимо
		4 - Попал
		*/

		//Меню
		system("cls");
		printf("\x1B[97mМеню:\n1)Играть\n2)Играть онлайн\n3)Выйти\n");
		cin >> v;
		std::system("cls");

		if (v == '1') {
			printf("\x1B[97mРежим игры:\n1)Легкий\n2)Сложный\n");
			cin >> level;
			std::system("cls");

			printf("\x1B[97mРасстановка кораблей:\n1)Вручную\n2)Автоматически\n");
			cin >> s;
			std::system("cls");

			switch (s)
			{
			case '1':
				//Расставка кораблей пользователем вручную
				ManualPlacementShip(countShip, yp, xp, mapX, mapY, maxShip, b, map);
				break;
			case '2':
				//Расставка кораблей пользователем автоматически
				AutoPlacementShip(countShip, mapX, mapY, maxShip, b, map);
				break;
			default:
				break;
			}

			//Показ кораблей раставленных пользователем
			ShowMapPlayer(map, mapY, mapX);

			//Расставка кораблей компьютером
			AutoPlacementShip(countShip2, mapX, mapY, maxShip2, b2, mapEnemy);

			//Атака кораблей компьютера пользователем
			s = ' ';
			int sv = 0;
			while (countShip2 > 0) {
				outStr = "\x1B[97mПоле противника";
				outStr += Margins(mapX);
				outStr += "Ваше поле\n";
				printf(outStr.c_str());
				outStr = "";
				for (int y = 0; y < mapY; y++)
				{
					for (int x = 0; x < mapX; x++)
					{
						if (x == xp && y == yp)
						{
							printf("\x1B[32m@");
						}
						else {
							if (mapEnemy[y * mapX + x] == 1) {
								printf("\x1B[31m1");
							}
							else if (mapEnemy[y * mapX + x] == 3)
							{
								printf("\x1B[90m@");
							}
							else if (mapEnemy[y * mapX + x] == 4)
							{
								printf("\x1B[31mX");
							}
							else {
								printf("\x1B[34m0");
							}
						}
					}

					cout << "     ";
					for (int x2 = 0; x2 < mapX; x2++)
					{
						if (map[y * mapX + x2] == 1) {
							printf("\x1B[31m1");
						}
						else if (map[y * mapX + x2] == 2)
						{
							printf("\x1B[33m@");
						}
						else if (map[y * mapX + x2] == 3)
						{
							printf("\x1B[90m@");
						}
						else if (map[y * mapX + x2] == 4)
						{
							printf("\x1B[31mX");
						}
						else {
							printf("\x1B[34m0");
						}
					}

					printf("\n");
				}

				cout << outStr;
				outStr = "";

				int key = GetKEY();
				char s = ' ';

				switch (key)
				{
				case 87:
					if (yp > 1) {
						yp--;
					}
					break;
				case 83:
					if (yp < mapY - 2) {
						yp++;
					}
					break;
				case 65:
					if (xp > 1) {
						xp--;
					}
					break;
				case 68:
					if (xp < mapX - 2) {
						xp++;
					}
					break;
				case 13:
					if (mapEnemy[yp * mapX + xp] != 3 && mapEnemy[yp * mapX + xp] != 4)
					{
						if (mapEnemy[yp * mapX + xp] == 0) {
							mapEnemy[yp * mapX + xp] = 3;
						}
						else if (mapEnemy[yp * mapX + xp] == 2)
						{
							mapEnemy[yp * mapX + xp] = 4;

							//Проверка на уничтожение корабля
							if ((mapEnemy[(yp - 1) * mapX + xp] != 2 && mapEnemy[(yp + 1) * mapX + xp] != 2) &&
								(mapEnemy[(yp - 2) * mapX + xp] != 2 && mapEnemy[(yp + 2) * mapX + xp] != 2) &&
								((mapEnemy[(yp - 3) * mapX + xp] != 2 || mapEnemy[(yp + 3) * mapX + xp] != 2) && ((mapEnemy[(yp - 1) * mapX + xp] != 3 || (mapEnemy[(yp + 1) * mapX + xp] != 3)))))
							{
								countShip2--;
								outStr += "Вы уничтожили корабль\n";
								outStr += "Осталось уничтожить: ";
								string str = "";

								if (countShip2 == 1)
								{
									str = " корабль";
								}
								else if (countShip2 > 0 && countShip2 < 5)
								{
									str = " корабля";
								}
								else if (countShip2 > 4)
								{
									str = " кораблей";
								}

								outStr += to_string(countShip2) + str;
							}

							if (countShip2 == 0)
							{
								system("cls");
								printf("\x1B[37mВы выйграли!!!\n");
								system("pause");
							}
						}

						xp = 8;
						yp = 5;

						//Атака кораблей пользователя компьютером
						if (sv == 0 || level == 1)
						{
							xpC = 1 + rand() % (mapX - 2);
							ypC = 1 + rand() % (mapY - 2);

							while (map[ypC * mapX + xpC] == 3 || map[ypC * mapX + xpC] == 4) {
								xpC = 1 + rand() % (mapX - 2);
								ypC = 1 + rand() % (mapY - 2);
							}
						}
						else if (sv == 1 && level == 2)
						{
							ypC += 1;
						}
						else if (sv == 2 && level == 2)
						{
							ypC -= 1;
						}

						if (map[ypC * mapX + xpC] == 0) {
							map[ypC * mapX + xpC] = 3;

							if (sv == 1 && level == 2)
							{
								sv = 2;
							}

							break;
						}
						else if (map[ypC * mapX + xpC] == 2)
						{
							if (level == 2 && sv != 2)
							{
								sv = 1;
							}
							map[ypC * mapX + xpC] = 4;

							//Проверка на уничтожение корабля
							if ((map[(ypC - 1) * mapX + xpC] != 2 && map[(ypC + 1) * mapX + xpC] != 2) &&
								(map[(ypC - 2) * mapX + xpC] != 2 && map[(ypC + 2) * mapX + xpC] != 2) &&
								((map[(ypC - 3) * mapX + xpC] != 2 || map[(ypC + 3) * mapX + xpC] != 2) && ((map[(ypC - 1) * mapX + xpC] != 3 || (map[(ypC + 1) * mapX + xpC] != 3)))))
							{
								countShip--;
								if (level == 2)
								{
									sv = 0;
								}
							}

							if (countShip == 0)
							{
								std::system("cls");
								printf("\x1B[37mВы проиграли!!!\n");
								std::system("pause");
								s = '2';
							}
						}
					}
					break;
				case 81:
					std::system("cls");

					printf("\x1B[97mПауза:\n1)Продолжить\n2)Выйти в главное меню\n");
					cin >> s;
					break;
				default:
					break;
				}

				system("cls");
				if (s == '2')
				{
					break;
				}
			}
		}
		else if (v == '2')
		{
			//Меню онлайн
			cout << "Меню:\n1)Создать игру\n2)Присоединиться к игре\n3)Выйти\n";
			cin >> v;

			if (v == '3') {
				system("cls");
				continue;
			}

			WSADATA wsaDATA;
			SOCKADDR_IN addr;
			SOCKET server, client;
			int sizeofaddr, port;
			string ss;
			const char* ip;
			char msg[216];

			WORD DLLVERSION = MAKEWORD(2, 2);
			if (WSAStartup(DLLVERSION, &wsaDATA) != 0)
			{
				cout << "Error";
				return 1;
			}

			system("cls");
			switch (v)
			{
			case '1':
				cout << "Введите порт: ";
				cin >> port;

				system("cls");

				addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
				addr.sin_port = htons(port);
				addr.sin_family = AF_INET;

				sizeofaddr = sizeof(addr);

				server = socket(AF_INET, SOCK_STREAM, NULL);
				bind(server, (SOCKADDR*)&addr, sizeofaddr);
				listen(server, SOMAXCONN);

				printf("\x1B[97mРасстановка кораблей:\n1)Вручную\n2)Автоматически\n");
				cin >> s;
				std::system("cls");

				switch (s)
				{
				case '1':
					//Расставка кораблей пользователем вручную
					ManualPlacementShip(countShip, yp, xp, mapX, mapY, maxShip, b, map);
					break;
				case '2':
					//Расставка кораблей пользователем автоматически
					AutoPlacementShip(countShip, mapX, mapY, maxShip, b, map);
					break;
				default:
					break;
				}

				ShowMapPlayer(map, mapY, mapX);

				printf("\x1B[97mServer started...\n");
				cout << "IP for connection: " << GetIP();
				motion = 1;

				client = accept(server, (SOCKADDR*)&addr, &sizeofaddr);
				system("cls");

				for (int i = 0; i < 216; i++)
				{
					msg[i] = map[i] + '0';
				}
				send(client, msg, sizeof(msg), NULL);
				recv(client, msg, sizeof(msg), NULL);
				for (int i = 0; i < 216; i++)
				{
					if ((char)msg[i] == '1')
					{
						mapEnemy[i] = 1;
					}
					else if ((char)msg[i] == '2')
					{
						mapEnemy[i] = 2;
					}
					else {
						mapEnemy[i] = 0;
					}
				}
				countShip2 = 10;
				break;
			case '2':
				cout << "Введите ip: ";
				cin >> ss;
				ip = ss.c_str();

				system("cls");

				cout << "Введите порт: ";
				cin >> port;

				system("cls");

				addr.sin_addr.S_un.S_addr = inet_addr(ip);
				addr.sin_port = htons(port);
				addr.sin_family = AF_INET;

				sizeofaddr = sizeof(addr);

				printf("\x1B[97mРасстановка кораблей:\n1)Вручную\n2)Автоматически\n");
				cin >> s;
				std::system("cls");

				switch (s)
				{
				case '1':
					//Расставка кораблей пользователем вручную
					ManualPlacementShip(countShip, yp, xp, mapX, mapY, maxShip, b, map);
					break;
				case '2':
					//Расставка кораблей пользователем автоматически
					AutoPlacementShip(countShip, mapX, mapY, maxShip, b, map);
					break;
				default:
					break;
				}

				ShowMapPlayer(map, mapY, mapX);

				client = socket(AF_INET, SOCK_STREAM, NULL);
				connect(client, (SOCKADDR*)&addr, sizeofaddr);

				printf("\x1B[97mServer connected...");
				motion = 2;
				system("cls");

				recv(client, msg, sizeof(msg), NULL);
				for (int i = 0; i < 216; i++)
				{
					if ((char)msg[i] == '1')
					{
						mapEnemy[i] = 1;
					}
					else if ((char)msg[i] == '2')
					{
						mapEnemy[i] = 2;
					}
					else {
						mapEnemy[i] = 0;
					}
				}
				countShip2 = 10;
				for (int i = 0; i < 216; i++)
				{
					msg[i] = map[i] + '0';
				}
				send(client, msg, sizeof(msg), NULL);
				break;
			default:
				break;
			}

			s = ' ';
			int sv = 0;
			while (countShip2 > 0 && s != '2') {
				printf("\x1B[97mПоле противника\t       Ваше поле\n");
				for (int y = 0; y < mapY; y++)
				{
					for (int x = 0; x < mapX; x++)
					{
						if (x == xp && y == yp)
						{
							printf("\x1B[32m@");
						}
						else {
							if (mapEnemy[y * mapX + x] == 1) {
								printf("\x1B[31m1");
							}
							else if (mapEnemy[y * mapX + x] == 3)
							{
								printf("\x1B[90m@");
							}
							else if (mapEnemy[y * mapX + x] == 4)
							{
								printf("\x1B[31mX");
							}
							else {
								printf("\x1B[34m0");
							}
						}
					}

					cout << "     ";
					for (int x2 = 0; x2 < mapX; x2++)
					{
						if (map[y * mapX + x2] == 1) {
							printf("\x1B[31m1");
						}
						else if (map[y * mapX + x2] == 2)
						{
							printf("\x1B[33m@");
						}
						else if (map[y * mapX + x2] == 3)
						{
							printf("\x1B[90m@");
						}
						else if (map[y * mapX + x2] == 4)
						{
							printf("\x1B[31mX");
						}
						else {
							printf("\x1B[34m0");
						}
					}

					printf("\n");
				}

				cout << outStr;
				outStr = "";

				char msg[sizeof(int)];

				if (motion == 2) {
					if (countShip == 0)
					{
						system("cls");
						printf("\x1B[37mВы проиграли!!!\n");
						system("pause");
						s = '2';
						break;
					}

					cout << endl << "Ожидайте ваш противник ходит..." << endl;

					char msg[sizeof(int)];
					recv(client, msg, sizeof(int), 0);
					int pos = atoi(msg);

					if (map[pos] == 2)
					{
						map[pos] = 4;

						if ((map[pos - mapX] != 2 && map[pos + mapX] != 2) &&
							(map[pos - (mapX * 2)] != 2 && map[pos + (mapX * 2)] != 2) &&
							((map[pos - (mapX * 3)] != 2 || map[pos + (mapX * 3)] != 2) && ((map[pos - mapX] != 3 || (map[pos + mapX] != 3)))))
						{
							countShip--;
						}
					}
					else {
						motion = 1;
						map[pos] = 3;
					}

					system("cls");
					continue;
				}

				//Очищение буфера консоли
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

				int key = GetKEY();
				char s = ' ';

				switch (key)
				{
				case 87:
					if (yp > 1) {
						yp--;
					}
					break;
				case 83:
					if (yp < mapY - 2) {
						yp++;
					}
					break;
				case 65:
					if (xp > 1) {
						xp--;
					}
					break;
				case 68:
					if (xp < mapX - 2) {
						xp++;
					}
					break;
				case 13:
					if (mapEnemy[yp * mapX + xp] != 3 && mapEnemy[yp * mapX + xp] != 4)
					{
						if (mapEnemy[yp * mapX + xp] == 0) {
							mapEnemy[yp * mapX + xp] = 3;

							motion = 2;
							string s = to_string((yp * mapX + xp));
							const char* msg = s.c_str();
							send(client, (char*)msg, sizeof(int), 0);
						}
						else if (mapEnemy[yp * mapX + xp] == 2)
						{
							mapEnemy[yp * mapX + xp] = 4;

							string s = to_string((yp * mapX + xp));
							const char* msg = s.c_str();
							send(client, (char*)msg, sizeof(int), 0);

							//Проверка на уничтожение корабля
							if ((mapEnemy[(yp - 1) * mapX + xp] != 2 && mapEnemy[(yp + 1) * mapX + xp] != 2) &&
								(mapEnemy[(yp - 2) * mapX + xp] != 2 && mapEnemy[(yp + 2) * mapX + xp] != 2) &&
								((mapEnemy[(yp - 3) * mapX + xp] != 2 || mapEnemy[(yp + 3) * mapX + xp] != 2) && ((mapEnemy[(yp - 1) * mapX + xp] != 3 || (mapEnemy[(yp + 1) * mapX + xp] != 3)))))
							{
								countShip2--;
								outStr += "Вы уничтожили корабль\n";
								outStr += "Осталось уничтожить: ";
								string str = "";

								if (countShip2 == 1)
								{
									str = " корабль";
								}
								else if (countShip2 > 0 && countShip2 < 5)
								{
									str = " корабля";
								}
								else if (countShip2 > 4)
								{
									str = " кораблей";
								}

								outStr += to_string(countShip2) + str;
							}
						}


						xp = 8;
						yp = 5;
					}
					break;
				default:
					break;
				}

				if (countShip2 == 0)
				{
					system("cls");
					printf("\x1B[37mВы выйграли!!!\n");
					system("pause");
					s = '2';
					break;
				}

				std::system("cls");
			}
		}
		else if (v == '3')
		{
			return 0;
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
