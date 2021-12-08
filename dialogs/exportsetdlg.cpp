#include "exportsetdlg.h"
#include "ui_exportsetdlg.h"

ExportSetDlg::ExportSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportSetDlg)
{
    ui->setupUi(this);
}

ExportSetDlg::~ExportSetDlg()
{
    delete ui;
}
