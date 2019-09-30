#ifndef PROTOCORE_CHANNEL_H
#define PROTOCORE_CHANNEL_H

#include "../global.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace J {

enum ChannelType {
    ChannelInvalid = -1,    //
    ChannelSerial = 0,      // serialport
    ChannelUdp,             // udp channel
    ChannelFile,            // file channel
    ChannelArinc429,        // arinc429
    ChannelBle,             // ble-bluetooth
    ChannelTotal            //
};

class Channel;
typedef std::shared_ptr<Channel> ChannelPtr;
typedef std::vector<ChannelPtr> ChannelPtrArray;

class ChannelData;

class PROTOCORE_EXPORT Channel : public Json::Serializable
{
public:
    explicit Channel(ChannelType channelType = ChannelInvalid, const std::string &id = std::string());
    virtual ~Channel() J_OVERRIDE;

    static ChannelPtr create(int channelType, const std::string &id = std::string());
    static ChannelPtr create(const std::string &config);
    static ChannelPtr create(const Json::Value &config);
    static ChannelPtr createByType(const std::string &sType, const std::string &id = std::string());

    virtual bool isOpen() const;
    virtual bool open();
    virtual void close();

    virtual bool waitForReadyRead(int msecs);
    virtual int read(char* buffer, int size);
    virtual int write(const char* buffer, int size);

    virtual int sizeOfIn() const;
    virtual int sizeOfOut() const;
    virtual void flush();

    ChannelType channelType() const;
    std::string channelTypeString() const;
    static std::string channelTypeString(ChannelType type);
    static ChannelType stringChannelType(const std::string &str);

    std::string identity() const;
    void setIdentity(const std::string &identity);

    virtual std::string config() const;
    virtual bool setConfig(const std::string &config);
    bool setConfig(const std::unordered_map<std::string, std::string> &items);

    virtual std::string name() const;
    void setName(const std::string &name);

    bool autoSend() const;
    void setAutoSend(bool enabled);

    int sendInterval() const;
    void setSendInterval(int interval);

    int recvInterval() const;
    void setRecvInterval(int interval);

    virtual std::string desc() const;
    virtual void setDesc(const std::string &desc);

    virtual int lastErrorCode() const;
    virtual std::string lastError() const;

    ChannelPtr relayer() const;
    void setRelayer(const ChannelPtr &relayer);

    static std::unordered_map<std::string, std::string> parseConfig(const std::string &config);
    static std::string parserValue(const std::string &config, const std::string &key);

    // Serializable interface
public:
    virtual Json::Value save() const override;
    virtual bool restore(const Json::Value &json, int /*deep*/ = -1) override;

private:
    J_DISABLE_COPY(Channel)
    ChannelData *d;
};

} // end of namespace J

#endif // PROTOCORE_CHANNEL_H
