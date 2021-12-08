#ifndef LABELSBASE_H
#define LABELSBASE_H

#include <QWidget>
#include "ilabelsbase.h"
#include "tablelabelsbase.h"
#include "addLabelDlg/addlabeldlg.h"

namespace Ui {
class LabelsBase;
}

class LabelsBase : public QWidget, public ILabelsBase
{
    Q_OBJECT

public:
    explicit LabelsBase(QWidget *parent = nullptr);
    ~LabelsBase();

private:
    Ui::LabelsBase *ui;
    TableLabelsBase *m_table;
    AddLabelDlg *m_addlabelDlg;

    // ILabelsBase interface
public:
    void setModel(QStandardItemModel *model);
private slots:
    void on_addBtn_clicked();
signals:
    void acceptAddDlg();
    void deleteItem();
    void editItem();
    // ILabelsBase interface
public:
    QString getNameAddMeaning();
    QString getDescriptionAddMeaning();

    // ILabelsBase interface
public:
    void setReziseToContent();

    // ILabelsBase interface
public:
    QModelIndex getCurrentIndexTable();

    // ILabelsBase interface
public:
    bool getQuestionBox(QString name);

    // ILabelsBase interface
public:
    void addAccept();

    // ILabelsBase interface
public:
    void editLabel(const QString &name, const QString &description);

    // ILabelsBase interface
public:
    QString getOldName();

    // ILabelsBase interface
public:
    void viewMessageBox(const QString& message);
};

#endif // LABELSBASE_H
