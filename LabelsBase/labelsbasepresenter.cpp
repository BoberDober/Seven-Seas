#include "labelsbasepresenter.h"
#include <QDebug>

LabelsBasePresenter::LabelsBasePresenter(ILabelsBase *view, QObject *parent) : QObject(parent)
{
    m_view = view;
    m_model = new LabelsBaseModel(this);

    m_model->updateModel();
    m_view->setModel(m_model);

    QObject *obj = dynamic_cast<QObject*>(m_view);
    QObject::connect(obj, SIGNAL(acceptAddDlg()), this, SLOT(acceptAddLabel()));
    QObject::connect(obj, SIGNAL(deleteItem()), this, SLOT(deleteItem()));
    QObject::connect(obj, SIGNAL(editItem()), this, SLOT(editItem()));
}

void LabelsBasePresenter::acceptAddLabel()
{
    if(!m_model->addMeaning(m_view->getOldName(), m_view->getNameAddMeaning(), m_view->getDescriptionAddMeaning()))
    {
        m_view->viewMessageBox("Метка уже существует!");
    }
    else
    {
        updateModel();
        m_view->addAccept();
    }
}

void LabelsBasePresenter::deleteItem()
{
    QStandardItem *item = m_model->itemFromIndex(m_model->index(m_view->getCurrentIndexTable().row(), 0));
    if(!item)
    {
        return;
    }
    if(!m_view->getQuestionBox(item->text()))
        return;
    if(!m_model->checkDeleteMeaning(item->text()))
    {
        m_view->viewMessageBox("Невозможно удалить связную метку!");
    }
    updateModel();
}

void LabelsBasePresenter::editItem()
{
    QStandardItem *itemName = m_model->itemFromIndex(m_model->index(m_view->getCurrentIndexTable().row(), 0));
    QStandardItem *itemDescription = m_model->itemFromIndex(m_model->index(m_view->getCurrentIndexTable().row(), 1));
    if(!itemName || !itemDescription)
    {
        return;
    }
    m_view->editLabel(itemName->text(), itemDescription->text());
}

void LabelsBasePresenter::updateModel()
{
    m_model->updateModel();
    m_view->setReziseToContent();
}
