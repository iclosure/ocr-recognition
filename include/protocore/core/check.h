#ifndef PROTOCORE_CHECK_H
#define PROTOCORE_CHECK_H

#include "item.h"

namespace J {

//
enum CheckType {
    CheckInvalid = -1,  /**<  */
    CheckNone,          /**<  */
    CheckSum8,          /**< 8 bits sum */
    CheckSum16,         /**< 16 bits sum */
    CheckSum32,         /**< 32 bits sum */
    CheckCrc8,          /**< 8 bits crc */
    CheckCrc16,         /**< 16 bits crc */
    CheckCrc32,         /**< 16 bits crc */
    CheckXor8,          /**< 8 bits xor */
    CheckXor16,         /**< 16 bits xor */
    CheckXor32,         /**< 16 bits xor */
    CheckTotal          /**<  */
};

class Check;
typedef std::shared_ptr<Check> CheckPtr;

class CheckData;

class PROTOCORE_EXPORT Check : public Item
{
public:
    explicit Check(Object *parent = nullptr);
    explicit Check(const std::string &id, Object *parent = nullptr);
    Check(const Check &other);
    ~Check() J_OVERRIDE;

    int rtti() const override;
    bool isShowableItem() const override;

    bool isValid() const;

    CheckType checkType() const;
    void setCheckType(CheckType type);
    std::string checkTypeString() const;
    static std::string checkTypeString(CheckType type);
    static CheckType stringCheckType(const std::string &str);

    double data() const override;
    void setData(double data) override;
    std::string dataString() const override;
    double dataFromBuffer(const char *buffer) const override;

    int startPos() const;
    void setStartPos(int startPos);

    int endPos() const;
    void setEndPos(int endPos);

    int checkLength() const;

    bool isComplementCodeEnabled() const;
    void setComplementCodeEnabled(bool enabled);

    std::string typeName() const override;
    std::string typeString() const override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    Check &operator =(const Check &other);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    CheckData *d;
};

} // end of namespace J

#endif // PROTOCORE_CHECK_H
