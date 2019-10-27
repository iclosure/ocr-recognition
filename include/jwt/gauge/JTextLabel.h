#ifndef JTEXTLABEL_H
#define JTEXTLABEL_H

#include "JWidgetLabel.h"

// class JTextLabel

class JTextLabelPrivate;

class JWT_EXPORT JTextLabel : public JWidgetLabel
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString text2 READ text2 WRITE setText2 NOTIFY text2Changed)
    Q_PROPERTY(bool text2Visible READ text2Visible WRITE setText2Visible NOTIFY text2VisibleChanged)
    Q_PROPERTY(bool highlight READ highlight WRITE setHighlight NOTIFY highlightChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)
    Q_PROPERTY(bool highlight2 READ highlight2 WRITE setHighlight2 NOTIFY highlight2Changed)
    Q_PROPERTY(QColor highlightColor2 READ highlightColor2 WRITE setHighlightColor2 NOTIFY highlightColor2Changed)
    Q_PROPERTY(QString bottomText READ bottomText WRITE setBottomText NOTIFY bottomTextChanged)
public:
    explicit JTextLabel(QWidget *parent = nullptr);
    explicit JTextLabel(const QString &title, QWidget *parent = nullptr);
    virtual ~JTextLabel() J_OVERRIDE;

    QString text() const;
    QString text2() const;
    bool text2Visible() const;
    bool highlight() const;
    QColor highlightColor() const;
    bool highlight2() const;
    QColor highlightColor2() const;
    QString bottomText() const;
    int bottomHeight() const;

    virtual QSize minimumSizeHint() const override;

Q_SIGNALS:
    void textChanged(const QString &value);
    void text2Changed(const QString &value);
    void text2VisibleChanged(bool visible);
    void highlightChanged(bool highlight);
    void highlightColorChanged(const QColor &color);
    void highlight2Changed(bool highlight);
    void highlightColor2Changed(const QColor &color);
    void bottomTextChanged(const QString &text);

public Q_SLOTS:
    void setText(const QString &text);
    void setText2(const QString &text);
    void setText2Visible(bool visible);
    void setText(int index, const QString &text);
    void setHighlight(bool highlight);
    void setHighlightColor(const QColor &color);
    void setHighlight2(bool highlight);
    void setHighlightColor2(const QColor &color);
    void setBottomText(const QString &text);

protected:
    virtual void drawScale(QPainter *painter, const JGauge::PainterContext *context) override;
    virtual void drawValue(QPainter *painter, const JGauge::PainterContext *context) override;
    virtual void drawText(QPainter *painter, const JGauge::PainterContext *context,
                          const QString &text, const QColor &color);

private:
    Q_DISABLE_COPY(JTextLabel)
    J_DECLARE_PRIVATE(JTextLabel)
};

#endif  // JTEXTLABEL_H
