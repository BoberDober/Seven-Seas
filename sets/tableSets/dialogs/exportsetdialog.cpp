#include "exportsetdialog.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

ExportSetDialog::ExportSetDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Импортировать набор"));
    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *lblName = new QLabel("Название", this);
    gridLayout->addWidget(lblName, 0, 0);
    m_lineEditName = new QLineEdit(this);
    gridLayout->addWidget(m_lineEditName, 0, 1);

    QLabel *lblPathImg = new QLabel("Путь изображений", this);
    gridLayout->addWidget(lblPathImg, 1, 0);
    m_lineEditPathImg = new QLineEdit(this);
    gridLayout->addWidget(m_lineEditPathImg, 1, 1);
    QPushButton *browserPathImg = new QPushButton("Обзор", this);
    gridLayout->addWidget(browserPathImg, 1, 2);

    QLabel *lblPathAnnot = new QLabel("Путь аннотаций", this);
    gridLayout->addWidget(lblPathAnnot, 2, 0);
    m_lineEditPathAnnot = new QLineEdit(this);
    gridLayout->addWidget(m_lineEditPathAnnot, 2, 1);
    QPushButton *browserPathAnnot = new QPushButton("Обзор", this);
    gridLayout->addWidget(browserPathAnnot, 2, 2);

    QLabel *lblQuality = new QLabel("Оценка качества", this);
    gridLayout->addWidget(lblQuality, 3, 0);
    m_spinBoxQuality = new QSpinBox(this);
    m_spinBoxQuality->setRange(0, 3);
    gridLayout->addWidget(m_spinBoxQuality, 3, 1);

    QLabel *lblDescription = new QLabel("Описание", this);
    gridLayout->addWidget(lblDescription, 4, 0);
    m_textEdit = new QTextEdit(this);
    gridLayout->addWidget(m_textEdit, 4, 1);


    QHBoxLayout *hBoxLayout = new QHBoxLayout();

    QPushButton *cancelBtn = new QPushButton("Отмена", this);
    QPushButton *okBtn = new QPushButton("Ок", this);
    hBoxLayout->addWidget(cancelBtn);
    hBoxLayout->addWidget(okBtn);
    gridLayout->addLayout(hBoxLayout, 5, 0, 1, 3);

    setLayout(gridLayout);

    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(okBtn, SIGNAL(clicked()), this, SLOT(okBtnSlot()));

    connect(browserPathImg, SIGNAL(clicked()), this, SLOT(browserPathImgSlot()));
    connect(browserPathAnnot, SIGNAL(clicked()), this, SLOT(browserPathAnnotSlot()));
    connect(this, SIGNAL(rejected()), this, SLOT(clean()));
}

void ExportSetDialog::browserPathImgSlot()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Выберите папку изображений"),
                                                 QDir::homePath(), QFileDialog::ShowDirsOnly
                                          | QFileDialog::DontResolveSymlinks);
    m_lineEditPathImg->setText(folderName);
}

void ExportSetDialog::browserPathAnnotSlot()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Выберите папку аннотаций"),
                                                     QDir::homePath(), QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    m_lineEditPathAnnot->setText(folderName);
}

void ExportSetDialog::okBtnSlot()
{
    if(m_lineEditName->text().isEmpty() || m_lineEditPathImg->text().isEmpty() || m_lineEditPathAnnot->text().isEmpty())
        openMessageBox("Не все поля заполнены!");
    else
    {
        emit acceptCheck();
    }
}

QLineEdit *ExportSetDialog::lineEditName() const
{
    return m_lineEditName;
}

QLineEdit *ExportSetDialog::lineEditPathImg() const
{
    return m_lineEditPathImg;
}

QLineEdit *ExportSetDialog::lineEditPathAnnot() const
{
    return m_lineEditPathAnnot;
}

QTextEdit *ExportSetDialog::textEdit() const
{
    return m_textEdit;
}

QSpinBox *ExportSetDialog::spinBoxQuality() const
{
    return m_spinBoxQuality;
}

void ExportSetDialog::openMessageBox(QString text)
{
    QMessageBox msgBox(this);
    msgBox.setText(text);
    msgBox.exec();
}

void ExportSetDialog::clean()
{
    m_lineEditName->clear();
    m_lineEditPathImg->clear();
    m_lineEditPathAnnot->clear();
    m_textEdit->clear();
    m_spinBoxQuality->setValue(0);
}
