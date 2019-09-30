#ifndef JLISTWIDGET_H
#define JLISTWIDGET_H

#include "../global.h"
#include <QListWidget>
#include <QStyledItemDelegate>

// class JListIndicatorDelegate

class JWT_EXPORT JListIndicatorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit JListIndicatorDelegate(QObject *parent = nullptr);
    virtual ~JListIndicatorDelegate() J_OVERRIDE;

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const override;
};

// class JListWidget

class JListWidgetPrivate;
class QGraphicsDropShadowEffect;

class JWT_EXPORT JListWidget : public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(bool shadowEnabled READ isShadowEnabled WRITE setShadowEnabled NOTIFY shadowEnabledChanged)
    Q_PROPERTY(qreal blurRadius READ blurRadius WRITE setBlurRadius NOTIFY blurRadiusChanged)
public:
    explicit JListWidget(QWidget *parent = nullptr);
    ~JListWidget() J_OVERRIDE;

    bool isShadowEnabled() const;
    qreal blurRadius() const;
    QGraphicsDropShadowEffect *effect() const;

Q_SIGNALS:
    void shadowEnabledChanged(bool enabled);
    void blurRadiusChanged(qreal blurRadius);

public Q_SLOTS:
    void setShadowEnabled(bool enabled);
    void setBlurRadius(qreal radius);

private:
    Q_DISABLE_COPY(JListWidget)
    J_DECLARE_PRIVATE(JListWidget)
};

#endif // JLISTWIDGET_H
