#ifndef PROTOCORE_VEHICLE_H
#define PROTOCORE_VEHICLE_H

#include "system.h"

namespace J {

class Vehicle;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::vector<VehiclePtr> VehiclePtrArray;

class VehicleData;

class PROTOCORE_EXPORT Vehicle : public Object
{
public:
    explicit Vehicle(Object *parent = nullptr);
    explicit Vehicle(const std::string &id, Object *parent = nullptr);
    Vehicle(const Vehicle &other);
    ~Vehicle() J_OVERRIDE;

    int rtti() const override;

    SystemPtrArray systems();
    const SystemPtrArray &systems() const;
    void appendSystem(const SystemPtr &system);
    void insertSystem(int index, const SystemPtr &system);
    void removeSystem(int index);
    void removeSystemByMark(const std::string &mark);
    void clearSystem();
    int systemCount() const;
    SystemPtr systemAt(int index) const;
    SystemPtr systemByName(const std::string &name) const;
    SystemPtr systemByMark(const std::string &mark) const;
    bool isEmpty() const;

    int childCount() const override;
    void resetData() override;
    void clearData() override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Vehicle &operator =(const Vehicle &other);

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
    VehicleData *d;
};

} // end of namespace J

#endif // PROTOCORE_VEHICLE_H
