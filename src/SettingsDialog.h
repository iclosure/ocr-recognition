#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "jwt/style/JShadowDialog.h"
#include "jwt/JStorableProxy.h"

class QComboBox;
class QLineEdit;

class SettingsDialog : public JShadowDialog, public JStorableProxy
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() J_OVERRIDE;

    bool init();

Q_SIGNALS:

public Q_SLOTS:
    void accept() override;

    // StorableProxy interface
protected:
    void saveStatus() const override;
    void restoreStatus() override;

private:
    QComboBox *comboType_;
    QLineEdit *editNumber_;
};

#endif  // SETTINGSDIALOG_H
