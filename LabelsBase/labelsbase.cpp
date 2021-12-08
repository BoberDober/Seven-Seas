#include "labelsbase.h"
#include "ui_labelsbase.h"
#include <QDebug>
#include <QMessageBox>

LabelsBase::LabelsBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelsBase)
{
    ui->setupUi(this);

    m_table = new TableLabelsBase(this);
    QVBoxLayout *tableLayout = new QVBoxLayout();
    tableLayout->addWidget(m_table);
    ui->tableLabelsBaseWgt->setLayout(tableLayout);

    m_addlabelDlg = new AddLabelDlg(this);
    connect(m_addlabelDlg, SIGNAL(accepted()), this, SIGNAL(acceptAddDlg()));
    connect(m_table, SIGNAL(deletedItem()), this, SIGNAL(deleteItem()));
    connect(m_table, SIGNAL(editItem()), this, SIGNAL(editItem()));
}

LabelsBase::~LabelsBase()
{
    delete ui;
}

void LabelsBase::setModel(QStandardItemModel *model)
{
    m_table->setModel(model);
    setReziseToContent();
}

void LabelsBase::on_addBtn_clicked()
{
    m_addlabelDlg->open();
}

QString LabelsBase::getNameAddMeaning()
{
    return m_addlabelDlg->getNameLineEdit();
}

QString LabelsBase::getDescriptionAddMeaning()
{
    return m_addlabelDlg->getDescriptionLineEdit();
}

void LabelsBase::setReziseToContent()
{
    m_table->sectionResize();
}

QModelIndex LabelsBase::getCurrentIndexTable()
{
    return m_table->currentIndex();
}

bool LabelsBase::getQuestionBox(QString name)
{
    QMessageBox::StandardButton reply;
    QString question_str = "Вы действительно хотите удалить метку " + name + "?";
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

void LabelsBase::addAccept()
{
    m_addlabelDlg->reject();
    m_addlabelDlg->close();
}

void LabelsBase::editLabel(const QString &name, const QString &description)
{
    m_addlabelDlg->openEdit(name, description);
}

QString LabelsBase::getOldName()
{
    return m_addlabelDlg->getOldName();
}

void LabelsBase::viewMessageBox(const QString& message)
{
    QMessageBox msgBox(this);
    msgBox.setText(message);
    msgBox.exec();
}
