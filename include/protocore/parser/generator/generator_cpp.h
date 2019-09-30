#ifndef PROTOCORE_GENERATOR_CPP_H
#define PROTOCORE_GENERATOR_CPP_H

#include "generator.h"

namespace J {

class CppGenerator;
typedef std::shared_ptr<CppGenerator> CppGeneratorPtr;

class CppGeneratorData;

class PROTOCORE_EXPORT CppGenerator : public Generator
{
public:
    explicit CppGenerator(Parser *parser);
    ~CppGenerator() J_OVERRIDE;

    bool startup() override;
    void shutdown() override;
    bool generate(const ObjectPtr &object, const std::string &filePath) override;
    bool generate(const TablePtr &table, const std::string &filePath) override;

private:
    J_DISABLE_COPY(CppGenerator)
    CppGeneratorData *d;
};

} // end of namespace J

#endif // PROTOCORE_GENERATOR_CPP_H
