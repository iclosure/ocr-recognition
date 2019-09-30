#ifndef PROTOCORE_XML_DELEGATE_H
#define PROTOCORE_XML_DELEGATE_H

#include "../parser.h"

namespace J {

// class XmlDelegate

class XmlDelegate;
typedef std::shared_ptr<XmlDelegate> XmlDelegatePtr;

class XmlDelegate : public ValueDelegate
{
public:
    explicit XmlDelegate(TiXmlElement *value, const std::string &key = std::string());
    ~XmlDelegate() J_OVERRIDE;

    // ValueDelegate interface
public:
    Value owner() const override;
    void setOwner(const Value &owner) override;

    int parserType() const override;
    int valueType() const override;

    static ValueDelegatePtr staticCreate(const TiXmlElement *value,
                                         const std::string &key = std::string());
    ValueDelegatePtr create(const std::string &key = std::string()) const override;

    Value copy() const override;

    void *meta() const override;
    void *takeMeta() override;

    bool contains(const std::string &key) const override;
    void remove(const std::string &key, bool attribute = true, bool children = true) override;

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

    std::string key(const std::string &name = std::string()) const override;

    bool field(const std::string &key, bool &value) const override;
    bool field(const std::string &key, int &value) const override;
    bool field(const std::string &key, unsigned int &value) const override;
    bool field(const std::string &key, long long &value) const override;
    bool field(const std::string &key, unsigned long long &value) const override;
    bool field(const std::string &key, float &value) const override;
    bool field(const std::string &key, double &value) const override;
    bool field(const std::string &key, std::string &value, bool format = false) const override;
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
    void setField(const std::string &key, const char *value, bool format = false) override;
    void setField(const std::string &key, const std::string &value, bool format = false) override;
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
    J_DISABLE_COPY(XmlDelegate)
    Value owner_;
    TiXmlElement *value_;
    TiXmlElement *next_;
    std::string key_;
};

}   // end of namespace J

#endif  // PROTOCORE_XML_DELEGATE_H
