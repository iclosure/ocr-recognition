#ifndef JROUNDBUTTON_H
#define JROUNDBUTTON_H

#include "../global.h"
#include "JButton.h"

class JRoundButtonPrivate;

class JWT_EXPORT JRoundButton : public JButton
{
    Q_OBJECT
    Q_PROPERTY(qreal borderRadius READ borderRadius WRITE setBorderRadius NOTIFY borderRadiusChanged)
    Q_PROPERTY(bool autoChecked READ isAutoChecked WRITE setAutoChecked NOTIFY autoCheckedChanged)
public:
    explicit JRoundButton(QWidget *parent = nullptr);
    explicit JRoundButton(const QString &text, QWidget *parent = nullptr);
    JRoundButton(const QString &icon, const QString &text, QWidget *parent = nullptr);
    JRoundButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    ~JRoundButton() J_OVERRIDE;

    qreal borderRadius() const;
    bool isAutoChecked() const;

Q_SIGNALS:
    void borderRadiusChanged(qreal radius);
    void autoCheckedChanged(bool enabled);

public Q_SLOTS:
    void setBorderRadius(qreal radius);
    void setAutoChecked(bool enabled);
    void setImmChecked(bool checked);

protected:
    void nextCheckState() override;

private:
    Q_DISABLE_COPY(JRoundButton)
    J_DECLARE_PRIVATE(JRoundButton)
};

#endif // JROUNDBUTTON_H
