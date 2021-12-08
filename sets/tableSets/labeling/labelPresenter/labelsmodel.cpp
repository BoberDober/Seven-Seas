#include "labelsmodel.h"
#include <QDebug>
#include <QPair>
#include "../../../../database.h"

LabelsModel::LabelsModel(QObject *parent) : QObject(parent)
{

}


QList<QObject*> LabelsModel::getList(const QString &setsName, int frame)
{
    qDeleteAll(m_list);
    m_list.clear();
    int id_set = getSetID(setsName);
    QString request_str = "SELECT * FROM labels "
                          "WHERE id_set = ? AND (frame = ?) OR id_set = ? AND (keyFrame = ? AND frame <= ? AND noFrame = ?);";

    QSqlQuery query(Database::getInstance().prepare(request_str)
                    .setVal(id_set)
                    .setVal(frame)
                    .setVal(id_set)
                    .setVal(true) //keyFrame
                    .setVal(frame)
                    .setVal(false)
                    .selectRows());

    QSqlRecord rec = query.record();
    LabelsItem *item;
    while(query.next())
    {
        item = new LabelsItem();
        item->setName(m_hashLabel.value(query.value(rec.indexOf("labels.id_label")).toInt()));
        QRect tmpRect;
        tmpRect.setX(query.value(rec.indexOf("labels.x")).toInt());
        tmpRect.setY(query.value(rec.indexOf("labels.y")).toInt());
        tmpRect.setWidth(query.value(rec.indexOf("labels.w")).toInt());
        tmpRect.setHeight(query.value(rec.indexOf("labels.h")).toInt());

        int id = query.value(rec.indexOf("labels.id")).toInt();
        int parentFrame = query.value(rec.indexOf("labels.parentFrame")).toInt();
        int newFrame = query.value(rec.indexOf("labels.frame")).toInt();
        bool noFrame = query.value(rec.indexOf("labels.noFrame")).toBool();
        bool keyFrame = query.value(rec.indexOf("labels.keyFrame")).toBool();

        if(newFrame < frame && !noFrame)
        {
            parentFrame = id;
            id = -1;
            keyFrame = false;
        }

        item->setParentFrame(parentFrame);
        item->setKeyFrame(keyFrame);
        item->setId(id);
//        qDebug() << item->id() << parentFrame << keyFrame;

        item->setRect(tmpRect);
        m_list.append(item);
    }

    return m_list;
}

void LabelsModel::editLabel(QRectF rect, bool keyFrame, int parentFrame, int frame)
{
    QString request_str = "UPDATE labels SET x = ?, y = ?, w = ?, h = ?, keyFrame = ?, parentFrame = ? WHERE parentFrame = ? AND frame = ?;";
    bool res = Database::getInstance().prepare(request_str)
            .setVal(rect.x())
            .setVal(rect.y())
            .setVal(rect.width())
            .setVal(rect.height())
            .setVal(keyFrame)
            .setVal(parentFrame)
            .setVal(parentFrame)
            .setVal(frame)
            .update();
    if(!res)
    {
        qDebug() << "невозможно редактировать метку " << Database::getInstance().lastError();
    }
}

void LabelsModel::editLabel(int id, QRectF rect, bool keyFrame, int parentFrame)
{
    QString request_str = "UPDATE labels SET x = ?, y = ?, w = ?, h = ?, keyFrame = ?, parentFrame = ? WHERE id = ?;";
    bool res = Database::getInstance().prepare(request_str)
            .setVal(rect.x())
            .setVal(rect.y())
            .setVal(rect.width())
            .setVal(rect.height())
            .setVal(keyFrame)
            .setVal(parentFrame)
            .setVal(id)
            .update();
    if(!res)
    {
        qDebug() << "невозможно редактировать метку " << Database::getInstance().lastError();
    }
}

void LabelsModel::addFrameLabel(int parentFrame, int frame, const QRectF& rect, bool keyFrame)
{
    QString request_str = "SELECT id_label, id_set FROM labels WHERE id = ?;";

    QSqlQuery query(Database::getInstance().prepare(request_str)
                    .setVal(parentFrame)
                    .selectRows());

    QSqlRecord rec = query.record();
    int id_label = -1;
    int id_set = -1;

    if(query.next())
    {
        id_label = query.value(rec.indexOf("id_label")).toInt();
        id_set = query.value(rec.indexOf("id_set")).toInt();
    }
    if(id_set == -1 || id_label == -1)
    {
        qDebug() << "Ошибка запроса добавления метки!";
        return;
    }

    createLabel(id_label, id_set, frame, rect, keyFrame, parentFrame, false);
}

