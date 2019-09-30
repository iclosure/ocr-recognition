#ifndef JSTYLEDFRAME_H
#define JSTYLEDFRAME_H

#include "../global.h"
#include "JShadowFrame.h"

class JStyledFramePrivate;

class JWT_EXPORT JStyledFrame : public JShadowFrame
{
    Q_OBJECT
public:
    explicit JStyledFrame(QWidget *parent = nullptr);
    virtual ~JStyledFrame() J_OVERRIDE;

Q_SIGNALS:

public Q_SLOTS:

private:
    Q_DISABLE_COPY(JStyledFrame)
    J_DECLARE_PRIVATE(JStyledFrame)
};

#endif // JSTYLEDFRAME_H
