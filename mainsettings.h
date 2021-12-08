#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QObject>
#include <QSettings>

#define ORGANIZATION_NAME "LIGHTHILL"
#define APPLICATION_NAME "SevenSeas"

struct MainOptions
{
    QString workFolder;
};

class MainSettings : public QObject
{
    Q_OBJECT
public:
    static MainSettings& getInstance();
    void setWorkFolder(QString value);
    QString getWorkFolder();
private:
    explicit MainSettings(QObject *parent = nullptr);
    ~MainSettings();
    MainSettings(MainSettings const&) = delete;
    MainSettings& operator= (MainSettings const&) = delete;
    void saveConfig();
    void loadConfig();
    QSettings *m_settings;
    QString m_pathFile;
    MainOptions *m_mainOptions;
signals:

public slots:
};

#endif // MAINSETTINGS_H
