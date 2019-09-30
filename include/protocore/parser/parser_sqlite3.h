#ifndef PROTOCORE_PARSER_SQLITE3_H
#define PROTOCORE_PARSER_SQLITE3_H

#include "parser_sql.h"
#include "../3rdpart/sqlite3/sqlite3.h"
#include "generator/generator.h"

namespace J {

class JSqlite3Parser;
typedef std::shared_ptr<JSqlite3Parser> JSqlite3ParserPtr;

class JSqlite3ParserData;

class PROTOCORE_EXPORT JSqlite3Parser : public JSqlParser, public Generator
{
public:
    explicit JSqlite3Parser(const Json::Value &config);
    ~JSqlite3Parser() J_OVERRIDE;

    int sqlType() const override;

    // JSqlParser interface
protected:
    std::string keyQuote() const override;

    // Generator interface
public:
    bool startup() override;
    void shutdown() override;
    bool generate(const ObjectPtr &object, const std::string &filePath) override;
    bool generate(const TablePtr &table, const std::string &filePath) override;
    Parser *parser() override;
    const Parser *parser() const override;

private:
    J_DISABLE_COPY(JSqlite3Parser)
    JSqlite3ParserData *d;
};

}   // end of namespace J

#endif // PROTOCORE_PARSER_SQLITE3_H
