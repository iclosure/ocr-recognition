#ifndef PROTOCORE_SYSTEM_H
#define PROTOCORE_SYSTEM_H

#include "table.h"

namespace J {

class System;
typedef std::shared_ptr<System> SystemPtr;
typedef std::vector<SystemPtr> SystemPtrArray;

class Vehicle;
typedef std::shared_ptr<Vehicle> VehiclePtr;

class SystemData;

class PROTOCORE_EXPORT System : public Object
{
public:
    explicit System(Object *parent = nullptr);
    explicit System(const std::string &id, Object *parent = nullptr);
    System(const System &other);
    ~System() J_OVERRIDE;

    int rtti() const override;

    TablePtrArray tables();
    const TablePtrArray &tables() const;
    void appendTable(const TablePtr &table);
    void insertTable(int index, const TablePtr &table);
    void removeTable(int index);
    void removeTableByMark(const std::string &mark);
    void clearTable();
    int tableCount() const;
    TablePtr tableAt(int index) const;
    TablePtr tableByName(const std::string &name) const;
    TablePtr tableByMark(const std::string &mark) const;
    bool isEmpty() const;

    int childCount() const override;
    void resetData() override;
    void clearData() override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    System &operator =(const System &other);

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

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    SystemData *d;
};

} // end of namespace J

#endif // PROTOCORE_SYSTEM_H
