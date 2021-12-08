#ifndef LISTLABELSVIEW_H
#define LISTLABELSVIEW_H

#include <QWidget>
#include <QQuickWidget>
#include "ilistlabelsview.h"
#include "CreateLabelDlg/createlabeldlg.h"
#include "CreateLabelDlg/createlabeldlgpresenter.h"
#include "listlabelsengine.h"

namespace Ui {
class ListLabelsView;
}

class ListLabelsView : public QWidget, public IListLabelsView
{
    Q_OBJECT

public:
    explicit ListLabelsView(QWidget *parent = nullptr);
    ~ListLabelsView();
signals:
    void acceptCreate(QString, QPoint);
    void acceptDelete(int, int);
    void frameClose(int);
private:
    Ui::ListLabelsView *ui;
    QQuickWidget* m_quickWgt;
    CreateLabelDlg *m_createLabelDlg;
    CreateLabelDlgPresenter *m_createLabelDlgPresenter;
    ListLabelsEngine *m_listEngine;
    // IListLabelsView interface
public:
    void setModel(QList<QObject *> model);
private slots:
    void on_addBtn_clicked();

    // IListLabelsView interface
public:
    void addLabel(const QPoint &point);
};

#endif // LISTLABELSVIEW_H
