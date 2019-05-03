import random
import math

from .config import FIELD_X_START, FIELD_Y_START, FIELD_X_END, FIELD_Y_END


class Animal:
    all_animals = []

    all_rabbit = []
    all_wolf_men = []
    all_wolf_girl = []

    def __init__(self, x: int = 1, y: int = 1):
        Animal.all_animals.append(self)

        self.x = x
        self.y = y
        self.life_points = 1

    def move(self) -> None:
        code_movement: int = random.randint(1, 9)

        if code_movement == 1 and self.y != FIELD_Y_START:
            self.y -= 1
        elif code_movement == 2 and self.x != FIELD_X_START:
            self.x -= 1
        elif code_movement == 3 and self.y != FIELD_Y_END:
            self.y += 1
        elif code_movement == 4 and self.x != FIELD_X_END:
            self.x += 1

        elif code_movement == 5 and self.x != FIELD_X_START and self.y != FIELD_Y_END:
            self.x -= 1
            self.y += 1
        elif code_movement == 6 and self.x != FIELD_X_START and self.y != FIELD_Y_START:
            self.x -= 1
            self.y -= 1
        elif code_movement == 7 and self.x != FIELD_X_END and self.y != FIELD_Y_END:
            self.x += 1
            self.y += 1
        elif code_movement == 8 and self.x != FIELD_X_END and self.y != FIELD_Y_START:
            self.x += 1
            self.y -= 1
        elif code_movement == 9:
            pass


class WolfGirl(Animal):
    def __init__(self, x: int, y: int) -> None:
        super().__init__(x=x, y=y)
        self.all_wolf_girl.append(self)

        self.follow_rabbit = False
        self.followed_rabbit = None

        self.name = 'wolf Girl'

    def tick(self) -> None:

        if self.follow_rabbit:
            if self.followed_rabbit not in self.all_rabbit:
                self.follow_rabbit = False
                self.followed_rabbit = None

        self.search_rabbit()

        if self.follow_rabbit:
            if self.x < self.followed_rabbit.x:
                self.x += 1
            elif self.x > self.followed_rabbit.x:
                self.x -= 1

            if self.y < self.followed_rabbit.y:
                self.y += 1
            elif self.y > self.followed_rabbit.y:
                self.y -= 1

            if self.x == self.followed_rabbit.x and self.y == self.followed_rabbit.y:
                print(f'The Rabbit with id {id(self.followed_rabbit)} has been killed')

                try:
                    Animal.all_animals.remove(self.followed_rabbit)
                except ValueError:
                    pass
                self.life_points += 1
                self.follow_rabbit = False
                self.followed_rabbit = None
            else:
                self.life_points -= 0.1

                if self.life_points == 0:
                    print(f'The {self.name} with id {id(self)} have died')

                    Animal.all_animals.remove(self)
        else:
            self.move()

    def search_rabbit(self):
        if not self.follow_rabbit:

            for rabbit in Animal.all_rabbit:
                if not self.follow_rabbit and math.sqrt(((self.x - rabbit.x) ** 2) + ((self.y - rabbit.y) ** 2)) < 2:
                    self.follow_rabbit = True
                    self.followed_rabbit = rabbit


class WolfMan(Animal):
    def __init__(self, x, y):
        super().__init__(x=x, y=y)
        self.all_wolf_men.append(self)

        self.follow_rabbit = False
        self.follow_wolfgirl = False

        self.followed_rabbit = None
        self.followed_wolfgirl = None

        self.name = 'wolf MAN'

    def tick(self) -> None:
        if self.follow_rabbit:
            if self.followed_rabbit not in self.all_rabbit:
                self.follow_rabbit = False
                self.followed_rabbit = None

        self.search_rabbit()

        if self.follow_rabbit:
            if self.x < self.followed_rabbit.x:
                self.x += 1
            elif self.x > self.followed_rabbit.x:
                self.x -= 1

            if self.y < self.followed_rabbit.y:
                self.y += 1
            elif self.y > self.followed_rabbit.y:
                self.y -= 1

            if self.x == self.followed_rabbit.x and self.y == self.followed_rabbit.y:
                Animal.all_rabbit.remove(self.followed_rabbit)

                print(f'The Rabbit with id {id(self.followed_rabbit)} has been killed')

                self.life_points += 1
                self.follow_rabbit = False
                self.followed_rabbit = None
            else:
                self.life_points -= 0.1

                if self.life_points == 0:
                    print(f'The {self.name} with id {id(self)} have died')
                    Animal.all_animals.remove(self)

        elif not self.follow_rabbit:
            self.search_wolfgirls()

        if self.follow_wolfgirl:
            if self.x < self.followed_wolfgirl.x:
                self.x += 1
            elif self.x > self.followed_wolfgirl.x:
                self.x -= 1

            if self.y < self.followed_wolfgirl.y:
                self.y += 1
            elif self.y > self.followed_wolfgirl.y:
                self.y -= 1

            if self.x == self.followed_wolfgirl.x and self.y == self.followed_wolfgirl.y:
                sex = random.randint(0, 1)
                print(f'The wolf kid has been born')
                if sex == 0:
                    Animal.all_wolf_girl.append(WolfGirl(((self.x + 10) % 20) + 1, ((self.y + 15) % 20) + 1))
                elif sex == 1:
                    Animal.all_wolf_men.append(WolfMan(((self.x + 10) % 20) + 1, ((self.y + 15) % 20) + 1))

                self.follow_wolfgirl = False
                self.followed_wolfgirl = None

        else:
            self.move()

    def search_rabbit(self):
        if not self.follow_rabbit:

            for rabbit in Animal.all_rabbit:
                if not self.follow_rabbit and math.sqrt(((self.x - rabbit.x) ** 2) + ((self.y - rabbit.y) ** 2)) < 2:
                    self.follow_rabbit = True
                    self.followed_rabbit = rabbit

                    self.follow_wolfgirl = False
                    self.followed_wolfgirl = None

    def search_wolfgirls(self):
        if not self.follow_wolfgirl:
            for wolfgirl in Animal.all_wolf_girl:

                distance_to_obj = math.sqrt(((self.x - wolfgirl.x) ** 2) + ((self.y - wolfgirl.y) ** 2))

                if not self.follow_wolfgirl and distance_to_obj < 2:
                    self.follow_wolfgirl = True
                    self.followed_wolfgirl = wolfgirl
                    print(f'The wolf girl with id {id(self.followed_wolfgirl)} is watched by wolf man with id {id(self)}')


class Rabbit(Animal):
    def __init__(self, x, y):
        super().__init__(x=x, y=y)

        self.all_rabbit.append(self)
        self.name = 'Rabbit'

    def tick(self) -> None:
        self.try_create_new_rab()
        self.move()

    def try_create_new_rab(self) -> None:
        code = random.randint(1, 10)
        if code == 1:
            Animal.all_rabbit.append(Rabbit(self.x, self.y))
