#ifndef PROTOCORE_FRAME_H
#define PROTOCORE_FRAME_H

#include "item.h"
#include <unordered_map>

namespace J {

class Table;
typedef std::shared_ptr<Table> TablePtr;

class FrameCode;
typedef std::shared_ptr<FrameCode> FrameCodePtr;

class Frame;
typedef std::shared_ptr<Frame> FramePtr;
typedef std::map<uint64_t/*code*/, TablePtr> TablePtrMap;

class FrameData;

class PROTOCORE_EXPORT Frame : public Item
{
public:
    explicit Frame(Object *parent = nullptr);
    explicit Frame(const std::string &id, Object *parent = nullptr);
    Frame(const Frame &other);
    ~Frame() J_OVERRIDE;

    int rtti() const override;
    bool isSimpleItem() const override;

    bool followOffset() const;
    void setFollowOffset(bool enabled);

    void addTable(const TablePtr &table);
    void removeTable(uint64_t code);
    void clearTable();
    bool replaceCode(uint64_t oldCode, uint64_t newCode);
    bool updateCode(const std::string &id);
    TablePtrMap tables();
    const TablePtrMap &tables() const;
    int tableCount() const;
    TablePtr tableAt(uint64_t code) const;
    TablePtr tableById(const std::string &id) const;

    std::weak_ptr<FrameCode> frameCode() const;
    void setFrameCode(const std::weak_ptr<FrameCode> &frameCode);

    double data() const override { return 0.0; }
    void setData(double) override { }
    std::string dataString() const override;

    void setBuffer(char *buffer) override;
    void setBufferSize(int size) override;

    std::string typeName() const override;

    int childCount() const override;
    void resetData() override;
    void clearData() override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Frame &operator =(const Frame &other);

    ObjectPtr itemByName(const std::string &name, bool deep = true, bool ignoreComplex = true) const;
    ObjectPtr itemByMark(const std::string &mark, bool deep = true, bool ignoreComplex = true) const;
    TablePtr tableByName(const std::string &name, bool deep = true) const;
    TablePtr tableByMark(const std::string &mark, bool deep = true) const;
    ObjectPtr itemByDomain(const std::string &domain, DomainType domainType = DomainId,
                           bool ignoreComplex = true) const;
    TablePtr tableByDomain(const std::string &domain, DomainType domainType = DomainId) const;

    ObjectPtr findByDomain(const std::string &domain, int domainType = DomainId,
                           bool ignoreComplex = true) const override;
    template<typename T> inline
    std::shared_ptr<T> itemByName(const std::string &name, bool deep = true) const;
    template<typename T> inline
    std::shared_ptr<T> itemByMark(const std::string &mark, bool deep = true) const;
    template<typename T> inline
    std::shared_ptr<T> tableByMark(const std::string &mark, bool deep = true) const;
    template<typename T> inline
    std::shared_ptr<T> itemByDomain(const std::string &domain, DomainType domainType = DomainId,
                                    bool ignoreComplex = true) const;
    template<typename T> inline
    std::shared_ptr<T> tableByDomain(const std::string &domain, DomainType domainType = DomainId) const;

    bool hasChildByName(const std::string &name, const ObjectPtr &exclude = ObjectPtr()) const override;
    bool hasChildByMark(const std::string &mark, const ObjectPtr &exclude = ObjectPtr()) const override;
    ObjectPtr childAt(uint64_t index) const override;
    ObjectPtr replaceChild(uint64_t index, const ObjectPtr &other) override;
    ObjectPtr replaceChild(const std::string &id, const ObjectPtr &other) override;
    void removeChild(uint64_t beginIndex, int endIndex = -1) override;
    void removeChild(const std::list<uint64_t> &indexes) override;
    void clearChildren() override;

    uint64_t updateSend(uint64_t code);
    bool updateRecv(uint64_t code);
    void resetSend();

    static std::vector<ItemType> supportedItemType();
    static bool isSupportedItemType(ItemType type);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

protected:
    void setBufferOffset(int offset) override;
    void adjustBufferOffset() override;

    void adjustOffset(int index) override;

private:
    static void updateSend(Frame *frame, Table *table, bool period);

private:
    FrameData *d;
    friend class FrameCode;
};

template<typename T>
std::shared_ptr<T> Frame::itemByName(const std::string &name, bool deep) const
{ return shared_cast<T>(itemByName(name, deep)); }
template<typename T>
std::shared_ptr<T> Frame::itemByMark(const std::string &mark, bool deep) const
{ return shared_cast<T>(itemByMark(mark, deep)); }
template<typename T>
std::shared_ptr<T> Frame::tableByMark(const std::string &mark, bool deep) const
{ return shared_cast<T>(tableByMark(mark, deep)); }
template<typename T>
std::shared_ptr<T> Frame::itemByDomain(const std::string &domain, DomainType domainType,
                                       bool ignoreComplex) const
{ return shared_cast<T>(itemByDomain(domain, domainType, ignoreComplex)); }

} // end of namespace J

#endif // PROTOCORE_FRAME_H
