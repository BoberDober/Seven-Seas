#ifndef TABLELABELSBASE_H
#define TABLELABELSBASE_H

#include <QTableView>

class TableLabelsBase : public QTableView
{
    Q_OBJECT

public:
    explicit TableLabelsBase(QWidget *parent = nullptr);
    void sectionResize();

private slots:
    void openContexMenu();
signals:
    void deletedItem();
    void editItem();
    void moreItem();
};

#endif // TABLELABELSBASE_H
