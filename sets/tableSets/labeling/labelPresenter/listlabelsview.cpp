#include "listlabelsview.h"
#include "ui_listlabelsview.h"
#include <QVBoxLayout>
#include <QQmlContext>
#include <QDebug>

ListLabelsView::ListLabelsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListLabelsView)
{
    ui->setupUi(this);
    m_createLabelDlg = new CreateLabelDlg(this);
    m_createLabelDlgPresenter = new CreateLabelDlgPresenter(m_createLabelDlg);
    m_listEngine = new ListLabelsEngine(this);

    connect(m_createLabelDlgPresenter, SIGNAL(acceptCreate(QString, QPoint)), this, SIGNAL(acceptCreate(QString, QPoint)));
    connect(m_listEngine, SIGNAL(itemDeleted(int, int)), this, SIGNAL(acceptDelete(int, int)));
    connect(m_listEngine, SIGNAL(itemClosed(int)), this, SIGNAL(frameClose(int)));
    QQmlContext *ctxt = ui->quickWgt->rootContext();
    ctxt->setContextProperty("engine", m_listEngine);
    ui->quickWgt->setSource(QUrl("qrc:/qml/qml/listLabels.qml"));
}

ListLabelsView::~ListLabelsView()
{
    delete ui;
}

void ListLabelsView::setModel(QList<QObject*> model)
{
    m_listEngine->setModel(model);
}

void ListLabelsView::on_addBtn_clicked()
{
    m_createLabelDlgPresenter->openDialog(QPoint(0, 0));
}

void ListLabelsView::addLabel(const QPoint &point)
{
    m_createLabelDlgPresenter->openDialog(point);
}
