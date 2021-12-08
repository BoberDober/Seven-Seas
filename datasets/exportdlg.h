#ifndef EXPORTDLG_H
#define EXPORTDLG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class ExportDlg;
}

class ExportDlg : public QDialog
{
    Q_OBJECT

signals:
    void exportDetector(QString, QString);
    void exportClassifier(QString, QString);

public:
    explicit ExportDlg(QWidget *parent = nullptr);
    void openDlg(const QString& name);
    ~ExportDlg();

private slots:
    void on_cancelBtn_clicked();
    void on_exportBtn_clicked();
    void on_pathDetectorBrowse_clicked();

    void on_pathClassifierBrowse_clicked();

private:
    Ui::ExportDlg *ui;
    QString m_name;
    void closeDlg();
};

#endif // EXPORTDLG_H
