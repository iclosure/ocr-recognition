#ifndef PROTOCORE_CIRCBUFF_H
#define PROTOCORE_CIRCBUFF_H

#include "../global.h"
#include <algorithm>

namespace J {

class CircBuffData;

class PROTOCORE_EXPORT CircBuff
{
public:
    explicit CircBuff(size_t capacity);
    ~CircBuff();

    bool isValid() const;
    size_t size() const;
    size_t capacity() const;
    size_t write(const char *data, size_t size);
    size_t read(char *data, size_t size);
    void clear();

private:
    J_DISABLE_COPY(CircBuff)
    CircBuffData *d;
};

}   // end of namespace J

#endif // PROTOCORE_CIRCBUFF_H
