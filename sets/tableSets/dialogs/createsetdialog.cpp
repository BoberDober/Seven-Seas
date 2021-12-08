#include "createsetdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

QComboBox *CreateSetDialog::comboBoxVideo() const
{
    return m_comboBoxVideo;
}

CreateSetDialog::CreateSetDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Импортировать набор"));
    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *lblName = new QLabel("Название", this);
    gridLayout->addWidget(lblName, 0, 0);
    m_lineEditName = new QLineEdit(this);
    gridLayout->addWidget(m_lineEditName, 0, 1);

    QLabel *lblVideo = new QLabel("Выберите видео", this);
    gridLayout->addWidget(lblVideo, 1, 0);
    m_comboBoxVideo = new QComboBox(this);
    gridLayout->addWidget(m_comboBoxVideo, 1, 1);

    QLabel *lblQuality = new QLabel("Оценка качества", this);
    gridLayout->addWidget(lblQuality, 2, 0);
    m_spinBoxQuality = new QSpinBox(this);
    m_spinBoxQuality->setRange(0, 3);
    gridLayout->addWidget(m_spinBoxQuality, 2, 1);

    QLabel *lblDescription = new QLabel("Описание", this);
    gridLayout->addWidget(lblDescription, 3, 0);
    m_textEdit = new QTextEdit(this);
    gridLayout->addWidget(m_textEdit, 3, 1);

    QHBoxLayout *hBoxLayout = new QHBoxLayout();

    QPushButton *cancelBtn = new QPushButton("Отмена", this);
    QPushButton *okBtn = new QPushButton("Ок", this);
    hBoxLayout->addWidget(cancelBtn);
    hBoxLayout->addWidget(okBtn);
    gridLayout->addLayout(hBoxLayout, 4, 0, 1, 3);

    setLayout(gridLayout);

    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(okBtn, SIGNAL(clicked()), this, SLOT(okBtnSlot()));
    connect(this, SIGNAL(rejected()), this, SLOT(clean()));
}

void CreateSetDialog::okBtnSlot()
{
    if(m_lineEditName->text().isEmpty())
        openMessageBox("Не все поля заполнены!");
    else
    {
        emit acceptCheck();
    }
}

QLineEdit *CreateSetDialog::lineEditName() const
{
    return m_lineEditName;
}

QTextEdit *CreateSetDialog::textEdit() const
{
    return m_textEdit;
}

QSpinBox *CreateSetDialog::spinBoxQuality() const
{
    return m_spinBoxQuality;
}

void CreateSetDialog::openMessageBox(QString text)
{
    QMessageBox msgBox(this);
    msgBox.setText(text);
    msgBox.exec();
}

void CreateSetDialog::setVideo(QStringList list)
{
    m_comboBoxVideo->clear();
    m_comboBoxVideo->addItems(list);
}

void CreateSetDialog::clean()
{
    m_lineEditName->clear();
    m_textEdit->clear();
    m_spinBoxQuality->setValue(0);
}
