#include "mainpathdialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include "../mainsettings.h"

MainPathDialog::MainPathDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Импортировать набор"));
    QGridLayout *gridLayout = new QGridLayout(this);

    QLabel *lblWorkFolder = new QLabel("Рабочий каталог", this);
    gridLayout->addWidget(lblWorkFolder, 0, 0);
    m_lineEditWorkFolder = new QLineEdit(this);
    m_lineEditWorkFolder->setText(MainSettings::getInstance().getWorkFolder());
    gridLayout->addWidget(m_lineEditWorkFolder, 0, 1);
    QPushButton *browserWorkFolder = new QPushButton("Обзор", this);
    gridLayout->addWidget(browserWorkFolder, 0, 2);

    QHBoxLayout *hBoxLayout = new QHBoxLayout();

    QPushButton *cancelBtn = new QPushButton("Отмена", this);
    QPushButton *okBtn = new QPushButton("Ок", this);
    hBoxLayout->addWidget(cancelBtn);
    hBoxLayout->addWidget(okBtn);
    gridLayout->addLayout(hBoxLayout, 1, 0, 1, 3);

    setLayout(gridLayout);

    connect(browserWorkFolder, SIGNAL(clicked()), this, SLOT(browserWorkFolderSlot()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(this, SIGNAL(accepted()), this, SLOT(okSlot()));
}

void MainPathDialog::browserWorkFolderSlot()
{
    QString folderName = QFileDialog::getExistingDirectory(this, tr("Выберите папку аннотаций"),
                                                     "/media/hdd/vatic/", QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    m_lineEditWorkFolder->setText(folderName);
}

void MainPathDialog::okSlot()
{
    MainSettings::getInstance().setWorkFolder(m_lineEditWorkFolder->text());
}
