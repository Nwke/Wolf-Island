#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>

#include <time.h> 
#include <algorithm>
#include <cmath>

#include "Rabbit.h"
#include "WolfGirl.h"
#include "WolfMan.h"
#include "Constants.h"



using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "================================ Краткое руководство ================================\n\n" << endl;
    cout << "Приветствую вас в приложении экологической модели “Волчий остров”.\nПожалуйста, ознакомьтесь с моделью для дальнейшей работы.\nСуть экологической модели “Волчий остров”:\nУ вас есть поле 20х20, на котором заселены дикие кролики, волки и волчицы.\nПравила данной модели приближены к реальным.\nДанное приложение пытается смоделировать исход эксперимента так, как если бы он проходил в условиях реальной жизни.\nВ дальнейшем вам предложат ввести параметры, чтобы привести приложение в активное состояние.\nВы также можете различным образом менять, комбинировать параметры, чтобы \nпоэксперементировать, выявить какие-либо закономерности, выдвинуть гипотезы." << endl;

    vector<shared_ptr<Rabbit>> all_rabbits;
    vector<shared_ptr<WolfGirl>> all_wolfgirl;
    vector<shared_ptr<WolfMan>> all_wolfman;
    

    int count_rabbits;
    int count_wolfgirl;
    int count_wolfman;

    cout << "\n\n" << endl;
    cout << "Введите количество кролликов на поле: ";
    cin >> count_rabbits;

    cout << "Введите количество волчиц на поле: " ;
    cin >> count_wolfgirl;

    cout << "Введите количество волков на поле: " ;
    cin >> count_wolfman;

    for (size_t i = 0; i < count_rabbits; i++) {
        int x = 0;
        int y = 0;
        cout << "==============" << endl;
        cout << "Кроллик по номеру " << i + 1  << endl;
        cout << "Введите координату Х в диапазоне от  " << FIELD_X_D << " До " << FIELD_X_U <<": ";

        cin >> x;

        cout << "Введите координату У в диапазоне от " << FIELD_Y_D << " До " << FIELD_Y_U << ": ";
        cin >> y;

        shared_ptr<Rabbit> new_rabbit(new Rabbit(x, y, &all_rabbits));
        all_rabbits.push_back(new_rabbit);
    }

    for (size_t i = 0; i < count_wolfgirl; i++) {
        int x = 0;
        int y = 0;
        cout << "==============" << endl;
        cout << "Волчица по номеру " << i + 1  << endl;
        cout << "Введите координату Х в диапазоне от " << FIELD_X_D << " До " << FIELD_X_U << ": ";

        cin >> x;

        cout << "Введите координату У в диапазоне от " << FIELD_Y_D << " До " << FIELD_Y_U << ": ";
        cin >> y;

        shared_ptr<WolfGirl> new_wolfgirl(new WolfGirl(x, y, &all_rabbits, &all_wolfgirl));

        all_wolfgirl.push_back(new_wolfgirl);
    }


    for (size_t i = 0; i < count_wolfman; i++) {
        int x = 0;
        int y = 0;
        cout << "==============" << endl;
        cout << "Волк по номеру " << i + 1 << endl;
        cout << "Введите координату Х в диапазоне от " << FIELD_X_D << " До " << FIELD_X_U << ": ";

        cin >> x;

        cout << "Введите координату У в диапазоне от " << FIELD_Y_D << " До " << FIELD_Y_U << ": ";
        cin >> y;

        shared_ptr<WolfMan> new_wolfman(new WolfMan(x, y, &all_rabbits, &all_wolfman, &all_wolfgirl));

        all_wolfman.push_back(new_wolfman);
    }

    cout << "\n\n";
    cout << "=========== НАЧАЛО СИМУЛЯЦИИ ===========" << endl;

    while (all_rabbits.size() != 0) {
        vector<shared_ptr<Rabbit>> rabbits_copy(all_rabbits);
        vector<shared_ptr<WolfGirl>> wolfgirl_copy(all_wolfgirl);
        vector<shared_ptr<WolfMan>> wolfman_copy(all_wolfman);

  

        for (auto rabb : rabbits_copy) {
            (*rabb).tick();
        }



        for (auto wolf_girl : wolfgirl_copy) {
            (*wolf_girl).tick();
            cout << "Количество очков определенной волчицы: " << (*wolf_girl).life_points << endl;

        }

        for (auto wolf_man : wolfman_copy) {
            (*wolf_man).tick();
            cout << "Количество всех кролликов: " << all_rabbits.size() << endl;
            cout << "Количество очков определенного волка: " << (*wolf_man).life_points << endl;
        }

        cout << "Количество всех кролликов: " << all_rabbits.size() << endl;
        cout << "Количество всех волчиц: " << all_wolfgirl.size() << endl;
        cout << "Количество всех волков: " << all_wolfman.size() << endl;

        cout << "===============================================" << endl;
        
        
    }

    cout << "=========== КОНЕЦ СИМУЛЯЦИИ ===========" << endl;
    cout << endl;
    cout << endl;
    cout << "=========== ИТОГИ ===========" << endl;

    cout << "Количество всех кролликов: " << all_rabbits.size() << endl;
    cout << "Количество всех волчиц: " << all_wolfgirl.size() << endl;
    cout << "Количество всех волков: " << all_wolfman.size() << endl;





    all_rabbits.clear();
    cout << "Игра окончена" << endl;
    system("pause");
}


