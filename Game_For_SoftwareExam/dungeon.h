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
    bool DidWin;
    bool GoToMain;
    bool EndOfGame=false;
    void ChooseDungeon(){
    MainGame:
    WantToQuit=false;
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
        GoToMain=true;
        return;
    case 1:
        House:
        TheFight.ChooseFight(TheEnemy,TheDatabase, TheDatabase.EnemiesLoaded, TheDatabase.EnemyTypes);
        if(TheFight.DidWin==false)
        {
        goto Quit;
        };
        if(TheFight.WantToQuit==true){std::cin.clear();goto MainGame;}
        if(TheFight.DidWin==true)
        {
            goto House;
        }
        goto MainGame;
        break;
        case 2:
        ChosenDungeon(TheDatabase, TheEnemy, 0);
        if(WantToQuit==true)
        {goto MainGame;};
        if(DidWin==false)
        {
        return;
        }
        goto MainGame;
        break;
    case 3:
        ChosenDungeon(TheDatabase, TheEnemy, 1);
        if(WantToQuit==true)
        {goto MainGame;};
        if(DidWin==false)
        {
        return;
        }
        goto MainGame;
        break;
    case 4:
        ChosenDungeon(TheDatabase, TheEnemy, 2);
        if(WantToQuit==true)
        {goto MainGame;};
        if(DidWin==false)
        {
        return;
        }
        goto MainGame;
        break;
    default:
        std::cout<<"\nINVALID INPUT\n";
        goto MainGame;
        }
    Quit:;
    }
    void DungeonFight (Enemy &TheEnemy,Database &TheDatabase, int Dungeon,int Progress)
    {
        TheEnemy.GetStats(TheEnemy,TheDatabase,TheDatabase.InDungeon[Dungeon][Progress][0]-1);
        WantToQuit=false;
        TheHero.totDMG=0;
        TheEnemy.totDMG=0;
        TheHero.HP=TheHero.MaxHP;
        bool IgnoreFix=true;
        while(true){
            std::cout<<std::endl<<TheHero._name<<" attacks dealing "<<TheHero.DMG<<" Damage\n";
            TheEnemy.totDMG=TheEnemy.totDMG+TheHero.DMG;
            if(TheEnemy.isEnemyAlive()==false){
                std::cout<<"\nYOU WON!\n";
                DidWin=true;
                TheHero.totDMG=0;
                std::cout<<"Gold: "<<TheHero.Gold<<" + "<<TheEnemy.Gold<<" = ";
                TheHero.Gold=TheHero.Gold+TheEnemy.Gold;
                std::cout<<TheHero.Gold<<std::endl;
                std::cout<<TheHero.EXP<<" + "<<TheEnemy.EXP<<" = ";
                TheHero.EXP=TheHero.EXP+TheEnemy.EXP;
                std::cout<<TheHero.EXP<<std::endl;
                TheHero.LVUP(TheHero);
                TheDatabase.UpdateProgress(TheDatabase,Dungeon);
               TheHero.UpdateHero(TheDatabase);
                if(Progress==TheDatabase.InDungeon[Dungeon].size()-1){TheDatabase.Reward(TheDatabase,Dungeon); if(Dungeon==2)
                    {
                        std::cout<<"\nAs you finally see a great gash in the elder god Azathoth's nigh incomprehensible form a passage from the Necronomicon burns bright.\n \"Azathoth The Blind Idiot God: The being whose dream is responsible for the entire existance of the universe and if ever awoken will cease the universes existance\"\nAs you read this your foe begins to awake-";
                        TheDatabase.EndOfGame();
                        abort();
                    };
                }
                break;
            }
            std::cout<<TheEnemy._name<<"'s HP: "<<TheEnemy.HP-TheEnemy.totDMG<<std::endl;
            std::cout<<TheEnemy._name<<" attacks dealing "<<TheEnemy.DMG<<" Damage "<<std::endl<<TheHero._name<<"'s HP: ";
            TheHero.totDMG=TheHero.totDMG+TheEnemy.DMG;
            std::cout<<TheHero.HP-TheHero.totDMG;
            if(TheHero.isHeroAlive()==false){
                TheHero.HP=TheHero.MaxHP;
                std::cout<<"\nYOU DIED\n";
                DidWin=false;
                break;
            }
            std::cout<<"\nPress ENTER to continue";
            if(IgnoreFix==true&TheHero.EXP!=0){std::cin.ignore();IgnoreFix=false;};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        };
    }
    void ChosenDungeon(Database& TheDatabase, Enemy& TheEnemy,int Dungeon)
    {
        Reset:
        int E;
        WantToQuit=false;
        DidWin=true;
        TheDatabase.GetProgress(TheDatabase,Dungeon);
        int Progress=TheDatabase.Progress;
        std::vector<std::string>EnemyTypes=TheDatabase.DungeonEnemyTypes[Dungeon];
        std::vector<std::vector<int>> EnemiesUsed=TheDatabase.InDungeon[Dungeon];
        if(EnemiesUsed.size()-Progress==0){std::cout<<"\nYou wander aimlessly... nothing of use can be found...";}
        if(EnemiesUsed.size()-Progress==0){std::cout<<"\n The Necronomicon opens up and you see the list of those who wish to harm you... abominable or not\n";}
        for(int i=Progress; i<EnemiesUsed.size();i++)
        {
            std::cout<< i+1 <<". "<< EnemyTypes[i] <<" . HP: "<<EnemiesUsed[i][1]<<". DMG: "<<EnemiesUsed[i][2]<<". EXP: "<<EnemiesUsed[i][3]<<". Gold "<<EnemiesUsed[i][4]<<".\n";
        };
        if(EnemiesUsed.size()-Progress==0){goto Quit;}
        std::cout<<"\nTO CONTINUE INPUT 1.\nTO QUIT TO HUB INPUT 0\n";
        std::cin>>E;
        switch(E)
        {
        case 0:
            goto Quit;
        break;
        case 1:
        DungeonFight(TheEnemy,TheDatabase,Dungeon,Progress);
        if(DidWin==false){return;}
        goto Reset;
        };
    Quit:;
    };
private:
    Database &TheDatabase;
    Enemy &TheEnemy;
    Fight &TheFight;
    Hero& TheHero;
};

#endif // DUNGEON_H
