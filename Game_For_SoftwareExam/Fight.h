#ifndef FIGHT_H
#define FIGHT_H
#include "enemy.h"
#include "hero.h"
#include "database.h"
#include <limits>

class Fight{
public:
    bool WantToQuit;
    bool DidWin;
    Fight(Hero& hero, Enemy& enemy, Database& database):FightHero(hero),FightEnemy(enemy),TheDatabase(database){};

    void CurrentlyFighting(Hero& HeroFight, Enemy& EnemyFight){

        WantToQuit=false;
        FightHero.totDMG=0;
        FightEnemy.totDMG=0;
        FightHero.HP=FightHero.MaxHP;
        while(true){
            std::cout<<std::endl<<HeroFight._name<<" attacks dealing "<<HeroFight.DMG<<" Damage\n";
            EnemyFight.totDMG=EnemyFight.totDMG+HeroFight.DMG;
            if(EnemyFight.isEnemyAlive()==false){
                std::cout<<"\nYOU WON!\n";
                DidWin=true;
                FightHero.totDMG=0;
                std::cout<<"Gold: "<<HeroFight.Gold<<" + "<<EnemyFight.Gold<<" = ";
                HeroFight.Gold=HeroFight.Gold+EnemyFight.Gold;
                std::cout<<HeroFight.Gold<<std::endl;
                std::cout<<HeroFight.EXP<<" + "<<EnemyFight.EXP<<" = ";
                HeroFight.EXP=HeroFight.EXP+EnemyFight.EXP;
                std::cout<<HeroFight.EXP<<std::endl;
                HeroFight.LVUP();
                HeroFight.UpdateHero(TheDatabase);
                break;
            }
            std::cout<<EnemyFight._name<<"'s HP: "<<EnemyFight.HP-EnemyFight.totDMG<<std::endl;
            std::cout<<EnemyFight._name<<" attacks dealing "<<EnemyFight.DMG<<" Damage "<<std::endl<<HeroFight._name<<"'s HP: ";
            HeroFight.totDMG=HeroFight.totDMG+EnemyFight.DMG;
            std::cout<<HeroFight.HP-HeroFight.totDMG;
            if(HeroFight.isHeroAlive()==false){
                HeroFight.HP=HeroFight.MaxHP;
                std::cout<<"\nYOU DIED\n";
                DidWin=false;
                break;
            }
            std::cout<<"\nPress ENTER to continue";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        };
    }
    void ChooseFight(Enemy &Enemy, Database &TheDatabase)
    {
    std::cin.clear();
    std::cout<<"\nINPUT NUMBER OF DESIRED ENEMY:\n";
    for(int i=0;i<=TheDatabase.EnemiesLoaded.size()-1;i++)
    {
    std::cout<< i+1 <<". "<< TheDatabase.EnemyTypes[i] <<" . HP: "<<TheDatabase.EnemiesLoaded[i][1]<<". DMG: "<<TheDatabase.EnemiesLoaded[i][2]<<". EXP: "<<TheDatabase.EnemiesLoaded[i][3]<<". Gold "<<TheDatabase.EnemiesLoaded[i][4]<<".\n";
    }
    std::cout<<"INPUT \"0\" TO QUIT TO MENU\n";
    int E;
    std::cin>>E;
    if(E==0|isdigit(E)!=true){WantToQuit=true; goto Quitting;}
    FightEnemy.GetStats(Enemy, TheDatabase, E-1);
    std::cin.clear();
    std::cin.ignore();
    CurrentlyFighting(FightHero, FightEnemy);
    Quitting:
    ;
    };
private:
    Enemy& FightEnemy;
    Hero& FightHero;
    Database& TheDatabase;
};
#endif // FIGHT_H
