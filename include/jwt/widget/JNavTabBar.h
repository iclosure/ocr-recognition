#ifndef JNAVTABBAR_H
#define JNAVTABBAR_H

#include "../global.h"
#include "JShadowFrame.h"
#include <QPushButton>
#include <QLayout>

// class JNavTabButton

class JNavTabButtonPrivate;

class JWT_EXPORT JNavTabButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
public:
    explicit JNavTabButton(int index, QWidget *parent = nullptr);
    JNavTabButton(int index, const QIcon &icon, const QString &text,
                  QWidget *parent = nullptr);
    virtual ~JNavTabButton() J_OVERRIDE;

    int index() const;
    bool isSelected() const;

Q_SIGNALS:
    void indexChanged(int index);
    void selectedChanged(bool selected);

public Q_SLOTS:
    void setSelected(bool selected);

private:
    Q_DISABLE_COPY(JNavTabButton)
    J_DECLARE_PRIVATE(JNavTabButton)
};

// class JNavSwitchButton

class JNavSwitchButtonPrivate;

class JWT_EXPORT JNavSwitchButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
public:
    JNavSwitchButton(int index, bool hasSwitch, const QString &id, const QString &text,
                     QWidget *parent = nullptr);
    virtual ~JNavSwitchButton() J_OVERRIDE;

    int index() const;
    bool hasSwitch() const;
    QString id() const;
    QString text() const;
    bool isSelected() const;

Q_SIGNALS:
    void indexChanged(int index);
    void textChanged(const QString &text);
    void stateChanged(bool checked);
    void clicked();
    void selectedChanged(bool selected);

public Q_SLOTS:
    void setText(const QString &text);
    void setButtonVisible(bool visible);
    void setButtonChecked(bool checked);
    void setSelected(bool selected);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Q_DISABLE_COPY(JNavSwitchButton)
    J_DECLARE_PRIVATE(JNavSwitchButton)
};

// class JNavTabBar

class JNavTabBarPrivate;

class JWT_EXPORT JNavTabBar : public JShadowFrame
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool autoClicked READ autoClicked WRITE setAutoClicked NOTIFY autoClickedChanged)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
public:
    explicit JNavTabBar(QWidget *parent = nullptr);
    explicit JNavTabBar(QBoxLayout::Direction direction, QWidget *parent = nullptr);
    virtual ~JNavTabBar() J_OVERRIDE;

    QBoxLayout::Direction direction() const;
    void setDirection(QBoxLayout::Direction direction);

    int currentIndex() const;
    int count() const;
    bool autoClicked() const;

    JNavTabButton *addTab(const QString &text);
    JNavTabButton *addTab(const QIcon &icon, const QString &text);

    JNavTabButton *insertTab(int index, const QString &text);
    JNavTabButton *insertTab(int index, const QIcon &icon, const QString &text);
    int insertTab(int index, JNavTabButton *button);
    int appendTab(JNavTabButton *button);
    int insertTab(int index, JNavSwitchButton *button);
    int appendTab(JNavSwitchButton *button);

    QWidget *tabWidget(int index) const;
    JNavTabButton *tabButtonAt(int index) const;
    QWidget *currentTabWidget() const;
    int indexOf(JNavTabButton *button) const;

    void removeTab(int index);

    void clear();

    bool isTabEnabled(int index) const;
    void setTabEnabled(int index, bool enabled);

#ifndef QT_NO_TOOLTIP
    void setTabToolTip(int index, const QString &tip);
    QString tabToolTip(int index) const;
#endif

#if QT_CONFIG(whatsthis)
    void setTabWhatsThis(int index, const QString &text);
    QString tabWhatsThis(int index) const;
#endif

    QSize iconSize() const;
    void setIconSize(const QSize &size);

Q_SIGNALS:
    void currentIndexChanged(int index);
    void countChanged(int count);
    void autoClickedChanged(bool enabled);
    void tabBarClicked(int index);

public Q_SLOTS:
    void setCurrentIndex(int index);
    void setCurrentWidget(QWidget *widget);
    void setAutoClicked(bool enabled);

private:
    Q_DISABLE_COPY(JNavTabBar)
    J_DECLARE_PRIVATE(JNavTabBar)
};

#endif  // JNAVTABBAR_H
