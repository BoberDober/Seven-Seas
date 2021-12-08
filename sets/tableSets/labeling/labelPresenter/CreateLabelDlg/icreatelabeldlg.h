#ifndef ICREATELABELDLG_H
#define ICREATELABELDLG_H

#include <QStringList>

class ICreateLabelDlg {
public:
    virtual void openDialog() = 0;
    virtual void closeDialog() = 0;
    virtual void setModelComboBox(QStringList list) = 0;
    virtual QString getNameComboBox() = 0;
};

#endif // ICREATELABELDLG_H
