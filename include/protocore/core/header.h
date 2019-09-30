#ifndef PROTOCORE_HEADER_H
#define PROTOCORE_HEADER_H

#include "item.h"

namespace J {

class Header;
typedef std::shared_ptr<Header> HeaderPtr;
typedef std::vector<HeaderPtr> HeaderPtrArray;

class HeaderData;

class PROTOCORE_EXPORT Header : public Item
{
public:
    explicit Header(Object *parent = nullptr);
    explicit Header(const std::string &id, Object *parent = nullptr);
    Header(const Header &other);
    ~Header() J_OVERRIDE;

    int rtti() const override;
    bool isShowableItem() const override;

    double data() const override;
    void setData(double data) override;
    std::string dataString() const override;
    double dataFromBuffer(const char *buffer) const override;

    unsigned char value() const;
    void setValue(unsigned char value);

    std::string typeName() const override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Header &operator =(const Header &other);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    HeaderData *d;
};

} // end of namespace J

#endif // PROTOCORE_HEADER_H
