#ifndef PROTOCORE_PARSER_XML_H
#define PROTOCORE_PARSER_XML_H

#include "parser.h"
#include "generator/generator.h"
#include "parser_file.h"
#include <memory>

class TiXmlDocument;

namespace J {

class JXmlParser;
typedef std::shared_ptr<JXmlParser> JXmlParserPtr;

class PROTOCORE_EXPORT JXmlParser : public JFileParser, public Generator
{
public:
    explicit JXmlParser(const Json::Value &config);
    ~JXmlParser() J_OVERRIDE;

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

private:
    static TiXmlElement *createDocument(TiXmlDocument *document = nullptr, TiXmlElement *emRoot = nullptr);
    TiXmlElement *rootElement(bool create = false, TiXmlElement *emRoot = nullptr) const;
    TiXmlElement *vehicleElement(const std::string &vehicleId, bool create = false) const;
    TiXmlElement *systemElement(const std::string &vehicleId, const std::string &systemId,
                                bool create = false) const;
    TiXmlElement *tableElement(const std::string &vehicleId, const std::string &systemId,
                               const std::string &tableId, bool create = false) const;
    TiXmlElement *tableElement(const std::string &tableId, bool create = false) const;
    bool saveDocument(TiXmlDocument *document) const;
    bool saveAsDocument(TiXmlDocument *document, const std::string &filePath) const;

    // Generator interface
public:
    bool startup() override;
    void shutdown() override;
    bool generate(const ObjectPtr &object, const std::string &filePath) override;
    bool generate(const TablePtr &table, const std::string &filePath) override;
    Parser *parser() override;
    const Parser *parser() const override;

private:
    J_DISABLE_COPY(JXmlParser)
    friend class Parser;
};

}   // end of namespace J

#endif
