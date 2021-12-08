#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "rectitem.h"

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
    QSize m_size;
public:
    explicit GraphicsView(QWidget *parent = nullptr);
    void setSize(const QSize size);
    void setFrame(const QPixmap& pix);
    void addRect(int id, bool keyFrame, int parentFrame, const QString &text, QRect rect, QColor color);
    void clearScene();

public slots:
    void resetZoom();
    void setZoom(int level);
    int zoomLevel() const;

protected:
    void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem* m_frame;
    int m_zoomLevel;
    QList<RectItem*> m_itemOnScene;
signals:
    void editModel(bool, int, int, QRectF);
    void doubleClick(QPoint);
    void next();
    void prev();
    void play_pause();

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // GRAPHICSVIEW_H
