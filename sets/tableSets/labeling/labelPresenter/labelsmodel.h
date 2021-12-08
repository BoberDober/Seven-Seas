#ifndef LABELSMODEL_H
#define LABELSMODEL_H

#include <QObject>
#include "labelsitem.h"
#include <QList>
#include <QHash>

enum DeleteType {
    NEXT = 0,
    PREV
};

class LabelsModel : public QObject
{
    Q_OBJECT
private:
    QList<QObject*> m_list;
    QHash<int, QString> m_hashLabel;
    int getSetID(QString name);
public:
    explicit LabelsModel(QObject *parent = nullptr);
    ~LabelsModel();
    QList<QObject *> getList(const QString &setsName, int frame);
    void editLabel(QRectF rect, bool keyFrame, int parentFrame, int frame);
    void addFrameLabel(int parentFrame, int frame, const QRectF &rect, bool keyFrame);
    void editLabel(int id, QRectF rect, bool keyFrame, int parentFrame);
    void updateHashLabel();
    void createLabel(const QString &labelName, const QString &setName, int frame, const QPoint &point, bool keyFrame, int parentFrame, bool noFrame);
    void createLabel(int labelName, int setName, int frame, const QRectF &rect, bool keyFrame, int parentFrame, bool noFrame);
    void deleteLabel(int id);
    void closeFrame(int id);
    int getFrameFromID(int id);
    QRectF getBox(int id);
    bool boxIsExists(int id);
    int getMaxFrame(const QString &set_name, int parentFrame, int frame);
    int getIDMaxFrame(int parentFrame, int frame);

    int getIDChildKeyFrame(int id);
    int getIDParent(int _id);
    void deleteNotKeyFrame(const QString &set_name, int id, int frame, const DeleteType& deleteType);
    void deleteByParent(const QString &set_name, int parentID);
    void editParentFrame(int parentID, int id);
    void deleteFromParentFrame(int id);
    bool isImport(int id);
signals:

public slots:
};

#endif // LABELSMODEL_H
