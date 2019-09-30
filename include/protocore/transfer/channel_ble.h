#ifndef PROTOCORE_CHANNEL_BLE_H
#define PROTOCORE_CHANNEL_BLE_H

#include "channel.h"

namespace J {

// struct PeripheralInfo

struct PeripheralInfo
{
    std::string name;
    std::string address;
    std::string uuid;
    int type;
    int rssi;

    PeripheralInfo()
        : type(-1)
        , rssi(-1)
    {

    }

    PeripheralInfo(const std::string &name, const std::string &address,
                  const std::string &uuid, int type, int rssi)
        : name(name), address(address), uuid(uuid), type(type), rssi(rssi)
    {

    }

    PeripheralInfo(const PeripheralInfo &other)
    {
        *this = other;
    }

    PeripheralInfo &operator =(const PeripheralInfo &other)
    {
        if (this == &other) {
            return *this;
        }
        name = other.name;
        address = other.address;
        uuid = other.uuid;
        type = other.type;
        rssi = other.rssi;
        return *this;
    }

    bool operator ==(const PeripheralInfo &other) const
    {
        if (this == &other) {
            return true;
        }
        return (name == other.name
                && address == other.address
                && uuid == other.uuid
                && type == other.type);
    }
};

// class BleChannel

class BleChannel;
typedef std::shared_ptr<BleChannel> BleChannelPtr;

class BleChannelData;

class PROTOCORE_EXPORT BleChannel : public Channel
{
public:
    typedef std::function<void(int state)> StateChangedEvent;
    typedef std::function<void(const std::string &uuid, const std::string &address,
                               const std::string &name, int type, int rssi)> DiscoverEvent;
    typedef std::function<void(const std::string &uuid, const std::string &name,
                               const std::string &errorString)> FailToConnectEvent;
    typedef std::function<void(const std::string &uuid, const std::string &name)> ConnectedEvent;
    typedef std::function<void(const std::string &uuid, const std::string &name,
                               const std::string &errorString)> DisconnectedEvent;
    typedef std::function<void(const std::string &uuid, const std::string &name)> UpdateNameEvent;
    typedef std::function<void(const std::string &uuid, int rssi)> UpdateRSSIEvent;
    typedef std::function<void(const std::string &uuid)> ReadyToWriteEvent;
    typedef std::function<void(const std::string &uuid, const char *data, int size)> RecvDataEvent;

    enum DeviceState {
        StateUnknown = 0,
        StateResetting,
        StateUnsupported,
        StateUnauthorized,
        StatePoweredOff,
        StatePoweredOn
    };

    enum ConnectState {
        ConnectStateDisconnected = 0,
        ConnectStateConnecting,
        ConnectStateConnected,
        ConnectStateDisconnecting
    };

    explicit BleChannel(const std::string &id = std::string());
    virtual ~BleChannel() J_OVERRIDE;

    bool isOpen() const override;
    bool open() override;
    void close() override;

    bool waitForReadyRead(int msecs) override;
    int read(char* buffer, int size) override;
    int write(const char* buffer, int size) override;
    int sizeOfIn() const override;
    int sizeOfOut() const override;
    void flush() override;

    std::string config() const override;
    bool setConfig(const std::string &config) override;

    std::string desc() const override;

    int lastErrorCode() const override;
    std::string lastError() const override;

    //

    int deviceState() const;
    int connectState() const;

    std::string notifyServerUuid() const;
    void setNotifyServerUuid(const std::string &uuid);

    std::string writeServerUuid() const;
    void setWriteServerUuid(const std::string &uuid);

    std::string notifyCharacteristicUuid() const;
    void setNotifyCharacteristicUuid(const std::string &uuid);

    std::string readCharacteristicUuid() const;
    void setReadCharacteristicUuid(const std::string &uuid);

    std::string writeCharacteristicUuid() const;
    void setWriteCharacteristicUuid(const std::string &uuid);

    bool startScan();
    void stopScan();
    void clearDevice();
    bool isScanning() const;

    bool isConnected(const std::string &uuid) const;
    std::string currentUuid() const;
    bool connectTo(const std::string &uuid);
    void disconnectFrom(const std::string &uuid);

    void setStateChangedEvent(StateChangedEvent event, void *owner);
    void setDiscoverEvent(DiscoverEvent event, void *owner);
    void setFailToConnectEvent(FailToConnectEvent event, void *owner);
    void setConnectedEvent(ConnectedEvent event, void *owner);
    void setDisconnectedEvent(DisconnectedEvent event, void *owner);
    void setUpdateNameEvent(UpdateNameEvent event, void *owner);
    void setUpdateRSSIEvent(UpdateRSSIEvent event, void *owner);
    void setReadyToWriteEvent(ReadyToWriteEvent event, void *owner);
    void setRecvDataEvent(RecvDataEvent event, void *owner);

    // Serializable interface
public:
    Json::Value save() const override;
    bool restore(const Json::Value &json, int /*deep*/ = -1) override;

private:
    J_DISABLE_COPY(BleChannel)
    BleChannelData *d;
};

} // end of namespace J

#endif // PROTOCORE_CHANNEL_BLE_H
