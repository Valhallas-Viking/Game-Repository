/*std::vector<Enemy> Database::EnemyExtract(){
    std::vector<Enemy> enemyVector;
    QSqlQuery query(_db);

    qDebug() << query.exec("SELECT * FROM enemy"); // employee er her navnet på en tabel, ikke et schema

    qDebug() << "Number of rows:" << query.size();

    while (query.next()) {
        int hp = query.value(0).toInt();
        QString navn = query.value(1).toString();
        int styrke = query.value(2).toInt();
        enemyVector.push_back(Enemy(navn, hp, styrke));
    }

    return enemyVector;

};*/
