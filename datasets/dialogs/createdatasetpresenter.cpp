#include "createdatasetpresenter.h"
#include <QDebug>
#include <QTime>

CreateDatasetPresenter::CreateDatasetPresenter(ICreateDialog *view, QObject *parent) : QObject(parent)
{
    m_view = view;
    m_model = new CreateDatasetModel(this);

    QObject *obj = dynamic_cast<QObject*>(m_view);
    QObject::connect(obj, SIGNAL(rejected()), this, SLOT(closeDialog()));
    QObject::connect(obj, SIGNAL(updateSetInfo(QModelIndex)), this, SLOT(updateSetInfo(QModelIndex)));
    QObject::connect(obj, SIGNAL(createDataset()), this, SLOT(createDataset()));
}

void CreateDatasetPresenter::openDialog()
{
    m_model->updateModels();
    m_view->setCurrentModel(m_model->updateCurrentHash());
    m_view->setListSetsModel(m_model->getSetsList());
    m_view->openDialog();
}

void CreateDatasetPresenter::closeDialog()
{
//    m_model->clearModel();
}

void CreateDatasetPresenter::updateSetInfo(const QModelIndex &index)
{
    qDebug() << Q_FUNC_INFO;
    QStandardItem *item = m_model->getSetsList()->itemFromIndex(index);
    if(!item)
    {
        qDebug() << "пустая модель";
        return;
    }
    QString setName = item->text();
    SetInfoData data = m_model->getInfoData(setName);
    connect(data.setInfoModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(onEditModel()));
    m_view->setSetInfo(setName, data.description);
    m_view->setTableLableModel(data.setInfoModel);
}

void CreateDatasetPresenter::createDataset()
{
    QModelIndex parent = QModelIndex();

    DatasetInfo datasetInfo;
    datasetInfo.name = m_view->getNameSet();
    datasetInfo.dateTime = QDateTime::currentDateTime().toString("dd MMMM yyyy HH:mm");
    datasetInfo.description = m_view->getDescriptionSet();

    m_model->createDataset(datasetInfo);

    int datasetID = m_model->getDatasetID(datasetInfo.name);

    if(datasetID == -1)
    {
        qDebug() << "Ошибка ID датасета!";
        return;
    }

    foreach (QString key, m_model->getHash().keys())
    {
        forEach(m_model->getHash().value(key).setInfoModel, parent, key, datasetID);
    }
    m_view->closeDialog();
    emit updateDatasetModel();
}

void CreateDatasetPresenter::onEditModel()
{
    m_view->setCurrentModel(m_model->updateCurrentHash());
}

void CreateDatasetPresenter::forEach(QAbstractItemModel* model, QModelIndex parent, QString setName, int datasetID)
{
    for(int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex indexName = model->index(r, 0, parent);
        QModelIndex indexCount = model->index(r, 2, parent);

        CurrentSetInfo setInfo;
        setInfo.name = model->data(indexName).toString();
        setInfo.count = model->data(indexCount).toInt();
        qDebug() << setInfo.name << setInfo.count;
        m_model->createDatasetlabels(setName, setInfo, datasetID);

        if(model->hasChildren(indexName) ) {
            forEach(model, indexName, setName, datasetID);
        }
    }
}
