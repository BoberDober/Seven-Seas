#include "createlabeldlgmodel.h"
#include "../../../../../database.h"
#include <QDebug>

CreateLabelDlgModel::CreateLabelDlgModel(QObject *parent) : QObject(parent)
{

}

QStringList CreateLabelDlgModel::updateNameList()
{
    QStringList list;
    QSqlQuery query(Database::getInstance().prepare("SELECT * FROM meanings;").selectRows());
    QSqlRecord rec = query.record();
    while(query.next())
    {
        list.append(query.value(rec.indexOf("name")).toString());
    }

    return list;
}
