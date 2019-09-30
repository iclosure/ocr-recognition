#ifndef PROTOCORE_OBJECT_H
#define PROTOCORE_OBJECT_H

#include "../global.h"
#include "../3rdpart/jsoncpp/json_tool.h"
#include <list>

namespace J {

//
enum ObjectType {
    ObjectInvalid       = 0x00,
    ObjectRoot          = 0x01,
    ObjectVehicle       = 0x02,
    ObjectSystem        = 0x03,
    ObjectTable         = 0x04,
    ObjectLimit         = 0x05,
    ObjectItem          = 0x10,
    ObjectComplexItem   = 0x20 | ObjectItem,
    // extern
    ObjectSimple        = 0x00 | ObjectItem,
    ObjectHeader        = 0x01 | ObjectItem,
    ObjectCounter       = 0x02 | ObjectItem,
    ObjectCheck         = 0x03 | ObjectItem,
    ObjectFrameCode     = 0x04 | ObjectItem,
    ObjectNumeric       = 0x05 | ObjectItem,
    ObjectArray         = 0x06 | ObjectItem,
    ObjectBitMap        = 0x07 | ObjectItem,
    ObjectBitValue      = 0x08 | ObjectItem,
    ObjectDateTime      = 0x09 | ObjectItem,
    ObjectComplex       = 0x0A | ObjectComplexItem,
    ObjectFrame         = 0x0B | ObjectComplexItem
};

//
enum DomainType {
    DomainInvalid = -1,
    DomainId,
    DomainName,
    DomainMark
};

class Object;
typedef std::shared_ptr<Object> ObjectPtr;
typedef std::vector<ObjectPtr> ObjectPtrArray;

class Table;
class ObjectData;

class PROTOCORE_EXPORT Object : public Serializable
{
public:
    explicit Object(ObjectType type = ObjectInvalid, Object *parent = nullptr);
    explicit Object(const std::string &id, ObjectType type = ObjectInvalid,
                    Object *parent = nullptr);
    Object(const Object &other);
    virtual ~Object() J_OVERRIDE;

    virtual int rtti() const;
    virtual bool isSimpleItem() const;
    static bool isSimpleItem(int rtti);

    ObjectType objectType() const;

    std::string id() const;
    void setId(const std::string &id);
    std::string domain() const;
    void setDomain(const std::string &domain);
    std::string name() const;
    void setName(const std::string &name);
    std::string mark() const;
    void setMark(const std::string &mark);
    std::string desc() const;
    void setDesc(const std::string &desc);

    virtual bool isPrivateMark() const;

    std::string objectTypeString() const;
    static ObjectType stringObjectType(const std::string &str);
    std::string domainOfType(int domainType) const;
    static DomainType stringDomainType(const std::string &str);
    static std::string nameOfDomainType(int domainType);

    Object *parent() const;
    virtual void setParent(Object *parent);
    virtual int childCount() const;
    virtual void resetData();
    virtual void clearData();

    virtual ObjectPtr copy() const;
    virtual ObjectPtr clone() const;
    Object &operator =(const Object &other);

    virtual ObjectPtr findByDomain(const std::string &domain, int domainType = DomainId,
                                   bool ignoreComplex = true) const;
    template<typename T> inline
    std::shared_ptr<T> findByDomain(const std::string &domain, int domainType = DomainId,
                                    bool ignoreComplex = true) const;

    virtual bool hasChildByName(const std::string &name, const ObjectPtr &exclude = ObjectPtr()) const;
    virtual bool hasChildByMark(const std::string &mark, const ObjectPtr &exclude = ObjectPtr()) const;
    virtual ObjectPtr childAt(uint64_t index) const;
    virtual ObjectPtr replaceChild(uint64_t index, const ObjectPtr &other);
    virtual ObjectPtr replaceChild(const std::string &id, const ObjectPtr &other);
    virtual void moveChild(int sourceIndex, int targetIndex);
    virtual void removeChild(uint64_t beginIndex, int endIndex = -1);
    virtual void removeChild(const std::list<uint64_t> &indexes);
    virtual void clearChildren();

    Table *topLevelTable();

    // Serializable interface
public:
    virtual Value save(const Value &creator) const override;
    virtual bool restore(const Value &value, int deep = -1) override;

protected:
    bool restoring() const;
    void beginRestore();
    void endRestore();

    virtual void adjustOffset(int index) { (void)index; }

    static std::string generateId(int rtti);
	
private:
    ObjectData *d;
    friend class ComplexData;
    friend class FrameData;
    friend class TableData;
};

template<typename T>
std::shared_ptr<T> Object::findByDomain(const std::string &domain, int domainType, bool ignoreComplex) const
{ return shared_cast<T>(findByDomain(domain, domainType, ignoreComplex)); }

} // end of namespace J

#endif // PROTOCORE_OBJECT_H