void LabelsModel::updateHashLabel()
{
    m_hashLabel.clear();
    QString request_str = "SELECT * FROM meanings;";
    QSqlQuery query(Database::getInstance().prepare(request_str).selectRows());
    QSqlRecord rec = query.record();

    while(query.next())
    {
        m_hashLabel.insert(query.value(rec.indexOf("id")).toInt(), query.value(rec.indexOf("name")).toString());
    }
}

void LabelsModel::createLabel(const QString& labelName, const QString& setName, int frame, const QPoint& point, bool keyFrame, int parentFrame, bool noFrame)
{
    QString request_str = "INSERT INTO labels ('id_set', 'x', 'y', 'w', 'h', 'frame', 'id_label', 'keyFrame', 'parentFrame', 'noFrame') VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    bool res = Database::getInstance().prepare(request_str)
            .setVal(getSetID(setName))
            .setVal(point.x())
            .setVal(point.y())
            .setVal(100)
            .setVal(100)
            .setVal(frame)
            .setVal(m_hashLabel.key(labelName))
            .setVal(keyFrame)
            .setVal(parentFrame)
            .setVal(noFrame)
            .insert();
    qDebug() << getSetID(setName) << point.x() << point.y() << 100 << 100 << frame
             << m_hashLabel.key(labelName) << keyFrame << parentFrame << noFrame;
    if(!res)
    {
        qDebug() << "невозможно создать метку" << Database::getInstance().lastError();
    }
}

void LabelsModel::createLabel(int id_label, int id_set, int frame, const QRectF &rect, bool keyFrame, int parentFrame, bool noFrame)
{
    QString request_str = "INSERT INTO labels ('id_set', 'x', 'y', 'w', 'h', 'frame', 'id_label', 'keyFrame', 'parentFrame', 'noFrame') VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    bool res = Database::getInstance().prepare(request_str)
            .setVal(id_set)
            .setVal(static_cast<int>(rect.x()))
            .setVal(static_cast<int>(rect.y()))
            .setVal(static_cast<int>(rect.width()))
            .setVal(static_cast<int>(rect.height()))
            .setVal(frame)
            .setVal(id_label)
            .setVal(keyFrame)
            .setVal(parentFrame)
            .setVal(noFrame)
            .insert();
    if(!res)
    {
        qDebug() << "невозможно создать метку (overload func)" << Database::getInstance().lastError();
    }
}

void LabelsModel::deleteLabel(int id)
{
    QString request_str = "DELETE FROM labels WHERE id = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(id).del();
    if(!res)
    {
        qDebug() << "невозможно удалить метку " << Database::getInstance().lastError();
    }
}

void LabelsModel::closeFrame(int id)
{
    QString request_str = "UPDATE labels SET noFrame = ? WHERE id = ?;";
    bool res = Database::getInstance().prepare(request_str)
            .setVal(true)
            .setVal(id)
            .update();
    if(!res)
    {
        qDebug() << "невозможно закрыть метку" << id << Database::getInstance().lastError();
    }
}

int LabelsModel::getFrameFromID(int id)
{
    int frame = -1;
    if(id == -1)
        return -1;
    QString request_str = "SELECT frame FROM labels WHERE id = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(id).selectRows());
    QSqlRecord rec = query.record();

    if(query.next())
    {
        frame = query.value(rec.indexOf("frame")).toInt();
    }

    return frame;
}

QRectF LabelsModel::getBox(int id)
{
    QRectF rect;
    QString request_str = "SELECT x, y, w, h FROM labels WHERE id = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(id).selectRows());
    QSqlRecord rec = query.record();

    if(query.next())
    {
        rect.setX(query.value(rec.indexOf("x")).toDouble());
        rect.setY(query.value(rec.indexOf("y")).toDouble());
        rect.setWidth(query.value(rec.indexOf("w")).toDouble());
        rect.setHeight(query.value(rec.indexOf("h")).toDouble());
    }

    return rect;
}

