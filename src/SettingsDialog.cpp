#include "SettingsDialog.h"
#include "jwt/widget/JGroupBox.h"
#include "jwt/widget/JRoundButton.h"
#include "global.h"
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>

SettingsDialog::SettingsDialog(QWidget *parent)
    : JShadowDialog(parent, Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
    , JStorableProxy(QLatin1String("settings"))
{
    resize(600, 200);

    QVBoxLayout *layoutMain = new QVBoxLayout(centralWidget());

    JGroupBox *groupMain = new JGroupBox(tr("Settings"), this);
    layoutMain->addWidget(groupMain);

    QFormLayout *layoutSettings = new QFormLayout(groupMain);
    layoutSettings->setLabelAlignment(Qt::AlignRight);

    comboType_ = new QComboBox(groupMain);
    layoutSettings->addRow(tr("Select Type:"), comboType_);

    editNumber_ = new QLineEdit(groupMain);
    layoutSettings->addRow(tr("Input Number:"), editNumber_);

    QHBoxLayout *layoutButton = new QHBoxLayout();
    layoutMain->addLayout(layoutButton);

    layoutButton->addStretch();

    JRoundButton *buttonOk = new JRoundButton(tr("Ok"), this);
    buttonOk->setMinimumWidth(150);
    layoutButton->addWidget(buttonOk);

    layoutButton->addSpacing(10);

    JRoundButton *buttonCancel = new JRoundButton(tr("Cancel"), this);
    buttonCancel->setMinimumWidth(150);
    layoutButton->addWidget(buttonCancel);

    layoutButton->addStretch();

    connect(buttonOk, &JRoundButton::clicked, this, [=](){
        this->accept();
    });
    connect(buttonCancel, &JRoundButton::clicked, this, [=](){
        this->reject();
    });
}

SettingsDialog::~SettingsDialog()
{

}

bool SettingsDialog::init()
{
    bool result = true;

    // product type

    comboType_->clear();

    const Json::Value productTypeJson = JMain::instance()->config(QLatin1String("ocr.info.product_types"));
    if (!productTypeJson.isArray()) {
        return false;
    }

    for (Json::ArrayIndex i = 0; i < productTypeJson.size(); ++i) {
        const Json::Value &itemJson = productTypeJson[i];
        if (!itemJson.isMember("name")) {
            continue;
        }
        const QString name = QString::fromStdString(itemJson["name"].asString()).trimmed();
        if (name.isEmpty()) {
            continue;
        }
        comboType_->addItem(name);
    }

    restoreStatus();

    return result;
}

void SettingsDialog::accept()
{
    if (comboType_->currentIndex() == -1) {
        return;
    }

    const QString number = editNumber_->text().trimmed();
    if (number.isEmpty()) {
        editNumber_->setFocus();
        editNumber_->selectAll();
        return;
    }

    JMain::instance()->setProductType(comboType_->currentText());

    JMain::instance()->setProductNumber(number);

    saveStatus();

    JShadowDialog::accept();
}

void SettingsDialog::saveStatus() const
{
    writeValue(QLatin1String("product-type"), comboType_->currentIndex());
    writeValue(QLatin1String("product-number"), editNumber_->text().trimmed());
}

void SettingsDialog::restoreStatus()
{
    comboType_->setCurrentIndex(readValue<int>(QLatin1String("product-type")));
    editNumber_->setText(readValue<QString>(QLatin1String("product-number")));
}
