#include "mainwin.hh"

CLabelDialog::CLabelDialog(QStringList listItem, QString text, QWidget *parent)
{
    m_iEdit = std::make_shared<QLineEdit>(this);
    m_iEdit->setText(text);
    m_iEdit->setValidator(new QRegExpValidator(QRegExp("^[^ \t].+"), this));
    connect(m_iEdit.get(), SIGNAL(editingFinished()), this, SLOT(PostProcess()));

    m_iModel = std::make_shared<QStringListModel>();
    m_iModel->setStringList(listItem);
    m_iCompleter = std::make_shared<QCompleter>();
    m_iCompleter->setModel(m_iModel.get());
    m_iEdit->setCompleter(m_iCompleter.get());

    m_iLayout = new QVBoxLayout();
    m_iLayout->addWidget(m_iEdit.get());
    m_iButtonBox = std::make_shared<QDialogButtonBox>(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    m_iButtonBox->button(QDialogButtonBox::Ok)->setIcon(QIcon(":/icons/done.png"));
    m_iButtonBox->button(QDialogButtonBox::Cancel)->setIcon(QIcon(":/icons/undo.png"));
    connect(m_iButtonBox.get(), SIGNAL(accepted()), this, SLOT(Validate()));
    connect(m_iButtonBox.get(), SIGNAL(rejected()), this, SLOT(rejected()));
    m_iLayout->addWidget(m_iButtonBox.get());

    if(!listItem.empty() and listItem.length() > 0){
        m_iListWidget = std::make_shared<QListWidget>(this);
        foreach(const QString &item, listItem){
            m_iListWidget->addItem(item);
        }
        connect(m_iListWidget.get(), SIGNAL(itemClicked(QListWidgetItem *item)), this, SLOT(ListItemClick(QListWidgetItem *item)));
        connect(m_iListWidget.get(), SIGNAL(itemDoubleClicked(QListWidgetItem *item)), this, SLOT(ListItemDoubleClick(QListWidgetItem *item)));
        m_iLayout->addWidget(m_iListWidget.get());
    }
    setLayout(m_iLayout);
}

CLabelDialog::~CLabelDialog()
{

}

void CLabelDialog::PostProcess()
{
    m_iEdit->setText(m_iEdit->text().trimmed());
}

void CLabelDialog::Validate(){
    QString content = m_iEdit->text();
    if(!content.trimmed().isEmpty()){
        accept();
    }
}

void CLabelDialog::ListItemClick(QListWidgetItem *item){
    QString text = item->text().trimmed();
    m_iEdit->setText(text);
}

void CLabelDialog::ListItemDoubleClick(QListWidgetItem *item){
    ListItemClick(item);
    Validate();
}

CMainWin::CMainWin(QString defaultFilename, QString defaultPrefdefClassFile, QString defaultSaveDir, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(APPNAME);

    // Save as Pascal voc xml
    m_cDefaultSaveDir = defaultSaveDir;
    m_bUsingPascalVocFormat = true;
    m_bUsingYoloFormat = false;

    // Load predefined classes to the list
    __LoadPredefinedClasses(defaultPrefdefClassFile);

    // Main widgets and related state.
    m_iLabelDialog = std::make_shared<CLabelDialog>(m_LabelHist);
    m_iListLayout = new QVBoxLayout();
    m_iListLayout->setContentsMargins(0, 0, 0, 0);

    // Create a widget for using default label
    m_iUseDefaultLabelCheckbox = std::make_shared<QCheckBox>(tr("Use Default Label"));
    m_iUseDefaultLabelCheckbox->setChecked(false);
    m_iDefaultLabelTextLine = std::make_shared<QLineEdit>();
    m_iUseDefaultLblLayout = new QHBoxLayout();
    m_iUseDefaultLblLayout->addWidget(m_iUseDefaultLabelCheckbox.get());
    m_iUseDefaultLblLayout->addWidget(m_iDefaultLabelTextLine.get());
    m_iUseDefaultLblContainer = std::make_shared<QWidget>();
    m_iUseDefaultLblContainer->setLayout(m_iUseDefaultLblLayout);

    // Create a widget for edit and diffc button
    m_iDiffcultBtn = std::make_shared<QCheckBox>(tr("difficult"));
    m_iDiffcultBtn->setChecked(false);
    connect(m_iDiffcultBtn.get(), SIGNAL(stateChanged(int state)), this, SLOT(Diffcult_State_Changed(int state)));
    m_iEditButton = std::make_shared<QToolButton>();
    m_iEditButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    // Add some of widgets to listLayout
    m_iListLayout->addWidget(m_iEditButton.get());
    m_iListLayout->addWidget(m_iDiffcultBtn.get());
    m_iListLayout->addWidget(m_iUseDefaultLblContainer.get());

    // Create and add a widget for showing current label items
    m_iLabelList = std::make_shared<QListWidget>();
    m_iLabelListContainer = std::make_shared<QWidget>();
    m_iLabelListContainer->setLayout(m_iListLayout);
    m_iLabelList->itemActivated.connect(self.labelSelectionChanged)
    m_iLabelList->itemSelectionChanged.connect(self.labelSelectionChanged)
    m_iLabelList->itemDoubleClicked.connect(self.editLabel)
    # Connect to itemChanged to detect checkbox changes.
    self.labelList.itemChanged.connect(self.labelItemChanged)
    listLayout.addWidget(self.labelList)
}

CMainWin::~CMainWin()
{

}

void CMainWin::Diffcult_State_Changed(int state)
{

}

void CMainWin::__LoadPredefinedClasses(QString predefClassesFile)
{
    QFile classesFile(predefClassesFile);
    if(classesFile.exists()){
        if (!classesFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            return;
        }

        QTextStream in(&classesFile);
        QString line = in.readLine();
        while (!line.isNull()) {
            m_LabelHist << line;
            line = in.readLine();
        }
    }
}
