#ifndef PROTOCORE_PARSER_FILE_H
#define PROTOCORE_PARSER_FILE_H

#include "parser.h"

namespace J {

class JFileParser;
typedef std::shared_ptr<JFileParser> JFileParserPtr;

class JFileParserData;

class PROTOCORE_EXPORT JFileParser : public Parser
{
public:
    enum FileType {
        InvalidFile = -1,
        JsonFile,
        XmlFile
    };

    explicit JFileParser(int fileType, const Json::Value &config);
    virtual ~JFileParser() J_OVERRIDE;

    static ParserPtr create(const Json::Value &config);

    int fileType() const;

    std::string filePath() const;
    void setFilePath(const std::string &filePath);

    std::string basePath() const;
    std::string fileName() const;
    std::string suffix() const;

    static std::string suffix(const std::string &fileName);
    static bool exists(const std::string &filePath);
    static bool copy(const std::string &from, const std::string &to);
    static bool rename(const std::string &from, const std::string &to);
    static bool remove(const std::string &filePath);
    static std::string fullPath(const std::string &basePath, const std::string &fileName);

private:
    J_DISABLE_COPY(JFileParser)
    JFileParserData *d;
};

} // end of namespace J

#endif // PROTOCORE_PARSER_FILE_H
