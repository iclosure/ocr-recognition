#ifndef PROTOCORE_ARRAY_H
#define PROTOCORE_ARRAY_H

#include "numeric.h"

namespace J {

//
enum ArrayType {
    ArrayInvalid = -1,
    ArrayI8,
    ArrayU8,
    ArrayI16,
    ArrayU16,
    ArrayI32,
    ArrayU32,
    ArrayI64,
    ArrayU64,
    ArrayF32,
    ArrayF64,
    ArrayTotal
};

class Array;
typedef std::shared_ptr<Array> ArrayPtr;

class ArrayData;

class PROTOCORE_EXPORT Array : public Item
{
public:
    explicit Array(Object *parent = nullptr);
    explicit Array(const std::string &id, Object *parent = nullptr);
    Array(const Array &other);
    ~Array() J_OVERRIDE;

    int rtti() const override;

    ArrayType arrayType() const;
    void setArrayType(ArrayType type);
    std::string arrayTypeString() const;
    static std::string arrayTypeString(ArrayType type);
    static ArrayType stringArrayType(const std::string &str);

    NumericType toNumericType() const;
    static NumericType toNumericType(ArrayType type);

    int count() const;
    void setCount(int count);

    bool isExpand() const;
    void setExpand(bool enabled);
    std::string typeName() const override;
    std::string typeString() const override;
    int typeSize() const;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Array &operator =(const Array &other);

    std::string dataString() const override;
    std::string toString() const;
    int8_t *i8() const;
    uint8_t *u8() const;
    int16_t *i16() const;
    uint16_t *u16() const;
    int32_t *i32() const;
    uint32_t *u32() const;
    int64_t *i64() const;
    uint64_t *u64() const;
    float32_t *f32() const;
    float64_t *f64() const;

    void resetData() override;
    void clearData() override;
    void setValue(const char *buffer, int size);

    double originalDataAt(int index) const;
    double dataAt(int index) const;
    void setDataAt(int index, double data);
    std::string dataStringAt(int index) const;
    bool outOfLimitAt(int index) const;

    double originalDataFromBufferAt(const char *buffer, int index) const;
    double dataFromBufferAt(const char *buffer, int index) const;

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

    std::string prettyValueAt(int index) const;
    static std::string prettyValue(double value, int arrayType);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int deep = -1) override;

private:
    ArrayData *d;
};

}   // end of namespace J

#endif // PROTOCORE_ARRAY_H
