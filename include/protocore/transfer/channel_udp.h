#ifndef PROTOCORE_CHANNEL_UDP_H
#define PROTOCORE_CHANNEL_UDP_H

#include <string>
#include "channel.h"

namespace J {

class UdpChannel;
typedef std::shared_ptr<UdpChannel> UdpChannelPtr;

class UdpChannelData;

class PROTOCORE_EXPORT UdpChannel : public Channel
{
public:
    enum OpenMode {
        NotOpen = 0x0000,
        ReadOnly = 0x0001,
        WriteOnly = 0x0002,
        ReadWrite = ReadOnly | WriteOnly
    };

    explicit UdpChannel(const std::string &id = std::string());
    explicit UdpChannel(std::string localAddr, int localPort,
                        std::string remoteAddr, int remotePort,
                        int openMode = ReadWrite,
                        const std::string &id = std::string());
    virtual ~UdpChannel() J_OVERRIDE;

    bool isOpen() const override;
    bool open() override;
    void close() override;
    int read(char* buffer, int size) override;
    int write(const char* buffer, int size) override;
    int sizeOfIn() const override;
    int sizeOfOut() const override;
    void flush() override;

    /**
     * @brief config
     * @return "udp: -local [ip]:[port] -remote [ip]:[port]"
     */
    std::string config() const override;

    /**
     * @brief setConfig
     * @param config : "udp: -local [ip]:[port] -remote [ip]:[port]"
     * @return
     */
    bool setConfig(const std::string &config) override;

    std::string desc() const override;

    int openMode() const;
    void setOpenMode(int openMode);

    bool setConfig(const std::string &localAddr, int localPort,
                   const std::string &remoteAddr, int remotePort);

    bool isMulticast(const std::string &ip) const;

    std::string localAddr() const;
    void setLocalAddr(const std::string &addr);
    int localPort() const;
    void setLocalPort(int port);

    std::string remoteAddr() const;
    void setRemoteAddr(const std::string &addr);
    int remotePort() const;
    void setRemotePort(int port);

    int lastErrorCode() const override;
    std::string lastError() const override;

    // Serializable interface
public:
    Json::Value save() const override;
    bool restore(const Json::Value &json, int /*deep*/ = -1) override;

private:
    J_DISABLE_COPY(UdpChannel)
    UdpChannelData *d;
};

} // end of namespace J

#endif // J::COMM_UDPCHANNEL_H
