#ifndef RECTITEM_H
#define RECTITEM_H
#include <QGraphicsRectItem>
constexpr const int RectZTop = 5;
constexpr const int RectZDown = 4;

enum State {
    CHANGED = 1,
    NON_CHANGED
};

class RectItem: public QGraphicsRectItem
{
private:
    int m_id;
    bool m_keyFrame;
    int m_parentFrame;
    State m_currentState;
    QGraphicsTextItem *m_itemText;

public:
    RectItem(int id, bool keyFrame, int parentFrame, const QString &text, const QColor &color);
    int getId() const;

//signals:
//    void itemEdit(int, QRectF);

    bool getKeyFrame() const;

    State getCurrentState() const;

    int getParentFrame() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent * event );
    void mouseMoveEvent (QGraphicsSceneMouseEvent * event );

    bool updateCursor(const QPointF& pos);
    void hoverMoveEvent (QGraphicsSceneHoverEvent * event);

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    virtual void onItemChanged(){}

    enum ResizeState{
        rsNone,
        rsHL,//horizontal left
        rsHR,//horizontal right
        rsVT,//vertial top
        rsVB,//vertical bottom
        rsBothLT, //left top
        rsBothRT, //right top
        rsBothLB, //left bottom
        rsBothRB //right bottom

    };

    ResizeState getResizeState(const QPointF& scenePos);
    ResizeState m_state;
    QPointF m_startMousePos;
    QPointF m_startRectPos;
    QRectF m_startRect;
};

#endif // RECTITEM_H
