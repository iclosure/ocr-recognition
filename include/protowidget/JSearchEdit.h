#ifndef JSEARCHEDIT_H
#define JSEARCHEDIT_H

#include <QWidget>
#include "global.h"

class QLineEdit;

namespace J {

class JSearchEditPrivate;

class PROTOWIDGET_EXPORT JSearchEdit : public QWidget
{
    Q_OBJECT
public:
    explicit JSearchEdit(QWidget *parent = nullptr);
    ~JSearchEdit() J_OVERRIDE;

Q_SIGNALS:
    void textChanged(const QString &text);

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JSearchEdit)
    J_DECLARE_PRIVATE(JSearchEdit)
};

} // end of namespace J

#endif // JSEARCHEDIT_H
