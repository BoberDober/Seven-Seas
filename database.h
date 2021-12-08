#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QTextCodec>
#include <QObject>

/*! \class Database adbclass.h "adbclass.h"
 *  This class is a wrapper for working with database
 */

class  Database: public QObject
{
    Q_OBJECT
public:
    static Database& getInstance();
public slots:
    bool isOpened();

    bool openDB(QString Driver,QString database="postgres",QString pass="postgres",QString host="localhost" , QString login="postgres",int port=5432);
    /*! \fn bool openDB(QString Driver,QString database="postgres",QString pass="postgres",QString host="localhost" , QString login="postgres",int port=5432)
    * \brief Open specified DB
    * \param Driver - driver name, curretnly supported QSQLITE, QPSQL
    * \param database - database name
    * \param pass - password, only for postges
    * \param host - hostname, only for postges
    * \param login - login, only for postges
    * \param port - port, only for postges
    * \return true if opened, false otherwise
    */
    bool createTable(QString sql);
    /*! \fn bool createTable(QString sql)
    * \brief create new table with specified request
    * \param sql - sql request for table creating
    * \return true if table created, fale otherwise
    */
    QString getDBError();
    /*! \fn QString getDBError()
    * \brief Database system errors, like fail open/close database
    * \return Error description
    */
    void transaction();
    /*! \fn void transaction()
    * \brief Transaction support, start transaction
    */
    void commit();
    /*! \fn void commit()
    * \brief Transaction support, commit transaction
    */
    void rollback();
    /*! \fn void rollback()
    * \brief Transaction support,rollback transaction
    */
    Database& prepare(QString sql);
    /*! \fn Database& prepare(QString sql)
    * \brief prepare sql statement
    * \param sql statement
    * \return this class link
    */
    Database& setVal(const QVariant& val);
    /*! \fn Database& setVal(const QVariant& val)
    * \brief setup value, specified in prepare statement as "?"
    * \param val - any value
    * \return this class link
    */
    bool insert();
    /*! \fn bool insert()
    * \brief sql insert action
    * \return true if ok, false otherwise
    */
    bool del();
    /*! \fn bool del()
    * \brief sql delete action
    * \return true if ok, false otherwise
    */
    bool update();
    /*! \fn bool update()
    * \brief sql update action
    * \return true if ok, false otherwise
    */
    int getColumns();
    /*! \fn int getColumns()
    * \brief get columns of requested recordset
    * \return numbers of columns
    */
    QString getColName(int i);
    /*! \fn QString getColName(int i)
    * \brief get column name
    * \param i - column number
    * \return name of specified column
    */
    QSqlQuery selectRows();
    /*! \fn QSqlQuery selectRows()
    * \brief get rows recordset
    * \return QSqlQuery object
    */
    QVariant insertLastId();
    /*! \fn QVariant insertLastId()
    * \brief get last insrted id, please not for postgres you must add "returning id" string in the prepare statement
    * \return last inerted id
    */
    QVariant selectValue();
    /*! \fn QVariant selectValue()
    * \brief Select value
    * \return selected value
    */
    QList<QVariant> selectValues(int count);
    QString lastError();
    /*! \fn QString lastError()
    * \brief Last Sql non system error
    * \return last request error
    */
    bool isSuccess();
    /*! \fn bool isSuccess()
    * \brief Check success of last query
    * \return true if ok, false otherwise
    */
    void close();
    /*! \fn void close()
    * \brief close database
    */
    QString getDriverName();

    QSqlQuery currentQuery();

    bool exec(const QString& sql);
private:
    Database();
    /*! \fn Database()
    * \brief Class constructor
    */
    ~Database();
    /*! \fn ~Database()
    * \brief Class destructor
    */
    QSqlDatabase db;
    /*! \var QSqlDatabase db
    * database object
    */
    QString dname;
    /*! \var QString dname
    * database name
    */
    QSqlQuery query;
    /*! \var QSqlQuery query
    * database query object
    */
    bool success;
    /*! \var bool success
    * Sql error flag
    */
    QString dberror;
    /*! \var QString dberror
    * System error flag
    */
    QString connectionName;
    Database(Database const&) = delete;
    Database& operator= (Database const&) = delete;

};


#endif // DATABASE_H


