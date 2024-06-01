#ifndef DUNGEON_H
#define DUNGEON_H
#include<iostream>
#include"database.h"
#include"enemy.h"
#include"hero.h"
#include"Fight.h"
class Dungeon
{
public:
    Dungeon(Enemy& enemy, Database& database, Fight& fight, Hero& hero):TheEnemy(enemy),TheDatabase(database),TheFight(fight), TheHero(hero){};
    bool WantToQuit;
    int TheDungeon;
    int Progress;
    void DungeonFighting(Enemy &TheEnemy, Database &TheDatabase, std::vector<std::vector<int>> EnemiesUsed,std::vector<std::string> EnemyTypes, std::vector<std::string> Scenario, int Progress){
    std::cout<<Scenario[Progress];
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout<<"\nINPUT NUMBER OF DESIRED ENEMY:\n";
    for(int i=Progress;i<=EnemyTypes.size();i++)
    {
    std::cout<< i+1 <<". "<< EnemyTypes[i] <<" . HP: "<<EnemiesUsed[i][1]<<". DMG: "<<EnemiesUsed[i][2]<<". EXP: "<<EnemiesUsed[i][3]<<". Gold "<<EnemiesUsed[i][4]<<".\n";
    }
    WantToQuit=false;
    std::cout<<"\nENTER 1 TO START FIGHT\nINPUT \"0\" TO EXIT DUNGEON\n";
    int E;
    std::cin>>E;
    if(E==0){WantToQuit=true; goto Quitting;}
    if(E>5){std::cout<<"INVALID INDEX"; goto Quitting;};
    TheEnemy.GetStats(TheEnemy, TheDatabase, E-1);
    TheFight.CurrentlyFighting(TheHero, TheEnemy);
    Quitting:;
    };
    void ChooseDungeon(){
    WantToQuit=false;
    MainGame:
    int Input;
    std::cout<<"\nWhere do you want to go?\n1: House. The place where you maintain a semblance of control.\n2: Museum. Home of the artifacts of the old ones. Target of many.\n3: R'lyeh. Where in his house at R'lyeh dead Cthulhu lies sleeping\n4: The Void. Where your adventure as well as all ends in the domain of Azathoth\n 0: Quit to main menu.\n";
    std::cin>>Input;
    if(std::cin.fail()){
        std::cout<<"ERROR INVALID INPUT";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        goto MainGame;}
    switch(Input)
        {
    case 0:
        WantToQuit=true;
        break;
    case 1:
        House:
        TheFight.ChooseFight(TheEnemy,TheDatabase, TheDatabase.EnemiesLoaded, TheDatabase.EnemyTypes);
        if(TheFight.DidWin==false)
        {
        goto Quit;
        };
        if(TheFight.WantToQuit==true){std::cin.clear();goto House;}
        goto MainGame;
        break;
    case 2:
        ChosenDungeon(TheDatabase, TheEnemy, 0);
        break;
    case 3:
        ChosenDungeon(TheDatabase, TheEnemy, 1);
        break;
    case 4:
        ChosenDungeon(TheDatabase, TheEnemy, 2);
        break;
        }
    Quit:;
    }
    void CurrentDungeon(Enemy &TheEnemy, int ID)
    {
        TheEnemy.GetStats(TheEnemy,TheDatabase,ID);

    };
    void ChosenDungeon(Database& TheDatabase, Enemy& TheEnemy,int Dungeon)
    {
        std::vector<std::string>EnemyTypes=TheDatabase.DungeonEnemyTypes[Dungeon];
        std::vector<std::vector<int>> EnemiesUsed=TheDatabase.InDungeon[Dungeon];
        std::cout<<"\n The Necronomicon opens up and you see the list of those who wish to harm you... abominable or not\n";
        for(int i=Progress; i<TheDatabase.InDungeon.size();i++)
        {
            std::cout<< i+1 <<". "<< EnemyTypes[i] <<" . HP: "<<EnemiesUsed[i][1]<<". DMG: "<<EnemiesUsed[i][2]<<". EXP: "<<EnemiesUsed[i][3]<<". Gold "<<EnemiesUsed[i][4]<<".\n";
        };
    };
private:
    Database &TheDatabase;
    Enemy &TheEnemy;
    Fight &TheFight;
    Hero& TheHero;
};

#endif // DUNGEON_H
