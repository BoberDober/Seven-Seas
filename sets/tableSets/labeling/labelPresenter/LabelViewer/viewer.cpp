#include "viewer.h"

#include <QDir>
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

static bool compare(const QString& first, const QString& second)
{
    int firstNum = first.split(".")[0].toInt();
    int secondNum = second.split(".")[0].toInt();

    if (firstNum < secondNum)
    {
        return true;
    }
    else if (firstNum > secondNum)
    {
        return false;
    }
    else
    {
        return  false;
    }
}

int Viewer::currentFrame() const
{
    return m_currentFrame;
}

void Viewer::clearScene()
{
    m_graphicsView->clearScene();
}

Viewer::Viewer(QWidget *parent) : QWidget(parent)
{
    m_currentFrame = 0;
    m_graphicsView = new GraphicsView(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_graphicsView);
    setLayout(layout);

    connect(m_graphicsView, SIGNAL(editModel(bool, int, int, QRectF)), this, SIGNAL(editModel(bool, int, int, QRectF)));
    connect(m_graphicsView, SIGNAL(doubleClick(QPoint)), this, SIGNAL(doubleClick(QPoint)));
    connect(m_graphicsView, SIGNAL(next()), this, SLOT(nextFrame()));
    connect(m_graphicsView, SIGNAL(prev()), this, SLOT(prevFrame()));
    connect(m_graphicsView, SIGNAL(play_pause()), this, SIGNAL(play_pause()));
}

void Viewer::setImagePath(QString path)
{
    qDebug() << path;
    if(path == "")
    {
        m_listFile.clear();
        m_graphicsView->clearScene();
        m_currentFrame = 0;
    }
    else
    {
        m_pathImages = path;
        QDir dir(path);
        QStringList filters;
        filters << "*.jpg" << "*.png";
        dir.setNameFilters(filters);
        QFileInfoList listFile = dir.entryInfoList();
        for (int i = 0; i < listFile.size(); ++i)
        {
            QFileInfo fileInfo = listFile.at(i);
            m_listFile.append(fileInfo.fileName());
        }
        std::sort(m_listFile.begin(), m_listFile.end(), compare);
        emit setSlider(0);
        emit maximumSlider(m_listFile.size() - 1);
        drawFrame(0);
    }
}

void Viewer::drawFrame(int frame)
{
    QPixmap image(m_pathImages + m_listFile[frame]);
    m_graphicsView->setFrame(image);
    int realFrame =  m_listFile[frame].split(".")[0].toInt();
    emit frameChanged(realFrame);
}

void Viewer::drawObject(int id, bool keyFrame, int parentFrame,  const QString &text, const QRect &rect, const QColor &color)
{
    m_graphicsView->addRect(id, keyFrame, parentFrame, text, rect, color);
}

void Viewer::prevFrame()
{
    if(m_currentFrame == 0)
        return;
    m_graphicsView->clearScene();
    m_currentFrame--;
    emit setSlider(m_currentFrame);
    drawFrame(m_currentFrame);
}

void Viewer::nextFrame()
{
    if(m_currentFrame == m_listFile.size() - 1)
        return;
    m_graphicsView->clearScene();
    m_currentFrame++;
    drawFrame(m_currentFrame);
    emit setSlider(m_currentFrame);
}

void Viewer::setFrame(int frame)
{
    m_currentFrame = frame;
    drawFrame(m_currentFrame);
}
