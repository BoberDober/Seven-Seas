#include "datasetspresenter.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>

#include "mainsettings.h"
#include "../utils/progressdlg.h"

DatasetsPresenter::DatasetsPresenter(IDatasets *view, QObject *parent) : QObject(parent)
{
    m_view = view;
    m_model = new DatasetsModel(this);

    QObject *obj = dynamic_cast<QObject*>(m_view);
    QObject::connect(obj, SIGNAL(updateDatasetModel()), this, SLOT(updateListModel()));
    QObject::connect(obj, SIGNAL(exportDataset()), this, SLOT(exportDataset()));
    QObject::connect(obj, SIGNAL(deleteDataset()), this, SLOT(deleteDataset()));
    QObject::connect(obj, SIGNAL(exportDetector(QString, QString)), this, SLOT(exportDetector(QString, QString)));
    QObject::connect(obj, SIGNAL(exportClassifier(QString, QString)), this, SLOT(exportClassifier(QString, QString)));

    updateListModel();
}

QDomElement DatasetsPresenter::makeElementCustom(QDomDocument& domDoc, const QString& strName, const QString& strText)
{
    QDomElement domElement = domDoc.createElement(strName);

    QDomText domText = domDoc.createTextNode(strText);
    domElement.appendChild(domText);

    return domElement;
}

void DatasetsPresenter::savingDetectorDataset(Progress::Ptr progress, IError::Ptr error, const QString& finalDestination, const QString& name)
{
    ProgressLocker locker(progress);
    progress->setStage(0);
    QDir().mkdir(finalDestination);
    QDir().mkdir(finalDestination + "img");
    QDir().mkdir(finalDestination + "annot");

    QVector<int> listID = m_model->getListID(name);

    progress->setProgress(100);
    progress->setStage(1);

    for(int i = 0; i < listID.size(); i++)
    {
        LabelData label = m_model->getLabel(listID.at(i), i);

        QString source = MainSettings::getInstance().getWorkFolder() + QDir::separator() + "Sets" + QDir::separator() + m_model->getSetName(label.id_set) + QDir::separator() + "img" + QDir::separator() + QString::number(label.frame) + ".jpg";
        QString dstImg = finalDestination + "img" + QDir::separator() + QString::number(label.count) + ".jpg";
        QString dstAnnot = finalDestination + "annot" + QDir::separator();

        if (!QFile::exists(source))
        {
            qDebug() << "Файла не существует!";
        }
        else
        {
            QImage img(source);
            ImageInfo imageInfo;
            imageInfo.width = img.width();
            imageInfo.height = img.height();
            imageInfo.depth = img.depth();

            QFile::copy(source, dstImg);
            saveXML(imageInfo, dstAnnot, label);
        }
        progress->setProgress(qRound(double(i)/double(listID.size())*100));
    }
    progress->setProgress(100);
    locker.setExitCode(0);
}

void DatasetsPresenter::savingClassifierDataset(Progress::Ptr progress, IError::Ptr error, const QString &finalDestination, const QString &name)
{
    //    QImage image("/media/hdd/dataset/winter_day_1_5/dataset/train-images/0.jpg");
    //    QImage copy;
    //    copy = image.copy(824, 293, 885-824, 349-293);
    //    copy.save("/home/ppronin/cropped_image.jpg");

    ProgressLocker locker(progress);
    progress->setStage(0);
    QDir().mkdir(finalDestination);

    QVector<int> listID = m_model->getListID(name);

    progress->setProgress(100);
    progress->setStage(1);

    QHash<QString, int> hash;
    int count = 0;
    for(int i = 0; i < listID.size(); i++)
    {
        LabelData label = m_model->getLabel(listID.at(i), i);
        if (!hash.contains(label.name))
        {
            qDebug() << label.name;
            hash.insert(label.name, count);
            QDir().mkdir(finalDestination + QDir::separator() + QString::number(count));
            count++;
        }

        QString source = MainSettings::getInstance().getWorkFolder() + QDir::separator() + "Sets" + QDir::separator() + m_model->getSetName(label.id_set) + QDir::separator() + "img" + QDir::separator() + QString::number(label.frame) + ".jpg";
        QImage image(source);
        QImage copy;
        copy = image.copy(label.x, label.y, label.w, label.h);
        copy.save(finalDestination + QDir::separator() + QString::number(hash.value(label.name)) + QDir::separator() + QString::number(i) + ".jpg");
        progress->setProgress(qRound(double(i)/double(listID.size())*100));
    }
    progress->setProgress(100);
    locker.setExitCode(0);

}

void DatasetsPresenter::prepareExport()
{

}

