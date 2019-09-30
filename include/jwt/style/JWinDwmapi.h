#ifndef JWINDWMAPI_H
#define JWINDWMAPI_H

#include <qwindowdefs.h>
#include <QMargins>
#include "../global.h"

class JWinDwmapiPrivate;

class JWT_EXPORT JWinDwmapi
{
public:
    JWinDwmapi();
    ~JWinDwmapi();

    bool isCompositionEnabled() const;
    bool extendFrameIntoClientArea(WId winId, const QMargins &margins) const;

private:
    J_DISABLE_COPY(JWinDwmapi)
    J_DECLARE_PRIVATE(JWinDwmapi)
    J_DECLARE_SINGLE_INSTANCE(JWinDwmapi)
};

#endif // JWINDWMAPI_H
