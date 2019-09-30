#ifndef PROTOCORE_PARSER_PSQL_H
#define PROTOCORE_PARSER_PSQL_H

#include "parser_sql.h"

namespace J {

class JPSQLParser;
typedef std::shared_ptr<JPSQLParser> JPSQLParserPtr;

class JPSQLParserData;

class PROTOCORE_EXPORT JPSQLParser : public JSqlParser
{
public:
    explicit JPSQLParser(const Json::Value &config);
    ~JPSQLParser() J_OVERRIDE;

    int sqlType() const override;

    // JSqlParser interface
protected:
    std::string autoIncrementKey() const override;
    std::string keyQuote() const override;
    std::string nameOfDoubleType() const override;
    std::string serialColumn(const std::string &name, bool unique, bool notNull) const override;

private:
    J_DISABLE_COPY(JPSQLParser)
    JPSQLParserData *d;
};

}   // end of namespace J

#endif // PROTOCORE_PARSER_PSQL_H
