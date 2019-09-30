#ifndef JLINEEDIT_H
#define JLINEEDIT_H

#include "../global.h"
#include <QLineEdit>

class JLineEditPrivate;

class JWT_EXPORT JLineEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(bool baseLineVisible READ isBaseLineVisible WRITE setBaseLineVisible NOTIFY baseLineVisibleChanged)
public:
    explicit JLineEdit(QWidget *parent = nullptr);
    ~JLineEdit() J_OVERRIDE;

    bool isBaseLineVisible() const;

Q_SIGNALS:
    void baseLineVisibleChanged(bool visible);

public Q_SLOTS:
    void setBaseLineVisible(bool visible);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(JLineEdit)
    J_DECLARE_PRIVATE(JLineEdit)
};

#endif // JLINEEDIT_H
