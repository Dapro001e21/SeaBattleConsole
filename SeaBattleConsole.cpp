// SeaBattleConsole.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <sstream>

using namespace std;

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

void ManualPlacementShip(int &countShip, int yp, int xp, int mapX, int mapY, int maxShip, int b, int* map)
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

		int key = _getch();
		switch (key)
		{
		case 119:
			if (yp - b > 1) {
				yp--;
			}
			break;
		case 115:
			if (yp < mapY - 2) {
				yp++;
			}
			break;
		case 97:
			if (xp > 1) {
				xp--;
			}
			break;
		case 100:
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

void AutoPlacementShip(int &countShip, int mapX, int mapY, int maxShip, int b, int* map)
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

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	//Меню
	while (true)
	{
		int xp = 8, yp = 5;
		int xpC = 8, ypC = 5;

		int mapX = 18, mapY = 12, mapX2 = 18, mapY2 = 12, level;
		int countShip = 0, maxShip = 10, b = 0, countShip2 = 0, maxShip2 = 10, b2 = 0;

		char s, v;
		string outStr = "";

		int map[] = {
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};

		int mapEnemy[] = {
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
		};

		printf("\x1B[97mМеню:\n1)Играть\n2)Выйти\n");
		cin >> v;
		std::system("cls");

		if (v == '2') {
			break;
		}

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

		//Расставка кораблей компьютером
		AutoPlacementShip(countShip2, mapX2, mapY2, maxShip2, b2, mapEnemy);

		//Показ кораблей раставленных компьютером
		/*for (int y = 0; y < mapY2; y++)
		{
			for (int x = 0; x < mapX2; x++)
			{
				if (mapEnemy[y * mapX2 + x] == 1) {
					printf("\x1B[31m1");
				}
				else if (mapEnemy[y * mapX2 + x] == 2)
				{
					printf("\x1B[33m@");
				}
				else {
					printf("\x1B[34m0");
				}
			}

			printf("\n");
		}

		system("pause");
		system("cls");*/

		//Атака кораблей компьютера пользователем
		s = ' ';
		int sv = 0;
		while (countShip2 > 0 && s != '2') {
			printf("\x1B[97mПоле противника\t       Ваше поле\n");
			for (int y = 0; y < mapY2; y++)
			{
				for (int x = 0; x < mapX2; x++)
				{
					if (x == xp && y == yp)
					{
						printf("\x1B[32m@");
					}
					else {
						if (mapEnemy[y * mapX2 + x] == 1) {
							printf("\x1B[31m1");
						}
						else if (mapEnemy[y * mapX2 + x] == 3)
						{
							printf("\x1B[90m@");
						}
						else if (mapEnemy[y * mapX2 + x] == 4)
						{
							printf("\x1B[31m@");
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
					else if (map[y * mapX2 + x2] == 3)
					{
						printf("\x1B[90m@");
					}
					else if (map[y * mapX2 + x2] == 4)
					{
						printf("\x1B[31m@");
					}
					else {
						printf("\x1B[34m0");
					}
				}

				printf("\n");
			}

			cout << outStr;
			outStr = "";

			int key = _getch();
			s = ' ';

			switch (key)
			{
			case 119:
				if (yp > 1) {
					yp--;
				}
				break;
			case 115:
				if (yp < mapY2 - 2) {
					yp++;
				}
				break;
			case 97:
				if (xp > 1) {
					xp--;
				}
				break;
			case 100:
				if (xp < mapX2 - 2) {
					xp++;
				}
				break;
			case 13:
				if (mapEnemy[yp * mapX2 + xp] == 0) {
					mapEnemy[yp * mapX2 + xp] = 3;

					xp = 8;
					yp = 5;
				}
				else if (mapEnemy[yp * mapX2 + xp] == 2)
				{
					mapEnemy[yp * mapX2 + xp] = 4;

					//Проверка на уничтожение корабля
					if (mapEnemy[(yp - 1) * mapX2 + xp] != 2 && mapEnemy[(yp + 1) * mapX2 + xp] != 2 &&
						mapEnemy[(yp - 2) * mapX2 + xp] != 2 && mapEnemy[(yp + 2) * mapX2 + xp] != 2)
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
						outStr = "Вы выйграли";
					}

					xp = 8;
					yp = 5;
				}

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
				}
				else if (map[ypC * mapX + xpC] == 2)
				{
					if (sv == 0 && level == 2)
					{
						sv = 1;
					}
					map[ypC * mapX + xpC] = 4;

					//Проверка на уничтожение корабля
					if (map[(ypC - 1) * mapX + xpC] != 2 && map[(ypC + 1) * mapX + xpC] != 2 &&
						map[(ypC - 2) * mapX + xpC] != 2 && map[(ypC + 2) * mapX + xpC] != 2)
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
				/*system("cls");
				for (int y = 0; y < mapY; y++)
				{
					for (int x = 0; x < mapX; x++)
					{
						if (map[y * mapX + x] == 1) {
							std::printf("\x1B[31m1");
						}
						else if (map[y * mapX + x] == 2)
						{
							std::printf("\x1B[33m@");
						}
						else if (map[y * mapX + x] == 3)
						{
							std::printf("\x1B[90m@");
						}
						else if (map[y * mapX + x] == 4)
						{
							std::printf("\x1B[31m@");
						}
						else {
							std::printf("\x1B[34m0");
						}
					}

					std::printf("\n");
				}
				system("pause");*/
				break;
			case 113:
				std::system("cls");

				printf("\x1B[97mПауза:\n1)Продолжить\n2)Выйти в главное меню\n");
				cin >> s;
				break;
			default:
				break;
			}

			std::system("cls");
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
