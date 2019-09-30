#ifndef PROTOCORE_SHAREDFILE_H
#define PROTOCORE_SHAREDFILE_H

#include "../global.h"
#include <stdint.h>

namespace J {

class SharedFileData;

class PROTOCORE_EXPORT SharedFile
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
        Unbuffered = 0x0020,
        NewOnly = 0x0040,
        ExistingOnly = 0x0080
    };

    explicit SharedFile(const std::string &fileName);
    ~SharedFile();

    std::string fileName() const;
    void setFileName(const std::string &fileName);

    static std::string encodeName(const std::string &fileName);
    static std::string decodeName(const std::string &localFileName);

    bool exists() const;

    bool isOpen() const;
    bool open(OpenMode openMode);
    void close();

    int64_t size() const;

    bool resize(int64_t size);

    int64_t pos() const;
    bool seek(int64_t pos);

    int64_t write(const char *data, int64_t size);
    int64_t read(char *data, int64_t size);

    bool flush();

private:
    J_DISABLE_COPY(SharedFile)
    SharedFileData *d;
};

}   // end of namespace J

#endif  // PROTOCORE_SHAREDFILE_H