bool LabelsModel::boxIsExists(int id)
{
    QString request_str = "SELECT * FROM labels WHERE id = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(id).selectRows());
    QSqlRecord rec = query.record();

    if(query.next())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int LabelsModel::getMaxFrame(const QString &set_name, int parentFrame, int frame)
{
    int maxFrame = -1;

    QString request_str = "SELECT * FROM labels WHERE id_set AND parentFrame = ? AND frame > ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(getSetID(set_name)).setVal(parentFrame).setVal(frame).selectRows());
    QSqlRecord rec = query.record();

    while(query.next())
    {
        int tmp_frame = query.value(rec.indexOf("frame")).toInt();
        if(tmp_frame > maxFrame)
            maxFrame = tmp_frame;
    }

    return maxFrame;
}

int LabelsModel::getIDMaxFrame(int parentFrame, int frame)
{
    int id = -1;
    int maxFrame = -1;
    QString request_str = "SELECT * FROM labels WHERE parentFrame = ? AND frame > ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(parentFrame).setVal(frame).selectRows());
    QSqlRecord rec = query.record();

    while(query.next())
    {
        int tmp_frame = query.value(rec.indexOf("frame")).toInt();
        if(tmp_frame > maxFrame)
        {
            maxFrame = tmp_frame;
            id = query.value(rec.indexOf("id")).toInt();
        }
    }

    return id;
}

int LabelsModel::getIDChildKeyFrame(int _id)
{
    int id = -1;
    QString request_str = "SELECT * FROM labels WHERE keyFrame = ? AND parentFrame = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(true).setVal(_id).selectRows());
    QSqlRecord rec = query.record();

    while(query.next())
    {
        id = query.value(rec.indexOf("id")).toInt();
    }

    return id;
}

int LabelsModel::getIDParent(int _id)
{
    int id = -2;
    QString request_str = "SELECT * FROM labels WHERE id = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(_id).selectRows());
    QSqlRecord rec = query.record();

    if(query.next())
    {
        id = query.value(rec.indexOf("parentFrame")).toInt();
    }

    return id;
}

void LabelsModel::deleteNotKeyFrame(const QString &set_name, int id, int frame, const DeleteType &deleteType)
{
    QString request_str;
    bool res = false;

    switch (deleteType)
    {
    case NEXT:
        request_str = "DELETE FROM labels WHERE id_set = ? AND parentFrame = ? AND keyFrame = ? AND frame > ?;";
        res = Database::getInstance().prepare(request_str).setVal(getSetID(set_name)).setVal(id).setVal(false).setVal(frame).del();
        break;
    case PREV:
        request_str = "DELETE FROM labels WHERE id_set = ? AND parentFrame = ? AND keyFrame = ? AND frame < ?;";
        res = Database::getInstance().prepare(request_str).setVal(getSetID(set_name)).setVal(id).setVal(false).setVal(frame).del();
        break;
    default:
        qDebug() << "Ошибка параметров удаления!";
        return;
    }

    if(!res)
    {
        qDebug() << "невозможно удалить метку " << Database::getInstance().lastError();
    }
}

void LabelsModel::deleteByParent(const QString &set_name, int parentID)
{
    QString request_str;
    request_str = "DELETE FROM labels WHERE id_set = ? AND parentFrame = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(getSetID(set_name)).setVal(parentID).del();


    if(!res)
    {
        qDebug() << Q_FUNC_INFO << "невозможно удалить метку " << Database::getInstance().lastError();
    }
}

void LabelsModel::editParentFrame(int parentID, int id)
{
//    qDebug() << parentID << id;
    QString request_str = "UPDATE labels SET parentFrame = ? WHERE id = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(parentID).setVal(id)

            .update();
    if(!res)
    {
        qDebug() << "невозможно редактировать метку " << Database::getInstance().lastError();
    }
}

void LabelsModel::deleteFromParentFrame(int id)
{
    QString request_str = "DELETE FROM labels WHERE keyFrame = ? AND parentFrame = ?;";
    bool res = Database::getInstance().prepare(request_str).setVal(false).setVal(id).del();
    if(!res)
    {
        qDebug() << Q_FUNC_INFO << "Невозможно удалить метки" << id;
    }
}

bool LabelsModel::isImport(int id)
{
    bool import = false;
    QString request_str = "SELECT * FROM labels WHERE id = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(id).selectRows());
    QSqlRecord rec = query.record();

    if(query.next())
    {
        import = query.value(rec.indexOf("import")).toBool();
    }
    return import;
}

int LabelsModel::getSetID(QString name)
{
    int id = -1;
    QString request_str = "SELECT * FROM sets WHERE name = ?;";
    QSqlQuery query(Database::getInstance().prepare(request_str).setVal(name).selectRows());
    QSqlRecord rec = query.record();

    while(query.next())
    {
        id = query.value(rec.indexOf("id")).toInt();
    }
    return id;
}

LabelsModel::~LabelsModel()
{
    qDeleteAll(m_list);
    m_list.clear();
}
