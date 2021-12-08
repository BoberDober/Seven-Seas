#ifndef ILABELSBASE_H
#define ILABELSBASE_H

#include <QStandardItemModel>

class ILabelsBase
{
public:
    virtual void setModel(QStandardItemModel *model) = 0;
    virtual void setReziseToContent() = 0;
    virtual QString getNameAddMeaning() = 0;
    virtual QString getDescriptionAddMeaning() = 0;
    virtual QString getOldName() = 0;
    virtual QModelIndex getCurrentIndexTable() = 0;
    virtual bool getQuestionBox(QString name) = 0;
    virtual void addAccept() = 0;
    virtual void editLabel(const QString& name, const QString& description) = 0;
    virtual void viewMessageBox(const QString& message) = 0;
};

#endif // ILABELSBASE_H
