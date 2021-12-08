#ifndef LABELSBASEMODEL_H
#define LABELSBASEMODEL_H

#include <QStandardItemModel>

class LabelsBaseModel : public QStandardItemModel
{
    Q_OBJECT
private:
    int getCountMeanings(int id);
    void insertMeaning(const QString& name, const QString& description);
    int getIDMeaning(const QString& name) const;
    void updateMeaning(const QString& name, const QString& description, const QString& oldName);
    void replaceMeaningLabels(int oldID, int ID);
    void deleteMeaning(const QString& name);
    bool checkMeaningUsed(int id);
    void updateMeaningDescription(int id, const QString& name);
public:
    explicit LabelsBaseModel(QObject *parent = nullptr);
    void updateModel();
    bool addMeaning(const QString &oldName, const QString &name, const QString &description);
    bool checkDeleteMeaning(const QString& name);
signals:

public slots:
};

#endif // LABELSBASEMODEL_H
