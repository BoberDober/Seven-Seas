#ifndef LABELING_H
#define LABELING_H

#include <QDialog>
#include "labelPresenter/labelspresenter.h"
#include "labelPresenter/labelingplayerview.h"
#include "labelPresenter/listlabelsview.h"

//#include "tools/tools.h"
//#include "labelingPlayer/labelingplayer.h"
//#include "labels/labelspresenter.h"
//#include "labels/labels.h"

namespace Ui {
class Labeling;
}

class Labeling : public QDialog
{
    Q_OBJECT
private:
    LabelingPlayerView *m_playerView;
    ListLabelsView *m_listView;
    LabelsPresenter *m_presenter;

//    Tools *m_tools;
//    LabelingPlayer *m_labelingPlayer;
//    LabelsPresenter *m_labelsPresenter;
//    Labels *m_labels;
public:
    explicit Labeling(QWidget *parent = nullptr);
    void openLabeling(const QString &workFolder, const QString &setsName);
    ~Labeling();

private slots:
    void clear();
private:
    Ui::Labeling *ui;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);

    // QDialog interface
public slots:
    void reject();
};

#endif // LABELING_H
