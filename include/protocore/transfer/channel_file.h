#ifndef PROTOCORE_CHANNEL_FILE_H
#define PROTOCORE_CHANNEL_FILE_H

#include "channel.h"
#include <fstream>

namespace J {

class FileChannel;
typedef std::shared_ptr<FileChannel> FileChannelPtr;

class FileChannelData;

/**
 * @brief 数据文件通道，用于数据记录或回放
 *        数据文件通道不支持同时读和写操作，必须在初始化时指定是读模式还是写模式
 */
class PROTOCORE_EXPORT FileChannel : public Channel
{
public:
    enum OpenMode {
        NotOpen = 0x0000,
        ReadOnly = 0x0001,
        WriteOnly = 0x0002,
        ReadWrite = ReadOnly | WriteOnly,
        Append = 0x0004,
        Truncate = 0x0008,
        Text = 0x0010,
        Unbuffered = 0x0020
    };

    enum SaveFormat {
        SaveFormatDomain = 0x01,    // include domain of table
        SaveFormatTimestamp = 0x02, // include timestamp
        SaveFormatNormal = SaveFormatDomain | SaveFormatTimestamp
    };

    explicit FileChannel(const std::string &id);
    explicit FileChannel(const std::string &filePath, OpenMode openMode,
                         const std::string &id = std::string());
    virtual ~FileChannel() J_OVERRIDE;

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
     * @return "file: -f ["filePath"] -m [r][w]"
     */
    std::string config() const override;

    /**
     * @brief setConfig
     * @param config : "file: -f ["filePath"] -m [r][w]"
     * @return
     */
    bool setConfig(const std::string &config) override;

    std::string desc() const override;

    std::string filePath() const;
    void setFilePath(const std::string &filePath);

    OpenMode openMode() const;
    void setOpenMode(OpenMode openMode);

    SaveFormat saveFormat() const;
    void setSaveFormat(SaveFormat saveFormat);

    unsigned int fileHeader() const;
    void setFileHeader(unsigned int header);

    std::string domain() const;
    void setDomain(const std::string &domain);

    int lastErrorCode() const override;
    std::string lastError() const override;

    // Serializable interface
public:
    Json::Value save() const override;
    bool restore(const Json::Value &json, int /*deep*/ = -1) override;

private:
    J_DISABLE_COPY(FileChannel)
    FileChannelData *d;
};

} // end of namespace J

#endif // PROTOCORE_CHANNEL_FILE_H
