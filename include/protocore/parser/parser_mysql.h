#ifndef PROTOCORE_PARSER_MYSQL_H
#define PROTOCORE_PARSER_MYSQL_H

#include "parser_sql.h"

namespace J {

class JMySqlParser;
typedef std::shared_ptr<JMySqlParser> JMySqlParserPtr;

class JMySqlParserData;

class PROTOCORE_EXPORT JMySqlParser : public JSqlParser
{
public:
    explicit JMySqlParser(const Json::Value &config);
    ~JMySqlParser() J_OVERRIDE;

    int sqlType() const override;

    // JSqlParser interface
protected:
    bool existsTable(const std::string &tableName) const override;
    soci::details::prepare_temp_type prepareTableNames(const std::string &like) const override;
    std::string autoIncrementKey() const override;
    std::string keyQuote() const override;

private:
    J_DISABLE_COPY(JMySqlParser)
    JMySqlParserData *d;
};

}   // end of namespace J

#endif // PROTOCORE_PARSER_MYSQL_H
