#ifndef ILABELINGPLAYERVIEW_H
#define ILABELINGPLAYERVIEW_H

#include <QString>
#include <QObject>

class ILabelingplayerview
{
public:
    virtual void setImagePath(const QString &path) = 0;
    virtual void setModel(QList<QObject*> model)= 0;
    virtual int getCurrentFrame() = 0;
    virtual bool openQuestionBox() = 0;
};

#endif // ILABELINGPLAYERVIEW_H
