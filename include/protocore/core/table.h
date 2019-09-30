#ifndef PROTOCORE_TABLE_H
#define PROTOCORE_TABLE_H

#include "item.h"
#include <unordered_map>

namespace J {

class Counter;
typedef std::shared_ptr<Counter> CounterPtr;

class Check;
typedef std::shared_ptr<Check> CheckPtr;

class Frame;
typedef std::shared_ptr<Frame> FramePtr;

class DateTime;
typedef std::shared_ptr<DateTime> DateTimePtr;

class FrameCode;
typedef std::shared_ptr<FrameCode> FrameCodePtr;
typedef std::vector<FrameCodePtr> FrameCodePtrArray;

class Bit;
typedef std::shared_ptr<Bit> BitPtr;

class Table;
typedef std::shared_ptr<Table> TablePtr;
typedef std::weak_ptr<Table> WeakTablePtr;
typedef std::vector<TablePtr> TablePtrArray;

class TableData;

class PROTOCORE_EXPORT Table : public Object
{
public:
    explicit Table(Object *parent = nullptr);
    explicit Table(const std::string &id, Object *parent = nullptr);
    Table(const Table &other);
    ~Table() J_OVERRIDE;

    int rtti() const override;

    int index() const;
    int bufferSize() const;
    int bufferOffset() const;
    char *buffer() const;
    void setBuffer(char *buffer);

    ItemPtrArray items();
    const ItemPtrArray &items() const;
    void appendItem(const ItemPtr &item);
    void insertItem(int index, const ItemPtr &item);
    void removeItem(int index);
    void removeItemByMark(const std::string &mark);
    void clearItem();
    bool isEmpty() const;
    int itemCount() const;
    ItemPtr itemAt(int index) const;
    ItemPtr firstItem() const;
    ItemPtr lastItem() const;
    
    ItemPtr itemById(const std::string &id, int rtti = ObjectInvalid) const;
    ObjectPtr itemByName(const std::string &name, bool deep = true, bool ignoreComplex = true) const;
    ObjectPtr itemByMark(const std::string &mark, bool deep = true, bool ignoreComplex = true) const;
    TablePtr tableByName(const std::string &name, bool deep = true) const;
    TablePtr tableByMark(const std::string &mark, bool deep = true) const;

    ObjectPtr itemByDomain(const std::string &domain, DomainType domainType = DomainId,
                           bool ignoreComplex = true) const;
    TablePtr tableByDomain(const std::string &domain, DomainType domainType = DomainId) const;
    ObjectPtr findByDomain(const std::string &domain, int domainType = DomainId,
                           bool ignoreComplex = true) const override;

    bool hasChildByName(const std::string &name, const ObjectPtr &exclude = ObjectPtr()) const override;
    bool hasChildByMark(const std::string &mark, const ObjectPtr &exclude = ObjectPtr()) const override;
    ObjectPtr childAt(uint64_t index) const override;
    ObjectPtr replaceChild(uint64_t index, const ObjectPtr &other) override;
    ObjectPtr replaceChild(const std::string &id, const ObjectPtr &other) override;
    void moveChild(int sourceIndex, int targetIndex) override;
    void removeChild(uint64_t beginIndex, int endIndex = -1) override;
    void removeChild(const std::list<uint64_t> &indexes) override;
    void clearChildren() override;

    static int adjustOffset(const ItemPtrArray &items, int index = 0, int bufferOffset = 0);

    const std::vector<char> &headers() const;
    CounterPtr counter();
    const CounterPtr &counter() const;
    bool isCheckValid() const;
    CheckPtr check();
    const CheckPtr &check() const;
    DateTimePtr globalTime() const;
    bool isGlobalTimeValid() const;
    bool isComplementCodeEnabled() const;
    const FrameCodePtrArray &frameCodes() const;

    void updateCheck();
    bool updatedCheck(char *buffer, int size) const;
    void updateSend(bool period);
    void updateRecv();
    void resetSend();

    void bindBuffer();
    void createBuffer();
    void deleteBuffer();
    bool isOwnBuffer() const;

    int sequence() const;
    void setSequence(int sequence);
    int period() const;
    bool isFrameTable() const;
    bool isSubFrameTable() const;

    bool isSingleItemEnabled() const;
    void setSingleItemEnabled(bool enabled);

    int frameCodeType() const;
    uint64_t frameCode() const;
    
    std::string typeName() const;
    std::string codeName() const;

    int childCount() const override;
    void resetData() override;
    void clearData() override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Table &operator =(const Table &other);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

public:
    template<typename T> inline std::shared_ptr<T> itemAt(int index) const;
    template<typename T> inline std::shared_ptr<T> itemById(const std::string &id, int rtti = ObjectInvalid) const;
    template<typename T> inline std::shared_ptr<T> itemByName(const std::string &name, bool deep = true) const;
    template<typename T> inline std::shared_ptr<T> itemByMark(const std::string &mark, bool deep = true) const;
    template<typename T> inline std::shared_ptr<T> itemByDomain(const std::string &domain, DomainType domainType = DomainId,
                                                                bool ignoreComplex = true) const;
    template<typename T> inline std::shared_ptr<T> findByDomain(const std::string &domain, int domainType = DomainId,
                                                                bool ignoreComplex = true) const;

    void reset();

    static void linkFrame(const Table *table);
    static void linkFrame(const ItemPtrArray &items);
    static void linkFrame(const ItemPtrArray &items, const std::unordered_map<std::string, FramePtr> &mapFrame);

    bool checksum() const;
    static bool checksum(const TablePtr &table, const char *buffer);
    static bool checksum(const Table *table, const char *buffer);
    static uint8_t crc8(const char *data, int size);
    static uint16_t crc16(const char *data, int size);
    static uint32_t crc32(const char *data, int size);

protected:
    void adjustOffset(int index) override;
    void adjustSingleSize();

private:
    void linkFrame();
    static void linkFrame(const Table *table, const std::unordered_map<std::string, FramePtr> &mapFrame);
    static void linkFrame(const ItemPtrArray &items, const FrameCodePtrArray &frameCodes);
    static void linkFrame(const ItemPtrArray &items, const FrameCodePtrArray &frameCodes,
                          const std::unordered_map<std::string, FramePtr> &mapFrame);

    void setIndex(int index);
    void setBufferOffset(int offset);

private:
    TableData *d;
    friend class Complex;
    friend class ComplexData;
    friend class Frame;
    friend class FrameData;
};

template<typename T> inline std::shared_ptr<T> Table::itemAt(int index) const
{ return shared_cast<T>(itemAt(index)); }
template<typename T> inline std::shared_ptr<T>
Table::itemById(const std::string &id, int rtti) const
{ return shared_cast<T>(itemById(id, rtti)); }
template<typename T> inline std::shared_ptr<T>
Table::itemByName(const std::string &name, bool deep) const
{ return shared_cast<T>(itemByName(name, deep)); }
template<typename T> inline std::shared_ptr<T>
Table::itemByMark(const std::string &mark, bool deep) const
{ return shared_cast<T>(itemByMark(mark, deep)); }
template<typename T> inline std::shared_ptr<T>
Table::itemByDomain(const std::string &domain, DomainType domainType, bool ignoreComplex) const
{ return shared_cast<T>(itemByDomain(domain, domainType, ignoreComplex)); }

} // end of namespace J

#endif // PROTOCORE_TABLE_H
