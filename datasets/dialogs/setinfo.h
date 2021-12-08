#ifndef SETINFO_H
#define SETINFO_H

#include <QStandardItemModel>
#include <QWidget>
#include "tablelabelswgt.h"

namespace Ui {
class SetInfo;
}

class SetInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SetInfo(QWidget *parent = nullptr);
    void setInfo(QString name, QString description);
    void setTableLableModel(QStandardItemModel *model);

    ~SetInfo();

private:
    Ui::SetInfo *ui;
    TableLabelsWgt *m_tableLabelsWgt;
};

#endif // SETINFO_H
