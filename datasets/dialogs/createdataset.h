#ifndef CREATEDATASET_H
#define CREATEDATASET_H

#include <QDialog>
#include "listsets.h"
#include "setinfo.h"
#include "icreatedialog.h"
#include "createdatasetmodel.h"

namespace Ui {
class CreateDataset;
}

class CreateDataset : public QDialog, public ICreateDialog
{
    Q_OBJECT

public:
    explicit CreateDataset(QWidget *parent = nullptr);
    void setSetInfo(QString name, QString description);
    void setTableLableModel(QStandardItemModel *model);
    void closeDialog();
    QString getNameSet();
    QString getDescriptionSet();
    ~CreateDataset();

private:
    Ui::CreateDataset *ui;
    ListSets *m_list;
    SetInfo *m_setInfo;
signals:
    void updateSetInfo(const QModelIndex &index);
    void createDataset();
private slots:
    void on_createBtn_clicked();
    void on_closeBtn_clicked();
    void clearDlg();

    // ICreateDialog interface
public:
    void openDialog();

    // ICreateDialog interface
public:
    void setListSetsModel(QStandardItemModel *model);

    // ICreateDialog interface

    // ICreateDialog interface
public:
    void setCurrentModel(const QHash<QString, int>& hash);
};

#endif // CREATEDATASET_H
