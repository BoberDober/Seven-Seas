#include "createdataset.h"
#include "ui_createdataset.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>

CreateDataset::CreateDataset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDataset)
{
    ui->setupUi(this);

    m_list = new ListSets(this);
    QVBoxLayout *listLayout = new QVBoxLayout();
    listLayout->addWidget(m_list);
    ui->listSetsWgt->setLayout(listLayout);

    m_setInfo = new SetInfo(this);
    QVBoxLayout *setInfoLayout = new QVBoxLayout();
    setInfoLayout->addWidget(m_setInfo);
    ui->setInfo->setLayout(setInfoLayout);
    connect(m_list, SIGNAL(setChanged(QModelIndex)), this, SIGNAL(updateSetInfo(QModelIndex)));
    connect(this, SIGNAL(rejected()), this, SLOT(clearDlg()));
//    m_TableHeader <<"#"<<"Name"<<"Text";
    QStringList tableHeader;
    tableHeader << "Название" << "Количество";
    ui->currentTable->setColumnCount(2);
    ui->currentTable->setHorizontalHeaderLabels(tableHeader);
}

void CreateDataset::setSetInfo(QString name, QString description)
{
    m_setInfo->setInfo(name, description);
}

void CreateDataset::setTableLableModel(QStandardItemModel *model)
{
    m_setInfo->setTableLableModel(model);
}

QString CreateDataset::getNameSet()
{
    return ui->nameLineEdit->text();
}

QString CreateDataset::getDescriptionSet()
{
    return ui->descriptionLineEdit->text();
}

CreateDataset::~CreateDataset()
{
    delete ui;
}
void CreateDataset::on_createBtn_clicked()
{
    QString name = ui->nameLineEdit->text();
    if(name.isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setText("Введите название!");
        msgBox.exec();
    }
    else
    {
        emit createDataset();
    }
}

void CreateDataset::closeDialog()
{
    reject();
    close();
}

void CreateDataset::on_closeBtn_clicked()
{
    closeDialog();
}

void CreateDataset::clearDlg()
{
    ui->nameLineEdit->clear();
    ui->descriptionLineEdit->clear();
}

void CreateDataset::openDialog()
{
    open();
}

void CreateDataset::setListSetsModel(QStandardItemModel *model)
{
    m_list->setListModel(model);
}

void CreateDataset::setCurrentModel(const QHash<QString, int> &hash)
{
    ui->currentTable->setRowCount(hash.size());
    int row = 0;
    foreach(QString key, hash.keys())
    {
        ui->currentTable->setItem(row,0, new QTableWidgetItem(key));
        ui->currentTable->setItem(row,1, new QTableWidgetItem(QString::number(hash.value(key))));
        row++;
    }

    ui->currentTable->resizeRowsToContents();
    ui->currentTable->resizeColumnsToContents();
    for (int c = 0; c < ui->currentTable->horizontalHeader()->count(); ++c)
    {
        ui->currentTable->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}
