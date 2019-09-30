#ifndef JDIALGAUGE_H
#define JDIALGAUGE_H

#include "../global.h"
#include "../widget/JTitleFrame.h"
#include <QFontMetricsF>

// class JDialGauge

class JDialGaugePrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JDialGauge : public JTitleFrame
{
    Q_OBJECT
    Q_PROPERTY(qreal minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(qreal maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(bool valueVisible READ isValueVisible WRITE setValueVisible NOTIFY valueVisibleChanged)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals NOTIFY decimalsChanged)
    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix NOTIFY prefixChanged)
    Q_PROPERTY(QString suffix READ suffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(QColor startColor READ startColor WRITE setStartColor NOTIFY startColorChanged)
    Q_PROPERTY(QColor endColor READ endColor WRITE setEndColor NOTIFY endColorChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor NOTIFY scaleColorChanged)
    Q_PROPERTY(QString bottomTitle READ bottomTitle WRITE setBottomTitle NOTIFY bottomTitleChanged)
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
        int scale;
        qreal side;
        QRectF area;
        qreal radius;
        qreal range;
        qreal valueAngle;
    } PainterContext;

    explicit JDialGauge(QWidget *parent = nullptr);
    explicit JDialGauge(const QString &title, QWidget *parent = nullptr);
    virtual ~JDialGauge() J_OVERRIDE;

    qreal minimum() const;
    qreal maximum() const;
    qreal value() const;
    bool isValueVisible() const;
    int decimals() const;
    QString prefix() const;
    QString suffix() const;
    QColor startColor() const;
    QColor endColor() const;
    QString icon() const;
    QSize iconSize() const;
    QColor scaleColor() const;
    QString bottomTitle() const;

    void addWarningRange(int id, qreal from, qreal to, const QColor &color);
    void removeWarningRange(int id);
    const QMap<int, WarningContext> &warnRanges() const;

    static qreal fromCoordAngle(qreal angle);
    static qreal toCoordAngle(qreal angle);

    QColor colorAtWarnRange(const PainterContext *context, qreal value) const;

    qreal valueToAngle(const PainterContext *context, qreal value) const;

Q_SIGNALS:
    void minimumChanged(qreal value);
    void maximumChanged(qreal value);
    void rangeChanged(qreal minimum, qreal maximum);
    void valueChanged(qreal value);
    void valueVisibleChanged(bool visible);
    void decimalsChanged(int value);
    void suffixChanged(const QString &text);
    void prefixChanged(const QString &text);
    void startColorChanged(const QColor &color);
    void endColorChanged(const QColor &color);
    void iconChanged(const QString &icon);
    void iconSizeChanged(const QSize &size);
    void scaleColorChanged(const QColor &color);
    void bottomTitleChanged(const QString &text);

public Q_SLOTS:
    void setMinimum(qreal value);
    void setMaximum(qreal value);
    void setRange(qreal minimum, qreal maximum);
    void setValue(qreal value, bool animation = false);
    void setValueVisible(bool visible);
    void setDecimals(int value);
    void setPrefix(const QString &text);
    void setSuffix(const QString &text);
    void setStartColor(const QColor &color);
    void setEndColor(const QColor &color);
    void setColorRange(const QColor &startColor, const QColor &endColor);
    void setIcon(const QString &icon);
    void setIconSize(const QSize &size);
    void setScaleColor(const QColor &color);
    void setBottomTitle(const QString &text);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void drawTitle(QPainter *painter, const PainterContext *context);
    virtual void drawBackground(QPainter *painter, const PainterContext *context);
    virtual void drawScale(QPainter *painter, const PainterContext *context);
    virtual void drawNeedle(QPainter *painter, const PainterContext *context);
    virtual void drawValue(QPainter *painter, const PainterContext *context);

private:
    Q_DISABLE_COPY(JDialGauge)
    J_DECLARE_PRIVATE(JDialGauge)
};

#endif  // JDIALGAUGE_H
