#ifndef PROTOCORE_FRAMECODE_H
#define PROTOCORE_FRAMECODE_H

#include "frame.h"
#include <map>
#include <unordered_map>
namespace J {

//
enum FrameCodeType {
    FrameCodeInvalid = -1,
    FrameCodeU8,
    FrameCodeU16,
    FrameCodeU32,
    FrameCodeU64,
    FrameCodeTotal
};

class FrameCode;
typedef std::shared_ptr<FrameCode> FrameCodePtr;
typedef std::vector<FrameCodePtr> FrameCodePtrArray;

class Frame;
typedef std::weak_ptr<Frame> WeakFramePtr;
typedef std::unordered_map<std::string/*id*/, WeakFramePtr> WeakFramePtrMap;

typedef std::weak_ptr<Table> WeakTablePtr;

class FrameCodeData;

class PROTOCORE_EXPORT FrameCode : public Item
{
public:
    explicit FrameCode(Object *parent = nullptr);
    explicit FrameCode(const std::string &id, Object *parent = nullptr);
    FrameCode(const FrameCode &other);
    ~FrameCode() J_OVERRIDE;

    int rtti() const override;

    FrameCodeType frameCodeType() const;
    void setFrameCodeType(FrameCodeType type);
    std::string frameCodeTypeString() const;
    static std::string frameCodeTypeString(FrameCodeType type);
    static FrameCodeType stringFrameCodeType(const std::string &str);

    double data() const override;
    void setData(double data) override;
    std::string dataString() const override;
    double dataFromBuffer(const char *buffer) const override;

    std::vector<std::string> frameIds() const;
    std::string frameIdsString() const;
    static std::string frameIdsString(const FrameCode *frameCode);
    const WeakFramePtr frame() const;
    const WeakFramePtrMap &frames() const;
    bool isFrameValid() const;
    void addFrame(const std::string &id, const WeakFramePtr &weakFrame = WeakFramePtr());
    void replaceId(const std::string &oldId, const std::string &newId);
    WeakFramePtr replaceFrame(const std::string &id, const WeakFramePtr &weakFrame, bool append = true);
    void removeFrame(const std::string &id);
    void removeFrame(const WeakFramePtr &weakFrame);
    void clearFrame();
    WeakFramePtr frameById(const std::string &id) const;
    WeakFramePtr frameByName(const std::string &name) const;
    WeakFramePtr frameByMark(const std::string &mark) const;
    bool containsFrame(const WeakFramePtr &weakFrame) const;

    int sequenceCount() const;
    void setSequenceCount(int count);

    void updateSend(bool period);
    void updateRecv();
    void resetSend();
    void resetData() override;
    void clearData() override;

    std::string typeName() const override;
    std::string typeString() const override;

    ObjectPtr copy() const override;
    ObjectPtr clone() const override;
    FrameCode &operator =(const FrameCode &other);

    // Serializable interface
public:
    Value save(const Value &creator) const override;
    bool restore(const Value &value, int = -1) override;

private:
    bool insertTableSeq(Frame *frame, const WeakTablePtr &weakTable);
    bool removeTableSeq(const WeakTablePtr &weakTable);

private:
    FrameCodeData *d;
    friend class Frame;
};

} // end of namespace J

#endif // PROTOCORE_FRAMECODE_H
