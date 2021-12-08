#ifndef MAINPATHDIALOG_H
#define MAINPATHDIALOG_H

#include <QDialog>
#include <QLineEdit>

class MainPathDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *m_lineEditWorkFolder;
public:
    explicit MainPathDialog(QWidget *parent = nullptr);

signals:

public slots:

private slots:
    void browserWorkFolderSlot();
    void okSlot();
};

#endif // MAINPATHDIALOG_H
