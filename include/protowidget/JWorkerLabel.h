#ifndef JWORKERLABEL_H
#define JWORKERLABEL_H

#include <QWidget>
#include "global.h"
#include "JChannelPane.h"
#include <QEvent>

namespace J {

class Worker;
typedef std::shared_ptr<Worker> WorkerPtr;

class JWorkerLabelPrivate;

class PROTOWIDGET_EXPORT JWorkerLabel : public QWidget
{
    Q_OBJECT
public:
    explicit JWorkerLabel(const WorkerPtr &worker, JChannelPane::OperateAttributes attrs,
                          QWidget *parent = nullptr);
    ~JWorkerLabel() J_OVERRIDE;

    void updateUi();

    WorkerPtr worker() const;
    JChannelPane::OperateAttributes attrs() const;
    QPixmap icon() const;
    void setIndicatorVisible(bool visible);

Q_SIGNALS:

public Q_SLOTS:

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Q_DISABLE_COPY(JWorkerLabel)
    J_DECLARE_PRIVATE(JWorkerLabel)
};

} // end of namespace J

#endif // JWORKERLABEL_H
