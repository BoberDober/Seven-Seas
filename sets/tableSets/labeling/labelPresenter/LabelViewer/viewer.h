#ifndef VIEWER_H
#define VIEWER_H

#include <QFileInfoList>
#include <QWidget>
#include "graphicsview.h"

class Viewer : public QWidget
{
    Q_OBJECT
private:
    GraphicsView *m_graphicsView;
    QString m_pathImages;
    int m_currentFrame;
    QList<QString> m_listFile;
public:
    explicit Viewer(QWidget *parent = nullptr);
    void setImagePath(QString path);
    void drawFrame(int frame);
    void drawObject(int id, bool keyFrame, int parentFrame, const QString &text, const QRect &rect, const QColor &color);
    int currentFrame() const;
    void clearScene();

signals:
    void maximumSlider(int size);
    void setSlider(int value);
    void frameChanged(int frame);
    void editModel(bool, int, int, QRectF);
    void doubleClick(QPoint);
    void play_pause();

public slots:
    void prevFrame();
    void nextFrame();
    void setFrame(int frame);
};

#endif // VIEWER_H
