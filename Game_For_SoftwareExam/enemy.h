#ifndef ENEMY_H
#define ENEMY_H
#include <iostream>
#include <vector>
#include <tuple>
#include "database.h"
class Enemy
{
public:
    Enemy(){};
    Database TheDatabase;
    int EnemyID;
    std::string _name;
    int HP;
    int DMG;
    int totDMG;
    int EXP;
    int Gold;
    std::vector<std::string> Name=TheDatabase.EnemyTypes;
    std::vector<int> ChosenEnemy;
    void GetStats(Enemy &Enemy,Database &TheDatabase, int Entry)
    {
    ChosenEnemy = TheDatabase.EnemiesLoaded[Entry];
    EnemyID = ChosenEnemy[0];
    HP = ChosenEnemy[1];
    DMG = ChosenEnemy[2];
    EXP = ChosenEnemy[3];
    Gold = ChosenEnemy[4];
    totDMG = 0;
    _name = TheDatabase.EnemyTypes[Entry];

    };
    bool isEnemyAlive()
    {
        return HP>totDMG;
    }
};

#endif // ENEMY_H
