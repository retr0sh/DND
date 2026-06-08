#include <iostream>
#include <windows.h>

using namespace std;

class enemy {
public:
	string name = "Enemy";
	int health;
	int max_health;
	int damage;
	int max_gold;

	enemy(string n = "Enemy", int h = 50, int mh = 50, int d = 5, int g = 10) {
		name = n;
		health = h;
		max_health = mh;
		damage = d;
		max_gold = g;
	}
};

class player_class {
public:
	string name = "";
	string proffi = "";

	int health = 0;
	int max_health = 0;
	int mana = 0;
	int max_mana = 0;
	int rage = 0;
	int max_rage = 0;

	int damage = 0;
	int crit_damage = 0;
	int crit_damage_chacne = 10;

	int gold = 0;



	void change_name() {
		system("cls");
		cout << "Введите новое имя: ";
		cin >> name;
	}

	void change_proffi() {
		system("cls");
		cout << ",----- Проффесии -----," << endl
			<< "   1. Воин             " << endl
			<< "      Здоровье 25      " << endl
			<< "      Макс. Ярость 10  " << endl
			<< "                       " << endl
			<< "   2. Маг              " << endl
			<< "      Здоровье 15      " << endl
			<< "      Макс. Мана 10    " << endl
			<< "'---------------------'" << endl
			<< "Выберите проффесию: ";
		string a;
		cin >> a;
		if (a == "1") {
			proffi = "warrior";
			reset_stats();
		}
		else if (a == "2") {
			proffi = "mage";
			reset_stats();
		}
		else change_proffi();
	}

	void reset_stats() {
		if (proffi == "warrior") {
			health = 25;
			max_health = 25;
			rage = 0;
			max_rage = 10;
			damage = 5;
			crit_damage = 8;
		}
		else if (proffi == "mage") {
			health = 15;
			max_health = 15;
			mana = 10;
			max_mana = 10;
			damage = 4;
			crit_damage = 7;
		}
	}

	void game_over() {
		system("cls");
		int a;
		cout << ",----------------," << endl
			<< "|   GAME  OVER   |" << endl
			<< "'----------------'" << endl
			<< "Вы умерли..." << endl
			<< "Продолжить? "; cin >> a;
		exit(1);
	};


	void battle(enemy& ene) {
		bool enemy_dead = false;
		while (enemy_dead == false) {
			system("cls");
			string a;
			if (ene.health <= 0) {
				enemy_dead = true;

				int min_gold = ene.max_gold * 0.5;
				int get_gold = min_gold + rand() % (ene.max_gold - min_gold + 1);
				gold += get_gold;

				cout << "Вы победили врага!" << endl
					<< "Вы получили " << get_gold << " золота" << endl
					<< "Продолжить? ";
				cin >> a;
				break;
			}
			else if (health <= 0) {
				game_over();
			}
			else {
				cout << ",--- СТАТУС ИГРОКА ---," << endl
					<< "   Здоровье: " << health << "/" << max_health << endl;
				if (proffi == "warrior") cout << "   Ярость: " << rage << "/" << max_rage << endl;
				else if (proffi == "mage") cout << "   мана: " << mana << "/" << max_mana << endl;
				cout << "   Урон: " << damage << endl
					<< ";--- СТАТУС  ВРАГА ---;" << endl
					<< "   Здоровье: " << ene.health << "/" << ene.max_health << endl
					<< "   Урон: " << ene.damage << endl
					<< ";---------------------;" << endl
					<< "   1. Ударить          " << endl
					<< "   2. Особая атака     " << endl
					<< "   3. Сбежать (10%)    " << endl
					<< "'---------------------'" << endl
					<< "Выбор: ";

				cin >> a;

				if (a == "1") {
					bool crit = false;
					if (rand() % 100 < crit_damage_chacne) { crit = true; }

					if (crit == false) {
						ene.health -= damage;
						cout << "Вы нанесли " << damage << " урона" << endl;
					}
					else {
						ene.health -= crit_damage;
						cout << "КРИТИЧЕСКИЙ УРОН! Вы нанесли " << crit_damage << " урона" << endl;
					}

					health -= ene.damage;
					cout << "Враг нанёс вам " << ene.damage << " урона" << endl;

					if (proffi == "warrior") { if (rage < max_rage) rage++; }
					else if (proffi == "mage") { if (mana < max_mana) mana++; }

					cout << "Продолжить? "; cin >> a;
				}
				else if (a == "2" and rage >= 5 or mana >= 5) {
					if ((proffi == "warrior" && rage >= 5) || (proffi == "mage" && mana >= 5)) {
						ene.health -= damage * 2;
						health -= ene.damage;

						cout << "ОСОБАЯ АТАКА! Вы нанесли " << damage * 2 << " урона" << endl;
						cout << "Враг нанёс вам " << ene.damage << " урона" << endl;

						if (proffi == "warrior") { rage -= 5; }
						else if (proffi == "mage") { mana -= 5; }
					}
					else {
						cout << "Недостаточно ресурсов для особой атаки!" << endl;
					}
					cout << "Продолжить? "; cin >> a;
				}
				else if (a == "3") {
					int escape_chance = rand() % 100;
					if (escape_chance < 10) {
						enemy_dead = true;
						cout << "Вы сбежали!" << endl
							<< "Продолжить? ";
						cin >> a;
						break;
					}
					else {
						cout << "Не удалось сбежать!" << endl;
						health -= ene.damage;
						cout << "Враг нанёс вам " << ene.damage << " урона" << endl;
						cout << "Продолжить? "; cin >> a;
					}
				}
			}
		}
	}

};