#ifndef PROTOCORE_NULL_DELEGATE_H
#define PROTOCORE_NULL_DELEGATE_H

#include "../parser.h"

namespace J {

// class NullDelegate

class NullDelegate : public ValueDelegate
{
public:
    explicit NullDelegate();
    ~NullDelegate() J_OVERRIDE;

    // ValueDelegate interface
public:
    Value owner() const override;
    void setOwner(const Value &owner) override;

    int parserType() const override;
    int valueType() const override;

    static ValueDelegatePtr staticCreate(const std::string &name = std::string());
    ValueDelegatePtr create(const std::string &name = std::string()) const override;

    Value copy() const override;

    void *meta() const override;
    void *takeMeta() override;

    bool contains(const std::string &name) const override;
    void remove(const std::string &name, bool attribute = true, bool children = true) override;

    bool isNull() const override;
    bool isValid() const override;

    bool empty() const override;
    Value first() const override;
    Value last() const override;
    void begin() override;
    bool hasNext() const override;
    Value next() override;

    void clear() override;

    Value operator [](const std::string &key) const override;
    void append(const Value &value) override;

    std::string key(const std::string &name = std::string()) const  override;

    bool field(const std::string &key, bool &value) const override;
    bool field(const std::string &key, int &value) const override;
    bool field(const std::string &key, unsigned int &value) const override;
    bool field(const std::string &key, long long &value) const override;
    bool field(const std::string &key, unsigned long long &value) const override;
    bool field(const std::string &key, float &value) const override;
    bool field(const std::string &key, double &value) const override;
    bool field(const std::string &key, std::string &value, bool format = true) const override;
    Value field(const std::string &key) const override;
    bool field(std::string &key, std::string &value, const std::string &keyName,
               const std::string &valueName) const override;

    void setField(const std::string &key, bool value) override;
    void setField(const std::string &key, int32_t value) override;
    void setField(const std::string &key, uint32_t value) override;
    void setField(const std::string &key, int64_t value) override;
    void setField(const std::string &key, uint64_t value) override;
    void setField(const std::string &key, float value) override;
    void setField(const std::string &key, double value) override;
    void setField(const std::string &key, const char *value, bool format = true) override;
    void setField(const std::string &key, const std::string &value, bool format = true) override;
    void setField(const std::string &key, const Value &value) override;
    void setField(const std::string &nodeName, const std::string &key, const std::string &value,
                  const std::string &keyName, const std::string &valueName) override;

    bool toBool(bool *ok = nullptr) const override;
    int toInt(bool *ok = nullptr) const override;
    unsigned int toUInt(bool *ok = nullptr) const override;
    long long toLongLong(bool *ok = nullptr) const override;
    unsigned long long toULongLong(bool *ok = nullptr) const override;
    float toFloat(bool *ok = nullptr) const override;
    double toDouble(bool *ok = nullptr) const override;
    std::string toString(bool format = true, bool *ok = nullptr) const override;
    Value toValue() const override;

    Value beginValue(const std::string &key, const std::string &subKey = std::string()) override;
    Value beginArray(const std::string &key) override;
    Value beginObject(const std::string &key) override;
    void endValue(const Value &value) override;

private:
    J_DISABLE_COPY(NullDelegate)
};

}   // end of namespace J

#endif  // PROTOCORE_NULL_DELEGATE_H
