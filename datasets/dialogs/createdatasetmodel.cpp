#include "createdatasetmodel.h"
#include "../../database.h"
#include <QDebug>

QStandardItemModel *CreateDatasetModel::getSetsList() const
{
    return m_setsList;
}

SetInfoData CreateDatasetModel::getInfoData(QString name)
{
    return m_hash.value(name);
}

QHash<QString, SetInfoData> CreateDatasetModel::getHash() const
{
    return m_hash;
}

void CreateDatasetModel::createDataset(DatasetInfo datasetInfo)
{
    QString request_str = "INSERT INTO datasets ('name', 'date', 'description') VALUES (?, ?, ?);";
    bool res = Database::getInstance().prepare(request_str).setVal(datasetInfo.name).setVal(datasetInfo.dateTime).setVal(datasetInfo.description).insert();
    if(!res)
    {
        qDebug() << "невозможно добавить датасет " << Database::getInstance().lastError();
    }
}

void CreateDatasetModel::createDatasetlabels(QString setName, CurrentSetInfo setInfo, int datasetID)
{
    qDebug() << Q_FUNC_INFO << setInfo.name << setInfo.count;
    int setID = getIDSet(setName);
    if(setID == -1)
    {
        qDebug() << "Ошибка, неверный ID набора";
        return;
    }

    int labelID = getIDMeaning(setInfo.name);

    if(setID == -1)
    {
        qDebug() << "Ошибка, неверный ID метки";
        return;
    }

    if(!setInfo.count)
        return;

    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM labels WHERE id_label = ? AND id_set = ?;").setVal(labelID).setVal(setID).selectRows());
    QSqlRecord rec = query.record();
    int count = 0;
    while(query.next())
    {
        int labelID = query.value(rec.indexOf("id")).toInt();
        insertDatasetLabel(datasetID, labelID);
        count++;
        if(setInfo.count == count)
            break;
    }
}

int CreateDatasetModel::getDatasetID(QString name)
{
    int id = -1;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM datasets WHERE name = ?;").setVal(name).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        id = query.value(rec.indexOf("id")).toInt();
    }
    return id;
}

QHash<QString, int> CreateDatasetModel::updateCurrentHash()
{
    m_currentHash.clear();
    foreach (SetInfoData data, m_hash)
    {
        for (int row = 0; row < data.setInfoModel->rowCount(); row++)
        {
            m_currentHash[data.setInfoModel->data(data.setInfoModel->index(row, 0)).toString()] += data.setInfoModel->data(data.setInfoModel->index(row, 2)).toInt();
        }
    }

    return m_currentHash;
}

QString CreateDatasetModel::getNameLabel(int id)
{
    QString name;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings WHERE id = ?;").setVal(id).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        name = query.value(rec.indexOf("name")).toString();
    }
    return name;
}

int CreateDatasetModel::getIDSet(QString name)
{
    int id = -1;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM sets WHERE name = ?;").setVal(name).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        id = query.value(rec.indexOf("id")).toInt();
    }
    return id;
}

int CreateDatasetModel::getIDMeaning(QString name)
{
    int id = -1;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings WHERE name = ?;").setVal(name).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        id = query.value(rec.indexOf("id")).toInt();
    }
    return id;
}

void CreateDatasetModel::insertDatasetLabel(int id_dataset, int id_label)
{
    QString request_str = "INSERT INTO datasetLabels (id_dataset, id_label) VALUES (?, ?);";
    bool res = Database::getInstance().prepare(request_str).setVal(id_dataset).setVal(id_label).insert();
    if(!res)
    {
        qDebug() << "невозможно добавить метку датасета " << Database::getInstance().lastError();
    }
}

CreateDatasetModel::CreateDatasetModel(QObject *parent) : QObject(parent)
{
    m_setsList = new QStandardItemModel(this);
}

void CreateDatasetModel::updateModels()
{
    m_hash.clear();

    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM sets;").selectRows());
    QSqlRecord rec = query.record();
    QStandardItem *item = nullptr;
    int count = 0;
    while(query.next())
    {        
        QString nameSet = query.value(rec.indexOf("name")).toString();
        int idSet = query.value(rec.indexOf("id")).toInt();
        QString description = query.value(rec.indexOf("description")).toString();

        item = new QStandardItem(nameSet);
        m_setsList->setItem(count, 0, item);
        count++;

        QHash<QString, int> tmp_hashInfo;
        QSqlQuery queryLabels(Database::getInstance().prepare("SELECT id_label FROM labels WHERE id_set = ?;").setVal(idSet).selectRows());
        QSqlRecord recLabels = queryLabels.record();
        while(queryLabels.next())
        {
            QString nameLabel = getNameLabel(queryLabels.value(recLabels.indexOf("id_label")).toInt());
            if(tmp_hashInfo.contains(nameLabel))
            {
                tmp_hashInfo.insert(nameLabel, tmp_hashInfo.value(nameLabel)+1);
            }
            else
            {
                tmp_hashInfo.insert(nameLabel, 1);
            }
        }

        QStandardItemModel *tmp_model = new QStandardItemModel();
        QStandardItem *itemSetInfo = nullptr;
        int countInfo = 0;
        QStringList header;
        header << "Название" << "Количество" << "Выбрано";
        tmp_model->setHorizontalHeaderLabels(header);
        foreach (QString key, tmp_hashInfo.keys())
        {
            itemSetInfo = new QStandardItem(key);
            tmp_model->setItem(countInfo, 0, itemSetInfo);

            itemSetInfo = new QStandardItem(QString::number(tmp_hashInfo.value(key)));
            tmp_model->setItem(countInfo, 1, itemSetInfo);

            itemSetInfo = new QStandardItem(QString::number(0));
            tmp_model->setItem(countInfo, 2, itemSetInfo);

            countInfo++;
        }
        SetInfoData setInfoData;
        setInfoData.description = description;
        setInfoData.setInfoModel = tmp_model;
        m_hash.insert(nameSet, setInfoData);
    }
}
