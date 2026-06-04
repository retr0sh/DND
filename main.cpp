#include <iostream>
#include<windows.h>

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


	void battle(enemy &ene) {
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

player_class player;
enemy goblin{"goblin", 35, 35, 3, 25};
enemy skelet{ "skelet", 50, 50, 5, 30 };

void start_game() {
	if (player.name == "") { player.change_name(); }
	if (player.proffi == "") { player.change_proffi(); }
	string conti;

	system("cls");
	cout << "Это начало вашей истории";
	for (int i = 0; i < 3; i++) {
		cout << ".";
		Sleep(1000);
	}
	Sleep(2000);


	system("cls");
	cout << ",--------------------------------------------------------------------------------------------------------------------------------," << endl
		 << "  Вы просыпаетесь в подземелье, пытаясь вспомнить как вы оказались здесь," << endl 
		 << "  С сильной головной болью вы вспоминаете своего друга Пуфендуя который предложил вам заработать лёгких деньжат." << endl
		 << "  Но только как вы спустились в подземелье, вы почувствовали что Пуфендуй затеял что-то не хорошое." << endl
		 << "  Хоть и когда вы шли до подземелья никакой опасности вы не чувствовали," << endl 
		 << "  Только лишь Пуфендуй борматал себе под нос что никто не узнает что случилось на протяжении всей дороги к подземелью." << endl
		 << "  И вот на лестнице Пуфендуй берёт свою палку и замихивается на вас, после чего он попадает себе в глаз, и падает крича от боли." << endl
		 << "  От удивления вы падаете в обморок и катитесь по лестнице ударяясь своей головой об ступеньки." << endl
		 << "'--------------------------------------------------------------------------------------------------------------------------------'" << endl;

	cout << "Продолжить? ";	cin >> conti;


	system("cls");
	cout << ",---------------------------------------------------------," << endl
		 << "  Вы осмотрели себя и убедились что с вами всё в порядке," << endl 
		 << "  Не считая тово что вы стали не много тупее чем раньше." << endl
		 << "'---------------------------------------------------------'" << endl;

	cout << "Продолжить? ";	cin >> conti;

	bool search_room = false, exit_room = false;
	while (exit_room == false) {
		string a;
		system("cls");
		cout << "Выбор: " << endl
			 << "1. Осмотреть комнату" << endl;

		if (search_room == true) cout << "2. Зайти в дверной проём" << endl 
			                          << "3. Выйти в окно" << endl;

		cout << endl << "Ваш выбор: "; cin >> a;

		if (a == "1") {
			search_room = true;
			system("cls");
			cout << "Вы осмотрели комнату и с горем пополам нашли дверной проём ведущий на поверхность," << endl
				 << "Помимо дверного проёма вы видете окно." << "\n\n";

			cout << "Продолжить? ";	cin >> conti;
		}

		if (a == "2" and search_room == true) {
			exit_room = true;

			system("cls");
			cout << "Вы поднялись по лестнице и вот уже стоите на пороге следующей комнаты" << "\n\n";

			cout << "Продолжить? ";	cin >> conti;
		}

		if (a == "3" and search_room == true) {
			system("cls");
			cout << "Вы подходите к окну и выходите через него, и через 3 минуты полёта к вам приходит осознание," << endl
				 << "В подземельях не может быть окон, врено???" << endl << endl
				 << "Вы умерли от голода падая в бесконечной пропасти." << endl << endl;

			cout << "Продолжить? ";	cin >> conti;
			player.game_over();
		}
	}


	search_room = false;
	exit_room = false;
	bool grabbed_item = false;
	while (exit_room == false) {
		string a;
		system("cls");
		cout << "Выбор: " << endl
			 << "1. Осмотреть комнату" << endl;

		if (search_room == true) {
			if (goblin.health > 0) cout << "2. Подойти к гоблину" << endl;
			else if (goblin.health <= 0) cout << "2. Выйти в следующую комнату" << endl;;
			cout << "3. Подойти к сундуку (А)" << endl
				 << "4. Подойти к сундуку (Б)" << endl;
		}

		cout << endl << "Ваш выбор: "; cin >> a;

		if (a == "1") {
			search_room = true;
			system("cls");
			cout << "Осматривая комнату вы замечаете гоблина охроняющего дверной проём." << endl
				 << "Помимо дверного проёма с гоблином, вы видете целых два алых сундука с позолотой." << endl << endl;

			cout << "Продолжить? ";	cin >> conti;
		}

		if (a == "2" and search_room == true) {
			system("cls");
			if (goblin.health <= 0) {
				system("cls");
				exit_room = true;
				cout << "Вы проходите в следующую комнату." << endl
					 << "Перед вами предстаёт торговец." << endl << endl
					 << "Продолжить? ";
				cin >> conti;
			}
			else if (goblin.health > 0) {
				cout << "Вы подходите к гоблину, начинается битва." << endl << endl;

				cout << "Продолжить? ";	cin >> conti;
				player.battle(goblin);
			}
		}

		if (a == "3" and search_room == true) {
			system("cls");
			cout << "Вы подходите к сундуку и вас ловит мимик," << endl
				 << "Кто бы мог подумать, что монстры могут быть так похожи на сундуки???" << endl << endl
				 << "Вы умерли от мимика в его пасти." << endl << endl;

			cout << "Продолжить? ";	cin >> conti;
			player.game_over();
		}


		if (a == "4" and search_room == true) {
			if (player.proffi == "warrior") {
				system("cls");
				cout << "Вы подходите к сундуку и открываете его," << endl;

				if (grabbed_item == false) {
					cout << "Невероятно, вы нашли легендарную бутылку эля!" << endl << endl
						<< "Выбор:" << endl
						<< "1. Взять бутылку и выпить" << endl
						<< "2. Положить обратно" << endl << endl;

					string b;
					cin >> b;

					if (b == "1") {
						grabbed_item = true;
						player.damage = 15;
						player.crit_damage = 22;
						system("cls");
						cout << "Вы взяли бутылку, выпили эль и разбили ее об стену" << endl
							<< "Теперь у вас есть розочка из бутылки эля." << endl
							<< "+15 к урону" << endl
							<< "-30 к интеллекту " << endl << endl;
					}
					if (b == "2") {
						system("cls");
						cout << "Вы положили бутылку обратно в сундук." << endl << endl;
					}
				}
				else if (grabbed_item == true) {
					cout << "Невероятно, в нём пусто..." << endl << endl;
				}

				cout << "Продолжить? "; cin >> conti;
			}

			if (player.proffi == "mage") {
				system("cls");
				cout << "Вы подходите к сундуку и открываете его," << endl;

				if (grabbed_item == false) {
					cout << "Невероятно, вы нашли легендарные..." << endl
						<< "Мыльные пузири???" << endl << endl
						<< "Выбор:" << endl
						<< "1. Взять мыльные пузири" << endl
						<< "2. Положить обратно" << endl << endl;

					string b;
					cin >> b;

					if (b == "1") {
						grabbed_item = true;
						player.damage = 15;
						player.crit_damage = 22;
						system("cls");
						cout << "Вы взяли мыльные пузири" << endl
							<< "Теперь у вас есть розочка из бутылки эля." << endl
							<< "+15 к урону" << endl
							<< "+30 к суеверию " << endl << endl;
					}
					if (b == "2") {
						system("cls");
						cout << "Вы положили мыльные пузири обратно в сундук." << endl << endl;
					}
				}
				else if (grabbed_item == true) {
					cout << "Невероятно, в нём пусто..." << endl << endl;
				}

				cout << "Продолжить? "; cin >> conti;
			}
		}
	}

	bool get_hp = false, get_armor = false;
	exit_room = false;
	while (exit_room == false) {
		system("cls");
		string a;

		cout << "Хотите поторговать?" << endl
			 << "1. Да" << endl
			 << "2. Нет" << endl
			 << "Выбор: ";
		cin >> a;

		if (a == "1") {
			while (exit_room == false) {
				system("cls");
				cout << "Золото: " << player.gold << endl
					 << "Торговец вам предлагает:" << endl;

				if (get_hp == false) { cout << "1. Залатать раны - 5 золота" << endl; }
				if (get_armor == false) { cout << "2. Кожные доспехи (+15 HP) - 15 золота" << endl;  }
				cout << endl << "0. Закончить торговлю" << endl
					 << "Выбор: ";
				cin >> a;
				if (a == "1") {
					if (player.gold >= 5 and get_hp == false) {
						system("cls");
						get_hp = true;
						player.gold -= 5;
						player.health = player.max_health; 
						cout << "Вы залатали раны" << endl
							 << "Теперь у вас " << player.gold << " золота" << endl
							 << "Продолжить? ";
						cin >> conti;
					}
					else if (player.gold < 5) {
						system("cls");
						cout << "Торговец вас ударил по шапке (-1 к интелекту)" << endl
							 << "У вас нету столько золота!" << endl
							 << "Продолжть? ";
						cin >> conti;
					}
				}
				else if (a == "2" and get_armor == false) {
					if (player.gold >= 15) {
						system("cls");
						get_armor = true;
						player.gold -= 15;
						player.max_health += 15;
						cout << "Вы купили кожаные доспехи (+15 HP)" << endl
							<< "Теперь у вас " << player.gold << " золота" << endl
							<< "Продолжить? ";
						cin >> conti;
					}
					else if (player.gold < 15) {
						system("cls");
						cout << "Торговец вас ударил по шапке (-1 к интелекту)" << endl
							<< "У вас нету столько золота!" << endl
							<< "Продолжть? ";
						cin >> conti;
					}
				}
				else if (a == "0") {
					exit_room = true;
				}
			}
		}
		else if (a == "2") {
			exit_room = true;
		}
	}

	system("cls");
	cout << "Зайдя в слдедующую комнату вы видите запертую дверь, 4 статуи и плиту на которой написанно:" << endl
		 << "Женщины слепы к мужским достижениям, но бедняки воспользуются своим шансом отдать своему господину" << endl 
		 << "посеянную им награду, чтобы вскоре потекло вино" << endl
		 << "Продолжить? ";
	cin >> conti;

	exit_room = false;
	while (exit_room == false) {
		system("cls");
		cout << "Женщины слепы к мужским достижениям, но бедняки воспользуются своим шансом отдать своему господину" << endl
			 << "посеянную им награду, чтобы вскоре потекло вино" << endl << endl;
		cout << "Введите направления для каждой статуи:" << endl;
		cout << "1 (бедняки) - 2.ЮГ или 4.ВОСТОК: ";
		string dir1; cin >> dir1;
		cout << "2 (господин) - 1.СЕВЕР или 4.ВОСТОК: ";
		string dir2; cin >> dir2;
		cout << "3 (женщина с бутылкой) - 1.СЕВЕР или 3.ЗАПАД: ";
		string dir3; cin >> dir3;
		cout << "4 (женщина с бокалом) - 2.ЮГ или 3.ЗАПАД: ";
		string dir4; cin >> dir4;

		// 2 - Бедняки ВОСТОК
		// 4 - Господин СЕВЕР
		// 1 - Женщина с бутылкой ЗАПАД
		// 2 - Женщина с бокалом ЮГ

		if ((dir1 == "2") && (dir2 == "4") && (dir3 == "1") &&(dir4 == "2")) {
			exit_room = true;
			system("cls");
			cout << "Бедняки и господин смотрят на восток!" << endl
				 << "Господин и женщина с бутылкой смотрят на север!" << endl
				 << "Женщина с бутылкой и женщина с бокалом смотрят на запад!" << endl
				 << "Урожай передан, вино налито! Дверь открыта!" << endl;
			
			cout << "Продолжить? "; cin >> conti;
		}
		else {
			system("cls");
			cout << "Ничего не произошло. Статуи не видят друг друга. Попробуйте снова." << endl
				 << "Продолжить? ";
			cin >> conti;
		}
	}


	exit_room = false;
	while (exit_room == false) {
		string a;
		system("cls");
		cout << "И вот пройдя в следующую комнату перед вами становится скелет за которм виднеется поверхность." << endl
			 << "Он предложи вам выбор срзится с ним, либо решить загадку." << endl
			 << "1. Сразится" << endl
			 << "2. Решить загадку" << endl
			 << "Выбор: "; cin >> a;

		if (a == "1") {
			system("cls");
			cout << "Начинается битва" << endl
				 << "Продолжить"; cin >> conti;

			player.battle(skelet);
			exit_room = true;
		}
		else if (a == "2") {
			system("cls");
			cout << "Начнём же!" << endl
				 << "Реши простенькое уравнение: (sin(π/2)−1)+(e^iπ + 1) + (ln(1)) + (cos(0)−1) = ???" << endl
				 << "Ответ: "; cin >> a;
			if (a == "0") {
				system("cls");
				cout << "Скелет от удивления падает, и благодарит вас, ведь вы разрушили его проклятие." << endl
					 << "И в одно мгновенье скелет превращается в прекрасную деву," << endl 
					 << "после чего эта дева, просит стать вашей спутницей на всю жизнь." << endl 
					 << "Но вы её оставили, ведь мама говорила что легко доступные женщины это зло!!!" << endl
					 << "А слово мамы закон. так что вы покинули подземелье." << endl
					 << "Продолжить?"; cin >> conti;
				exit_room = true;
			}
			else {
				system("cls");
				cout << "Ты не решил мою загадку, так что сразись со мной." << endl
					 << "Начинается битва" << endl
					 << "Продолжить? "; cin >> conti;

				player.battle(skelet);
				exit_room = true;
			}
		}

	}

	system("cls");
	cout << ",---------------------------------------------------------------------------------------------------------," << endl
		 << "  Наконец покинув подземелье вы двигаетесь в сторону любимого и родного города." << endl
		 << "  И через пару минут вы оказываетесь в своём родном городе, и вдруг останавливаетесь в недоумении." << endl
		 << "  Вам казалось что вы с пуфендуем шли около 5 часов до подземелья, мимо гор и огненых рек," << endl 
		 << "  но осмотрев местность вы понимаете что ходили вокруг своего любимого бара,"<< endl 
		 << "  а те самые горы и реки были телами пъянииц и отходами из канализаций." << endl
		 << "  Вы заходите в бар и встречаете Пуфендуя, после чего начинается затяжной и неловкий диалог." << endl
		 << "  Через пару кружек водки, все проясняется. Пуфендуй расказал что тогда на лестнице он увидел" << endl
		 << "  маленького человека-паука у вас на голове, которого хотел смахнуть с вас своей палкой, но человек-паук" << endl
		 << "  прыгнул на него, и Пуфендуй со всей силой попал себе в глаз. И на этой весёлой ноте вы помирились." << endl
		 << "  конец." << endl
		 << "'---------------------------------------------------------------------------------------------------------'" << endl;
	cin >> conti;
	exit(1);

}


int main() {
	setlocale(LC_ALL, "ru");

	while (true) {
		srand(time(NULL));
		system("cls");
		cout << ",----- Console - RPG -----," << endl
			<< "   1. Начать игру          " << endl
			<< "                           " << endl
			<< "   2. Изменить имя         " << endl
			<< "   3. Изменить профессию   " << endl
			<< "                           " << endl
			<< "   0. Выйти                " << endl
			<< ";--------- Stats ---------;" << endl
			<< "   Имя: " << player.name << endl
			<< "   Проффесия: " << player.proffi << endl
			<< "'-------------------------'" << endl
			<< "Выберите опцию: ";

		string a;
		cin >> a;

		if (a == "0") exit(1);
		else if (a == "1") start_game();
		else if (a == "2") player.change_name();
		else if (a == "3") player.change_proffi();
	}
}
