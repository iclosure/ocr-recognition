#ifndef PROTOCORE_PARSER_H
#define PROTOCORE_PARSER_H

#include "../global.h"
#include "../core/object.h"

namespace J {

//
enum ParserType {
    InvalidParser = -1,
    JsonParser = 0,
    XmlParser,
    SQLParser,
    UserParserType = 100
};

// (notice: xmlparser is not supported)
enum ValueType {
    NullValue = 0,
    IntValue,
    UIntValue,
    RealValue,
    StringValue,
    BooleanValue,
    ArrayValue,
    ObjectValue
};

// ValueDelegate

class Object;

class Value;
class ValueDelegate;
typedef std::shared_ptr<ValueDelegate> ValueDelegatePtr;

class ValueDelegate
{
public:
    virtual ~ValueDelegate() {}

    virtual Value owner() const = 0;
    virtual void setOwner(const Value &owner) = 0;

    virtual int parserType() const = 0;
    virtual int valueType() const = 0;

    virtual ValueDelegatePtr create(const std::string &key = std::string()) const = 0;

    virtual Value copy() const = 0;

    virtual void *meta() const = 0;
    template<typename T> inline T* meta() const { return static_cast<T*>(meta()); }
    virtual void *takeMeta() = 0;
    template<typename T> inline T* takeMeta() { return static_cast<T*>(takeMeta()); }

    virtual bool contains(const std::string &key) const = 0;
    virtual void remove(const std::string &key, bool attribute = true,
                        bool children = true) = 0;

    virtual bool isNull() const = 0;
    virtual bool isValid() const = 0;

    virtual bool empty() const = 0;
    virtual Value first() const = 0;
    virtual Value last() const = 0;
    virtual void begin() = 0;
    virtual bool hasNext() const = 0;
    virtual Value next() = 0;

    virtual void clear() = 0;

    virtual Value operator [](const std::string &key) const = 0;
    virtual void append(const Value &value) = 0;

    virtual std::string key(const std::string &name = std::string()) const = 0;

    virtual bool field(const std::string &key, bool &value) const = 0;
    virtual bool field(const std::string &key, int &value) const = 0;
    virtual bool field(const std::string &key, unsigned int &value) const = 0;
    virtual bool field(const std::string &key, long long &value) const = 0;
    virtual bool field(const std::string &key, unsigned long long &value) const = 0;
    virtual bool field(const std::string &key, float &value) const = 0;
    virtual bool field(const std::string &key, double &value) const = 0;
    virtual bool field(const std::string &key, std::string &value, bool format = false) const = 0;
    virtual Value field(const std::string &key) const = 0;
    virtual bool field(std::string &key, std::string &value, const std::string &keyName,
                       const std::string &valueName) const = 0;

    virtual void setField(const std::string &key, bool value) = 0;
    virtual void setField(const std::string &key, int32_t value) = 0;
    virtual void setField(const std::string &key, uint32_t value) = 0;
    virtual void setField(const std::string &key, int64_t value) = 0;
    virtual void setField(const std::string &key, uint64_t value) = 0;
    virtual void setField(const std::string &key, float value) = 0;
    virtual void setField(const std::string &key, double value) = 0;
    virtual void setField(const std::string &key, const char *value, bool format = true) = 0;
    virtual void setField(const std::string &key, const std::string &value, bool format = true) = 0;
    virtual void setField(const std::string &key, const Value &value) = 0;
    virtual void setField(const std::string &nodeName, const std::string &key, const std::string &value,
                          const std::string &keyName, const std::string &valueName) = 0;

    virtual bool toBool(bool *ok = nullptr) const = 0;
    virtual int toInt(bool *ok = nullptr) const = 0;
    virtual unsigned int toUInt(bool *ok = nullptr) const = 0;
    virtual long long toLongLong(bool *ok = nullptr) const = 0;
    virtual unsigned long long toULongLong(bool *ok = nullptr) const = 0;
    virtual float toFloat(bool *ok = nullptr) const = 0;
    virtual double toDouble(bool *ok = nullptr) const = 0;
    virtual std::string toString(bool format = false, bool *ok = nullptr) const = 0;
    virtual Value toValue() const = 0;

