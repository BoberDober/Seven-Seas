#include "datasetsmodel.h"
#include "../database.h"
#include <QDebug>

#define BORDER_WEIGHT 4

QStandardItemModel *DatasetsModel::listModel() const
{
    return m_listModel;
}

QStandardItemModel *DatasetsModel::tableLabelsModel() const
{
    return m_tableLabelsModel;
}

QHash<QString, QStandardItemModel *> DatasetsModel::hashModel() const
{
    return m_hashModel;
}

QStandardItemModel *DatasetsModel::tableModel() const
{
    return m_tableModel;
}

QVector<int> DatasetsModel::getListID(const QString& name)
{
    int id = getDataset(name);
    QVector<int> listID;
    if(id == -1)
    {
        qDebug() << "Ошибка ID датасета!";
        return listID;
    }

    QSqlQuery queryDatasetLabels(Database::getInstance().prepare("SELECT * FROM datasetLabels WHERE id_dataset = ?;").setVal(id).selectRows());
    QSqlRecord recDatasetLabels = queryDatasetLabels.record();
    while(queryDatasetLabels.next())
    {
        listID.append(queryDatasetLabels.value(recDatasetLabels.indexOf("id_label")).toInt());
    }
    return listID;
}

QString DatasetsModel::getSetName(int id)
{
    QString name;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM sets WHERE id = ?;").setVal(id).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        name = query.value(rec.indexOf("name")).toString();
    }

    if(name.isEmpty())
    {
        qDebug() << "Ошибка ID набора!";
    }

    return name;
}

void DatasetsModel::deleteDatasetCollect(const QString &name)
{
    int id = getDataset(name);

    if(id == -1)
    {
        qDebug() << "Ошибка датасета!";
        return;
    }

    deleteDataset(id);
    deleteDatasetLabel(id);
}

QString DatasetsModel::getMeaning(int id)
{
    QString name;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings WHERE id = ?;").setVal(id).selectRows());
    QSqlRecord rec = query.record();
    if(query.next())
    {
        name = query.value(rec.indexOf("name")).toString();
    }

    if(name.isEmpty())
    {
        qDebug() << "Ошибка ID датасета!";
    }

    return name;
}

int DatasetsModel::getDataset(const QString &name)
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

void DatasetsModel::deleteDataset(int id)
{
    QString request_str = "DELETE FROM datasets WHERE id = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(id).del();
    if(!res)
    {
        qDebug() << "невозможно удалить метку " << Database::getInstance().lastError();
    }
}

void DatasetsModel::deleteDatasetLabel(int id)
{
    QString request_str = "DELETE FROM datasetLabels WHERE id_dataset = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(id).del();
    if(!res)
    {
        qDebug() << "невозможно удалить метку " << Database::getInstance().lastError();
    }
}

LabelData DatasetsModel::getLabel(int id, int count)
{
    LabelData label;
    QSqlQuery queryLabels(Database::getInstance().prepare("SELECT * FROM labels WHERE id = ?;").setVal(id).selectRows());
    QSqlRecord recLabels = queryLabels.record();
    while(queryLabels.next())
    {
        label.x = queryLabels.value(recLabels.indexOf("x")).toInt() + BORDER_WEIGHT;
        label.y = queryLabels.value(recLabels.indexOf("y")).toInt() + BORDER_WEIGHT;
        label.w = queryLabels.value(recLabels.indexOf("w")).toInt() - BORDER_WEIGHT;
        label.h = queryLabels.value(recLabels.indexOf("h")).toInt() - BORDER_WEIGHT;
        label.id_set = queryLabels.value(recLabels.indexOf("id_set")).toInt();
        label.frame = queryLabels.value(recLabels.indexOf("frame")).toInt();
        label.name = getMeaning(queryLabels.value(recLabels.indexOf("id_label")).toInt());
        label.count = count;
    }
    return label;
}

