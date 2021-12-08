#include "labelingplayerview.h"
#include "ui_labelingplayerview.h"
#include "labelsitem.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>

LabelingPlayerView::LabelingPlayerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelingPlayerView)
{
    ui->setupUi(this);
    m_viewer = new Viewer(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(80);
    QVBoxLayout *viewerLayout = new QVBoxLayout();
    viewerLayout->addWidget(m_viewer);
    ui->labelingViewer->setLayout(viewerLayout);
    m_player = false;
    connect(m_viewer, SIGNAL(setSlider(int)), this, SLOT(setValueSlider(int)));
    connect(m_viewer, SIGNAL(maximumSlider(int)), this, SLOT(setMaxValueSlider(int)));
    connect(m_viewer, SIGNAL(frameChanged(int)), this, SIGNAL(frameChanged(int)));
    connect(m_viewer, SIGNAL(doubleClick(QPoint)), this, SIGNAL(addLabel(QPoint)));
    connect(m_viewer, SIGNAL(editModel(bool, int, int, QRectF)), this, SIGNAL(editModel(bool, int, int, QRectF)));
    connect(m_viewer, SIGNAL(play_pause()), this, SLOT(on_mainBtn_clicked()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_nextBtn_clicked()));
}
LabelingPlayerView::~LabelingPlayerView()
{
    delete ui;
}

void LabelingPlayerView::setImagePath(const QString &path)
{
    m_viewer->setImagePath(path);
}

void LabelingPlayerView::setModel(QList<QObject *> model)
{
    m_viewer->clearScene();
    for (int i=0;i<model.size();i++)
    {
        LabelsItem *item = static_cast<LabelsItem*>(model.at(i));
        m_viewer->drawObject(item->id(), item->keyFrame(), item->parentFrame(), item->name(), item->rect(), item->color());
    }
}

int LabelingPlayerView::getCurrentFrame()
{
    return m_viewer->currentFrame();
}

bool LabelingPlayerView::openQuestionBox()
{
    QMessageBox::StandardButton reply;
    QString question_str = "Вы действительно хотите удалить метку ?";
    reply = QMessageBox::question(this, "Подтведите", question_str, QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void LabelingPlayerView::on_prevBtn_clicked()
{
    m_viewer->prevFrame();
}

void LabelingPlayerView::on_mainBtn_clicked()
{
    if(!m_player)
    {
        m_timer->start();
    }
    else
    {
        m_timer->stop();
    }
    m_player = !m_player;
}

void LabelingPlayerView::on_nextBtn_clicked()
{
    m_viewer->nextFrame();
}

void LabelingPlayerView::setMaxValueSlider(int maxValue)
{
    ui->frameSlider->setMaximum(maxValue);
}

void LabelingPlayerView::setValueSlider(int value)
{
    ui->frameSlider->setValue(value);
}

void LabelingPlayerView::on_frameSlider_sliderMoved(int position)
{
    m_viewer->setFrame(position);
}

void LabelingPlayerView::player()
{
    m_viewer->nextFrame();
}
