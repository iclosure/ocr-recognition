#ifndef JNAVTABWIDGET_H
#define JNAVTABWIDGET_H

#include "../global.h"
#include <QFrame>

// class JNavTabWidget

class JNavTabButton;
class JNavTabBar;

class JNavTabWidgetPrivate;

class JWT_EXPORT JNavTabWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(TabPosition tabPosition READ tabPosition WRITE setTabPosition)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(int count READ count)
public:
    enum TabPosition { North, South, West, East };
    Q_ENUM(TabPosition)

    explicit JNavTabWidget(QWidget *parent = nullptr);
    virtual ~JNavTabWidget() J_OVERRIDE;

    int addTab(QWidget *widget, const QString &label);
    int addTab(QWidget *widget, const QIcon& icon, const QString &label);

    int insertTab(int index, QWidget *widget, const QString &label);
    int insertTab(int index, QWidget *widget, const QIcon& icon, const QString &label);

    void removeTab(int index);

    bool isTabEnabled(int index) const;
    void setTabEnabled(int index, bool enabled);

    QString tabText(int index) const;
    void setTabText(int index, const QString &);

    QIcon tabIcon(int index) const;
    void setTabIcon(int index, const QIcon & icon);

#ifndef QT_NO_TOOLTIP
    void setTabToolTip(int index, const QString & tip);
    QString tabToolTip(int index) const;
#endif

#if QT_CONFIG(whatsthis)
    void setTabWhatsThis(int index, const QString &text);
    QString tabWhatsThis(int index) const;
#endif

    int currentIndex() const;
    JNavTabButton *currentTab() const;
    JNavTabButton *tabAt(int index) const;
    int indexOf(JNavTabButton *widget) const;
    int count() const;

    TabPosition tabPosition() const;
    void setTabPosition(TabPosition tabPosition);

    QSize iconSize() const;
    void setIconSize(const QSize &size);

    bool tabBarAutoHide() const;
    void setTabBarAutoHide(bool enabled);

    void clear();

    JNavTabBar* tabBar() const;

    void setTabBarHeight(int height);

Q_SIGNALS:
    void currentChanged(int index);
    void tabBarClicked(int index);

public Q_SLOTS:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);

private:
    Q_DISABLE_COPY(JNavTabWidget)
    J_DECLARE_PRIVATE(JNavTabWidget)
};

#endif  // JNAVTABWIDGET_H
