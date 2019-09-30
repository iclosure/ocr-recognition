#ifndef PROTOCORE_COMPLEX_H
#define PROTOCORE_COMPLEX_H

#include "item.h"

namespace J {

class Table;
typedef std::shared_ptr<Table> TablePtr;

class Complex;
typedef std::shared_ptr<Complex> ComplexPtr;

class ComplexData;

class PROTOCORE_EXPORT Complex : public Item
{
public:
    explicit Complex(Object *parent = nullptr);
    explicit Complex(const std::string &id, Object *parent = nullptr);
    Complex(const Complex &other);
    ~Complex() J_OVERRIDE;

    int rtti() const override;
    bool isSimpleItem() const override;

    bool isEmpty() const;
    TablePtr table() const;

    void setBuffer(char *buffer) override;

    std::string typeName() const override;

    int childCount() const override;

    void updateSend(bool period);
    void updateRecv();
    void resetSend();
    void resetData() override;
    void clearData() override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Complex &operator =(const Complex &other);

    ObjectPtr itemByName(const std::string &name, bool deep = true, bool ignoreComplex = true) const;
    ObjectPtr itemByMark(const std::string &mark, bool deep = true, bool ignoreComplex = true) const;
    TablePtr tableByName(const std::string &mark, bool deep = true) const;
    TablePtr tableByMark(const std::string &mark, bool deep = true) const;
    ObjectPtr itemByDomain(const std::string &domain, DomainType domainType = DomainId,
                           bool ignoreComplex = true) const;
    TablePtr tableByDomain(const std::string &domain, DomainType domainType = DomainId) const;
    
    ObjectPtr findByDomain(const std::string &domain, int domainType = DomainId,
                           bool ignoreComplex = true) const override;
    template<typename T> inline
    std::shared_ptr<T> itemByMark(const std::string &mark, bool deep = true) const;
    template<typename T> inline
    std::shared_ptr<T> tableByMark(const std::string &mark, bool deep = true) const;
    template<typename T> inline
    std::shared_ptr<T> itemByDomain(const std::string &domain, DomainType domainType = DomainId,
                                    bool ignoreComplex = true) const;
    template<typename T> inline
    std::shared_ptr<T> tableByDomain(const std::string &domain, DomainType domainType = DomainId) const;

    ObjectPtr replaceChild(uint64_t index, const ObjectPtr &other) override;
    ObjectPtr replaceChild(const std::string &id, const ObjectPtr &other) override;
    void moveChild(int sourceIndex, int targetIndex) override;
    void removeChild(uint64_t beginIndex, int endIndex = -1) override;
    void removeChild(const std::list<uint64_t> &indexes) override;
    void clearChildren() override;

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

public:
    void restoreTable();

protected:
    void setBufferOffset(int offset) override;
    void setBufferSize(int size) override;
    void adjustBufferOffset() override;
    void adjustOffset(int index) override;

private:
    void setTable(const TablePtr &table);

private:
    friend class ComplexData;
    ComplexData *d;
};

template<typename T>
std::shared_ptr<T> Complex::itemByMark(const std::string &mark, bool deep) const
{ return shared_cast<T>(itemByMark(mark, deep)); }
template<typename T>
std::shared_ptr<T> Complex::tableByMark(const std::string &mark, bool deep) const
{ return shared_cast<T>(tableByMark(mark, deep)); }
template<typename T>
std::shared_ptr<T> Complex::itemByDomain(const std::string &domain, DomainType domainType, bool ignoreComplex) const
{ return shared_cast<T>(itemByDomain(domain, domainType, ignoreComplex)); }
template<typename T>
std::shared_ptr<T> Complex::tableByDomain(const std::string &domain, DomainType domainType) const
{ return shared_cast<T>(tableByDomain(domain, domainType)); }

} // end of namespace J

#endif // PROTOCORE_COMPLEX_H
