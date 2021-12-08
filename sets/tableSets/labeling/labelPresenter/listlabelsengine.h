#ifndef LISTLABELSENGINE_H
#define LISTLABELSENGINE_H

#include <QObject>
#include "labelsitem.h"

class ListLabelsEngine : public QObject
{
    Q_OBJECT
private:
    QList<QObject *> m_model;
public:
    explicit ListLabelsEngine(QObject *parent = nullptr);
    void setModel(QList<QObject *> model);
    QList<QObject *> model() const;

public slots:
    void deleteItem(int id, int parentID);
    void closedFrame(int id);
signals:
    void sendModel(QList<QObject*> model);
    void itemDeleted(int, int);
    void itemClosed(int);
public slots:
};

#endif // LISTLABELSENGINE_H
