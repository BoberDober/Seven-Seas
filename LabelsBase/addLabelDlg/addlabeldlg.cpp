#include "addlabeldlg.h"
#include "ui_addlabeldlg.h"

#include <QMessageBox>
#include <QDebug>

QString AddLabelDlg::getOldName() const
{
    return m_oldName;
}

AddLabelDlg::AddLabelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLabelDlg)
{
    ui->setupUi(this);
    connect(this, SIGNAL(rejected()), this, SLOT(clearDlg()));
}

AddLabelDlg::~AddLabelDlg()
{
    delete ui;
}

void AddLabelDlg::on_addlabelBtn_clicked()
{
    QString name = ui->nameLabelLineEdit->text();
    QString description = ui->descriptionlabelLineEdit->text();
    if(name.isEmpty() || description.isEmpty())
    {
        QMessageBox msgBox(this);
        msgBox.setText("Не все поля заполнены!");
        msgBox.exec();
    }
    else
    {
        accept();
    }
}

void AddLabelDlg::on_cancelLabelBtn_clicked()
{
    this->close();
}

void AddLabelDlg::clearDlg()
{
    m_oldName.clear();
    ui->nameLabelLineEdit->clear();
    ui->descriptionlabelLineEdit->clear();
}

QString AddLabelDlg::getDescriptionLineEdit() const
{
    return ui->descriptionlabelLineEdit->text();
}

QString AddLabelDlg::getNameLineEdit() const
{
    return ui->nameLabelLineEdit->text();
}

void AddLabelDlg::openEdit(const QString &name, const QString &description)
{
    m_oldName = name;
    ui->nameLabelLineEdit->setText(name);
    ui->descriptionlabelLineEdit->setText(description);
    this->open();
}
