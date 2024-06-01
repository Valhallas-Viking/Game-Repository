#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
#include <vector>
#include <tuple>

class Database {
public:
    Database() {
        setupConnection();
    }

    ~Database() {
        _db.close();
    }

    void setupConnection() {
        _db = QSqlDatabase::addDatabase("QMYSQL");
        _db.setHostName("localhost");
        _db.setDatabaseName("Game");
        _db.setUserName("root");
        _db.setPassword("password");
        if (!_db.open()) {
            qDebug() << "Failed to open the database:" << _db.lastError().text();
        }
    }
    std::string Type;
    int DungeonEnemyID;
    int EnemyAmount=0;
    int ID;
    int HP;
    int DMG;
    int XP;
    int Gold;
    int Save;
    int LV;
    int PlayerEXP;
    int PlayerGold;
    int Progress;
    int DungeonID;
    std::string PlayerName;
    std::vector<std::string> HeroNames;
    std::vector<int> EnemyStats;
    std::vector<std::vector<int>> EnemiesLoaded;
    std::vector<std::string> EnemyTypes;
    std::vector<std::string> HeroName;
    std::vector<std::vector<int>> HeroSave;
    std::vector<int> HeroStats;
    std::vector<int> CurrentEnemy;
    std::vector<std::vector<int>>HerosProgress;
    std::vector<std::vector<std::vector<int>>> InDungeon;
    std::vector<std::vector<std::string>>DungeonEnemyTypes;
    std::vector<std::string> DungeonEnemyType;

    void LoadEnemies(Database &Database) {
        QSqlQuery query(_db);
        if (query.exec("SELECT * FROM Enemies")) {
            while (query.next()) {
                ID = query.value(0).toInt();
                Type = query.value(1).toString().toStdString();
                HP = query.value(2).toInt();
                DMG = query.value(3).toInt();
                XP = query.value(4).toInt();
                Gold = query.value(5).toInt();
                EnemyStats.push_back(ID);
                EnemyStats.push_back(HP);
                EnemyStats.push_back(DMG);
                EnemyStats.push_back(XP);
                EnemyStats.push_back(Gold);
                EnemyTypes.push_back(Type);
                EnemiesLoaded.push_back(EnemyStats);
                EnemyStats.clear();
                EnemyAmount++;
                                  }
        } else {
            qDebug() << "Enemy query failed:" << query.lastError().text();
        }
    }
    void DeleteSave()
    {
        int Save;
        do{
        std::cout<<"\nINPUT \"0\" TO QUIT TO MENU\nCHOOSE YOUR SACREFICE(delete save) BY INPUTTING INDEX: ";
        if(HeroSave.size()==0){std::cout<<"\nNO SACREFICES TO BE MADE (There are no saves)\n";break;};
        std::cin>>Save;
        Save=Save-1;
        if(Save==-1|Save>=HeroSave.size()){std::cout<<"Invalid ID going to main menu"; break;}
        QSqlQuery query(_db);
        query.prepare("DELETE FROM HERO WHERE id_Hero=:id_hero");
        query.bindValue(":id_hero",HeroSave[Save][0]);
        DeleteProgress(HeroSave[Save][0],Save);
        if(!query.exec())
        {
            qDebug()<<"Selected invalid ID exitting to menu"<<query.lastError().text(); break;
        }
        else
        {
            if(Save>HeroSave.size()-1){break;};
            std::cout<<HeroNames[Save]<<" Has drawn their last breath";
            HeroSave.erase(HeroSave.begin()+Save);
            break;
        }
        }while(true);
    }
    void DeleteProgress(int HeroID, int WhichHero)
    {
        QSqlQuery query(_db);
        query.prepare("DELETE FROM Progress WHERE id_Hero=:id_hero");
        query.bindValue(":id_hero",HeroID);
        if(!query.exec())
        {
            qDebug()<<"ERROR DELETING PROGRESS"<<query.lastError().text();
        }
    };
    void MakeHero(Database,std::string HeroName, int EXP, int LV, int Gold)
    {
        QSqlQuery query(_db);
        query.prepare("INSERT INTO HERO (Name, XP, LV, Gold) Values (?, ?, ?, ?)");
        query.addBindValue(QString::fromStdString(HeroName));
        query.addBindValue(EXP);
        query.addBindValue(LV);
        query.addBindValue(Gold);
        if (!query.exec()) {
                qDebug() << "Hero creation Query failed:" << query.lastError().text();
                return;
                 }
        MakeProgress(ReadID());

    };
    int ReadID() {
        int ID;
        QSqlQuery query(_db);
        query.prepare("SELECT id_Hero FROM HERO ORDER BY id_Hero DESC LIMIT 1");

        if (!query.exec()) {
            qDebug() << "Failed to execute query:" << query.lastError().text();
            return -1;
        }
        if (query.next()) {
            ID = query.value(0).toInt();
            return ID;
        } else {
            qDebug() << "No record fetched";
            return -1;
        }
    }
    void MakeProgress(int HeroID) {
        QSqlQuery query(_db);
        for (int i = 0; i <= 2; ++i) {
            query.prepare("INSERT INTO Progress (id_Hero, DungeonID, Progress) Values (?, ?, ?)");
            query.addBindValue(HeroID);
            query.addBindValue(i);
            query.addBindValue(0);

            if (!query.exec()) {
                qDebug() << "Hero creation Query failed:" << query.lastError().text();
            }
            query.clear(); // Clear the previous bindings if reusing the query object
        }
    }

