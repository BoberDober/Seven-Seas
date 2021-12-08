#ifndef DATASETS_H
#define DATASETS_H

#include <QWidget>
#include "idatasets.h"
#include "tabledatasets.h"
#include "dialogs/createdataset.h"
#include "dialogs/createdatasetpresenter.h"
#include "exportdlg.h"

namespace Ui {
class Datasets;
}

class Datasets : public QWidget, public IDatasets
{
    Q_OBJECT

public:
    explicit Datasets(QWidget *parent = nullptr);
    ~Datasets();

private:
    Ui::Datasets *ui;
    TableDatasets *m_table;
    CreateDataset *m_createDataset;
    CreateDatasetPresenter *m_createDatasetPresenter;
    ExportDlg *m_exportDlg;
    // IDatasets interface

public:
    void setModel(QStandardItemModel *model);
private slots:
    void on_addBtn_clicked();

signals:
    void openCreateDataset();
    void createDataset_setChanged(const QModelIndex &index);
    void updateDatasetModel();
    void exportDataset();
    void deleteDataset();
    void exportDetector(QString, QString);
    void exportClassifier(QString, QString);

    // IDatasets interface
public:
    QModelIndex getCurrentIndexTable();

    // IDatasets interface
public:
    bool accessDelete(const QString &name);

    // IDatasets interface
public:
    void exportDlgOpen(const QString &name);

    // IDatasets interface
public:
    void openMessageBox(const QString &text);

    // IDatasets interface
public:
    bool questionBox(const QString &text);
};

#endif // DATASETS_H
