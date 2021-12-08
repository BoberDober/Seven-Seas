#include "labelspresenter.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>

LabelsPresenter::LabelsPresenter(ILabelingplayerview *playerView, IListLabelsView *listView, QObject *parent) : QObject(parent)
{
    m_playerView = playerView;
    m_listView = listView;
    m_model = new LabelsModel(this);

    QObject *obj = dynamic_cast<QObject*>(m_playerView);
    QObject::connect(obj, SIGNAL(frameChanged(int)), this, SLOT(updateModel(int)));
    QObject::connect(obj, SIGNAL(editModel(bool, int, int, QRectF)), this, SLOT(editModel(bool, int, int, QRectF)));
    QObject::connect(obj, SIGNAL(addLabel(QPoint)), this, SLOT(addLabel(QPoint)));

    QObject *obj_list = dynamic_cast<QObject*>(m_listView);
    QObject::connect(obj_list, SIGNAL(acceptCreate(QString, QPoint)), this, SLOT(createLabel(QString, QPoint)));
    QObject::connect(obj_list, SIGNAL(acceptDelete(int, int)), this, SLOT(acceptDelete(int, int)));
    QObject::connect(obj_list, SIGNAL(frameClose(int)), this, SLOT(frameClose(int)));
}

void LabelsPresenter::openLabeling(QString workFolder, QString setsName)
{
    m_setName = setsName;
    QString path;
    QString nameFolder;
    path = workFolder + QDir::separator() + "Sets" + QDir::separator() + m_setName + QDir::separator() + "img" + QDir::separator();
    m_model->updateHashLabel();
    m_playerView->setImagePath(path);
}

void LabelsPresenter::closeLabeling()
{
    m_setName.clear();
    m_playerView->setImagePath("");
}

void LabelsPresenter::createLabel(const QString& name, const QPoint& point)
{
    m_model->createLabel(name, m_setName, m_playerView->getCurrentFrame(), point, true, -1, false);
    updateModel(m_playerView->getCurrentFrame());
}

void LabelsPresenter::acceptDelete(int id, int parentID)
{
    if(!m_playerView->openQuestionBox())
        return;

    int firstID;
    if(parentID == -1)
    {
        firstID = searchFirstBox(id);
    }
    else
    {
        firstID = searchFirstBox(parentID);
    }
    m_model->deleteLabel(firstID);
    deleteBoxesChild(firstID);
    updateModel(m_playerView->getCurrentFrame());
}

void LabelsPresenter::frameClose(int id)
{
    m_model->closeFrame(id);
}

void LabelsPresenter::addLabel(const QPoint &point)
{
    m_listView->addLabel(point);
}

double LabelsPresenter::interpolateLagrangePolynomial(double x, double *x_values, double *y_values, int size)
{
    double lagrange_pol = 0;
    double basics_pol;

    for (int i = 0; i < size; i++)
    {
        basics_pol = 1;
        for (int j = 0; j < size; j++)
        {
            if (j == i) continue;
            basics_pol *= (x - x_values[j])/(x_values[i] - x_values[j]);
        }
        lagrange_pol += basics_pol*y_values[i];
    }
    return lagrange_pol;
}

void LabelsPresenter::updateModel(int frame)
{
    QList<QObject*> model = m_model->getList(m_setName, frame);
    m_listView->setModel(model);
    m_playerView->setModel(model);
}

void LabelsPresenter::addKeyFrame(int id, int parentId, int frameIndex, const QRectF& rect)
{
    m_model->closeFrame(parentId);

    if(m_model->boxIsExists(id))
    {
        qDebug() << "EDIT";
        m_model->editLabel(id, rect, true, parentId);
    }
    else
    {
        qDebug() << "NEW";
        m_model->addFrameLabel(parentId, frameIndex, rect, true);
    }
}

