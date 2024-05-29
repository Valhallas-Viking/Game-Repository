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
        DMG=1+(LV/2);
        HP=10*LV;
        MaxHP=HP;
        totDMG=0;
    };
    void UpdateHero(Database &TheDatabase)
    {
        ID=TheDatabase.Save;
        TheDatabase.UpdateHero(LV,EXP,Gold,ID);
        DefineBasics();
    };
    void LVUP()
    {
          if(LV*1000==EXP)
          {
              EXP=EXP-LV*1000;
              LV++;
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
        for(int s=0; s<=TheDatabase.AmountOfSaves();s++)
        {
         std::cout<<s+1;
            {
            std::cout<<": Name: "<<HeroName[s]<<". Level: "<<TheHero[s][1]<<". EXP: "<<TheHero[s][2]<<". Gold: "<<TheHero[s][3]<<".\n";
            }
        }
    };
private:

};

#endif // HERO_H
