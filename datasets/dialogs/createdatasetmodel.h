#ifndef CREATEDATASETMODEL_H
#define CREATEDATASETMODEL_H

#include <QObject>
#include <QHash>
#include <QStandardItemModel>

struct SetInfoData {
    QString description;
    QStandardItemModel *setInfoModel;
};

struct CurrentSetInfo {
    QString name;
    int count;
};

struct DatasetInfo {
    QString name;
    QString dateTime;
    QString description;
};


class CreateDatasetModel : public QObject
{
    Q_OBJECT

private:
    QStandardItemModel *m_setsList;
    QHash<QString, SetInfoData> m_hash;
    QHash<QString, int> m_currentHash;
    QString getNameLabel(int id);
    int getIDSet(QString name);
    int getIDMeaning(QString name);
    void insertDatasetLabel(int id_dataset, int id_label);

public:
    explicit CreateDatasetModel(QObject *parent = nullptr);
    void updateModels();
    QStandardItemModel *getSetsList() const;

    SetInfoData getInfoData(QString name);

    QHash<QString, SetInfoData> getHash() const;
    void createDataset(DatasetInfo datasetInfo);
    void createDatasetlabels(QString setName, CurrentSetInfo setInfo, int datasetID);
    int getDatasetID(QString name);
    QHash<QString, int> updateCurrentHash();
signals:

public slots:
};

#endif // CREATEDATASETMODEL_H
