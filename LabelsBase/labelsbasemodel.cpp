#include "labelsbasemodel.h"
#include "../database.h"
#include <QDebug>

LabelsBaseModel::LabelsBaseModel(QObject *parent) : QStandardItemModel(parent)
{

}

void LabelsBaseModel::updateModel()
{
    clear();
    QStringList horizontalHeader;
    horizontalHeader.append("Название");
//    horizontalHeader.append("Количество значений");
    horizontalHeader.append("Описание");

    setHorizontalHeaderLabels(horizontalHeader);

    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings;").selectRows());
    QSqlRecord rec = query.record();
    QStandardItem *item = nullptr;
    int count = 0;
    while(query.next())
    {
        item = new QStandardItem(query.value(rec.indexOf("name")).toString());
        setItem(count, 0, item);

//        item = new QStandardItem(QString::number(getCountMeanings(query.value(rec.indexOf("id")).toInt())));
//        setItem(count, 1, item);

        item = new QStandardItem(query.value(rec.indexOf("description")).toString());
        setItem(count, 1, item);

        count++;
    }
    //    delete item; TO DO
}

bool LabelsBaseModel::addMeaning(const QString& oldName, const QString& name, const QString& description)
{
    int id = getIDMeaning(name);
    if(oldName == name)
    {
        qDebug() << oldName << name << description;
        qDebug() << "РЕДАКТИРОВАТЬ ОПИСАНИЕ";
        updateMeaningDescription(id, description);
        return true;
    }
    if(id == -1)
    {
        if(oldName.isEmpty())
        {
//            qDebug() << "СОВСЕМ НОВАЯ";
            insertMeaning(name, description);
        }
        else
        {
//            qDebug() << "НОВАЯ МЕТКА ИЗ СТАРОЙ";
            updateMeaning(name, description, oldName);
        }
        return true;
    }
    else
    {
        if(oldName.isEmpty())
        {
//            qDebug() << "МЕТКА СУЩЕСТВУЕТ, СОЗДАТЬ НЕВОЗМОЖНО!";
            return false;
        }
        else
        {
//            qDebug() << "МЕТКА СУЩЕСТВУЕТ, ОБЪЕДИНЯЮ";
            replaceMeaningLabels(getIDMeaning(oldName), id);
            deleteMeaning(oldName);
            return true;
        }
    }
}

bool LabelsBaseModel::checkDeleteMeaning(const QString &name)
{
    int id = getIDMeaning(name);
    qDebug() << id;
    if(!checkMeaningUsed(id))
    {
//        qDebug() << "УДАЛИТЬ!";
        deleteMeaning(name);
        return true;
    }
    else
    {
//        qDebug() << "УДАЛИТЬ НЕВОЗМОЖНО!";
        return false;
    }
}

void LabelsBaseModel::deleteMeaning(const QString &name)
{
    QString request_str = "DELETE FROM meanings WHERE name = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(name).del();
    if(!res)
    {
        qDebug() << "невозможно удалить метку " << Database::getInstance().lastError();
    }
}

bool LabelsBaseModel::checkMeaningUsed(int id)
{
    bool check = false;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM labels WHERE id_label = ?;").setVal(id).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        check = true;
    }
    return check;
}

void LabelsBaseModel::updateMeaningDescription(int id, const QString &description)
{


    QString request_str = "UPDATE meanings SET description = ? WHERE id = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(description).setVal(description).setVal(id).update();
    qDebug() << id << description << res;
    if(!res)
    {
        qDebug() << "невозможно редактировать значение " << Database::getInstance().lastError();
    }
}

int LabelsBaseModel::getCountMeanings(int id)
{
    int count = 0;

    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings WHERE element_id = ?;").setVal(id).selectRows());
    QSqlRecord rec = query.record();
    while(query.next())
    {
        count++;
    }
    return  count;
}

void LabelsBaseModel::insertMeaning(const QString &name, const QString &description)
{
    QString request_str = "INSERT INTO meanings ('name', 'description') VALUES (?, ?);";
    bool res = Database::getInstance().prepare(request_str).setVal(name).setVal(description).insert();
    if(!res)
    {
        qDebug() << "невозможно добавить значение " << Database::getInstance().lastError();
    }
}

int LabelsBaseModel::getIDMeaning(const QString &name) const
{
    int id = -1;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings WHERE name = ?;").setVal(name).selectRows());
    QSqlRecord rec = query.record();
    while(query.next())
    {
        id = query.value(rec.indexOf("id")).toInt();
    }

    return id;
}

void LabelsBaseModel::updateMeaning(const QString &name, const QString &description, const QString &oldName)
{
    QString request_str = "UPDATE meanings SET name = ?, description = ? WHERE name = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(name).setVal(description).setVal(oldName).update();
    if(!res)
    {
        qDebug() << "невозможно редактировать значение " << Database::getInstance().lastError();
    }
}

void LabelsBaseModel::replaceMeaningLabels(int oldID, int ID)
{
    QString request_str = "UPDATE labels SET id_label = ? WHERE id_label = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(ID).setVal(oldID).update();
    if(!res)
    {
        qDebug() << "невозможно редактировать значение " << Database::getInstance().lastError();
    }
}
