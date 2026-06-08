#include <iostream>
#include <string>
#include "classes.cpp"

using namespace std;

void run_all_tests() {
    system("cls");
    cout << "===== ТЕСТЫ =====\n" << endl;

    int ok = 0;
    int total = 0;

    // Тест 1: Создание врага
    {
        enemy e;
        total++;
        if (e.name == "Enemy" && e.health == 50 && e.damage == 5) {
            cout << "[OK] Создание врага" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Создание врага" << endl;
        }
    }

    // Тест 2: Гоблин
    {
        enemy e("goblin", 35, 3, 25, 25);
        total++;
        if (e.name == "goblin" && e.health == 35 && e.max_health == 3 && e.damage == 25 && e.max_gold == 25) {
            cout << "[OK] Создание гоблина" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Создание гоблина" << endl;
        }
    }

    // Тест 3: Скелет
    {
        enemy e("skelet", 50, 5);
        total++;
        if (e.name == "skelet" && e.health == 50 && e.damage == 5) {
            cout << "[OK] Создание скелета" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Создание скелета" << endl;
        }
    }

    // Тест 4: Урон врагу
    {
        enemy e("goblin", 35, 3);
        e.health -= 10;
        total++;
        if (e.health == 25) {
            cout << "[OK] Урон по врагу" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Урон по врагу" << endl;
        }
    }

    // Тест 5: Создание игрока
    {
        player_class p;
        total++;
        if (p.name == "" && p.gold == 0) {
            cout << "[OK] Создание игрока" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Создание игрока" << endl;
        }
    }

    // Тест 6: Воин
    {
        player_class p;
        p.proffi = "warrior";
        p.reset_stats();
        total++;
        if (p.health == 25 && p.damage == 5) {
            cout << "[OK] Статы воина" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Статы воина" << endl;
        }
    }

    // Тест 7: Маг
    {
        player_class p;
        p.proffi = "mage";
        p.reset_stats();
        total++;
        if (p.health == 15 && p.damage == 4) {
            cout << "[OK] Статы мага" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Статы мага" << endl;
        }
    }

    // Тест 8: Золото
    {
        player_class p;
        p.gold = 100;
        p.gold -= 30;
        total++;
        if (p.gold == 70) {
            cout << "[OK] Операции с золотом" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Операции с золотом" << endl;
        }
    }

    // Тест 9: Урон игроку
    {
        player_class p;
        p.proffi = "warrior";
        p.reset_stats();
        p.health -= 10;
        total++;
        if (p.health == 15) {
            cout << "[OK] Урон по игроку" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Урон по игроку" << endl;
        }
    }

    // Тест 10: Сравнение воин vs маг
    {
        player_class warrior;
        warrior.proffi = "warrior";
        warrior.reset_stats();

        player_class mage;
        mage.proffi = "mage";
        mage.reset_stats();

        total++;
        if (warrior.health > mage.health && warrior.damage > mage.damage) {
            cout << "[OK] Воин сильнее мага" << endl;
            ok++;
        }
        else {
            cout << "[FAIL] Воин сильнее мага" << endl;
        }
    }

    // Результат
    cout << "\n=== РЕЗУЛЬТАТ ===" << endl;
    cout << "Пройдено: " << ok << " / " << total << endl;
    cout << "=================\n" << endl;
    int b; cin >> b;
}
