#ifndef IDATASETS_H
#define IDATASETS_H

#include <QStandardItemModel>

class IDatasets
{
public:
    virtual void setModel(QStandardItemModel *model) = 0;
    virtual QModelIndex getCurrentIndexTable() = 0;
    virtual bool accessDelete(const QString& name) = 0;
    virtual void exportDlgOpen(const QString& name) = 0;
    virtual void openMessageBox(const QString& text) = 0;
    virtual bool questionBox(const QString& text) = 0;
};

#endif // IDATASETS_H
