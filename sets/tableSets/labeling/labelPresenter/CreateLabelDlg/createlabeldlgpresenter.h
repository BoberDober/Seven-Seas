#ifndef CREATELABELDLGPRESENTER_H
#define CREATELABELDLGPRESENTER_H

#include <QObject>
#include "createlabeldlgmodel.h"
#include "icreatelabeldlg.h"
#include <QPoint>

class CreateLabelDlgPresenter : public QObject
{
    Q_OBJECT
private:
    ICreateLabelDlg *m_view;
    CreateLabelDlgModel *m_model;

    QPoint m_point;
public:
    explicit CreateLabelDlgPresenter(ICreateLabelDlg *view, QObject *parent = nullptr);
    void openDialog(const QPoint &point);
signals:
    void acceptCreate(QString, QPoint);
public slots:
private slots:
    void closeDialog();
    void createLabel();
};

#endif // CREATELABELDLGPRESENTER_H
