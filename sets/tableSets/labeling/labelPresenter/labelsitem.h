#ifndef LABELSITEM_H
#define LABELSITEM_H

#include <QObject>
#include <QColor>
#include <QRect>

class LabelsItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool noFrame READ noFrame WRITE setNoFrame NOTIFY noFrameChanged)
    Q_PROPERTY(bool far READ far WRITE setFar NOTIFY farChanged)
    Q_PROPERTY(bool blocked READ blocked WRITE setBlocked NOTIFY blockedChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QRect rect READ rect WRITE setRect NOTIFY rectChanged)
    Q_PROPERTY(bool keyFrame READ keyFrame WRITE setKeyFrame NOTIFY keyFrameChanged)
    Q_PROPERTY(int parentFrame READ parentFrame WRITE setParentFrame NOTIFY parentFrameChanged)
public:
    explicit LabelsItem(QObject *parent = nullptr);

    int id() const;
    QString name() const;
    bool noFrame() const;
    bool far() const;
    bool blocked() const;
    QColor color() const;
    QRect rect() const;
    bool keyFrame() const;
    int parentFrame() const;



signals:
    void idChanged(int);
    void nameChanged(QString);
    void noFrameChanged(bool);
    void farChanged(bool);
    void blockedChanged(bool);
    void colorChanged(QColor);
    void rectChanged(QRect);
    void keyFrameChanged(bool);
    void parentFrameChanged(int);

public slots:
    void setId(int id);
    void setName(const QString &name);
    void setNoFrame(bool noFrame);
    void setFar(bool far);
    void setBlocked(bool blocked);
    void setColor(const QColor &color);
    void setRect(const QRect &rect);
    void setKeyFrame(bool keyFrame);
    void setParentFrame(int parentFrame);

private:
    int m_id;
    bool m_keyFrame;
    int m_parentFrame;
    QString m_name;
    bool m_noFrame;
    bool m_far;
    bool m_blocked;
    QColor m_color;
    QRect m_rect;
};

#endif // LABELSITEM_H
