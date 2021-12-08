#include "exportdlg.h"
#include "ui_exportdlg.h"

#include <QFileDialog>
#include <QMessageBox>

ExportDlg::ExportDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDlg)
{
    ui->setupUi(this);
}

void ExportDlg::openDlg(const QString &name)
{
    m_name = name;
    QDialog::open();
}

ExportDlg::~ExportDlg()
{
    delete ui;
}

void ExportDlg::on_cancelBtn_clicked()
{
    closeDlg();
}

void ExportDlg::on_exportBtn_clicked()
{
    int typeExport = ui->tabWidget->currentIndex();
    switch (typeExport)
    {
    case 0:
        emit exportDetector(ui->pathDetectorLE->text(), m_name);
        break;
    case 1:
        emit exportClassifier(ui->pathClassifierLE->text(), m_name);
        break;
    default:
        qDebug() << "unknow type";
    }
    closeDlg();
}

void ExportDlg::closeDlg()
{
    m_name.clear();
    ui->pathDetectorLE->clear();
    QDialog::close();
}

void ExportDlg::on_pathDetectorBrowse_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Выберите папку для экспорта детектора"),
        QDir::homePath(), QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
    ui->pathDetectorLE->setText(path);
}

void ExportDlg::on_pathClassifierBrowse_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Выберите папку для экспорта классификатора"),
        QDir::homePath(), QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
    ui->pathClassifierLE->setText(path);
}
