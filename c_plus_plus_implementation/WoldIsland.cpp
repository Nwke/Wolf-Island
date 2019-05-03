#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
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
    vector<shared_ptr<Rabbit>> all_rabbits;
    vector<shared_ptr<WolfGirl>> all_wolfgirl;
    vector<shared_ptr<WolfMan>> all_wolfman;
    
    shared_ptr<Rabbit> rabbit1(new Rabbit(1, 1, &all_rabbits));
    shared_ptr<WolfGirl> wolfgirl1(new WolfGirl(20, 20, &all_rabbits, &all_wolfgirl));
    shared_ptr<WolfMan> wolfman1(new WolfMan(15, 15, &all_rabbits, &all_wolfman, &all_wolfgirl));

    all_rabbits.push_back(rabbit1);
    all_wolfgirl.push_back(wolfgirl1);
    all_wolfman.push_back(wolfman1);
    
    

    while (all_rabbits.size() != 0) {
        vector<shared_ptr<Rabbit>> rabbits_copy(all_rabbits);
        vector<shared_ptr<WolfGirl>> wolfgirl_copy(all_wolfgirl);
        vector<shared_ptr<WolfMan>> wolfman_copy(all_wolfman);

  

        for (auto rabb : rabbits_copy) {
            (*rabb).tick();
        }



        for (auto wolf_girl : wolfgirl_copy) {
            (*wolf_girl).tick();
            cout << "POINTS: WOLFMAN: " << (*wolf_girl).life_points << endl;

        }

        for (auto wolf_man : wolfman_copy) {
            (*wolf_man).tick();
            cout << "Size all rabits is: " << all_rabbits.size() << endl;
            cout << "POINTS: WOLFMAN: " << (*wolf_man).life_points << endl;
        }

        cout << "Size all rabits is: " << all_rabbits.size() << endl;
        cout << "Size all wolfgirl is: " << all_wolfgirl.size() << endl;
        cout << "Size all wolfman is: " << all_wolfman.size() << endl;

        cout << "===============================================" << endl;
        
        
    }

    cout << "=========================" << endl;

    cout << "Size all rabits is: " << all_rabbits.size() << endl;
    cout << "Size all wolfgirl is: " << all_wolfgirl.size() << endl;
    cout << "Size all wolfman is: " << all_wolfman.size() << endl;





    std::cout << "Hello World!\n"; 
    all_rabbits.clear();
}


