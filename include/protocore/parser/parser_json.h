#ifndef PROTOCORE_PARSER_JSON_H
#define PROTOCORE_PARSER_JSON_H

#include "parser.h"
#ifndef HAVE_NO_GENERATOR
#include "generator/generator.h"
#endif
#include "parser_file.h"

namespace J {

class JJsonParser;
typedef std::shared_ptr<JJsonParser> JJsonParserPtr;

class PROTOCORE_EXPORT JJsonParser : public JFileParser
        #ifndef HAVE_NO_GENERATOR
        , public Generator
        #endif
{
public:
    explicit JJsonParser(const Json::Value &config);
    ~JJsonParser() J_OVERRIDE;

    bool parse(RootPtr &root, int deep) const override;
    bool parse(VehiclePtrArray &vehicles, int deep, Object *parent) const override;
    bool parse(const std::string &vehicleId, VehiclePtr &vehicle, int deep,
               Object *parent) const override;
    bool parse(const std::string &vehicleId, SystemPtrArray &systems, int deep,
               Object *parent) const override;
    bool parse(const std::string &vehicleId, const std::string &systemId, SystemPtr &system,
               int deep, Object *parent) const override;
    bool parse(const std::string &vehicleId, const std::string &systemId, TablePtrArray &tables,
               int deep, Object *parent) const override;
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

public:
    Json::Value queryRoot() const;
    Json::Value queryVehicles() const;
    Json::Value queryVehicle(const std::string &vehicleId) const;
    Json::Value querySystems(const std::string &vehicleId) const;
    Json::Value querySystem(const std::string &vehicleId, const std::string &systemId) const;
    Json::Value queryTables(const std::string &vehicleId, const std::string &systemId) const;
    Json::Value queryTable(const std::string &vehicleId, const std::string &systemId,
                           const std::string &tableId) const;
    Json::Value queryItems(const std::string &vehicleId, const std::string &systemId,
                           const std::string &tableId) const;
    Json::Value queryItem(const std::string &vehicleId, const std::string &systemId,
                          const std::string &tableId, const std::string &itemId) const;
    Json::Value queryTables() const;
    Json::Value queryTable(const std::string &tableId) const;

#ifndef HAVE_NO_GENERATOR
    // Generator interface
public:
    bool startup() override;
    void shutdown() override;
    bool generate(const ObjectPtr &object, const std::string &filePath) override;
    bool generate(const TablePtr &table, const std::string &filePath) override;
    Parser *parser() override;
    const Parser *parser() const override;
#endif

private:
    J_DISABLE_COPY(JJsonParser)
};

} // end of namespace J

#endif // PROTOCORE_PARSER_JSON_H

