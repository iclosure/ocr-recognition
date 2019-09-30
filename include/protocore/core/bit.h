#ifndef PROTOCORE_BIT_H
#define PROTOCORE_BIT_H

#include "item.h"
#include "limit.h"
#include <unordered_map>

namespace J {

class Bit;
typedef std::shared_ptr<Bit> BitPtr;

class BitData;

class PROTOCORE_EXPORT Bit : public Item
{
public:
    explicit Bit(Object *parent = nullptr);
    explicit Bit(ItemType type, Object *parent = nullptr);
    explicit Bit(const std::string &id, ItemType type, Object *parent = nullptr);
    Bit(const Bit &other);
    ~Bit() J_OVERRIDE;

    int rtti() const override;

    double data() const override;
    void setData(double d) override;
    bool testBit(int offset) const;
    void setBit(int offset, bool value);
    std::string dataString() const override;
    double dataFromBuffer(const char *buffer) const override;
    bool testBitFromBuffer(int offset, const char *buffer) const;

    int bitStart() const;
    void setBitStart(int bitStart);

    int bitCount() const;
    void setBitCount(int count);

    int bitEnd() const; // = bitStart + bitCount

    int calcSize() const;

    uint64_t mask() const;

    std::map<uint64_t, std::string> specs();
    const std::map<uint64_t, std::string> &specs() const;
    void addSpec(uint64_t key, const std::string &spec);
    void removeSpec(uint64_t key);
    void clearSpec();
    uint64_t keyOf(const std::string &spec, bool *ok = nullptr);
    std::string specAt(uint64_t key) const;
    std::string nameAt(int offset) const;
    static std::string nameOf(const std::string &spec);
    std::string descAt(int offset) const;

    std::string typeName() const override;
    std::string typeString() const override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Bit &operator =(const Bit &other);

    // for bitvalue
    double originalData() const;
    double originalDataFromBuffer(const char *buffer) const;

    double offset() const;
    void setOffset(double offset);

    double scale() const;
    void setScale(double scale);

    bool scaleReciprocal() const;
    void setScaleReciprocal(bool enabled);

    int decimals() const;
    void setDecimals(int value);

    LimitPtr limit() const;
    void setLimit(const LimitPtr &limit);

    std::string unit() const;
    void setUnit(const std::string &unit);

    std::pair<double, double> dataRange() const;
    std::pair<double, double> valueRange() const;

    bool outOfLimit() const;

    std::string prettyValue() const;
    static std::string prettyValue(double value);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    BitData *d;
};

} // end of namespace J

#endif // PROTOCORE_BIT_H
