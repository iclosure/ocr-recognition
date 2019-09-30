#ifndef PROTOCORE_PARSER_SQL_H
#define PROTOCORE_PARSER_SQL_H

#include "parser.h"
#include "soci/prepare-temp-type.h"

namespace soci {
class session;
typedef std::shared_ptr<session> sessionptr;
}

namespace J {

class Value;
class ValueDelegate;
typedef std::shared_ptr<ValueDelegate> ValueDelegatePtr;

class JSqlParser;
typedef std::shared_ptr<JSqlParser> JSqlParserPtr;

class SqlDelegate;
typedef std::shared_ptr<SqlDelegate> SqlDelegatePtr;

typedef std::map<std::string, std::string> map_key_value;

struct DsRowInfo;

class SqlParserData;

class JSqlParser : public Parser
{
public:
    enum SqlType {
        InvalidSql = -1,
        SQLite3Type,
        MySQLType,
        OracleType,
        ODBCType,
        PostgreSQLType,
        UserSqlType = 1000
    };

    explicit JSqlParser(const Json::Value &config);
    virtual ~JSqlParser() J_OVERRIDE;

    std::string connectString() const;
    void setConnectString(const std::string &str);

    soci::session &session() const;

    static ParserPtr create(const Json::Value &config);

    virtual int sqlType() const = 0;

    SqlDelegatePtr delegate() const;

public:
    bool isOpen() const;
    bool open();
    void close();
    bool beginTrans();
    bool commitTrans();
    bool rollbackTrans();

    virtual bool existsTable(const std::string &tableName) const;
    virtual soci::details::prepare_temp_type
    prepareTableNames(const std::string &like = std::string()) const;
    virtual std::string autoIncrementKey() const;
    virtual std::string keyQuote() const;
    std::string quoteKey(const std::string &key) const;
    virtual std::string nameOfDoubleType() const;
    virtual std::string serialColumn(const std::string &name, bool unique, bool notNull) const;

    std::shared_ptr<soci::statement> createMajorStmt(DsRowInfo &st) const;
    bool dropMajorTable();

protected:
    bool createMajorTable(bool drop = false);

private:
    bool parse(RootPtr &root, int deep) const override;
    bool parse(VehiclePtrArray &vehicles, int deep, Object *parent) const override;
    bool parse(const std::string &vehicleId, VehiclePtr &vehicle, int deep,
               Object *parent) const override;
    bool parse(const std::string &vehicleId, SystemPtrArray &systems, int deep,
               Object *parent) const override;
    bool parse(const std::string &vehicleId, const std::string &systemId,
               SystemPtr &system, int deep, Object *parent) const override;
    bool parse(const std::string &vehicleId, const std::string &systemId,
               TablePtrArray &tables, int deep, Object *parent) const override;
    bool parse(const std::string &vehicleId, const std::string &systemId, const std::string &tableId,
               TablePtr &table, int deep, Object *parent) const override;
    bool parse(const std::string &vehicleId, const std::string &systemId, const std::string &tableId,
               ItemPtrArray &items, int deep, Object *parent) const override;
    bool parse(TablePtrArray &tables) const override;
    bool parse(const std::string &tableId, TablePtr &table) const override;

    Json::Value queryTable(const std::string &domain, int domainType) const override;

    bool save(const RootPtr &root) override;
    bool save(const VehiclePtrArray &vehicles) override;
    bool save(const std::string &vehicleId, const VehiclePtr &vehicle) override;
    bool save(const std::string &vehicleId, const SystemPtrArray &systems) override;
    bool save(const std::string &vehicleId, const std::string &systemId,
              const SystemPtr &system) override;
    bool save(const std::string &vehicleId, const std::string &systemId,
              const TablePtrArray &tables) override;
    bool save(const std::string &vehicleId, const std::string &systemId,
              const std::string &tableId, const TablePtr &table) override;
    bool save(const std::string &vehicleId, const std::string &systemId,
              const std::string &tableId, const ItemPtrArray &items) override;
    bool save(const TablePtrArray &tables) override;
    bool save(const std::string &tableId, const TablePtr &table) override;
    bool save(const TablePtr &table) override;

private:
    bool queryTableNames(std::vector<std::string> &tableNames,
                         const std::string &like = std::string()) const;
    std::string majorTableName() const;
    bool dropTable(const std::string &tableName);

    bool insertRow(const std::string &tableName, const map_key_value &values);
    int existsRow(const std::string &tableName, const std::string &condition,
                  bool remove = false);

private:
    J_DISABLE_COPY(JSqlParser)
    friend class SqlDelegate;
    friend class JSqlite3Parser;
    SqlParserData *d;
};

} // end of namespace J

#endif // PROTOCORE_PARSER_SQL_H
