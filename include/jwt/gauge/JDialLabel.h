#ifndef JDIALLABEL_H
#define JDIALLABEL_H

#include "../global.h"
#include "JWidgetLabel.h"
#include <QDial>

// class JDialLabel

class JDialLabelPrivate;

class JWT_EXPORT JDialLabel : public JWidgetLabel
{
    Q_OBJECT
    Q_PROPERTY(qreal from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(qreal to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(qreal stepSize READ stepSize WRITE setStepSize NOTIFY stepSizeChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix)
    Q_PROPERTY(int fieldWidth READ fieldWidth WRITE setFieldWidth)
    Q_PROPERTY(bool wrap READ wrap WRITE setWrap)
public:
    explicit JDialLabel(QWidget *parent = nullptr);
    explicit JDialLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JDialLabel() J_OVERRIDE;

    qreal from() const;
    qreal to() const;
    qreal stepSize() const;
    qreal value() const;
    int decimals() const;
    QString suffix() const;
    int fieldWidth() const;
    bool wrap() const;

    QDial *dial() const;

Q_SIGNALS:
    void fromChanged(qreal value);
    void toChanged(qreal value);
    void stepSizeChanged(qreal value);
    void valueChanged(qreal value);

public Q_SLOTS:
    void setFrom(qreal value);
    void setTo(qreal value);
    void setRange(qreal from, qreal to);
    void setStepSize(qreal value);
    void setValue(qreal value);
    void setDecimals(int decimals);
    void setSuffix(const QString &text);
    void setFieldWidth(int width);
    void setWrap(bool wrap);

private:
    Q_DISABLE_COPY(JDialLabel)
    J_DECLARE_PRIVATE(JDialLabel)
};

#endif  // JDIALLABEL_H
