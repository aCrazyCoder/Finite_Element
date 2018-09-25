#include "Dialog_AppSetting.h"

Dialog_AppSetting::Dialog_AppSetting()
{
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 96));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(118);
    contentsWidget->setSpacing(10);

    pagesWidget = new QStackedWidget;
    configurationPage = new ConfigurationPage;
    pagesWidget->addWidget(configurationPage);
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new QueryPage);

    createIcons();
    contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget);

    QDialogButtonBox *m_DialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(m_DialogButtonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_DialogButtonBox, SIGNAL(rejected()), this, SLOT(cancelSettings()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(m_DialogButtonBox,0,Qt::AlignRight);
    setLayout(mainLayout);

    setWindowTitle(QString::fromLocal8Bit("软件设置"));
    setWindowIcon(QIcon(":/Image/Image/icon.png"));

}

void Dialog_AppSetting::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/Image/Image/Dialog_setting.png"));
    configButton->setText(QString::fromLocal8Bit("设置"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/Image/Image/Dialog_content.png"));
    updateButton->setText(QString::fromLocal8Bit("内容"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/Image/Image/Dialog_information.png"));
    queryButton->setText(QString::fromLocal8Bit("信息"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget, &QListWidget::currentItemChanged, this, &Dialog_AppSetting::changePage);
}

void Dialog_AppSetting::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void Dialog_AppSetting::cancelSettings()
{
    configurationPage->cancelSettings();

    close();
}
