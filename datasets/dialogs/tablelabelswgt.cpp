#include "tablelabelswgt.h"
#include <QHeaderView>
#include <QDebug>

TableLabelsWgt::TableLabelsWgt(QWidget *parent) :  QTableView(parent)
{

}

void TableLabelsWgt::setTableLabelModel(QStandardItemModel *model)
{
    setModel(model);
    sectionResize();
}

TableLabelsWgt::~TableLabelsWgt()
{

}

void TableLabelsWgt::sectionResize()
{
    resizeRowsToContents();
    resizeColumnsToContents();
    for (int c = 0; c < horizontalHeader()->count(); ++c)
    {
        horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
}