DatasetsModel::DatasetsModel(QObject *parent) : QObject(parent)
{
    m_tableModel = new QStandardItemModel(this);
    m_tableHeader.append("Название");
    m_tableHeader.append("Классов");
    m_tableHeader.append("Кадров");
    m_tableHeader.append("Дата создания");
    m_tableHeader.append("Описание");

    m_listModel = new QStandardItemModel(this);

    m_tableLabelsModel = new QStandardItemModel(this);
    m_tableLabelsHeader.append("Название");
    m_tableLabelsHeader.append("Меток всего");
    m_tableLabelsHeader.append("Выбрано");
}

QStandardItemModel *DatasetsModel::updateTableModel()
{
    m_tableModel->clear();
    m_tableModel->setHorizontalHeaderLabels(m_tableHeader);

    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM datasets;").selectRows());
    QSqlRecord rec = query.record();
    QStandardItem *item = nullptr;
    int count = 0;
    while(query.next())
    {
        item = new QStandardItem(query.value(rec.indexOf("name")).toString());
        m_tableModel->setItem(count, 0, item);

        item = new QStandardItem(QString::number(10));
        m_tableModel->setItem(count, 1, item);

        item = new QStandardItem(QString::number(20));
        m_tableModel->setItem(count, 2, item);

        item = new QStandardItem(query.value(rec.indexOf("date")).toString());
        m_tableModel->setItem(count, 3, item);

        item = new QStandardItem(query.value(rec.indexOf("description")).toString());
        m_tableModel->setItem(count, 4, item);

        count++;
    }
//    delete item; TO DO
    return  m_tableModel;
}

QStandardItemModel *DatasetsModel::updateListModel()
{
    m_listModel->clear();

    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM sets;").selectRows());
    QSqlRecord rec = query.record();
    QStandardItem *item = nullptr;
    int count = 0;
    while(query.next())
    {
        item = new QStandardItem(query.value(rec.indexOf("name")).toString());
        item->setCheckable(true);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);

        m_listModel->setItem(count, 0, item);

        count++;
    }

    return m_listModel;
}

QVariantMap DatasetsModel::updateInfoSets(const QString &name)
{
    QVariantMap map;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM sets WHERE name = ?;").setVal(name).selectRows());
    QSqlRecord rec = query.record();
    while(query.next())
    {
        map["name"] = query.value(rec.indexOf("name")).toString();
        map["description"] = query.value(rec.indexOf("description")).toString();
    }
    return map;
}

QStandardItemModel *DatasetsModel::updateTableLabels(const QString &name)
{
    QStringList setsList;
    QSqlQuery query0(Database::getInstance().prepare("SELECT name FROM sets;").selectRows());
    QSqlRecord rec0 = query0.record();
    while(query0.next())
    {
        setsList.append(query0.value(rec0.indexOf("name")).toString());
    }

    QVariantMap globalMap;
    foreach (QString key, setsList)
    {
        QVariantMap map;
        QSqlQuery query1(Database::getInstance().prepare("SELECT labels.label FROM sets INNER JOIN labels ON labels.id_set = sets.id WHERE sets.name = ?;").setVal(key).selectRows());
        QSqlRecord rec1 = query1.record();
        while(query1.next())
        {
            QString label = query1.value(rec1.indexOf("label")).toString();
            if(!map[label].isValid())
            {
                map[label] = 1;
            }
            else
            {
                map[label] = map[label].toInt() + 1;
            }
        }
        globalMap[key] = map;
    }

    foreach (QString key, globalMap.keys())
    {
        QStandardItemModel *model = new QStandardItemModel(this);
        qDebug() << key;
        QStandardItem *item = nullptr;
        int count = 0;
        QVariantMap map = globalMap[key].toMap();
        foreach (QString key, map.keys())
        {
            item = new QStandardItem(key);
            model->setItem(count, 0, item);

            item = new QStandardItem(QString::number(map[key].toInt()));
            model->setItem(count, 1, item);

            item = new QStandardItem(QString::number(map[key].toInt()));
            model->setItem(count, 2, item);
            count++;
        }
        m_hashModel.insert(key, model);
    }

    m_hashModel.value(name)->setHorizontalHeaderLabels(m_tableLabelsHeader);
    return m_hashModel.value(name);
}
