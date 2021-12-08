#ifndef ADDSETS_H
#define ADDSETS_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QMessageBox>
#include <QtConcurrent>
#include <QComboBox>

class CreateSetDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit *m_lineEditName;
    QComboBox *m_comboBoxVideo;
    QTextEdit *m_textEdit;
    QSpinBox *m_spinBoxQuality;

public:
    explicit CreateSetDialog(QWidget *parent = nullptr);
    QLineEdit *lineEditName() const;
    QLineEdit *lineEditPathImg() const;
    QLineEdit *lineEditPathAnnot() const;
    QTextEdit *textEdit() const;
    QSpinBox *spinBoxQuality() const;
    void openMessageBox(QString text);
    void setVideo(QStringList list);
    QComboBox *comboBoxVideo() const;

signals:
    void acceptCheck();
public slots:

private slots:
    void okBtnSlot();
    void clean();

};

#endif // ADDSETS_H
