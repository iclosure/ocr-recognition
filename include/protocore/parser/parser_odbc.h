#ifndef PROTOCORE_PARSER_ODBC_H
#define PROTOCORE_PARSER_ODBC_H

#include "parser_sql.h"

namespace J {

class JOdbcParser;
typedef std::shared_ptr<JOdbcParser> JOdbcParserPtr;

class JOdbcParserData;

class PROTOCORE_EXPORT JOdbcParser : public JSqlParser
{
public:
    explicit JOdbcParser(const Json::Value &config);
    ~JOdbcParser() J_OVERRIDE;

    int sqlType() const override;

    // JSqlParser interface
protected:

private:
    J_DISABLE_COPY(JOdbcParser)
    JOdbcParserData *d;
};

}   // end of namespace J

#endif // PROTOCORE_PARSER_ODBC_H
