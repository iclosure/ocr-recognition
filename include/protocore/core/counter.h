#ifndef PROTOCORE_COUNTER_H
#define PROTOCORE_COUNTER_H

#include "item.h"

namespace J {

//
enum CounterType {
    CounterInvalid = -1,
    CounterU8,
    CounterU16,
    CounterU32,
    CounterU64,
    CounterTotal
};

class Counter;
typedef std::shared_ptr<Counter> CounterPtr;
typedef std::vector<CounterPtr> CounterPtrArray;

class CounterData;

class PROTOCORE_EXPORT Counter : public Item
{
public:
    explicit Counter(Object *parent = nullptr);
    explicit Counter(const std::string &id, Object *parent = nullptr);
    Counter(const Counter &other);
    ~Counter() J_OVERRIDE;

    int rtti() const override;
    bool isShowableItem() const override;

    CounterType counterType() const;
    void setCounterType(CounterType type);
    std::string counterTypeString() const;
    static std::string counterTypeString(CounterType type);
    static CounterType stringCounterType(const std::string &str);

    double data() const override;
    void setData(double data) override;
    std::string dataString() const override;
    uint64_t value() const;
    void setValue(uint64_t value);

    double dataFromBuffer(const char *buffer) const override;

    std::string typeName() const override;
    std::string typeString() const override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Counter &operator =(const Counter &other);

    void increate(int value = 1);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    CounterData *d;
};

} // end of namespace J

#endif // PROTOCORE_COUNTER_H
