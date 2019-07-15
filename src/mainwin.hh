#ifndef MAINWIN_HH
#define MAINWIN_HH

#include <QMainWindow>
#include <QDialog>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <QStringListModel>
#include <QCompleter>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QListWidget>
#include <QFile>
#include <QCheckBox>
#include <QToolButton>
#include <memory>
#include "public.hh"

#define APPNAME  "labelassist"

class CLabelDialog : public QDialog
{
public:
    CLabelDialog(QStringList listItem, QString text = "Enter object label",QWidget *parent = 0);
    ~CLabelDialog();
public slots:
    void PostProcess();
    void Validate();
    void ListItemClick(QListWidgetItem *item);
    void ListItemDoubleClick(QListWidgetItem *item);

private:
    std::shared_ptr<QLineEdit> m_iEdit;
    std::shared_ptr<QStringListModel> m_iModel;
    std::shared_ptr<QCompleter> m_iCompleter;
    QVBoxLayout* m_iLayout;
    std::shared_ptr<QDialogButtonBox> m_iButtonBox;
    std::shared_ptr<QListWidget> m_iListWidget;
};

class CMainWin : public QMainWindow
{
    Q_OBJECT

public:
    CMainWin(QString defaultFilename = "", QString defaultPrefdefClassFile = "", QString defaultSaveDir = "",QWidget *parent = 0);
    ~CMainWin();
public slots:
    void Diffcult_State_Changed(int state);

private:
    void __LoadPredefinedClasses(QString predefClassesFile);

private:
    QString m_cDefaultSaveDir;
    bool m_bUsingPascalVocFormat;
    bool m_bUsingYoloFormat;
    QStringList m_LabelHist;
    std::shared_ptr<CLabelDialog> m_iLabelDialog;
    QVBoxLayout* m_iListLayout;
    std::shared_ptr<QCheckBox> m_iUseDefaultLabelCheckbox;
    std::shared_ptr<QLineEdit> m_iDefaultLabelTextLine;
    QHBoxLayout* m_iUseDefaultLblLayout;
    std::shared_ptr<QWidget> m_iUseDefaultLblContainer;
    std::shared_ptr<QCheckBox> m_iDiffcultBtn;
    std::shared_ptr<QToolButton> m_iEditButton;
    std::shared_ptr<QListWidget> m_iLabelList;
    std::shared_ptr<QWidget> m_iLabelListContainer;
};

#endif // MAINWIN_HH
