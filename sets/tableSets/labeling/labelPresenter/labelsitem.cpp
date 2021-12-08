#include "labelsitem.h"
#include <QDebug>

LabelsItem::LabelsItem(QObject *parent) : QObject(parent)
{
    qDebug() << "NEW LABEL";
    m_id = -1;
    m_name = "";
    m_noFrame = false;
    m_far = false;
    m_blocked = false;
    m_color = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    m_rect = QRect(0, 0, 0, 0);
}

QString LabelsItem::name() const
{
    return m_name;
}

void LabelsItem::setName(const QString &name)
{
    m_name = name;
    emit nameChanged(m_name);
}

bool LabelsItem::noFrame() const
{
    return m_noFrame;
}

void LabelsItem::setNoFrame(bool noFrame)
{
    m_noFrame = noFrame;
    emit noFrameChanged(m_noFrame);
}

bool LabelsItem::far() const
{
    return m_far;
}

void LabelsItem::setFar(bool far)
{
    m_far = far;
    emit farChanged(m_far);
}

bool LabelsItem::blocked() const
{
    return m_blocked;
}

void LabelsItem::setBlocked(bool blocked)
{
    m_blocked = blocked;
    emit blockedChanged(m_blocked);
}

QColor LabelsItem::color() const
{
    return m_color;
}

void LabelsItem::setColor(const QColor &color)
{
    m_color = color;
    emit colorChanged(m_color);
}

QRect LabelsItem::rect() const
{
    return m_rect;
}

void LabelsItem::setRect(const QRect &rect)
{
    m_rect = rect;
    emit rectChanged(rect);
}

bool LabelsItem::keyFrame() const
{
    return m_keyFrame;
}

void LabelsItem::setKeyFrame(bool keyFrame)
{
    m_keyFrame = keyFrame;
    emit keyFrameChanged(keyFrame);
}

int LabelsItem::parentFrame() const
{
    return m_parentFrame;
}

void LabelsItem::setParentFrame(int parentFrame)
{
    m_parentFrame = parentFrame;
    emit parentFrameChanged(parentFrame);
}

int LabelsItem::id() const
{
    return m_id;
}

void LabelsItem::setId(int id)
{
    m_id = id;
    emit idChanged(m_id);
}
