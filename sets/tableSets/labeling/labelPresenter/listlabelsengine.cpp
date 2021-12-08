#include "listlabelsengine.h"

#include <QDebug>

QList<QObject *> ListLabelsEngine::model() const
{
    return m_model;
}

ListLabelsEngine::ListLabelsEngine(QObject *parent) : QObject(parent)
{

}

void ListLabelsEngine::setModel(QList<QObject *> model)
{
    m_model = model;
    emit sendModel(model);
}

void ListLabelsEngine::deleteItem(int id, int parentID)
{
    emit itemDeleted(id, parentID);
}

void ListLabelsEngine::closedFrame(int id)
{
    emit itemClosed(id);
}
