#ifndef JSTACKVIEW_H
#define JSTACKVIEW_H

#include "../global.h"
#include <QStackedWidget>

class JStackViewPrivate;

class JWT_EXPORT JStackView : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY(int depth READ depth NOTIFY depthChanged)
public:
    explicit JStackView(QWidget *parent = nullptr);
    ~JStackView() J_OVERRIDE;

    int depth() const;
    bool isEmpty() const;

    void clear();
    void push(QWidget *widget);
    void pop();
    bool replace(QWidget *target, QWidget *widget);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

Q_SIGNALS:
    void depthChanged(int depth);

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JStackView)
    J_DECLARE_PRIVATE(JStackView)
};

#endif // JSTACKVIEW_H
