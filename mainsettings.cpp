#include "mainsettings.h"
#include <QDebug>
#include <QDir>

MainSettings &MainSettings::getInstance()
{
    static MainSettings instance;
    return instance;
}

void MainSettings::saveConfig()
{
    m_settings->beginGroup("MainSettings");
    m_settings->setValue("workFolder", m_mainOptions->workFolder);
    m_settings->endGroup();
}

void MainSettings::loadConfig()
{
    m_settings->beginGroup("MainSettings");
    m_mainOptions->workFolder = m_settings->value("workFolder", QDir::homePath() + QDir::separator() + "SevenSeas").toString();
    m_settings->endGroup();
}

void MainSettings::setWorkFolder(QString value)
{
    m_mainOptions->workFolder = value;
}

QString MainSettings::getWorkFolder()
{
    return m_mainOptions->workFolder;
}

MainSettings::MainSettings(QObject *parent) : QObject(parent)
{
    m_pathFile = QDir::homePath() + QDir::separator() + "Documents" + QDir::separator() + "SevenSeasSettings.ini";
    m_settings = new QSettings(m_pathFile, QSettings::IniFormat, this);
    m_mainOptions = new MainOptions();
    loadConfig();
}

MainSettings::~MainSettings()
{
    saveConfig();
}
