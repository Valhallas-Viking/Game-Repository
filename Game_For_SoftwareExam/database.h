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
        _db.setUserName("root");  // Use the appropriate username
        _db.setPassword("password");  // Use the correct password
        if (!_db.open()) {
            qDebug() << "Failed to open the database:" << _db.lastError().text();
        }
    }
    std::string Type;
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
    std::string PlayerName;
    std::vector<std::string> HeroNames;
    std::vector<int> EnemyStats;
    std::vector<std::vector<int>> EnemiesLoaded;
    std::vector<std::string> EnemyTypes;
    std::vector<std::string> HeroName;
    std::vector<std::vector<int>> HeroSave;
    std::vector<int> HeroStats;
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
        Reset:
        std::cout<<"\nINPUT \"0\" TO QUIT TO MENU\nCHOOSE YOUR SACREFICE(delete save) BY INPUTTING INDEX: ";
        if(HeroSave.size()==0){std::cout<<"\nNO SACREFICES TO BE MADE (There are no saves)\n";break;};
        std::cin>>Save;
        Save=Save-1;
        if(Save==-1|Save>=HeroSave.size()){std::cout<<"Invalid ID going to main menu"; break;}
        QSqlQuery query(_db);
        query.prepare("DELETE FROM HERO WHERE id_Hero=:id_hero");
        query.bindValue(":id_hero",HeroSave[Save][0]);
        HeroNames.erase(HeroNames.begin()+Save);
        if(!query.exec())
        {
            qDebug()<<"Selected invalid ID exitting to menu"<<query.lastError().text(); break;
        }
        else
        {
            std::cout<<HeroNames[Save]<<" Has drawn their last breath";
            goto Reset;
        }
        }while(true);
    }
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
            } else {
                qDebug() << "Hero created successfully!";
            }
    };
    void UpdateHero(int LV, int EXP, int Gold, int Save)
    {
        QSqlQuery query(_db);
        query.prepare("UPDATE HERO SET LV= :newLv, XP = :newExp, Gold = :newGold WHERE id_Hero=:idHero");
        query.bindValue(":newLv", LV);
        query.bindValue(":newExp", EXP);
        query.bindValue(":newGold", Gold);
        query.bindValue(":idHero", Save);
        if(!query.exec())
        {
            qDebug()<<"Update of Hero failed:"<<query.lastError().text();
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
        if (query.exec("SELECT * FROM HERO")) {
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
        } else {
            qDebug() << " Hero Load query failed:" << query.lastError().text();
        }
    }
    int AmountOfSaves()
    {
        QSqlQuery query(_db);
        query.prepare("Select COUNT(*) FROM HERO");
        if (!query.exec())
        {
            qDebug()<<" Load Save query failed:"<<query.lastError().text();
            return -1;
        }
        int count=0;
        if (query.next())
        {
            count=query.value(0).toInt();
        }
        return count-1;
    };
private:
    QSqlDatabase _db;
};
#endif
