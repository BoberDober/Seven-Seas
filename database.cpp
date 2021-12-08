#include "database.h"
#include <QDebug>
#include <QtCore/QCoreApplication>

Database &Database::getInstance()
{
    static Database instance;
    return instance;
}

Database::Database()
{
    this->success=true;
}
Database::~Database()
{
    db.close();
}
void Database::transaction()
{
    db.transaction();
}
void Database::commit()
{
    db.commit();
}
void Database::rollback()
{
    db.rollback();
}

bool Database::isOpened()
{
    return db.isOpen();
}

bool Database::openDB(QString Driver, QString database, QString pass, QString host, QString login,int port)
{
   if(db.isOpen())
        db.close();
    dname=Driver;
    QString uniqkey;
    uniqkey.setNum((unsigned long long)(this));

    if(Driver=="QSQLITE")
    {
        connectionName=database;
        if(database.isEmpty())
        {
            database="db.sql";
            connectionName = uniqkey + database;
            db=QSqlDatabase::addDatabase("QSQLITE", connectionName);
        }
        else if(database.contains("/"))
        {
            db=QSqlDatabase::addDatabase("QSQLITE", connectionName);
        }
        else
        {
            db=QSqlDatabase::addDatabase("QSQLITE", connectionName);
        }

        connectionName=database;
        db.setDatabaseName(connectionName);


    }
    else if(Driver=="QPSQL")
    {
        db=QSqlDatabase::addDatabase("QPSQL", uniqkey);
        qDebug()<<"Connecting db...";
        qDebug()<<"Host: "<<host;
        qDebug()<<"Port: "<<port;
        qDebug()<<"Database: "<<database;
        qDebug()<<"(login): "<<login;
        qDebug()<<"(pass): "<<pass;
        db.setHostName(host);
        db.setPort(port);
        db.setDatabaseName(database);
        db.setUserName(login);
        db.setPassword(pass);

    }

    bool ok = db.open();
    if(!ok){
        this->dberror=db.lastError().text();
        qDebug()<<"Fail to connect: "<<dberror;
        return false;
    }

    this->query=QSqlQuery(db);
    return true;
}
QString Database::getDriverName()
{
    return dname;
}
bool Database::createTable(QString sql)
{
    this->success=this->query.exec(sql);
    return this->success;
}
QString Database::getDBError()
{
    return this->dberror;
}
Database& Database::prepare(QString sql)
{
    this->query.clear();
    this->success=this->query.prepare(sql);
    return *this;
}
Database& Database::setVal(const QVariant& val)
{

    this->query.addBindValue(val);
    return *this;
}
bool Database::insert()
{
    this->success=this->query.exec();
    return this->success;
}
bool Database::del()
{
    this->success=this->query.exec();
    return this->success;
}
bool Database::update()
{
    this->success=this->query.exec();
    return this->success;
}

QVariant Database::selectValue()
{
    this->success=this->query.exec();
    if(this->success && this->query.next())
    {
        return this->query.value(0);
    }
    return "";
}
QList<QVariant> Database::selectValues(int count)
{
    QList<QVariant> data;
    this->success=this->query.exec();
    if(this->success && this->query.next())
    {
        for(int i=0;i<count;i++)
            data.append(query.value(i));
    }
    return data;
}
QVariant Database::insertLastId()
{

    this->success=this->query.exec();
    if(this->success)
    {
        if(dname=="QPSQL")
        {
            if(this->query.isActive())
            {
                this->query.next();
                return this->query.value(0);
            }
        }
        else
        {
            return this->query.lastInsertId();
        }
    }
    return 0;
}
bool Database::isSuccess()
{
    return this->success;
}
QString Database::lastError()
{
    if(!this->success)return this->query.lastError().text();
    return "";
}
int Database::getColumns()
{
    return this->query.record().count();
}
QString Database::getColName(int i)
{
    if(i<this->getColumns())
    {
        return this->query.record().fieldName(i);
    }
    else
    {
        return "";
    }
}
QSqlQuery Database::selectRows()
{
    this->success=this->query.exec();
    return this->query;
}

void Database::close()
{
    this->query.clear();
    query = QSqlQuery();
    db = QSqlDatabase();
    //db.close();
    QSqlDatabase::removeDatabase(connectionName);
}

QSqlQuery Database::currentQuery()
{
    return query;
}

bool Database::exec(const QString& sql)
{
    this->success=this->query.exec(sql);
    return this->success;
}
