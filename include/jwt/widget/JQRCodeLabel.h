#ifndef JQRCODELABEL_H
#define JQRCODELABEL_H

#include <QLabel>
#include "../global.h"

// class JQRCodeLabel

class QPainter;
class JQRCodeLabelPrivate;

class JWT_EXPORT JQRCodeLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor NOTIFY lightColorChanged)
    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor NOTIFY darkColorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit JQRCodeLabel(QWidget *parent = nullptr);
    ~JQRCodeLabel() J_OVERRIDE;

    QColor lightColor() const;
    QColor darkColor() const;
    QString text() const;

    void setLogo(const QIcon &icon);

Q_SIGNALS:
    void lightColorChanged(const QColor &color);
    void darkColorChanged(const QColor &color);
    void textChanged(const QString &text);

public Q_SLOTS:
    void setLightColor(const QColor &color);
    void setDarkColor(const QColor &color);
    void setText(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void render(QPainter *painter, bool gray = false) const;

private:
    Q_DISABLE_COPY(JQRCodeLabel)
    J_DECLARE_PRIVATE(JQRCodeLabel)
};


#endif // JQRCODELABEL_H
