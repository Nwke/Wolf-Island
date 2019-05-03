#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <cmath>

const int FIELD_X_D = 1;
const int FIELD_X_U = 5;
 
const int FIELD_Y_D = 1;
const int FIELD_Y_U = 5;



using namespace std;

class Animal {
public:

    virtual void move() {
        
    }

    virtual ~Animal() {

    }

};




class Rabbit : public Animal {
private:
    int x;
    int y;
public:

    int getx() {
        return x;
    }

    int gety() {
        return y;
    }

    void setx(int value) {
        this->x = value;
    }

    void sety(int value) {
        this->y = value;
    }

    int get_random(int from, int to) {
        int random;
        random = rand() % to + from;
        return random;
    }

    Rabbit(int x, int y) {
        this->x = x;
        this->y = y;
        //cout << "I was created and i have x and y: " << x << " " << y << endl;
    }
    ~Rabbit() {
        cout << "Rabbit was deleted" << endl;;
    }



    void move() {
        int code_movement = get_random(1, 9);

        if ((code_movement == 1) && (this->y != FIELD_Y_D)) {
            this->y -= 1;
        }
        if ((code_movement == 2) && (this->x != FIELD_X_D)) {
            this->x -= 1;
        }
        if ((code_movement == 3) && (this->y != FIELD_Y_U)) {
            this->y += 1;
        }
        if ((code_movement == 4) && (this->y != FIELD_X_U)) {
            this->x += 1;
        }
        if ((code_movement == 5) && (this->x != FIELD_X_D) && (this->y != FIELD_Y_U)) {
            this->x -= 1;
            this->y += 1;
        }
        if ((code_movement == 6) && (this->x != FIELD_X_D) && (this->y != FIELD_Y_D)) {
            this->x -= 1;
            this->y -= 1;
        }
        if ((code_movement == 7) && (this->x != FIELD_X_U) && (this->y != FIELD_Y_U)) {
            this->x += 1;
            this->y += 1;
        }
        if ((code_movement == 8) && (this->x != FIELD_X_U) && (this->y != FIELD_Y_D)) {
            this->x += 1;
            this->y -= 1;
        }
        if (code_movement == 9) {

        }
    }


    void try_create_new_rab(vector<shared_ptr<Rabbit>> *all_rabits) {
        int code = get_random(1, 10);
       
        if (code == 2) { 
            shared_ptr<Rabbit> p1(new Rabbit(this->x, this->y));
            (*all_rabits).push_back(p1);
            // cout << all_rabits.size() << endl;
        }
       

    }


    void tick(vector<shared_ptr<Rabbit>> *all_rabits) {
        try_create_new_rab(all_rabits);
        move();
    }

};


class WolfGirl : public Animal {
private:
    int x;
    int y;
public:

    vector<shared_ptr<Rabbit>> *all_rabbits;
    vector<shared_ptr<WolfGirl>> *all_wolfgirl;


    int life_points = 1;

    bool follow_rabbit = false;
    shared_ptr<Rabbit> followed_rabbit;


    int getx() {
        return x;
    }

    int gety() {
        return y;
    }

    void setx(int value) {
        this->x = value;
    }

    void sety(int value) {
        this->y = value;
    }

    int get_random(int from, int to) {
        int random;
        random = rand() % to + from;
        return random;
    }



    WolfGirl(int x, int y, vector<shared_ptr<Rabbit>> *all_rabbits, vector<shared_ptr<WolfGirl>> *all_wolfgirl) {
        this->x = x;
        this->y = y;
        this->all_rabbits = all_rabbits;
        this->all_wolfgirl = all_wolfgirl;
    

    }
    ~WolfGirl() {
        cout << "Wolf girl was deleted" << endl;;
    }

    void move() {
        int code_movement = get_random(1, 9);

        if ((code_movement == 1) && (this->y != FIELD_Y_D)) {
            this->y -= 1;
        }
        if ((code_movement == 2) && (this->x != FIELD_X_D)) {
            this->x -= 1;
        }
        if ((code_movement == 3) && (this->y != FIELD_Y_U)) {
            this->y += 1;
        }
        if ((code_movement == 4) && (this->y != FIELD_X_U)) {
            this->x += 1;
        }
        if ((code_movement == 5) && (this->x != FIELD_X_D) && (this->y != FIELD_Y_U)) {
            this->x -= 1;
            this->y += 1;
        }
        if ((code_movement == 6) && (this->x != FIELD_X_D) && (this->y != FIELD_Y_D)) {
            this->x -= 1;
            this->y -= 1;
        }
        if ((code_movement == 7) && (this->x != FIELD_X_U) && (this->y != FIELD_Y_U)) {
            this->x += 1;
            this->y += 1;
        }
        if ((code_movement == 8) && (this->x != FIELD_X_U) && (this->y != FIELD_Y_D)) {
            this->x += 1;
            this->y -= 1;
        }
        if (code_movement == 9) {

        }
    }

   void search_rabbit() {

       if (!this->follow_rabbit) {
           
           
           // cout << this->all_wolfgirl.size();
           for (auto rab : *this->all_rabbits) {
               
               cout << "ALL OK: " << endl;
   
   
               if ((!this->follow_rabbit) && (sqrt(pow(this->x - (*rab).getx(), 2) + pow(this->y - (*rab).gety(), 2) < 2))) {
                   cout << "WE FOUND A RABBIT FOR EAT" << endl;
               }
           }
       }
   }


    void tick() {

    }


};




// cout << "Size is: " << all_rabits.size() << endl;
// for (auto &rab : all_rabits) {
//     cout << "Coord x is: " << (*rab).getx() << endl;
// }

int main()
{

    vector<shared_ptr<Rabbit>> all_rabbits;
    vector<shared_ptr<WolfGirl>> all_wolfgirl;
    // THERE IS MISTAKE
    vector<shared_ptr<Rabbit>> all_wolfman;
    
    shared_ptr<Rabbit> p1(new Rabbit(5, 4));
    shared_ptr<Rabbit> p2(new Rabbit(5, 4));
    shared_ptr<Rabbit> p3(new Rabbit(5, 4));
    
    // cout << all_rabbits.size();
    
    shared_ptr<WolfGirl> p4(new WolfGirl(5, 4, &all_rabbits, &all_wolfgirl));

    all_wolfgirl.pushs_back(p4);


    all_rabbits.push_back(p1);

    all_rabbits.push_back(p2);

    all_rabbits.push_back(p3);

    
    

    int i = 10;
    while (i > 0) {
        // all rabbits
        vector<shared_ptr<Rabbit>> rabbits_copy(all_rabbits);
        vector<shared_ptr<WolfGirl>> wolfgirl_copy(all_wolfgirl);
        vector<shared_ptr<Rabbit>> wolfman_copy(all_wolfman);

  

        for (auto rab : rabbits_copy) {
            (*rab).tick(&all_rabbits);
            cout << "Size all rabits is: " << all_rabbits.size() << endl;
        }



        for (auto &wolf_girl : wolfgirl_copy) {
            (*wolf_girl).search_rabbit();
            //cout << "Size all rabits is: " << all_rabbits.size() << endl;
        }
        
        
    }





    std::cout << "Hello World!\n"; 
    all_rabbits.clear();
}


