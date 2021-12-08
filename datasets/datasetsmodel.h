#ifndef DATASETSMODEL_H
#define DATASETSMODEL_H

#include <QStandardItemModel>
#include <QHash>

struct LabelData {
    int x;
    int y;
    int w;
    int h;
    int id_set;
    QString name;
    int frame;
    int count;
};

class DatasetsModel : public QObject
{
    Q_OBJECT
private:
    QStandardItemModel *m_tableModel;
    QStandardItemModel *m_listModel;
    QStringList m_tableHeader;
    QStandardItemModel *m_tableLabelsModel;
    QStringList m_tableLabelsHeader;

    QString getMeaning(int id);
    int getDataset(const QString& name);

    void deleteDataset(int id);
    void deleteDatasetLabel(int id);

public:
    explicit DatasetsModel(QObject *parent = nullptr);
    QStandardItemModel *updateTableModel();
    QStandardItemModel *updateListModel();
    QVariantMap updateInfoSets(const QString &name);
    QStandardItemModel *updateTableLabels(const QString &name);
    QStandardItemModel *listModel() const;

    QStandardItemModel *tableLabelsModel() const;
    QHash<QString, QStandardItemModel*> m_hashModel;

    QHash<QString, QStandardItemModel *> hashModel() const;

    QStandardItemModel *tableModel() const;

    QVector<int> getListID(const QString &name);
    QString getSetName(int id);

    void deleteDatasetCollect(const QString& name);
    LabelData getLabel(int id, int count);
signals:

    void exportData(LabelData, QString);
public slots:
};

#endif // DATASETSMODEL_H
