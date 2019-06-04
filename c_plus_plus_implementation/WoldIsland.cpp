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
    cout << "================================ ������� ����������� ================================\n\n" << endl;
    cout << "����������� ��� � ���������� ������������� ������ ������� ������.\n����������, ������������ � ������� ��� ���������� ������.\n���� ������������� ������ ������� ������:\n� ��� ���� ���� 20�20, �� ������� �������� ����� �������, ����� � �������.\n������� ������ ������ ���������� � ��������.\n������ ���������� �������� ������������� ����� ������������ ���, ��� ���� �� �� �������� � �������� �������� �����.\n� ���������� ��� ��������� ������ ���������, ����� �������� ���������� � �������� ���������.\n�� ����� ������ ��������� ������� ������, ������������� ���������, ����� \n��������������������, ������� �����-���� ��������������, ��������� ��������." << endl;

    vector<shared_ptr<Rabbit>> all_rabbits;
    vector<shared_ptr<WolfGirl>> all_wolfgirl;
    vector<shared_ptr<WolfMan>> all_wolfman;
    

    int count_rabbits;
    int count_wolfgirl;
    int count_wolfman;

    cout << "\n\n" << endl;
    cout << "������� ���������� ��������� �� ����: ";
    cin >> count_rabbits;

    cout << "������� ���������� ������ �� ����: " ;
    cin >> count_wolfgirl;

    cout << "������� ���������� ������ �� ����: " ;
    cin >> count_wolfman;

    for (size_t i = 0; i < count_rabbits; i++) {
        int x = 0;
        int y = 0;
        cout << "==============" << endl;
        cout << "������� �� ������ " << i + 1  << endl;
        cout << "������� ���������� � � ��������� ��  " << FIELD_X_D << " �� " << FIELD_X_U <<": ";

        cin >> x;

        cout << "������� ���������� � � ��������� �� " << FIELD_Y_D << " �� " << FIELD_Y_U << ": ";
        cin >> y;

        shared_ptr<Rabbit> new_rabbit(new Rabbit(x, y, &all_rabbits));
        all_rabbits.push_back(new_rabbit);
    }

    for (size_t i = 0; i < count_wolfgirl; i++) {
        int x = 0;
        int y = 0;
        cout << "==============" << endl;
        cout << "������� �� ������ " << i + 1  << endl;
        cout << "������� ���������� � � ��������� �� " << FIELD_X_D << " �� " << FIELD_X_U << ": ";

        cin >> x;

        cout << "������� ���������� � � ��������� �� " << FIELD_Y_D << " �� " << FIELD_Y_U << ": ";
        cin >> y;

        shared_ptr<WolfGirl> new_wolfgirl(new WolfGirl(x, y, &all_rabbits, &all_wolfgirl));

        all_wolfgirl.push_back(new_wolfgirl);
    }


    for (size_t i = 0; i < count_wolfman; i++) {
        int x = 0;
        int y = 0;
        cout << "==============" << endl;
        cout << "���� �� ������ " << i + 1 << endl;
        cout << "������� ���������� � � ��������� �� " << FIELD_X_D << " �� " << FIELD_X_U << ": ";

        cin >> x;

        cout << "������� ���������� � � ��������� �� " << FIELD_Y_D << " �� " << FIELD_Y_U << ": ";
        cin >> y;

        shared_ptr<WolfMan> new_wolfman(new WolfMan(x, y, &all_rabbits, &all_wolfman, &all_wolfgirl));

        all_wolfman.push_back(new_wolfman);
    }

    cout << "\n\n";
    cout << "=========== ������ ��������� ===========" << endl;

    while (all_rabbits.size() != 0) {
        vector<shared_ptr<Rabbit>> rabbits_copy(all_rabbits);
        vector<shared_ptr<WolfGirl>> wolfgirl_copy(all_wolfgirl);
        vector<shared_ptr<WolfMan>> wolfman_copy(all_wolfman);

  

        for (auto rabb : rabbits_copy) {
            (*rabb).tick();
        }



        for (auto wolf_girl : wolfgirl_copy) {
            (*wolf_girl).tick();
            cout << "���������� ����� ������������ �������: " << (*wolf_girl).life_points << endl;

        }

        for (auto wolf_man : wolfman_copy) {
            (*wolf_man).tick();
            cout << "���������� ���� ���������: " << all_rabbits.size() << endl;
            cout << "���������� ����� ������������� �����: " << (*wolf_man).life_points << endl;
        }

        cout << "���������� ���� ���������: " << all_rabbits.size() << endl;
        cout << "���������� ���� ������: " << all_wolfgirl.size() << endl;
        cout << "���������� ���� ������: " << all_wolfman.size() << endl;

        cout << "===============================================" << endl;
        
        
    }

    cout << "=========== ����� ��������� ===========" << endl;
    cout << endl;
    cout << endl;
    cout << "=========== ����� ===========" << endl;

    cout << "���������� ���� ���������: " << all_rabbits.size() << endl;
    cout << "���������� ���� ������: " << all_wolfgirl.size() << endl;
    cout << "���������� ���� ������: " << all_wolfman.size() << endl;





    all_rabbits.clear();
    cout << "���� ��������" << endl;
    system("pause");
}


