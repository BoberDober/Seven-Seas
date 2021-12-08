#ifndef EXPORTSETDIALOG_H
#define EXPORTSETDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QMessageBox>
#include <QtConcurrent>

class ExportSetDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *m_lineEditName;
    QLineEdit *m_lineEditPathImg;
    QLineEdit *m_lineEditPathAnnot;
    QTextEdit *m_textEdit;
    QSpinBox *m_spinBoxQuality;

    int countFileFolder();

public:
    explicit ExportSetDialog(QWidget *parent = nullptr);
    QLineEdit *lineEditName() const;
    QLineEdit *lineEditPathImg() const;
    QLineEdit *lineEditPathAnnot() const;
    QTextEdit *textEdit() const;
    QSpinBox *spinBoxQuality() const;
    void openMessageBox(QString text);
signals:
    void acceptCheck();
public slots:

private slots:
    void browserPathImgSlot();
    void browserPathAnnotSlot();
    void okBtnSlot();
    void clean();

};

#endif // EXPORTSETDIALOG_H
