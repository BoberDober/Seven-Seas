#include "tabledatasets.h"
#include <QDebug>
#include <QMenu>
#include <QHeaderView>

TableDatasets::TableDatasets(QWidget *parent) : QTableView(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QTableView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(openContexMenu()));
}

void TableDatasets::sectionResize()
{
    resizeRowsToContents();
    resizeColumnsToContents();
    for (int c = 0; c < horizontalHeader()->count(); ++c)
    {
        horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}

void TableDatasets::openContexMenu()
{
    if(!currentIndex().isValid())
    {
        return;
    }

    QMenu *menu = new QMenu(this);
    QAction * moreDevice = new QAction("Подробнее", this);
    QAction * editDevice = new QAction("Редактировать", this);
    QAction * exportDevice = new QAction("Экспорт", this);
    QAction * deleteDevice = new QAction("Удалить", this);

    moreDevice->setEnabled(false);
    editDevice->setEnabled(false);

    connect(moreDevice, SIGNAL(triggered()), this, SIGNAL(moreDataset()));
    connect(editDevice, SIGNAL(triggered()), this, SIGNAL(editDataset()));
    connect(exportDevice, SIGNAL(triggered()), this, SIGNAL(exportDataset()));
    connect(deleteDevice, SIGNAL(triggered()), this, SIGNAL(deleteDataset()));
    connect(menu, SIGNAL(aboutToHide()), menu, SLOT(deleteLater()));

    menu->addAction(moreDevice);
    menu->addAction(editDevice);
    menu->addAction(exportDevice);
    menu->addAction(deleteDevice);
    menu->popup(QCursor::pos());
}
