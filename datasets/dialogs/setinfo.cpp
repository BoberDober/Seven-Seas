#include "setinfo.h"
#include "ui_setinfo.h"
#include <QDebug>
#include <QLineEdit>

SetInfo::SetInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetInfo)
{
    ui->setupUi(this);
    m_tableLabelsWgt = new TableLabelsWgt(this);
    QVBoxLayout *tableLabelsLayout = new QVBoxLayout();
    tableLabelsLayout->addWidget(m_tableLabelsWgt);
    ui->tableLabelWgt->setLayout(tableLabelsLayout);
}

void SetInfo::setInfo(QString name, QString description)
{
    qDebug() << Q_FUNC_INFO;
    ui->nameLbl->setText(name);
    ui->descriptionLbl->setText(description);
}

void SetInfo::setTableLableModel(QStandardItemModel *model)
{
    m_tableLabelsWgt->setTableLabelModel(model);
}

SetInfo::~SetInfo()
{
    delete ui;
}
