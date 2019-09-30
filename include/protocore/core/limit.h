#ifndef PROTOCORE_LIMIT_H
#define PROTOCORE_LIMIT_H

#include "object.h"

namespace J {

class Limit;
typedef std::shared_ptr<Limit> LimitPtr;

class LimitData;

class PROTOCORE_EXPORT Limit : public Object
{
public:
    explicit Limit();
    Limit(const Limit &other);
    ~Limit() J_OVERRIDE;

    virtual int rtti() const override;

    double minimum() const;
    void setMinimum(double minimum);

    double maximum() const;
    void setMaximum(double maximum);

    bool minimumInf() const;
    void setMinimumInf(bool inf);

    bool maximumInf() const;
    void setMaximumInf(bool inf);

    std::string toString() const;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Limit &operator =(const Limit &other);

public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    LimitData *d;
};

} // end of namespace J

#endif // PROTOCORE_LIMIT_H
