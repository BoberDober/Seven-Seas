#include "listsets.h"
#include <QDebug>

ListSets::ListSets(QWidget *parent) : QListView(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
//    connect(poModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(setChanged(QStandardItem*)));

    connect(this, SIGNAL(activated(const QModelIndex &)), this, SLOT(setActivated(const QModelIndex &)));
}

void ListSets::setListModel(QStandardItemModel *model)
{
    setModel(model);
}

void ListSets::setChanged(QStandardItem *item)
{
    qDebug() << Q_FUNC_INFO << item;
    // Get current index from item
//    const QModelIndex oCurrentIndex

//    // Get list selection model
//    QItemSelectionModel *poSelModel =
//            m_poListView->selectionModel();

//    // Set selection
//    poSelModel->select(
//                QItemSelection(oCurrentIndex, oCurrentIndex),
//                QItemSelectionModel::Select | QItemSelectionModel::Current);
}

void ListSets::setActivated(const QModelIndex &index)
{
    emit setChanged(index);
}