    virtual Value beginValue(const std::string &key, const std::string &subKey = std::string()) = 0;
    virtual Value beginArray(const std::string &key) = 0;
    virtual Value beginObject(const std::string &key) = 0;
    virtual void endValue(const Value &value) = 0;

    virtual inline bool useExtSerial() const { return false; }
    virtual inline Value save(const Object *object) const;
    virtual inline bool restore(Object *object, int deep = -1);
};

// Value

class Value;
class ValueData;
typedef std::shared_ptr<Value> ValuePtr;

class PROTOCORE_EXPORT Value
{
public:
    Value();
    explicit Value(const ParserType parserType, const std::string &key = std::string());
    explicit Value(const Json::Value &value, const std::string &key = std::string());
#ifndef HAVE_NO_TINYXML
    explicit Value(const TiXmlElement *value, const std::string &key = std::string());
#endif
    explicit Value(const ValueDelegatePtr &delegate);
    ~Value();

    Value(const Value &other);
    Value &operator=(const Value &other);

    Value create(const std::string &key = std::string()) const;
    static Value create(const Value &value, const std::string &key = std::string());
#if defined(_MSC_VER) && (_MSC_VER > 1600)
    explicit
#endif
    operator bool() const;
    ValueDelegatePtr delegate() const;
    ValueDelegate *operator->() const;
    Value field(const std::string &name) const;

private:
    ValueData *d;
};

//
Value ValueDelegate::save(const Object *object) const { (void)object; return Value(); }
bool ValueDelegate::restore(Object *object, int deep) { (void)object; (void)deep; return false; }

//

class Root;
typedef std::shared_ptr<Root> RootPtr;

class Vehicle;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::vector<VehiclePtr> VehiclePtrArray;

class System;
typedef std::shared_ptr<System> SystemPtr;
typedef std::vector<SystemPtr> SystemPtrArray;

class Table;
typedef std::shared_ptr<Table> TablePtr;
typedef std::vector<TablePtr> TablePtrArray;

class Item;
typedef std::shared_ptr<Item> ItemPtr;
typedef std::vector<ItemPtr> ItemPtrArray;

class Array;
typedef std::shared_ptr<Array> ArrayPtr;

class Bit;
typedef std::shared_ptr<Bit> BitPtr;

class Check;
typedef std::shared_ptr<Check> CheckPtr;

class Complex;
typedef std::shared_ptr<Complex> ComplexPtr;

class Counter;
typedef std::shared_ptr<Counter> CounterPtr;

class DateTime;
typedef std::shared_ptr<DateTime> DateTimePtr;

class Frame;
typedef std::shared_ptr<Frame> FramePtr;

class FrameCode;
typedef std::shared_ptr<FrameCode> FrameCodePtr;

class Header;
typedef std::shared_ptr<Header> HeaderPtr;

class Numeric;
typedef std::shared_ptr<Numeric> NumericPtr;

class Parser;
typedef std::shared_ptr<Parser> ParserPtr;

// class Parser

class ParserData;

class PROTOCORE_EXPORT Parser
{
public:
    explicit Parser(const Json::Value &config);
    virtual ~Parser();

    static ParserPtr create(const std::string &filePath);
    static ParserPtr create(const Json::Value &config);

    virtual bool parse(RootPtr &root, int deep) const = 0;
    virtual bool parse(VehiclePtrArray &vehicles, int deep, Object *parent = nullptr) const = 0;
    virtual bool parse(const std::string &vehicleId, VehiclePtr &vehicle, int deep,
                       Object *parent = nullptr) const = 0;
    virtual bool parse(const std::string &vehicleId, SystemPtrArray &systems, int deep,
                       Object *parent = nullptr) const = 0;
    virtual bool parse(const std::string &vehicleId, const std::string &systemId, SystemPtr &system,
                       int deep, Object *parent = nullptr) const = 0;
    virtual bool parse(const std::string &vehicleId, const std::string &systemId, TablePtrArray &tables,
                       int deep, Object *parent = nullptr) const = 0;
    virtual bool parse(const std::string &vehicleId, const std::string &systemId, const std::string &tableId,
                       TablePtr &table, int deep, Object *parent = nullptr) const = 0;
    virtual bool parse(const std::string &vehicleId, const std::string &systemId, const std::string &tableId,
                       ItemPtrArray &items, int deep, Object *parent = nullptr) const = 0;
    virtual bool parse(TablePtrArray &tables) const = 0;
    virtual bool parse(const std::string &tableId, TablePtr &table) const = 0;
    ObjectPtr parse(const std::string &domain, int objectType, int deep = 1, Object *parent = nullptr) const;

