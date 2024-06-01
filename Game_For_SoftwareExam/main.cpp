#include <iostream>
#include <string>
#include "hero.h"
#include "Fight.h"
#include "enemy.h"
#include "database.h"
#include "dungeon.h"
#include <limits>
int main()
{
    Hero myHero;
    Database TheDatabase;
    TheDatabase.setupConnection();
    Enemy TheEnemy;
    Fight TheFight(myHero,TheEnemy, TheDatabase);
    Dungeon TheDungeon(TheEnemy,TheDatabase,TheFight,myHero);
    int Input;
    int Input2;
    TheDatabase.LoadEnemies(TheDatabase);
    TheDatabase.LoadHeroes(TheDatabase);
    TheEnemy.GetStats(TheEnemy,TheDatabase, 0);
    ERROR1:
    myHero.Indicator=0;
    TheDatabase.LoadHeroes(TheDatabase);
    TheDatabase.LoadDungeonEnemies(TheDatabase);
    std::cout << R"(
         _    _      ______      ________ _____ _____            ______ _______   _____  _____  ______          __  __ _____ _   _  _____    _
      /\| |/\| |    / __ \ \    / /  ____/ ____|  __ \     /\   |  ____|__   __| |  __ \|  __ \|  ____|   /\   |  \/  |_   _| \ | |/ ____|/\| |/\
      \ ` ' /| |   | |  | \ \  / /| |__ | |    | |__) |   /  \  | |__     | |    | |  | | |__) | |__     /  \  | \  / | | | |  \| | |  __ \ ` ' /
     |_     _| |   | |  | |\ \/ / |  __|| |    |  _  /   / /\ \ |  __|    | |    | |  | |  _  /|  __|   / /\ \ | |\/| | | | | . ` | | |_ |_     _|
      / , . \| |___| |__| | \  /  | |___| |____| | \ \  / ____ \| |       | |    | |__| | | \ \| |____ / ____ \| |  | |_| |_| |\  | |__| |/ , . \
      \/|_|\/|______\____/   \/   |______\_____|_|  \_\/_/    \_\_|       |_|    |_____/|_|  \_\______/_/    \_\_|  |_|_____|_| \_|\_____|\/|_|\/ )";
    std::cout<< std::endl<<"                                                                  *Press 1 for new game*"<<std::endl<<"                                                                *Press 2 to manage saves*\n"<<"                                                                    *Press 3 to quit*\n";
    std::cin >> Input;
    std::cin.clear();
    std::cin.ignore();
    switch(Input){
    case 1:
            if(TheDatabase.HeroSave.size()>=3)
            {std::cout<<"One can only control 3 victims at once"; goto ERROR1;}
            std::cout<<"NAME: ";
            myHero.NewHero(TheDatabase);
            goto Start_Of_Game;
        break;
    case 2:
        std::cout<<"\nInput 1 to choose a victim\nInput 2 to sacrefice(delete) a victim\nInput 3 to return to menu\n";
        std::cout.clear();
        std::cin>>Input2;
        switch(Input2){
        case 1:
        myHero.ChooseHeroes(TheDatabase);
        if(myHero.Indicator==-1){std::cout<<"\nGoing to main menu\n";goto ERROR1;};
        break;
        case 2:
        myHero.ShowHeroes(TheDatabase);
        TheDatabase.DeleteSave();
        goto ERROR1;
        break;
        default:
        goto ERROR1;
        break;
                      };
        if(myHero.Indicator==-1){std::cout<<"INVALID SAVE TRY AGAIN";goto ERROR1;}
        if(myHero.LV==1&myHero.EXP==0)
        {
        goto Start_Of_Game;
        }
        else
        {
            goto MainGame;
        }
        break;
    case 3: return 0;
        break;
    default: std::cout<<"ERROR TRY AGAIN"<<std::endl;
        Input=0;
        goto ERROR1;
        break;
    };
    Start_Of_Game:
    myHero.LVUP();
    std::cin.clear();
    std::cin.ignore();
    int pauseInput;
    std::cout<<"You awaken in a strange room... although it is not unfamiliar to you as it is your room... right?"<<std::endl<<"Of course it is... it's not that your room is different but more that you don't recognise it..."<<std::endl<<"Enter anything to continue"<<std::endl;
    std::cout<<"Suddenly something scurries out from under your bed and you begin to feel drowzy...\n *Press enter to continue*";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // I have to write this to make the "Press enter to continue" work as it removes all former input which would trigger the other code
    std::cout<<"A... Rat? No a thing that looks like a rat with a human head and features runs out from under your bed and attacks you\n";
    std::cout<<TheEnemy._name<<"\nHP: "<<TheEnemy.HP<<" Damage: "<<TheEnemy.DMG;
    TheEnemy.GetStats(TheEnemy,TheDatabase,0);
    TheFight.CurrentlyFighting(myHero,TheEnemy);
    if(TheFight.DidWin==false)
    {
     goto ERROR1;
    };
    std::cout<<"As the ratlike creature lies dead in front of you you snap out of your dizzy trancelike state\n You realise that despite being on death's door moments before you're completely unscathed\n As you stand up you see on your nightstand a book titled \"Necronomicon\" which entails\n all manner of information on the grotesque monsters of this newly discovered state you're in.\n As you read the book you begin to see visages of the written abominable and arcane information:";
    MainGame:
    TheDungeon.ChooseDungeon();
    goto ERROR1;
}
