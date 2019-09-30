#ifndef PROTOCORE_CHANNEL_SERIAL_H
#define PROTOCORE_CHANNEL_SERIAL_H

#include "channel.h"
#include <vector>

namespace J {

typedef struct PortInfo_t {
    std::string port;
    std::string desc;
    std::string hardwareId;
} PortInfo_t;

class SerialChannel;
typedef std::shared_ptr<SerialChannel> SerialChannelPtr;

class SerialChannelData;

class PROTOCORE_EXPORT SerialChannel : public Channel
{
public:
    enum DataBits {
        Data5 = 5,
        Data6 = 6,
        Data7 = 7,
        Data8 = 8,
        UnknownDataBits = -1
    };

    enum StopBits {
        OneStop = 1,
        OneAndHalfStop = 3,
        TwoStop = 2,
        UnknownStopBits = -1
    };

    enum Parity {
        NoParity = 0,
        EvenParity = 2,
        OddParity = 3,
        SpaceParity = 4,
        MarkParity = 5,
        UnknownParity = -1
    };

    explicit SerialChannel(const std::string &id = std::string());
    explicit SerialChannel(const std::string &portName, int baudRate, int dataBits = Data8,
                           int stopBits = OneStop, int parity = NoParity,
                           const std::string &id = std::string());
    virtual ~SerialChannel() J_OVERRIDE;

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
    bool setConfig(const std::string &portName, int baudRate, int dataBits = Data8,
                   int stopBits = OneStop, int parity = NoParity);

    std::string portName() const;
    void setPortName(const std::string &portName);

    int baudRate() const;
    void setBaudRate(int baudRate);

    int dataBits() const;
    void setDataBits(int dataBits);

    int stopBits() const;
    void setStopBits(int stopBits);

    int parity() const;
    void setParity(int parity);

    int flowControl() const;
    void setFlowControl(int value);

    int lastErrorCode() const override;
    std::string lastError() const override;

    static std::vector<std::string> availablePorts();
    static void availablePorts(std::vector<std::string> &ports);

    static std::vector<int> standardBaudRates();
    static void standardBaudRates(std::vector<int> &baudRates);

    // Serializable interface
public:
    Json::Value save() const override;
    bool restore(const Json::Value &json, int /*deep*/ = -1) override;

private:
    J_DISABLE_COPY(SerialChannel)
    SerialChannelData *d;
};

} // end of namespace J

#endif // PROTOCORE_CHANNEL_SERIAL_H
