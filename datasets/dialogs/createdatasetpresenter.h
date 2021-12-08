#ifndef CREATEDATASETPRESENTER_H
#define CREATEDATASETPRESENTER_H

#include <QObject>
#include "createdatasetmodel.h"
#include "icreatedialog.h"

class CreateDatasetPresenter : public QObject
{
    Q_OBJECT
private:
    ICreateDialog *m_view;
    CreateDatasetModel *m_model;

    void forEach(QAbstractItemModel* model, QModelIndex parent, QString setName, int setID);

public:
    explicit CreateDatasetPresenter(ICreateDialog *view, QObject *parent = nullptr);
    void openDialog();
signals:
    void updateDatasetModel();
public slots:
private slots:
    void closeDialog();
    void updateSetInfo(const QModelIndex &index);
    void createDataset();
    void onEditModel();
};

#endif // CREATEDATASETPRESENTER_H
