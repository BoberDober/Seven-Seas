#include "createlabeldlgpresenter.h"
#include <QDebug>

CreateLabelDlgPresenter::CreateLabelDlgPresenter(ICreateLabelDlg *view, QObject *parent) : QObject(parent)
{
    m_view = view;
    m_model = new CreateLabelDlgModel(this);

    QObject *obj = dynamic_cast<QObject*>(m_view);
    QObject::connect(obj, SIGNAL(closedDialog()), this, SLOT(closeDialog()));
    QObject::connect(obj, SIGNAL(createLabel()), this, SLOT(createLabel()));
    m_point = QPoint(0, 0);
}

void CreateLabelDlgPresenter::openDialog(const QPoint& point)
{
    m_view->setModelComboBox(m_model->updateNameList());
    m_point = point;
    m_view->openDialog();
}

void CreateLabelDlgPresenter::closeDialog()
{
    m_point = QPoint(0, 0);
    m_view->closeDialog();
}

void CreateLabelDlgPresenter::createLabel()
{
    emit acceptCreate(m_view->getNameComboBox(), m_point);
    m_view->closeDialog();
}