void LabelsPresenter::editModel(bool keyFrame, int id, int parentId, QRectF rect)
{
//    "import BOOLEAN DEFAULT 0"
    int frameIndex = m_playerView->getCurrentFrame();
    int childId = m_model->getIDChildKeyFrame(id);
    qDebug() << "ID" << id << "parentId" << parentId << "childId" << childId << "frameIndex" << frameIndex << "keyFrame" << keyFrame;

    if(m_model->isImport(id))
    {
        qDebug() << "IMPORT BOX";
        addKeyFrame(id, parentId, frameIndex, rect);
    }
    else if(parentId == -1)
    {
        qDebug() << "FIRST BOX";
        addKeyFrame(id, parentId, frameIndex, rect);
        m_model->deleteFromParentFrame(id);
        QRectF firstRect = rect;
        QRectF secondRect = m_model->getBox(childId);
        int firstFrame = frameIndex;
        int secondFrame = m_model->getFrameFromID(childId);
        sectionInterpolation(firstRect, secondRect, firstFrame, secondFrame, id);
    }
    else if((id == -1) || (childId == -1 && keyFrame == true))
    {
        if(childId == -1 && keyFrame == true)
        {
            qDebug() << "LAST BOX";
            m_model->deleteFromParentFrame(parentId);
        }
        else
        {
            qDebug() << "GENERATED BOX";
        }
        addKeyFrame(id, parentId, frameIndex, rect);
        QRectF firstRect = m_model->getBox(parentId);
        QRectF secondRect = rect;
        int firstFrame = m_model->getFrameFromID(parentId);
        int secondFrame = frameIndex;
        sectionInterpolation(firstRect, secondRect, firstFrame, secondFrame, parentId);
    }
    else if((childId == -1 && keyFrame == false) || (childId != -1 && keyFrame == true))
    {
        if(childId == -1 && keyFrame == false)
        {
            childId = m_model->getIDChildKeyFrame(parentId);
        }
        else if(childId != -1 && keyFrame == true)
        {
            childId = m_model->getIDChildKeyFrame(id);
        }
        qDebug() << "IN SECTION" << parentId << childId;
        addKeyFrame(id, parentId, frameIndex, rect);
        m_model->closeFrame(id);
        m_model->deleteFromParentFrame(parentId);
        m_model->deleteFromParentFrame(id);
        QRectF firstRect = m_model->getBox(parentId);
        QRectF secondRect = rect;
        int firstFrame = m_model->getFrameFromID(parentId);
        int secondFrame = frameIndex;
        sectionInterpolation(firstRect, secondRect, firstFrame, secondFrame, parentId);

        firstRect = rect;
        secondRect = m_model->getBox(childId);
        firstFrame = frameIndex;
        secondFrame = m_model->getFrameFromID(childId);
        sectionInterpolation(firstRect, secondRect, firstFrame, secondFrame, id);
        m_model->editParentFrame(id, childId);
    }
    else
    {
        qDebug() << "unknow object";
    }
}

void LabelsPresenter::sectionInterpolation(const QRectF& firstRect, const QRectF& secondRect, double first_value, double second_value, int parentFrame)
{
    double x_values[2] = {firstRect.x(), secondRect.x()};
    double y_values[2] = {firstRect.y(), secondRect.y()};
    double w_values[2] = {firstRect.width(), secondRect.width()};
    double h_values[2] = {firstRect.height(), secondRect.height()};

    double frame_values[2] = {first_value, second_value};

    for(int i = static_cast<int>(first_value) + 1; i < static_cast<int>(second_value); i++)
    {
        QRectF rect_result;
        rect_result.setX(interpolateLagrangePolynomial(i, frame_values, x_values, 2));
        rect_result.setY(interpolateLagrangePolynomial(i, frame_values, y_values, 2));
        rect_result.setWidth(interpolateLagrangePolynomial(i, frame_values, w_values, 2));
        rect_result.setHeight(interpolateLagrangePolynomial(i, frame_values, h_values, 2));

//        qDebug() << parentFrame << i << rect_result;

        m_model->addFrameLabel(parentFrame, i, rect_result, false);
    }
}

int LabelsPresenter::searchFirstBox(int id)
{
    int parentID = m_model->getIDParent(id);
//    qDebug()  << "CHECK"<< id << parentID;
    if(parentID == -1)
    {
//        qDebug()  << "FIRST "<< id << parentID;
        return id;
    }
    searchFirstBox(parentID);
}

void LabelsPresenter::deleteBoxesChild(int id)
{
    int childID =  m_model->getIDChildKeyFrame(id);
    m_model->deleteByParent(m_setName, id);
//    qDebug() << id << childID;
    if(childID == -1)
    {
//        qDebug() << "END CHILD";
        return;
    }
    deleteBoxesChild(childID);
}
