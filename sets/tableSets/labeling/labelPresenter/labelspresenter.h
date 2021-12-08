#ifndef LABELSPRESENTER_H
#define LABELSPRESENTER_H

#include <QObject>
#include "ilabelingplayerview.h"
#include "ilistlabelsview.h"
#include "labelsmodel.h"

class LabelsPresenter : public QObject
{
    Q_OBJECT
private:
    ILabelingplayerview *m_playerView;
    IListLabelsView *m_listView;
    LabelsModel *m_model;
    QString m_setName;

    double interpolateLagrangePolynomial(double x, double* x_values, double* y_values, int size);
    void sectionInterpolation(const QRectF &firstRect, const QRectF &secondRect, double first_value, double second_value, int parentFrame);
    int searchFirstBox(int id);
    void deleteBoxesChild(int id);
private slots:
    void updateModel(int frame);
    void editModel(bool keyFrame, int id, int parentId, QRectF rect);
    void createLabel(const QString &name, const QPoint &point);
    void acceptDelete(int id, int parentID);
    void frameClose(int id);
    void addLabel(const QPoint& point);
public:
    explicit LabelsPresenter(ILabelingplayerview *playerView, IListLabelsView *listView, QObject *parent = nullptr);
    void openLabeling(QString workFolder, QString setsName);
    void closeLabeling();
    void addKeyFrame(int id, int parentId, int frameIndex, const QRectF &rect);
signals:

public slots:
};

#endif // LABELSPRESENTER_H
