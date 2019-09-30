#ifndef JTITLEBAR_H
#define JTITLEBAR_H

#include <QPushButton>
#include "../global.h"
#include <functional>

// class JSystemButton

class JSystemButtonPrivate;

class JWT_EXPORT JSystemButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QColor bkColor READ bkColor WRITE setBkColor NOTIFY bkColorChanged)
    Q_PROPERTY(QPainterPath iconPath READ iconPath WRITE setIconPath NOTIFY iconPathChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)
    Q_PROPERTY(bool rotateEnabled READ isRotateEnabled WRITE setRotateEnabled NOTIFY rotateEnabledChanged)
    Q_PROPERTY(qreal rotateStepAngle READ rotateStepAngle WRITE setRotateStepAngle NOTIFY rotateStepAngleChanged)
    Q_PROPERTY(int rotateInterval READ rotateInterval WRITE setRotateInterval NOTIFY rotateIntervalChanged)
public:
    JSystemButton(const QString &identity, const QIcon &icon, const QColor &highlightColor,
                  QWidget *parent = nullptr);
    JSystemButton(const QString &identity, const QPainterPath &iconPath, bool fillIconPath,
                  bool antialiasing, const QColor &highlightColor, QWidget *parent = nullptr);
    ~JSystemButton() J_OVERRIDE;

    QColor bkColor() const;
    QPainterPath iconPath() const;
    QColor highlightColor() const;
    bool isRotateEnabled() const;
    qreal rotateStepAngle() const;
    int rotateInterval() const;

Q_SIGNALS:
    void bkColorChanged(const QColor &color);
    void iconPathChanged(const QPainterPath &path);
    void highlightColorChanged(const QColor &color);
    void rotateEnabledChanged(bool enabled);
    void rotateStepAngleChanged(qreal degress);
    void rotateIntervalChanged(int interval);

public Q_SLOTS:
    void setBkColor(const QColor &color, bool animation = false);
    void setIconPath(const QPainterPath &path);
    void setHighlightColor(const QColor &color);
    void setRotateEnabled(bool enabled);
    void setRotateStepAngle(qreal degress);
    void setRotateInterval(int interval);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    Q_DISABLE_COPY(JSystemButton)
    J_DECLARE_PRIVATE(JSystemButton)
};

// class JTitleBar

class JTitleBarPrivate;
class JNativeEventFilter;

class JWT_EXPORT JTitleBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor bkColor READ bkColor WRITE setBkColor NOTIFY bkColorChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
    Q_PROPERTY(bool titleVisible READ isTitleVisible WRITE setTitleVisible NOTIFY titleVisibleChanged)
    Q_PROPERTY(Qt::Alignment titleAlignment READ titleAlignment WRITE setTitleAlignment NOTIFY titleAlignmentChanged)
public:
    enum ButtonType {
        ButtonSysMenu = 0x01,
        ButtonMenu = 0x02,
        ButtonMin = 0x04,
        ButtonMax = 0x08,
        ButtonClose = 0x10,
        AllButton = 0x1f
    };
    Q_ENUM(ButtonType)
    Q_DECLARE_FLAGS(ButtonTypes, ButtonType)

    typedef std::function<void(bool/*checked*/,JSystemButton * /*button*/)> ButtonCaller;

    explicit JTitleBar(QWidget *parent = nullptr);
    ~JTitleBar() J_OVERRIDE;

    QColor bkColor() const;
    QString title() const;
    QColor titleColor() const;
    QString displayTitle() const;
    bool isTitleVisible() const;
    Qt::Alignment titleAlignment() const;

    JNativeEventFilter *filter() const;
    void setFilter(JNativeEventFilter *filter);

    bool isShadowEffectEnabled() const;
    void setShadowEffectEnabled(bool enabled);

    QWidget *centralWidget() const;
    void setCentralWidget(QWidget *widget);

    QFont titleFont() const;
    void setTitleFont(const QFont &font);

    bool testButtonVisible(ButtonType button) const;
    void setButtonVisible(ButtonType button, bool visible = true);
    void setButtonsVisible(ButtonTypes buttons);

    bool testButtonEnabled(ButtonType button) const;
    void setButtonEnabled(ButtonType button, bool enabled = true);
    void setButtonsEnabled(ButtonTypes buttons);

    void addLeftWidget(const QString &identity, QWidget *widget);
    void addRightWidget(const QString &identity, QWidget *widget);
    JSystemButton *addLeftButton(const QString &identity, const QIcon &icon, ButtonCaller triggered = nullptr,
                                 const QSize &iconSize = QSize(12, 12), bool sync = true);
    JSystemButton *addRightButton(const QString &identity, const QIcon &icon, ButtonCaller triggered = nullptr,
                                  const QSize &iconSize = QSize(12, 12), bool sync = true);
    void removeWidget(const QString &identity);
    void setButtonIcon(const QString &identity, const QIcon &icon);
    bool isWidgetVisible(const QString &identity) const;
    bool containsWidget(const QString &identity) const;

signals:
    void bkColorChanged(const QColor &color);
    void titleChanged(const QString &text);
    void titleColorChanged(const QColor &color);
    void titleVisibleChanged(bool visible);
    void titleAlignmentChanged(Qt::Alignment alignment);
    void menuTrigglered(const QPoint &pos);
    void buttonTriggered(const QString &identity, bool checked = false);

public slots:
    void setBkColor(const QColor &color);
    void setTitle(const QString &text);
    void setTitleColor(const QColor &color);
    void setTitleVisible(bool visible);
    void setTitleAlignment(Qt::Alignment alignment);
    void setWidgetVisible(const QString &identity, bool visible);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *object, QEvent *event) override;

private:
    Q_DISABLE_COPY(JTitleBar)
    J_DECLARE_PRIVATE(JTitleBar)
};


#endif  // JTITLEBAR_H
