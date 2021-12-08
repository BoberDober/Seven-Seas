#ifndef CREATELABELDLG_H
#define CREATELABELDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include "icreatelabeldlg.h"

namespace Ui {
class CreateLabelDlg;
}

class CreateLabelDlg : public QDialog, public ICreateLabelDlg
{
    Q_OBJECT

public:
    explicit CreateLabelDlg(QWidget *parent = nullptr);
    void setModelComboBox(QStringList list);
    void openDialog();
    ~CreateLabelDlg();

private slots:
    void on_cancelBtn_clicked();
    void on_createBtn_clicked();
    void clearDlg();

signals:
    void closedDialog();
    void createLabel();
private:
    Ui::CreateLabelDlg *ui;
    QLineEdit *m_labelCmbBox;

    // ICreateLabelDlg interface
public:
    void closeDialog();

    // ICreateLabelDlg interface
public:
    QString getNameComboBox();
};

#endif // CREATELABELDLG_H
