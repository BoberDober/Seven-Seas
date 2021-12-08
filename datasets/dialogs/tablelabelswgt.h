#ifndef TABLELABELSWGT_H
#define TABLELABELSWGT_H

#include <QStandardItemModel>
#include <QTableWidget>

class TableLabelsWgt : public QTableView
{
    Q_OBJECT

public:
    explicit TableLabelsWgt(QWidget *parent = nullptr);
    void setTableLabelModel(QStandardItemModel *model);
    ~TableLabelsWgt();
    void sectionResize();
private:
};

#endif // TABLELABELSWGT_H
