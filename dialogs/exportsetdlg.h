#ifndef EXPORTSETDLG_H
#define EXPORTSETDLG_H

#include <QDialog>

namespace Ui {
class ExportSetDlg;
}

class ExportSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ExportSetDlg(QWidget *parent = 0);
    ~ExportSetDlg();

private:
    Ui::ExportSetDlg *ui;
};

#endif // EXPORTSETDLG_H