    void UpdateHero(int LV, int EXP, int Gold, int Save)
    {
        QSqlQuery query(_db);
        query.exec("SELECT id_Hero FROM HERO");
        query.prepare("UPDATE HERO SET LV= :newLv, XP = :newExp, Gold = :newGold WHERE id_Hero=:idHero");
        query.bindValue(":newLv", LV);
        query.bindValue(":newExp", EXP);
        query.bindValue(":newGold", Gold);
        query.bindValue(":idHero", Save);
        if(!query.exec())
        {
            qDebug()<<"Update of save failed:"<<query.lastError().text();
        }
        else
        {
            qDebug()<<"\nGame saved sucessfully\n";
        }
    }
    void LoadHeroes(Database &Database) {
        QSqlQuery query(_db);
        HeroNames.clear();
        HeroSave.clear();
        query.exec("SELECT * FROM HERO");{
            while (query.next()) {
                Save = query.value(0).toInt();
                PlayerName = query.value(1).toString().toStdString();
                LV = query.value(2).toInt();
                PlayerEXP = query.value(3).toInt();
                PlayerGold = query.value(4).toInt();
                HeroStats.push_back(Save);
                HeroStats.push_back(LV);
                HeroStats.push_back(PlayerEXP);
                HeroStats.push_back(PlayerGold);
                HeroNames.push_back(PlayerName);
                HeroSave.push_back(HeroStats);
                HeroStats.clear();
            }

        }
        if(!query.exec())
        {
            qDebug()<<"ERROR SAVES NOT LOADED";
        }
    };
    void UpdateProgress(Database,int Dungeon)
    {
        QSqlQuery query(_db);
        query.prepare("UPDATE Progress SET Progress=:NewProgress Where DungeonID=:CurrentDungeon AND id_Hero=:idhero");{
            query.bindValue(":NewProgress",Progress+1);
            query.bindValue(":idhero", HeroStats[0]);
            query.bindValue(":CurrentDungeon",Dungeon);
            if(!query.exec())
            {
                qDebug()<<"ERROR UPDATING PROGRESS FAILED: "<<query.lastError().text();
            };
        }
    };
    void LoadDungeonEnemies(Database)
    {
        QSqlQuery query(_db);
        for(int i=0;i<3;i++){//Too tired remember that the for loop is broken for tomorrow as the game has no way of knowing how big HerosProgress is gonna be
        query.prepare("SELECT EnemyID FROM Dungeon where DungeonID = :dungeonid");
        {
            query.bindValue(":dungeonid",i);
            if(query.exec())
            {
                while(query.next())
                {
                    int EnemyID = query.value(0).toInt()-1;
                    HerosProgress.push_back(EnemiesLoaded[EnemyID]);
                    DungeonEnemyType.push_back(EnemyTypes[EnemyID]);
                }
            }
            else{qDebug()<<"LoadingDungeons Failed:"<<query.lastError().text();}
        }
        InDungeon.push_back(HerosProgress);
        DungeonEnemyTypes.push_back(DungeonEnemyType);
      }
    };
    void GetProgress(Database,int Dungeon)
    {
        QSqlQuery query(_db);
            query.prepare("SELECT Progress From Progress WHERE DungeonID=:dungeonid");
            query.bindValue(":dungeonid", Dungeon);

            if (query.exec()) {
                if (query.next()) {  // Position the query on the first result record
                    Progress = query.value(0).toInt();
                } else {
                    qDebug() << "No records found for DungeonID:" << Dungeon;
                }
            } else {
                qDebug() << "SettingProgress Failed" << query.lastError().text();
            }
    };
private:
    QSqlDatabase _db;
};
#endif
