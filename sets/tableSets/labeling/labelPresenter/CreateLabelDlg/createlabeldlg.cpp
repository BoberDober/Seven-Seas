#include "createlabeldlg.h"
#include "ui_createlabeldlg.h"
#include <QDebug>

CreateLabelDlg::CreateLabelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateLabelDlg)
{
    ui->setupUi(this);


    m_labelCmbBox = new QLineEdit;
//    ui->nameLabelsCmbBox->setDuplicatesEnabled(false);
//    ui->nameLabelsCmbBox->setEditable(true);
//    ui->nameLabelsCmbBox->setLineEdit(m_labelCmbBox);
    connect(this, SIGNAL(rejected()), this, SLOT(clearDlg()));
}

CreateLabelDlg::~CreateLabelDlg()
{
    delete m_labelCmbBox;
    delete ui;
}

void CreateLabelDlg::closeDialog()
{
    reject();
    close();
}

QString CreateLabelDlg::getNameComboBox()
{
    return ui->nameLabelsCmbBox->currentText();
}

void CreateLabelDlg::setModelComboBox(QStringList list)
{
    ui->nameLabelsCmbBox->addItems(list);
}

void CreateLabelDlg::openDialog()
{
    open();
}

void CreateLabelDlg::on_cancelBtn_clicked()
{
    emit closedDialog();
}

void CreateLabelDlg::on_createBtn_clicked()
{
    emit createLabel();
}

void CreateLabelDlg::clearDlg()
{
    ui->nameLabelsCmbBox->clear();
}
