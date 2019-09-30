#ifndef PROTOCORE_NUMERIC_H
#define PROTOCORE_NUMERIC_H

#include "item.h"
#include "limit.h"
#include <map>

namespace J {

//
enum NumericType {
    NumericInvalid = -1,
    NumericI8,
    NumericU8,
    NumericI16,
    NumericU16,
    NumericI32,
    NumericU32,
    NumericI64,
    NumericU64,
    NumericF32,
    NumericF64,
    NumericTotal
};

class Numeric;
typedef std::shared_ptr<Numeric> NumericPtr;

class NumericData;

class PROTOCORE_EXPORT Numeric : public Item
{
public:
    explicit Numeric(Object *parent = nullptr);
    explicit Numeric(const std::string &id, Object *parent = nullptr);
    Numeric(const Numeric &other);
    ~Numeric() J_OVERRIDE;

    int rtti() const override;

    bool isValid() const;

    NumericType numericType() const;
    void setNumericType(NumericType type);
    std::string numericTypeString() const;
    static std::string numericTypeString(NumericType type);
    static NumericType stringNumericType(const std::string &str);

    double originalData() const;
    double data() const override;
    void setData(double data) override;
    std::string dataString() const override;

    double originalDataFromBuffer(const char *buffer) const;
    double dataFromBuffer(const char *buffer) const override;

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

    std::map<double, std::string> specs();
    const std::map<double, std::string> &specs() const;
    void addSpec(double key, const std::string spec);
    std::string specAt(double key) const;
    double keyOf(const std::string &spec, bool *ok = nullptr);
    void removeSpec(double key);
    void clearSpec();

    uint64_t dataMask() const;
    std::pair<double, double> dataRange() const;
    std::pair<double, double> valueRange() const;

    std::string typeName() const override;
    std::string typeString() const override;

    bool outOfLimit() const;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Numeric &operator =(const Numeric &other);

    std::string prettyValue() const;
    static std::string prettyValue(double value, int numericType);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    NumericData *d;
};

} // end of namespace J

#endif // PROTOCORE_NUMERIC_H
