#include "rectitem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QCursor>
#include <QPainter>
#include <cmath>
int RectItem::getId() const
{
    return m_id;
}

bool RectItem::getKeyFrame() const
{
    return m_keyFrame;
}


State RectItem::getCurrentState() const
{
    return m_currentState;
}

int RectItem::getParentFrame() const
{
    return m_parentFrame;
}

RectItem::RectItem(int id, bool keyFrame, int parentFrame, const QString &text, const QColor &color):
    m_state(rsNone)
{
    m_id = id;
    m_keyFrame = keyFrame;
    m_parentFrame = parentFrame;
    m_currentState = State::NON_CHANGED;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemIsFocusable);

    setAcceptHoverEvents(true);
    setRect(0,0,100,100);
    setPos(0,0);
    setZValue(RectZTop);
    setVisible(true);
    setZValue(100);

    QPen pen;
    pen.setColor(color);
    pen.setWidth(4);
    setPen(pen);

    m_itemText = new QGraphicsTextItem(text, this);
    QFont font;
    int weightFont = 30;
    font.setPixelSize(weightFont);
    font.setBold(true);
    m_itemText->setX(x());
    m_itemText->setY(y() - weightFont * 1.5);
    m_itemText->setFont(font);
    m_itemText->setDefaultTextColor(color);
}

void RectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << m_keyFrame << m_id;
    if(event->button() == Qt::LeftButton)
    {
        QPointF posInRect = event->pos();
        m_state = getResizeState(posInRect);

        m_startMousePos = event->scenePos();
        m_startRectPos = pos();
        m_startRect = rect();

        if(m_state == rsNone)
        {
            QGraphicsRectItem::mousePressEvent(event);
        }
    }
}

void RectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "ID" << m_id << "parentFrame" << m_parentFrame << "keyFrame" << m_keyFrame;
    QGraphicsRectItem::mouseReleaseEvent(event);
    onItemChanged();
}

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if(m_keyFrame != -1)
//        m_keyFrame = -1;
//    qDebug() << "ITEM CHANGED";

    m_currentState = State::CHANGED;

    if((event->buttons() & Qt::LeftButton) && m_state!=rsNone)
    {
        QPointF mousePos = event->scenePos();

        if(m_state == rsHL)
        {
            double newWidth = m_startMousePos.x() - mousePos.x() + m_startRect.width();
            setPos(mousePos.x(), m_startRectPos.y());
            setRect(0, 0, newWidth, m_startRect.height());
        }
        else if(m_state == rsHR)
        {
            double newWidth = mousePos.x() - m_startMousePos.x() + m_startRect.width();
            setRect(0, 0, newWidth, m_startRect.height());
        }
        else if(m_state == rsVT)
        {
            double newHeight = m_startMousePos.y() - mousePos.y() + m_startRect.height();
            setPos(m_startRectPos.x(), mousePos.y());
            setRect(0, 0, m_startRect.width(), newHeight);
        }
        else if(m_state == rsVB)
        {
            double newHeight = mousePos.y() - m_startMousePos.y() + m_startRect.height();
            setRect(0, 0, m_startRect.width(), newHeight);
        }
        else if(m_state == rsBothLT)
        {
            double newWidth = m_startMousePos.x() - mousePos.x() + m_startRect.width();
            double newHeight = m_startMousePos.y() - mousePos.y() + m_startRect.height();
            setRect(0,0,newWidth,newHeight);
            setPos(mousePos.x(),mousePos.y());
        }
        else if(m_state == rsBothRT)
        {
            double newWidth = mousePos.x() - m_startMousePos.x() + m_startRect.width();
            double newHeight = m_startMousePos.y() - mousePos.y() + m_startRect.height();
            setPos(m_startRectPos.x(), mousePos.y());
            setRect(0, 0, newWidth, newHeight);
        }
        else if(m_state == rsBothLB)
        {
            double newWidth = m_startMousePos.x() - mousePos.x() + m_startRect.width();
            double newHeight = mousePos.y() - m_startMousePos.y() + m_startRect.height();
            setPos(mousePos.x(), m_startRectPos.y());
            setRect(0,0,newWidth,newHeight);
        }
        else if(m_state == rsBothRB)
        {
            double newWidth = mousePos.x() - m_startMousePos.x() + m_startRect.width();
            double newHeight = mousePos.y() - m_startMousePos.y() + m_startRect.height();
            setRect(0,0,newWidth,newHeight);
        }

//        m_keyFrame = -1;
    }
    else
    {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
    onItemChanged();
}

bool RectItem::updateCursor(const QPointF &pos)
{
    ResizeState rs = getResizeState(pos);
    switch (rs) {
    case rsHL:
    case rsHR:
        setCursor(Qt::SizeHorCursor);
        break;
    case rsVT:
    case rsVB:
        setCursor(Qt::SizeVerCursor);
        break;
    case rsBothLT:
    case rsBothRB:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case rsBothRT:
    case rsBothLB:
        setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        return false;
    }
    return true;
}

void RectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    updateCursor(event->pos());
}

QVariant RectItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemSelectedHasChanged){
        if(value == 1){
            setZValue(RectZTop);
        }
        else{
            setZValue(RectZDown);
        }
    }
    return QGraphicsRectItem::itemChange(change, value);
}

RectItem::ResizeState RectItem::getResizeState(const QPointF &posInRect)
{
    double tolerance = 4;

    bool left = fabs(posInRect.x()) < tolerance;
    bool right = fabs(rect().width() - posInRect.x()) < tolerance;
    bool top = fabs(posInRect.y()) < tolerance;
    bool bottom = fabs(rect().height() - posInRect.y()) < tolerance;

    if((left || right) && (top || bottom))
    {
        if(left && top)
            return rsBothLT;
        else if(left && bottom)
            return rsBothLB;
        else if(right && top)
            return rsBothRT;
        else if(right && bottom)
            return rsBothRB;
    }

    if(left)
        return rsHL;
    if(right)
        return rsHR;
    if(top)
        return rsVT;
    if(bottom)
        return rsVB;

    return rsNone;
}
