#ifndef JGAUGE_H
#define JGAUGE_H

#include "../global.h"
#include "../widget/JTitleFrame.h"
#include <QFontMetricsF>

// class JGauge

class JGaugePrivate;

class JWT_EXPORT JGauge : public JTitleFrame
{
    Q_OBJECT
    Q_PROPERTY(int majorTickLength READ majorTickLength WRITE setMajorTickLength NOTIFY majorTickLengthChanged)
    Q_PROPERTY(int majorTickCount READ majorTickCount WRITE setMajorTickCount NOTIFY majorTickCountChanged)
    Q_PROPERTY(int minorTickLength READ minorTickLength WRITE setMinorTickLength NOTIFY minorTickLengthChanged)
    Q_PROPERTY(int minorTickCount READ minorTickCount WRITE setMinorTickCount NOTIFY minorTickCountChanged)
    Q_PROPERTY(qreal angleFrom READ angleFrom WRITE setAngleFrom NOTIFY angleFromChanged)
    Q_PROPERTY(qreal angleTo READ angleTo WRITE setAngleTo NOTIFY angleToChanged)
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString highlightText READ highlightText WRITE setHighlightText NOTIFY highlightTextChanged)
    Q_PROPERTY(QColor highlightTextColor READ highlightTextColor WRITE setHighlightTextColor NOTIFY highlightTextColorChanged)
public:
    enum ThemeStyle {
        LightStyle,
        DarkStyle
    };
    Q_ENUM(ThemeStyle)

    typedef struct _WarningContext {
        qreal from;
        qreal to;
        QColor color;
    } WarningContext;

    typedef struct _PainterContext {
        int majorCount;
        int scale;
        qreal side;
        QRectF area;
        qreal radius;
        qreal minimum;
        qreal maximum;
        qreal range;
        qreal valueAngle;
    } PainterContext;

    explicit JGauge(QWidget *parent = nullptr);
    explicit JGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JGauge() J_OVERRIDE;

    int majorTickLength() const;
    int majorTickCount() const;
    int minorTickLength() const;
    int minorTickCount() const;
    qreal angleFrom() const;
    qreal angleTo() const;

    qreal minimum() const;
    qreal maximum() const;
    qreal value() const;
    int decimals() const;
    QString suffix() const;

    QColor color() const;

    QString highlightText() const;
    QColor highlightTextColor() const;

    void addWarningRange(int id, qreal from, qreal to, const QColor &color);
    void removeWarningRange(int id);
    const QMap<int, WarningContext> &warnRanges() const;

    static qreal fromCoordAngle(qreal angle);
    static qreal toCoordAngle(qreal angle);

    int autoScaled(qreal &new_start, qreal &new_stop, qreal start, qreal stop, int intervals);
    static int autoScaled(qreal &new_start, qreal &new_stop, qreal start, qreal stop, int intervals,
                          const std::vector<qreal> &sortedMantissi);
    QColor colorAtWarnRange(const PainterContext *context, qreal value) const;

    qreal valueToAngle(const PainterContext *context, qreal value) const;

Q_SIGNALS:
    void majorTickLengthChanged(int value);
    void majorTickCountChanged(int value);
    void minorTickLengthChanged(int value);
    void minorTickCountChanged(int value);
    void tickChanged(int majorTickLength, int minorTickLength, int minorTickCount);
    void angleFromChanged(qreal value);
    void angleToChanged(qreal value);
    void angleChanged(qreal from, qreal to);

    void minimumChanged(qreal value);
    void maximumChanged(qreal value);
    void rangeChanged(qreal minimum, qreal maximum);
    void valueChanged(qreal value);
    void decimalsChanged(int value);
    void suffixChanged(const QString &text);

    void colorChanged(const QColor &color);

    void highlightTextChanged(const QString &text);
    void highlightTextColorChanged(const QColor &color);

public Q_SLOTS:
    void setMajorTickLength(int value);
    void setMajorTickCount(int value);
    void setMinorTickLength(int value);
    void setMinorTickCount(int value);
    void setTick(int majorTickLength, int minorTickLength, int minorTickCount);
    void setAngleFrom(qreal value);
    void setAngleTo(qreal value);
    void setAngleRange(qreal from, qreal to);

    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setValue(qreal value, bool animation = false);
    void setDecimals(int value);
    void setSuffix(const QString &text);

    void setColor(const QColor &color);

    void setHighlightText(const QString &text);
    void setHighlightTextColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void drawTitle(QPainter *painter, const PainterContext *context);
    virtual void drawBackground(QPainter *painter, const PainterContext *context);
    virtual void drawScale(QPainter *painter, const PainterContext *context);
    virtual void drawNeedle(QPainter *painter, const PainterContext *context);
    virtual void drawValue(QPainter *painter, const PainterContext *context);

private:
    Q_DISABLE_COPY(JGauge)
    J_DECLARE_PRIVATE(JGauge)
};

#endif  // JGAUGE_H
