#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoEdit/videoedit.h"
#include "sets/sets.h"
#include "database.h"
#include "dialogs/mainpathdialog.h"
#include "LabelsBase/labelsbase.h"
#include "LabelsBase/labelsbasepresenter.h"
#include "datasets/datasets.h"
#include "datasets/datasetspresenter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    VideoEdit *m_videoEdit;
    Sets *m_sets;
    LabelsBase *m_labelsBase;
    LabelsBasePresenter *m_labelsBasePresenter;
    Datasets *m_datasets;
    DatasetsPresenter *m_datasetsPresenter;

    MainPathDialog *m_mainPathDialog;
    void create();
    void drop();
    void createFolder(const QString& name);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionPath_triggered();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
