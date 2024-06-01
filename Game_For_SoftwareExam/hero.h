#ifndef HERO_H
#define HERO_H
#include<iostream>
#include"database.h"
class Hero
{
public:
    Hero(){};
    Database TheDatabase;
    std::vector<std::vector<int>> TheHero;
    std::vector<int> Stats;
    int Gold;
    int ID;
    std::string _name;
    int LV;
    int EXP;
    int HP;
    int DMG;
    int totDMG;
    int MaxHP;
    int Entry;
    int Indicator;
    std::vector<std::string> HeroName;
    bool isHeroAlive()
    {
        return HP>totDMG;
    }
    void DefineBasics()
    {
        DMG=1+(LV/1.5);
        HP=10*LV;
        MaxHP=HP;
        totDMG=0;
    };
    void UpdateHero(Database &TheDatabase)
    {
        ID=TheDatabase.HeroStats[0];
        TheDatabase.UpdateHero(LV,EXP,Gold,ID);
        DefineBasics();
    };
    void LVUP(Hero)
    {
          if(LV*1000<=EXP)
          {
              DoubleLV:
              EXP=EXP-LV*1000;
              LV++;
              std::cout<<"LEVEL UP!\nLevel "<<LV<<" reached!\n";
              if(LV*1000<=EXP)
              {goto DoubleLV;}
          }
    };
    void NewHero(Database &TheDatabase)
    {
        std::getline(std::cin, _name);
        LV=1;
        EXP=0;
        Gold=0;
        DefineBasics();
        TheDatabase.MakeHero(TheDatabase,_name,EXP,LV,Gold);
        Stats.push_back(LV);
        Stats.push_back(EXP);
        Stats.push_back(Gold);
        TheDatabase.LoadHeroes(TheDatabase);
    };
    void ChooseHeroes(Database &TheDatabase)
    {
        HeroName.clear();
        TheHero.clear();
        HeroName=TheDatabase.HeroNames;
        TheHero=TheDatabase.HeroSave;
        TryAgain:
        ShowHeroes(TheDatabase);
        std::cout<<"INPUT \"0\" TO QUIT TO MENU\n";
        std::cin>>Entry;
        if(Entry==0){Indicator=-1;goto EXIT;};
        Entry=Entry-1;
        {
            if(Entry>TheHero.capacity()-1)
            {
              std::cout<<"ERROR INVALID INDEX TRY AGAIN\n";
              std::cin.clear();
              goto TryAgain;
            };
            if(Entry>=TheHero.size()){Indicator=-1;goto EXIT;};
            TheDatabase.HeroStats=TheHero[Entry];
            ID=TheHero[Entry][0];
            _name=HeroName[Entry];
            LV=TheHero[Entry][1];
            EXP=TheHero[Entry][2];
            Gold=TheHero[Entry][3];
            DefineBasics();

        };
        EXIT:
        ;
        };
    void ShowHeroes(Database &TheDatabase)
    {
        TheDatabase.LoadHeroes(TheDatabase);
        HeroName=TheDatabase.HeroNames;
        TheHero=TheDatabase.HeroSave;
        if(TheHero.size()==0){std::cout<<"\nNO VICTIMS MANIFEST ONE (No saves make a new one)\n"; goto Invalid;}
        for(int s=0; s<=TheHero.size()-1;s++)
        {
         std::cout<<s+1;
            {
            std::cout<<": Name: "<<HeroName[s]<<". Level: "<<TheHero[s][1]<<". EXP: "<<TheHero[s][2]<<". Gold: "<<TheHero[s][3]<<".\n";
            }
        }
        Invalid:
        ;
    };
private:

};

#endif // HERO_H
