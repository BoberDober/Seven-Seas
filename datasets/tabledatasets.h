#ifndef TABLEDATASETS_H
#define TABLEDATASETS_H

#include <QTableView>

class TableDatasets : public QTableView
{
    Q_OBJECT
public:
    explicit TableDatasets(QWidget *parent = nullptr);
    void sectionResize();

signals:
    void exportDataset();
    void deleteDataset();
    void moreDataset();
    void editDataset();
private slots:
    void openContexMenu();
};

#endif // TABLEDATASETS_H
