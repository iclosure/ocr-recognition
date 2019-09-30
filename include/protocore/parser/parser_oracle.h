#ifndef PROTOCORE_PARSER_ORACLE_H
#define PROTOCORE_PARSER_ORACLE_H

#include "parser_sql.h"

namespace J {

class JOracleParser;
typedef std::shared_ptr<JOracleParser> JOracleParserPtr;

class JOracleParserData;

class PROTOCORE_EXPORT JOracleParser : public JSqlParser
{
public:
    explicit JOracleParser(const Json::Value &config);
    ~JOracleParser() J_OVERRIDE;

    int sqlType() const override;

    // JSqlParser interface
protected:

private:
    J_DISABLE_COPY(JOracleParser)
    JOracleParserData *d;
};

}   // end of namespace J

#endif // PROTOCORE_PARSER_ORACLE_H
