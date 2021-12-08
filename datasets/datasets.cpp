#include "datasets.h"
#include "ui_datasets.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

Datasets::Datasets(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Datasets)
{
    ui->setupUi(this);

    m_createDataset = new CreateDataset(this);
    m_createDatasetPresenter = new CreateDatasetPresenter(m_createDataset, this);

    m_table = new TableDatasets(this);
    QVBoxLayout *tableLayout = new QVBoxLayout();
    tableLayout->addWidget(m_table);
    ui->tableDatasetsWgt->setLayout(tableLayout);

    m_exportDlg = new ExportDlg(this);

    QObject *obj = dynamic_cast<QObject*>(m_createDatasetPresenter);
    QObject::connect(obj, SIGNAL(updateDatasetModel()), this, SIGNAL(updateDatasetModel()));

    connect(m_table, SIGNAL(exportDataset()), this, SIGNAL(exportDataset()));
    connect(m_table, SIGNAL(deleteDataset()), this, SIGNAL(deleteDataset()));
    connect(m_exportDlg, SIGNAL(exportDetector(QString, QString)), this, SIGNAL(exportDetector(QString, QString)));
    connect(m_exportDlg, SIGNAL(exportClassifier(QString, QString)), this, SIGNAL(exportClassifier(QString, QString)));

}



Datasets::~Datasets()
{
    delete ui;
}

void Datasets::setModel(QStandardItemModel *model)
{
    m_table->setModel(model);
    m_table->sectionResize();
}

void Datasets::on_addBtn_clicked()
{
    m_createDatasetPresenter->openDialog();
}

QModelIndex Datasets::getCurrentIndexTable()
{
    return m_table->currentIndex();
}

bool Datasets::accessDelete(const QString &name)
{
    QMessageBox::StandardButton reply;
    QString question_str = "Вы действительно хотите удалить датасет " + name + "?";
    reply = QMessageBox::question(this, "Подтведите", question_str, QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
      return true;
    }
    else
    {
      return false;
    }
}

void Datasets::exportDlgOpen(const QString &name)
{
    m_exportDlg->openDlg(name);
}

void Datasets::openMessageBox(const QString &text)
{
    QMessageBox msgBox(this);
    msgBox.setText(text);
    msgBox.exec();
}

bool Datasets::questionBox(const QString &text)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Подтведите", text, QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
      return true;
    }
    else
    {
      return false;
    }
}
