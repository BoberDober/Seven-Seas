#ifndef LISTSETS_H
#define LISTSETS_H

#include <QListView>
#include <QStandardItemModel>

class ListSets : public QListView
{
    Q_OBJECT
public:
    explicit ListSets(QWidget *parent = nullptr);
    void setListModel(QStandardItemModel *model);

signals:
    void setChanged(const QModelIndex &index);
public slots:

private slots:
    void setChanged(QStandardItem* item);
    void setActivated(const QModelIndex &index);
};

#endif // LISTSETS_H
