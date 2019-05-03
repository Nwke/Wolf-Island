from python_implementation.animal import Rabbit, WolfGirl, WolfMan, Animal


def run_main():
    Rabbit(1, 1)

    WolfGirl(20, 20)
    WolfMan(15, 15)

    while len(Animal.all_rabbit) != 0:
        print(f'Count of rabbits: {len(Animal.all_rabbit)}')
        print(f'Count of wolf men: {len(Animal.all_wolf_men)}')
        print(f'Count of wolf girls: {len(Animal.all_wolf_girl)}')
        print(f'===========================================')
        for animal in Animal.all_animals:
            animal.tick()


if __name__ == '__main__':
    run_main()
