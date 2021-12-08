#ifndef LABELSBASEPRESENTER_H
#define LABELSBASEPRESENTER_H

#include <QObject>
#include "labelsbasemodel.h"
#include "ilabelsbase.h"

class LabelsBasePresenter : public QObject
{
    Q_OBJECT
private:
    ILabelsBase *m_view;
    LabelsBaseModel *m_model;
public:
    explicit LabelsBasePresenter(ILabelsBase *view, QObject *parent = nullptr);
    void updateModel();

signals:

public slots:
private slots:
    void acceptAddLabel();
    void deleteItem();
    void editItem();
};

#endif // LABELSBASEPRESENTER_H
