#ifndef PROTOCORE_SQL_DELEGATE_H
#define PROTOCORE_SQL_DELEGATE_H

#include "../parser.h"
#include "soci/rowset.h"
#include <deque>

namespace J {

class JSqlParser;

class Object;
class Root;
class Vehicle;
class System;
class Table;
class Item;
class Array;
class Bit;
class Check;
class Complex;
class Counter;
class DateTime;
class Frame;
class FrameCode;
class Header;
class Numeric;

//
struct DsRowInfo
{
    std::string id;
    std::string name;
    std::string mark;
    int type;
    int level;
    std::string parent_id;
    std::string descr;
    std::string content;
    std::shared_ptr<soci::statement> stmt;

    DsRowInfo() : type(-1), level(-1) { }
    DsRowInfo(int level, const std::string &parent_id = std::string())
        : type(-1), level(level), parent_id(parent_id) { }

    void clear()
    {
        id.clear();
        name.clear();
        mark.clear();
        type = -1;
        descr.clear();
        content.clear();
    }

    bool execute(bool withDataExchange = true)
    {
        if (!stmt) {
            return false;
        }

        const bool result = stmt->execute(withDataExchange);
        clear();
        return result;
    }
};

// class SqlDelegate

typedef std::map<std::string, std::string> map_key_value;

class SqlDelegate;
typedef std::shared_ptr<SqlDelegate> SqlDelegatePtr;

class PROTOCORE_EXPORT SqlDelegate : public ValueDelegate
{
public:
    explicit SqlDelegate(JSqlParser *parser);
    ~SqlDelegate() J_OVERRIDE;

    // ValueDelegate interface
public:
    Value owner() const override;
    void setOwner(const Value &owner) override;

    int parserType() const override;
    int valueType() const override;

    static ValueDelegatePtr staticCreate(JSqlParser *parser,
                                         const std::string &name = std::string());
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

    Value operator [](const std::string &name) const override;
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

    bool useExtSerial() const override { return true; }
    Value save(const Object *object) const override;
    bool restore(Object *object, int deep) override;

private:
    std::string tableNameFromKey(const std::string &key) const;

    // ext-seial
private:
    std::string queryFromLevel(const std::string &parentId, int level,
                               const std::string &id = std::string(), int limits = -1) const;
    soci::rowset<soci::row> rowsFromLevel(const std::string &parentId, int level,
                                          const std::string &id = std::string(), int limits = -1) const;
    bool deleteFromLevel(const std::string &parentId, const std::string &levelCondition,
                         const std::string &id = std::string());
    bool deleteChildren(const std::string &parentId, int level, const std::string &id = std::string());
    // save
    bool _save(const Object *object, DsRowInfo &st) const;
    bool _save(const Root *root) const;
    bool _save(const Vehicle *vehicle, DsRowInfo &st) const;
    bool _save(const System *system, DsRowInfo &st) const;
    bool _save(const Table *table, DsRowInfo &st, bool saveSelf = true) const;
    bool _saveDispatch(const ItemPtr &item, DsRowInfo &st) const;
    bool _save(const Item *item, Json::Value &contentJson, DsRowInfo &st) const;
    bool _save(const Array *array, DsRowInfo &st) const;
    bool _save(const Bit *bit, DsRowInfo &st) const;
    bool _save(const Check *check, DsRowInfo &st) const;
    bool _save(const Complex *complex, DsRowInfo &st) const;
    bool _save(const Counter *counter, DsRowInfo &st) const;
    bool _save(const DateTime *dateTime, DsRowInfo &st) const;
    bool _save(const Frame *frame, DsRowInfo &st) const;
    bool _save(const FrameCode *frameCode, DsRowInfo &st) const;
    bool _save(const Header *header, DsRowInfo &st) const;
    bool _save(const Numeric *numeric, DsRowInfo &st) const;
    bool _save(const J::ObjectPtr &object) const;
    // restore
    bool _restore(const soci::row &row, Object *object);
    bool _restore(const soci::rowset<soci::row> &rowset, Root *root, int deep);
    bool _restore(const soci::row &row, Vehicle *vehicle, int deep, int level);
    bool _restore(const soci::rowset<soci::row> &rowset, Vehicle *vehicle, int deep, int level);
    bool _restore(const soci::row &row, System *system, int deep, int level);
    bool _restore(const soci::rowset<soci::row> &rowset, System *system, int deep, int level);
    bool _restore(const soci::row &row, Table *table, int deep, int level, const std::string &complexId = std::string());
    bool _restore(const soci::rowset<soci::row> &rowset, Table *table, int deep, int level);
    ItemPtr _restore(const soci::row &row, int deep, int level, int index, Object *parent);
    bool _restore(const soci::row &row, Item *item, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Array *array, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Bit *bit, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Check *check, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Complex *complex, int deep, Json::Value &contentJson, int level);
    bool _restore(const soci::row &row, Counter *counter, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, DateTime *dateTime, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Frame *frame, int deep, Json::Value &contentJson, int level);
    bool _restore(const soci::row &row, FrameCode *frameCode, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Header *header, int deep, const Json::Value &contentJson);
    bool _restore(const soci::row &row, Numeric *numeric, int deep, const Json::Value &contentJson);
//    bool _restore(const soci::rowset<soci::row> &rowset, J::ObjectPtr &object, Json::Value &contentJson,
//                  int deep = J::ObjectItem, int level = 0);

    static std::string cleanUuid(const std::string &source);
    static bool queryJsonByKey(const soci::row &row, Json::Value &value, const std::string &key);
    static std::string quoteValue(const std::string &value);

private:
    J_DISABLE_COPY(SqlDelegate)
    friend class JSqlParser;
    friend class JSqlite3Parser;
    JSqlParser *parser_;
    Value owner_;
    std::string key_;
    std::string tableName_;
    std::shared_ptr<soci::rowset<soci::row> > rowset_;
    soci::rowset<soci::row>::iterator rowset_iter_;
};

}  // end of namespace J

#include <soci/values.h>

namespace soci {

// struct type_conversion<J::DsRowInfo>

template<> struct type_conversion<J::DsRowInfo>
{
    typedef values base_type;

    static void from_base(values const &v, indicator /*ind*/, J::DsRowInfo &r)
    {
        r.id = v.get<std::string>("i", "");
        r.name = v.get<std::string>("n", "");
        r.mark = v.get<std::string>("m", "");
        r.type = v.get<int>("t", -1);
        r.level = v.get<int>("l", -1);
        r.parent_id = v.get<std::string>("p", "");
        r.descr = v.get<std::string>("d", "");
        r.content = v.get<std::string>("c", "");
    }

    static void to_base(const J::DsRowInfo &r, values &v, indicator &ind)
    {
        v.set("i", r.id, r.id.empty() ? i_null : i_ok);
        v.set("n", r.name, r.name.empty() ? i_null : i_ok);
        v.set("m", r.mark, r.mark.empty() ? i_null : i_ok);
        v.set("t", r.type);
        v.set("l", r.level);
        v.set("p", r.parent_id, r.parent_id.empty() ? i_null : i_ok);
        v.set("d", r.descr, r.descr.empty() ? i_null : i_ok);
        v.set("c", r.content, r.content.empty() ? i_null : i_ok);
        ind = i_ok;
    }
};

}  // end of namespace soci

#endif // PROTOCORE_SQL_DELEGATE_H
