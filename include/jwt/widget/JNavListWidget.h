#ifndef JNAVLISTWIDGET_H
#define JNAVLISTWIDGET_H

#include "../global.h"
#include "JListWidget.h"

class JNavListWidgetPrivate;

class JWT_EXPORT JNavListWidget : public JListWidget
{
    Q_OBJECT
public:
    explicit JNavListWidget(QWidget *parent = nullptr, bool showIndicator = true,
                           Flow flow = TopToBottom);
    ~JNavListWidget() J_OVERRIDE;

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    Q_DISABLE_COPY(JNavListWidget)
    J_DECLARE_PRIVATE(JNavListWidget)
};

#endif  // JNAVLISTWIDGET_H
