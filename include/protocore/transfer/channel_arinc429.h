#ifndef PROTOCORE_CHANNEL_ARINC429_H
#define PROTOCORE_CHANNEL_ARINC429_H

#include "channel.h"

namespace J {

class Arinc429Channel;
typedef std::shared_ptr<Arinc429Channel> Arinc429ChannelPtr;

class Arinc429ChannelData;

class PROTOCORE_EXPORT Arinc429Channel : public Channel
{
public:
    explicit Arinc429Channel(const std::string &id = std::string());
    virtual ~Arinc429Channel() J_OVERRIDE;

    bool isOpen() const override;
    bool open() override;
    void close() override;

    bool waitForReadyRead(int msecs) override;
    int read(char* buffer, int size) override;
    int write(const char* buffer, int size) override;
    int sizeOfIn() const override;
    int sizeOfOut() const override;
    void flush() override;

    /**
     * @brief config
     * @return "serial: -n [portname] -b [baudrate] -d [datebits] -s [stopbits] -p [parity]"
     */
    std::string config() const override;

    /**
     * @brief setConfig
     * @param config : "serial: -n [portname] -b [baudrate] -d [datebits] -s [stopbits] -p [parity]"
     * @return
     */
    bool setConfig(const std::string &config) override;

    std::string desc() const override;

    int lastErrorCode() const override;
    std::string lastError() const override;

    // Serializable interface
public:
    Json::Value save() const override;
    bool restore(const Json::Value &json, int /*deep*/ = -1) override;

private:
    J_DISABLE_COPY(Arinc429Channel)
    Arinc429ChannelData *d;
};

} // end of namespace J

#endif // PROTOCORE_CHANNEL_ARINC429_H
