#include "graphicsview.h"
#include <QDebug>
#include <QResizeEvent>
#include "graphicshelpers.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(nullptr),
    m_frame(new QGraphicsPixmapItem),
    m_zoomLevel(0)
{
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheBackground);

    setMouseTracking(true);
    m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setScene(m_scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setSize(QSize(10000, 10000));
    m_scene->addItem(m_frame);
}

void GraphicsView::setSize(const QSize size)
{
    m_size = size;
    m_scene->setSceneRect(QRect(0,0,size.width(),size.height()));
}

void GraphicsView::setFrame(const QPixmap &pix)
{
    m_frame->setPixmap(pix);
    setSize(pix.size());
}

void GraphicsView::addRect(int id, bool keyFrame, int parentFrame, const QString &text, QRect rect, QColor color)
{   
    RectItem* item = new RectItem(id, keyFrame, parentFrame, text, color);
    item->setRect(0,0,rect.width(), rect.height());
    item->setPos(rect.x(), rect.y());
    m_scene->addItem(item);
    m_itemOnScene.append(item);
}

void GraphicsView::clearScene()
{
    for (int i = 0; i<m_itemOnScene.size(); i++)
    {
        RectItem *item = m_itemOnScene.at(i);
        QRect rectItem;
        rectItem.setX(static_cast<int>(item->x()));
        rectItem.setY(static_cast<int>(item->y()));
        rectItem.setWidth(static_cast<int>(item->rect().width()));
        rectItem.setHeight(static_cast<int>(item->rect().height()));

        if(item->getCurrentState() == State::CHANGED)
        {
            emit editModel(item->getKeyFrame(), m_itemOnScene.at(i)->getId(), item->getParentFrame(), rectItem);
        }
        m_scene->removeItem(m_itemOnScene.at(i));
        delete m_itemOnScene.at(i);
    }
    m_itemOnScene.clear();
}

void GraphicsView::resetZoom()
{
    m_zoomLevel = 0;
    QTransform tr = transformFromZoom(m_zoomLevel);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setTransform(tr);
}

void GraphicsView::setZoom(int level){
    bool accepted = false;
    QTransform tr = transformFromZoom(level, &accepted);
    if(accepted)
    {
        m_zoomLevel = level;
    }
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setTransform(tr);
}

int GraphicsView::zoomLevel() const
{
    return m_zoomLevel;
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
    //qDebug() << Q_FUNC_INFO << event->size() << event->oldSize();
    /*QRectF bounds(0, 0, m_size.width(), m_size.height());
    bounds.setWidth(bounds.width());
    bounds.setHeight(bounds.height());
    fitInView(bounds, Qt::KeepAspectRatio);*/
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
   const int degrees = event->delta() / 8;
   int steps = degrees / 15;
   bool accepted = false;

   int level = m_zoomLevel + steps;

   QTransform tr = transformFromZoom(level, &accepted);
   if(accepted){
       m_zoomLevel += steps;
   }
   setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
   setTransform(tr);
}

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClick(event->pos());
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key::Key_V:
            emit next();
        break;
    case Qt::Key::Key_C:
            emit prev();
        break;
    case Qt::Key::Key_Space:
            emit play_pause();
        break;
    }
}