void DatasetsPresenter::saveXML(const ImageInfo& imageInfo, const QString& path, const LabelData& label)
{
    QDomDocument doc("SevenSeas");

    QDomElement  rootElement = doc.createElement("annotation");
    doc.appendChild(rootElement);
    rootElement.appendChild(makeElementCustom(doc, "filename", QString::number(label.count) + ".jpg"));

    QDomElement  sizeElement = doc.createElement("size");
    rootElement.appendChild(sizeElement);
    sizeElement.appendChild(makeElementCustom(doc, "width", QString::number(imageInfo.width)));
    sizeElement.appendChild(makeElementCustom(doc, "height", QString::number(imageInfo.height)));
    sizeElement.appendChild(makeElementCustom(doc, "depth", QString::number(imageInfo.depth)));

    QDomElement  objectElement = doc.createElement("object");

    rootElement.appendChild(objectElement);
    objectElement.appendChild(makeElementCustom(doc, "name", label.name));
    objectElement.appendChild(makeElementCustom(doc, "pose", "Unspecified"));
    objectElement.appendChild(makeElementCustom(doc, "truncated", "0"));
    objectElement.appendChild(makeElementCustom(doc, "difficult", "0"));

    QDomElement  bndboxElement = doc.createElement("bndbox");

    objectElement.appendChild(bndboxElement);
    bndboxElement.appendChild(makeElementCustom(doc, "xmin", QString::number(label.x)));
    bndboxElement.appendChild(makeElementCustom(doc, "ymin", QString::number(label.y)));
    bndboxElement.appendChild(makeElementCustom(doc, "xmax", QString::number(label.x + label.w)));
    bndboxElement.appendChild(makeElementCustom(doc, "ymax", QString::number(label.y + label.h)));

    QFile file(path + QString::number(label.count) + ".xml");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream(&file) << doc.toString();
        file.close();
    }
}

void DatasetsPresenter::updateListModel()
{
    m_view->setModel(m_model->updateTableModel());
}

void DatasetsPresenter::exportDataset()
{
    QStandardItem *item = m_model->tableModel()->itemFromIndex(m_model->tableModel()->index(m_view->getCurrentIndexTable().row(), 0));
    if(!item)
    {
        return;
    }

    m_view->exportDlgOpen(item->text());
}

void DatasetsPresenter::deleteDataset()
{
    QStandardItem *item = m_model->tableModel()->itemFromIndex(m_model->tableModel()->index(m_view->getCurrentIndexTable().row(), 0));
    if(!item)
    {
        return;
    }
    QString name = item->text();
    if(!m_view->accessDelete(name))
    {
        return;
    }
    m_model->deleteDatasetCollect(name);
    updateListModel();
}

void DatasetsPresenter::exportDetector(const QString &destination, const QString& name)
{
    if(!QDir(destination).exists())
    {
        m_view->openMessageBox("Выбран неверный путь!");
        return;
    }
    QString finalDestination = destination + QDir::separator() + name + "_detector" + QDir::separator();
    qDebug() << finalDestination << name;
    if(QDir(finalDestination).exists())
    {
        if(!m_view->questionBox(name + " уже существует, удалить?"))
        {
            return;
        }
        QDir(finalDestination).removeRecursively();
    }

    QStringList stages =
    {
        tr("Подготовка"),
        tr("Сохранение аннотаций"),
    };

    IError::Ptr error = ErrorBase::create();
    Progress::Ptr progress = Progress::create(tr("Создание набора"), stages);
    QFuture<void> future = QtConcurrent::run(this, &DatasetsPresenter::savingDetectorDataset, progress, error, finalDestination, name);
    m_watcher.setFuture(future);
    ProgressDlg dlg(progress);
    dlg.exec();

    if(error->hasError())
    {
        qDebug() << "Ошибка потока";
    }
}

void DatasetsPresenter::exportClassifier(const QString &destination, const QString &name)
{
    if(!QDir(destination).exists())
    {
        m_view->openMessageBox("Выбран неверный путь!");
        return;
    }
    QString finalDestination = destination + QDir::separator() + name + "_classifier" + QDir::separator();
    qDebug() << finalDestination << name;
    if(QDir(finalDestination).exists())
    {
        if(!m_view->questionBox(name + " уже существует, удалить?"))
        {
            return;
        }
        QDir(finalDestination).removeRecursively();
    }

    QStringList stages =
    {
        tr("Подготовка"),
        tr("Сохранение аннотаций"),
    };
    IError::Ptr error = ErrorBase::create();
    Progress::Ptr progress = Progress::create(tr("Создание набора"), stages);
    QFuture<void> future; QtConcurrent::run(this, &DatasetsPresenter::savingClassifierDataset, progress, error, finalDestination, name);
    m_watcher.setFuture(future);
    ProgressDlg dlg(progress);
    dlg.exec();

    if(error->hasError())
    {
        qDebug() << "Ошибка потока";
    }
}

