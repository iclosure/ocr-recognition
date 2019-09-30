#ifndef JSLIDERBAR_H
#define JSLIDERBAR_H

#include "../global.h"
#include "../widget/JTitleFrame.h"

// class JSliderBar

class JSliderBarPrivate;

class JWT_EXPORT JSliderBar : public JTitleFrame
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)
    Q_PROPERTY(qreal singleStep READ singleStep WRITE setSingleStep NOTIFY singleStepChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit JSliderBar(QWidget *parent = nullptr);
    explicit JSliderBar(const QString &title, QWidget *parent = nullptr);
    virtual ~JSliderBar() J_OVERRIDE;

    qreal minimum() const;
    qreal maximum() const;
    QString suffix() const;
    int decimals() const;
    qreal singleStep() const;
    qreal value() const;

    void setReadOnly(bool editable);

Q_SIGNALS:
    void minimumChanged(qreal value);
    void maximumChanged(qreal value);
    void rangeChanged(qreal minimum, qreal maximum);
    void suffixChanged(const QString &text);
    void decimalsChanged(int count);
    void singleStepChanged(qreal step);
    void valueChanged(qreal value);

public Q_SLOTS:
    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setSuffix(const QString &text);
    void setDecimals(int count);
    void setSingleStep(qreal step);
    void setValue(qreal value);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    Q_DISABLE_COPY(JSliderBar)
    J_DECLARE_PRIVATE(JSliderBar)
};

#endif  // JSLIDERBAR_H
