#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlRecord>
#include <QDir>
#include "mainsettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!QDir(MainSettings::getInstance().getWorkFolder()).exists())
    {
        QDir().mkdir(MainSettings::getInstance().getWorkFolder());
    }

    createFolder("Sets");
    createFolder("Video");

    if(!Database::getInstance().openDB("QSQLITE", MainSettings::getInstance().getWorkFolder() + "/sevenSeas_bd.sqlite"))
    {
        qDebug() << "MarkupDb fail open sqlite db:" << Database::getInstance().getDBError();
    }

//    drop();
    create();

    m_videoEdit = new VideoEdit(this);
    QVBoxLayout *videoEditLayout = new QVBoxLayout();
    videoEditLayout->addWidget(m_videoEdit);
    ui->videoEditWidget->setLayout(videoEditLayout);

    m_sets = new Sets(this);
    QVBoxLayout *setsLayout = new QVBoxLayout();
    setsLayout->addWidget(m_sets);
    ui->setsWidget->setLayout(setsLayout);

    QVBoxLayout *labelsBaseLayout = new QVBoxLayout();
    m_labelsBase = new LabelsBase(this);
    m_labelsBasePresenter = new LabelsBasePresenter(m_labelsBase, this);
    labelsBaseLayout->addWidget(m_labelsBase);
    ui->labelsBaseWidget->setLayout(labelsBaseLayout);

    QVBoxLayout *datasetsLayout = new QVBoxLayout();
    m_datasets = new Datasets(this);
    m_datasetsPresenter = new DatasetsPresenter(m_datasets, this);
    datasetsLayout->addWidget(m_datasets);
    ui->datasetsWidget->setLayout(datasetsLayout);

    m_mainPathDialog = new MainPathDialog(this);
}

void MainWindow::create()
{
    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS prefixs ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "name TEXT"
                                        ");");
    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS videos ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "name TEXT,"
                                        "path TEXT"
                                        ");");
    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS treeVideo ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "id_prefix INT,"
                                        "id_video INT"
                                        ");");
    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS sets ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "name TEXT UNIQUE NOT NULL, "
                                        "frames INT NOT NULL, "
                                        "quality INT NOT NULL CHECK (quality >= 0),"
                                        "date TEXT NOT NULL, "
                                        "description TEXT NOT NULL"
                                        ");");
    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS labels ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "id_set INTEGER NOT NULL, "
                                        "x INTEGER NOT NULL, "
                                        "y INTEGER NOT NULL, "
                                        "w INTEGER NOT NULL, "
                                        "h INTEGER NOT NULL, "
                                        "frame INTEGER NOT NULL, "
                                        "id_label INTEGER NOT NULL, "
                                        "keyFrame BOOLEAN NOT NULL, "
                                        "parentFrame INTEGER NOT NULL, "
                                        "noFrame BOOLEAN NOT NULL, "
                                        "import BOOLEAN DEFAULT 0"
                                        ");");

//    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS elements ("
//                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
//                                        "name TEXT NOT NULL, "
//                                        "description TEXT NOT NULL"
//                                        ");");

    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS meanings ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "name TEXT NOT NULL, "
//                                        "element_id INTEGER NOT NULL, "
                                        "description TEXT NOT NULL"
                                        ");");

    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS datasets ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "name TEXT NOT NULL, "
                                        "date TEXT NOT NULL, "
                                        "description TEXT NOT NULL"
                                        ");");

    Database::getInstance().createTable("CREATE TABLE IF NOT EXISTS datasetLabels ("
                                        "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                                        "id_dataset INTEGER NOT NULL, "
                                        "id_label INTEGER NOT NULL"
                                        ");");
}

void MainWindow::drop()
{
    Database::getInstance().prepare("DROP TABLE IF EXISTS prefixs;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS videos;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS treeVideo;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS sets;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS labels;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS elements;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS meanings;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS datasets;").del();
    Database::getInstance().prepare("DROP TABLE IF EXISTS datasetLabels;").del();
}

void MainWindow::createFolder(const QString &name)
{
    if(!QDir(MainSettings::getInstance().getWorkFolder() + QDir::separator() + name + QDir::separator()).exists())
    {
        QDir().mkdir(MainSettings::getInstance().getWorkFolder() + QDir::separator() + name + QDir::separator());
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPath_triggered()
{
    m_mainPathDialog->open();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index)
    {
    case 6:
        m_labelsBasePresenter->updateModel();
        break;
    }

}
