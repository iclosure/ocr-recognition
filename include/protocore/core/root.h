#ifndef PROTOCORE_ROOT_H
#define PROTOCORE_ROOT_H

#include "vehicle.h"

namespace J {

class Root;
typedef std::shared_ptr<Root> RootPtr;

class RootData;

class PROTOCORE_EXPORT Root : public Object
{
public:
    explicit Root(Object *parent = nullptr);
    explicit Root(const std::string &id, Object *parent = nullptr);
    Root(const Root &other);
    ~Root() J_OVERRIDE;

    int rtti() const override;

    VehiclePtrArray vehicles();
    const VehiclePtrArray &vehicles() const;

    void appendVehicle(const VehiclePtr &vehicle);
    void insertVehicle(int index, const VehiclePtr &vehicle);
    void removeVehicle(int index);
    void removeVehicleByMark(const std::string &mark);
    void clearVehicle();
    int vehicleCount() const;
    VehiclePtr vehicleAt(int index) const;
    VehiclePtr vehicleByName(const std::string &name) const;
    VehiclePtr vehicleByMark(const std::string &mark) const;
    bool isEmpty() const;

    int childCount() const override;
    void resetData() override;
    void clearData() override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Root &operator =(const Root &other);

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
    RootData *d;
};

} // end of namespace J

#endif // PROTOCORE_ROOT_H
