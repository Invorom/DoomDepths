#ifndef MONSTER_H
#define MONSTER_H

#define RED "\x1b[31m"
#define RED_2 "\x1b[38;5;196m"
#define RED_3 "\x1b[38;5;160m"
#define RED_4 "\x1b[38;5;124m"
#define RED_5 "\x1b[38;5;88m"
#define RED_6 "\x1b[38;5;52m"

#define RESET "\x1b[0m"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define BLACK "\x1b[30m"
#define RESET "\x1b[0m"

typedef struct Monster
{
    char *name;
    int life;
    int attackMin;
    int attackMax;
    int defense;
} Monster;

Monster *create_monster();

void display_monster(Monster *monster);

void display_hero();

#endif