    virtual Json::Value queryTable(const std::string &domain, int domainType) const;

    virtual bool save(const RootPtr &root) = 0;
    virtual bool save(const VehiclePtrArray &vehicles) = 0;
    virtual bool save(const std::string &vehicleId, const VehiclePtr &vehicle) = 0;
    virtual bool save(const std::string &vehicleId, const SystemPtrArray &systems) = 0;
    virtual bool save(const std::string &vehicleId, const std::string &systemId,
                      const SystemPtr &system) = 0;
    virtual bool save(const std::string &vehicleId, const std::string &systemId,
                      const TablePtrArray &tables) = 0;
    virtual bool save(const std::string &vehicleId, const std::string &systemId,
                      const std::string &tableId, const TablePtr &table) = 0;
    virtual bool save(const std::string &vehicleId, const std::string &systemId,
                      const std::string &tableId, const ItemPtrArray &items) = 0;
    virtual bool save(const TablePtrArray &tables) = 0;
    virtual bool save(const std::string &tableId, const TablePtr &table) = 0;
    virtual bool save(const TablePtr &table) = 0;
    bool save(const std::string &domain, const ObjectPtr &object,
              bool merge = false, bool fast = false);

    static bool isGeneratorPluginExists();
    bool saveAs(const ObjectPtr &object, const std::string &filePath);
    bool saveAs(const TablePtr &table, const std::string &filePath);

    std::string message() const;
    void setMessage(const std::string &message);

    double progressValue() const;
    void setProgressValue(double value);

    bool canceledSaveAs() const;
    void cancelSaveAs(bool cancel = true);
#ifndef HAVE_NO_TINYXML
    static bool createXmlFile(const std::string &filePath);
#endif
#ifndef HAVE_NO_SQL
    static bool createDBFile(const std::string &filePath);
#endif

    static bool loadPlugins();
    static void unloadPlugins();

private:
    J_DISABLE_COPY(Parser)
    friend class Generator;
    ParserData *d;
};

// extends

J::RootPtr PROTOCORE_EXPORT queryRoot(const std::string &filePath, int deep = J::ObjectItem);
Json::Value PROTOCORE_EXPORT queryTable(const std::string &filePath, const std::string &vehicleId,
                                        const std::string &systemId, const std::string &tableId);
Json::Value PROTOCORE_EXPORT queryTable(const std::string &filePath, const std::string &domain,
                                        int domainType = DomainId);
J::TablePtr PROTOCORE_EXPORT queryTableObject(const std::string &filePath, const std::string &vehicleId,
                                              const std::string &systemId, const std::string &tableId);
J::TablePtr PROTOCORE_EXPORT queryTableObject(const std::string &filePath, const std::string &domain,
                                              int domainType = DomainId);
J::TablePtr PROTOCORE_EXPORT queryTableObject(const ParserPtr &parser, const std::string &domain,
                                              int domainType = DomainId);
J::TablePtr PROTOCORE_EXPORT queryTableObject(const Json::Value &config);
Json::Value PROTOCORE_EXPORT queryPath(const std::string &filePath, const std::string &path,
                                       int domainType = DomainId);
Json::Value PROTOCORE_EXPORT queryTableFromContext(const std::string &context, const std::string &vehicleId,
                                                   const std::string &systemId, const std::string &tableId);
Json::Value PROTOCORE_EXPORT queryTableFromContext(const std::string &context, const std::string &domain,
                                                   int domainType = DomainId);
Json::Value PROTOCORE_EXPORT queryPathFromContext(const std::string &context, const std::string &path,
                                                  int domainType = DomainId);

} // end of namespace J

#endif // PROTOCORE_PARSER_H
