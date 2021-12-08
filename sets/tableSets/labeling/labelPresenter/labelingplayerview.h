#ifndef LABELINGPLAYERVIEW_H
#define LABELINGPLAYERVIEW_H

#include <QWidget>
#include <QTimer>
#include "ilabelingplayerview.h"
#include "LabelViewer/viewer.h"
#include "labelsitem.h"

namespace Ui {
class LabelingPlayerView;
}

class LabelingPlayerView : public QWidget, public ILabelingplayerview
{
    Q_OBJECT

public:
    explicit LabelingPlayerView(QWidget *parent = nullptr);
    ~LabelingPlayerView();

private slots:
    void on_prevBtn_clicked();
    void on_mainBtn_clicked();
    void on_nextBtn_clicked();

    void setMaxValueSlider(int maxValue);
    void setValueSlider(int value);

    void on_frameSlider_sliderMoved(int position);

private:
    Ui::LabelingPlayerView *ui;
    Viewer *m_viewer;
    QTimer *m_timer;
    bool m_player;

public slots:
    void player();

signals:
    void frameChanged(int frame);
    void editModel(bool, int, int, QRectF);
    void acceptDelete();
    void addLabel(QPoint);
    // ILabelingplayerview interface
public:
    void setImagePath(const QString &path);

    // ILabelingplayerview interface
public:
    void setModel(QList<QObject *> model);
    int getCurrentFrame();


    // ILabelingplayerview interface
public:
    bool openQuestionBox();

};

#endif // LABELINGPLAYERVIEW_H
