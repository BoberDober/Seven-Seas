#include "tablelabelsbase.h"
#include <QDebug>
#include <QMenu>
#include <QHeaderView>

TableLabelsBase::TableLabelsBase(QWidget *parent) : QTableView(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QTableView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContexMenu()));
}

void TableLabelsBase::sectionResize()
{
    resizeRowsToContents();
    resizeColumnsToContents();
    for (int c = 0; c < horizontalHeader()->count(); ++c)
    {
        horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

void TableLabelsBase::openContexMenu()
{
    if(!currentIndex().isValid())
    {
        return;
    }

    QMenu *menu = new QMenu(this);
    QAction * moreDevice = new QAction("Подробнее", this);
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    moreDevice->setEnabled(false);

    connect(moreDevice, SIGNAL(triggered()), this, SIGNAL(moreItem()));
    connect(editDevice, SIGNAL(triggered()), this, SIGNAL(editItem()));
    connect(deleteDevice, SIGNAL(triggered()), this, SIGNAL(deletedItem()));
    connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));

    menu->addAction(moreDevice);
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);
    menu->popup(QCursor::pos());
}
