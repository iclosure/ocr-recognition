#include "AboutDialog.h"
#include "global.h"
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent, Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint)
{
    resize(500, 120);
    setWindowTitle(tr("About"));
    setWindowIcon(QIcon(":/desktop/image/global/help.png"));

    QVBoxLayout *layoutMain = new QVBoxLayout(this);

    QHBoxLayout *layoutTop = new QHBoxLayout();
    layoutMain->addLayout(layoutTop);

    QLabel *labelIcon = new QLabel(this);
    labelIcon->setFixedSize(60, 60);
    labelIcon->setPixmap(QPixmap(":/desktop/image/app.png").scaled(60, 60));
    layoutTop->addWidget(labelIcon);

    layoutTop->addSpacing(10);

    QVBoxLayout *layoutRight = new QVBoxLayout();
    layoutRight->setSpacing(6);
    layoutTop->addLayout(layoutRight);

    QLabel *labelName = new QLabel(tr("Company"), this);
    labelName->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelName->setStyleSheet("font-size:16px;font-weight:bold");
    layoutRight->addWidget(labelName);

    QLabel *labelDetail = new QLabel(tr("Details %1").arg(JMain::instance()->appVersion()), this);
    labelDetail->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    labelDetail->setStyleSheet("font-size:12px;color:#aaa");
    labelDetail->setTextFormat(Qt::RichText);
    layoutRight->addWidget(labelDetail);

    layoutMain->addSpacing(20);

    QPushButton *buttonOk = new QPushButton(tr("Ok"), this);
    buttonOk->setFixedWidth(80);
    layoutMain->addWidget(buttonOk, 0, Qt::AlignRight);

    connect(buttonOk, &QPushButton::clicked, this, &AboutDialog::accept);
}
