#ifndef ICREATEDIALOG_H
#define ICREATEDIALOG_H

#include "createdatasetmodel.h"

class ICreateDialog
{
public:
    virtual void openDialog() = 0;
    virtual void setListSetsModel(QStandardItemModel *model) = 0;
    virtual void setSetInfo(QString name, QString description) = 0;
    virtual void setTableLableModel(QStandardItemModel *model) = 0;
    virtual QString getNameSet() = 0;
    virtual QString getDescriptionSet() = 0;
    virtual void closeDialog() = 0;
    virtual void setCurrentModel(const QHash<QString, int>& hash) = 0;
};

#endif // ICREATEDIALOG_H

