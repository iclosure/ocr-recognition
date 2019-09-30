#ifndef JSPINBOX_H
#define JSPINBOX_H

#include "../global.h"
#include <QSpinBox>

// - class JSpinBox -

class JSpinBoxPrivate;
class QLineEdit;

class JWT_EXPORT JSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit JSpinBox(QWidget *parent = nullptr);
    ~JSpinBox() J_OVERRIDE;

    int radix() const;
    void setRadix(int value);

    QChar fillChar() const;
    void setFillChar(const QChar &ch);

    QLineEdit *lineEdit() const;
    void setLineEdit(QLineEdit *lineEdit);

    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual QString textFromValue(int value) const override;
    virtual int valueFromText(const QString &text) const override;
    virtual void fixup(QString &str) const override;

    QString textByRadix(int radix = -1) const;

private:
    Q_DISABLE_COPY(JSpinBox)
    J_DECLARE_PRIVATE(JSpinBox)
};

// - class JDoubleSpinBox -

class JDoubleSpinBoxPrivate;

class JWT_EXPORT JDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    Q_PROPERTY(bool autoClearDecimal READ autoClearDecimal WRITE setAutoClearDecimal NOTIFY autoClearDecimalChanged)
public:
    explicit JDoubleSpinBox(QWidget *parent = nullptr);
    ~JDoubleSpinBox() J_OVERRIDE;

    bool autoClearDecimal() const;

    QLineEdit *lineEdit() const;
    void setLineEdit(QLineEdit *lineEdit);

Q_SIGNALS:
    void autoClearDecimalChanged(bool enabled);

public Q_SLOTS:
    void setAutoClearDecimal(bool enabled);

protected:
    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual QString textFromValue(double value) const override;

private:
    Q_DISABLE_COPY(JDoubleSpinBox)
    J_DECLARE_PRIVATE(JDoubleSpinBox)
};

// - class JLargeSinBox -

class JLargeSpinBoxPrivate;

class JWT_EXPORT JLargeSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit JLargeSpinBox(QWidget *parent = nullptr);
    ~JLargeSpinBox() J_OVERRIDE;

    int radix() const;
    void setRadix(int value);

    QChar fillChar() const;
    void setFillChar(const QChar &ch);

    qulonglong value() const;

    qulonglong singleStep() const;
    void setSingleStep(qulonglong value);

    qulonglong minimum() const;
    void setMinimum(qulonglong min);

    qulonglong maximum() const;
    void setMaximum(qulonglong max);

    void setRange(qulonglong min, qulonglong max);

    QLineEdit *lineEdit() const;
    void setLineEdit(QLineEdit *lineEdit);

    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual double valueFromText(const QString &text) const override;
    virtual QString textFromValue(double value) const override;
    virtual void fixup(QString &str) const override;

    QString textByRadix(int radix = -1) const;

Q_SIGNALS:
    void valueChanged(qulonglong);

public Q_SLOTS:
    void setValue(qulonglong value);

private:
    Q_DISABLE_COPY(JLargeSpinBox)
    J_DECLARE_PRIVATE(JLargeSpinBox)
};

#endif // JSPINBOX_H
