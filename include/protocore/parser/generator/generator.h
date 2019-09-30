#ifndef PROTOCORE_GENERATOR_H
#define PROTOCORE_GENERATOR_H

#include "../parser.h"

namespace J {

class Generator;
class GeneratorData;
typedef std::shared_ptr<Generator> GeneratorPtr;

class Object;
typedef std::shared_ptr<Object> ObjectPtr;

class Vehicle;
typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::vector<VehiclePtr> VehiclePtrArray;

class System;
typedef std::shared_ptr<System> SystemPtr;
typedef std::vector<SystemPtr> SystemPtrArray;

class Table;
typedef std::shared_ptr<Table> TablePtr;
typedef std::vector<TablePtr> TablePtrArray;

class Parser;

// class GeneratorFactory

class GeneratorFactory;
typedef std::shared_ptr<GeneratorFactory> GeneratorFactoryPtr;

class GeneratorFactory
{
public:
    virtual ~GeneratorFactory() {}
    virtual GeneratorPtr create(int type, Parser *parser) const = 0;
};

// class Generator

class PROTOCORE_EXPORT Generator
{
public:
    enum GeneratorType {
        GeneratorTypeInvalid = -1,
        GeneratorTypeXml,
        GeneratorTypeJson,
        GeneratorTypeCSharp,
        GeneratorTypeCpp,
        GeneratorTypeHtml,
        GeneratorTypeExcel,
        GeneratorTypeMatlab,
        GeneratorTypeWord,
        GeneratorTypePdf,
        GeneratorTypeSQLite
    };

    explicit Generator(GeneratorType type, Parser *parser = nullptr);
    virtual ~Generator();

    GeneratorType generateType() const;

    static std::string fileType(const std::string &filePath);
    static GeneratorPtr create(const Json::Value &config, Parser *parser = nullptr);
    virtual bool startup();
    virtual void shutdown();
    virtual bool generate(const ObjectPtr &object, const std::string &filePath);
    virtual bool generate(const TablePtr &table, const std::string &filePath) = 0;
    virtual Parser *parser();
    virtual const Parser *parser() const;

    static bool loadPlugins();
    static void unloadPlugins();

    static bool isGeneratorPluginExists();

private:
    J_DISABLE_COPY(Generator)
    GeneratorData *d;
};

} // end of namespace J

#endif // PROTOCORE_GENERATOR_H
