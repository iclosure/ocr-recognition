#ifndef JSPINLABEL_H
#define JSPINLABEL_H

#include "../global.h"
#include "../widget/JSpinBox.h"
#include "../widget/JFormFrame.h"

// class JSpinLabel

class JSpinLabelPrivate;

class JWT_EXPORT JSpinLabel : public JFormFrame
{
    Q_OBJECT
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit JSpinLabel(QWidget *parent = nullptr);
    explicit JSpinLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JSpinLabel() J_OVERRIDE;

    JSpinBox *field() const override;

    QString prefix() const;
    QString suffix() const;
    int minimum() const;
    int maximum() const;
    int singleStep() const;
    int value() const;

Q_SIGNALS:
    void valueChanged(int value);

public Q_SLOTS:
    void setPrefix(const QString &text);
    void setSuffix(const QString &text);
    void setMinimum(int value);
    void setMaximum(int value);
    void setRange(int minimum, int maximum);
    void setSingleStep(int value);
    void setValue(int value);

private:
    Q_DISABLE_COPY(JSpinLabel)
    J_DECLARE_PRIVATE(JSpinLabel)
};

// class JDoubleSpinLabel

class JDoubleSpinLabelPrivate;

class JWT_EXPORT JDoubleSpinLabel : public JFormFrame
{
    Q_OBJECT
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(qreal singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit JDoubleSpinLabel(QWidget *parent = nullptr);
    explicit JDoubleSpinLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JDoubleSpinLabel() J_OVERRIDE;

    JDoubleSpinBox *field() const override;

    QString prefix() const;
    QString suffix() const;
    qreal minimum() const;
    qreal maximum() const;
    int decimals() const;
    qreal singleStep() const;
    qreal value() const;

Q_SIGNALS:
    void valueChanged(qreal value);

public Q_SLOTS:
    void setPrefix(const QString &text);
    void setSuffix(const QString &text);
    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setDecimals(int value);
    void setSingleStep(qreal value);
    void setValue(qreal value);

private:
    Q_DISABLE_COPY(JDoubleSpinLabel)
    J_DECLARE_PRIVATE(JDoubleSpinLabel)
};

// class JLargeSpinLabel

class JLargeSpinLabelPrivate;

class JWT_EXPORT JLargeSpinLabel : public JFormFrame
{
    Q_OBJECT
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(qulonglong singleStep READ singleStep WRITE setSingleStep)
    Q_PROPERTY(qulonglong value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit JLargeSpinLabel(QWidget *parent = nullptr);
    explicit JLargeSpinLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JLargeSpinLabel() J_OVERRIDE;

    JLargeSpinBox *field() const override;

    QString prefix() const;
    QString suffix() const;
    qulonglong minimum() const;
    qulonglong maximum() const;
    qulonglong singleStep() const;
    qulonglong value() const;

Q_SIGNALS:
    void valueChanged(qulonglong value);

public Q_SLOTS:
    void setPrefix(const QString &text);
    void setSuffix(const QString &text);
    void setMinimum(qulonglong value);
    void setMaximum(qulonglong value);
    void setRange(qulonglong minimum, qulonglong maximum);
    void setSingleStep(qulonglong value);
    void setValue(qulonglong value);

private:
    Q_DISABLE_COPY(JLargeSpinLabel)
    J_DECLARE_PRIVATE(JLargeSpinLabel)
};

#endif // JSPINLABEL_H
