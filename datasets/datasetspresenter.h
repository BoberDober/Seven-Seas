#ifndef DATASETSPRESENTER_H
#define DATASETSPRESENTER_H

#include <QObject>
#include <QtXml>
#include "datasetsmodel.h"
#include "idatasets.h"
#include <QtConcurrent>
#include "../utils/progress.h"
#include "../utils/errorhandling.h"

struct ImageInfo {
    int width;
    int height;
    int depth;
};

class DatasetsPresenter : public QObject
{
    Q_OBJECT
private:
    IDatasets *m_view;
    DatasetsModel *m_model;    
    QFutureWatcher<void> m_watcher;
    QDomElement makeElementCustom(QDomDocument& domDoc, const QString& strName, const QString& strText);
    void savingDetectorDataset(Progress::Ptr progress, IError::Ptr error, const QString& finalDestination, const QString& name);
    void savingClassifierDataset(Progress::Ptr progress, IError::Ptr error, const QString& finalDestination, const QString& name);

    void prepareExport();

public:
    explicit DatasetsPresenter(IDatasets *view, QObject *parent = nullptr);
    void saveXML(const ImageInfo &imageInfo, const QString &path, const LabelData& label);

signals:

public slots:

private slots:
    void updateListModel();
    void exportDataset();
    void deleteDataset();
    void exportDetector(const QString& destination, const QString &name);
    void exportClassifier(const QString& destination, const QString &name);
};

#endif // DATASETSPRESENTER_H
