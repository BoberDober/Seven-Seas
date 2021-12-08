#ifndef ADDLABELDLG_H
#define ADDLABELDLG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class AddLabelDlg;
}

class AddLabelDlg : public QDialog
{
    Q_OBJECT
    QString m_oldName;

public:
    explicit AddLabelDlg(QWidget *parent = nullptr);
    ~AddLabelDlg();

    QString getDescriptionLineEdit() const;
    QString getNameLineEdit() const;
    void openEdit(const QString& name, const QString &description);

    QString getOldName() const;

private slots:
    void on_addlabelBtn_clicked();

    void on_cancelLabelBtn_clicked();
    void clearDlg();

signals:
    void acceptDlg(QString, QString);

private:
    Ui::AddLabelDlg *ui;
};

#endif // ADDLABELDLG_H
