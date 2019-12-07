import qbs
import qbs.File
import qbs.FileInfo
import qbs.Environment
import tools.EnvUtils

Product {
    name: 'DataStudioInstall'
    type: [ 'header.out', 'library.out' ]

    condition: !qbs.targetOS.contains('android')

    Depends { name: 'cpp' }
    Depends { name: 'module.soci' }

    readonly property path datastudioDir: EnvUtils.datastudioDir(project)
    readonly property bool datastudioExists: !!datastudioDir
    readonly property bool isSelfDirectory: (datastudioDir == project.sourceDirectory)
    readonly property bool isDSProject: (project.projectName === 'datastudio')

    property stringList modules: []
    property string moduleInstallDir: 'bin'
    property bool installGenerator: false
    property bool installMeta: false
    // soci
    property bool installSOCI: false
    property bool installSOCIAll: false
    property bool installEmpty: installSOCI || installSOCIAll
    property bool installSQLite3: installSOCI || installSOCIAll
    property bool installMySQL: installSOCI || installSOCIAll
    property bool installODBC: installSOCI || installSOCIAll
    property bool installOracle: installSOCIAll
    property bool installPostgreSQL: installSOCIAll
    property bool installDB2: installSOCIAll
    property bool installFireBird: installSOCIAll
    // plugin-xplane
    property bool installXPLM: false

    // modules - headers

    Group {
        id: modules_headers
        name: 'modules_headers'
        condition: {
            return datastudioExists && !isSelfDirectory
        }
        prefix: datastudioDir + '/include/'
        files: {
            var files = []
            modules.forEach(function(item){
                files.push(item + '/**/*.h')
                files.push(item + '/**/*.hh')
                files.push(item + '/**/*.hpp')
                files.push(item + '/**/*.hxx')
            })
            return files
        }
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: datastudioExists && !isSelfDirectory
        inputs: modules_headers.fileTags
        Artifact {
            fileTags: [ 'header.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.datastudioDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }

    // modules - library

    Group {
        id: modules_dynamic
        name: 'modules_dynamic'
        condition: datastudioExists && !isSelfDirectory || !isDSProject
        prefix: datastudioDir + '/lib/' + project.archDir + '/'
        files: {
            var files = []
            modules.forEach(function(item){
                files.push(item + EnvUtils.dylibSuffix(qbs) + '*')
            })
            return files
        }
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: 'bin'
    }

    Group {
        id: modules_library
        name: 'modules_library'
        condition: datastudioExists && !isSelfDirectory
        prefix: modules_dynamic.prefix
        files: {
            var files = []
            modules.forEach(function(item){
                files.push(item + '*.lib')
                files.push(item + '*.dll')
            })
            return files
        }
        excludeFiles: [ EnvUtils.incDylibFuzzy(qbs) ]
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: datastudioExists && !isSelfDirectory
        inputs: modules_dynamic.fileTags.concat(modules_library.fileTags)
        Artifact {
            fileTags: [ 'library.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.datastudioDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }

    // modules - protocore/generator

    Group {
        id: modules_generator
        name: 'modules_generator'
        condition: installGenerator && (datastudioExists && !isSelfDirectory || !isDSProject)
        prefix: datastudioDir + '/lib/' + project.archDir + '/plugins/generator/'
        files: [ '**/*.dll' ]
        excludeFiles: [ EnvUtils.excDylibFuzzy(qbs, true) ]
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: 'bin/plugins/generator'
        qbs.installSourceBase: prefix
    }

    //  modules - meta

    Group {
        id: meta_dynamic
        name: 'meta_dynamic'
        condition: installMeta && (datastudioExists && !isSelfDirectory || !isDSProject)
        prefix: datastudioDir + '/lib/' + project.archDir + '/plugins/meta/'
        files: [ '**/*.dll', '**/qmldir', '**/*.qml', '**/*.js', '**/imports/**/*' ]
        excludeFiles: [ EnvUtils.excDylibFuzzy(qbs, true) ]
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: 'bin/meta'
        qbs.installSourceBase: prefix
    }

    Group {
        id: meta_library
        condition: datastudioExists && installMeta && !isSelfDirectory
        name: 'meta_library'
        prefix: datastudioDir + '/lib/' + project.archDir + '/plugins/meta/'
        files: [ '**/*.dll', '**/*.qmltypes' ]
        excludeFiles: [ EnvUtils.incDylibFuzzy(qbs, true) ]
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: datastudioExists && installMeta && !isSelfDirectory
        inputs: meta_dynamic.fileTags.concat(meta_library.fileTags)
        Artifact {
            fileTags: [ 'library.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.datastudioDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand()
            cmd.description = "coping " + input.fileName
            //cmd.silent = true
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [cmd]
        }
    }

    // modules - soci

    Group {
        id: modules_soci_headers
        name: 'modules_soci_headers'
        condition: datastudioExists && !isSelfDirectory && installSOCI
        prefix: datastudioDir + '/include/soci/'
        files: [ '**/*.h' ]
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: datastudioExists && !isSelfDirectory && installSOCI
        inputs: modules_soci_headers.fileTags
        Artifact {
            fileTags: [ 'header.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.datastudioDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }

    Group {
        id: modules_soci_dynamic
        name: 'modules_soci_dynamic'
        condition: datastudioExists && installSOCI
        prefix: datastudioDir + '/lib/' + project.archDir + '/'
        files: [ EnvUtils.libPrefix(qbs) + 'soci_core' + EnvUtils.dylibSuffix(qbs) + '*' ]
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: moduleInstallDir
    }

    Group {
        id: modules_soci_library
        name: 'modules_soci_library'
        condition: datastudioExists && installSOCI && !isSelfDirectory
        prefix: modules_soci_dynamic.prefix
        files: {
            var files = []
            if (qbs.targetOS.contains('windows')) {
                files.push('soci_core*.lib')
                files.push('soci_core*.dll')
            } else {
                files.push(EnvUtils.libPrefix(qbs) + 'soci_core*' + EnvUtils.dylibExtension(qbs))
            }
            return files
        }
        excludeFiles: [ EnvUtils.incDylibFuzzy(qbs) ]
        fileTags: [ name + '.in' ]
    }

    Rule {
        condition: datastudioExists && !isSelfDirectory && installSOCI
        inputs: modules_soci_dynamic.fileTags.concat(modules_soci_library.fileTags)
        Artifact {
            fileTags: [ 'library.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.datastudioDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }

    // modules - soci
    Group {
        id: modules_soci
        name: 'modules_soci'
        condition: datastudioExists && !isSelfDirectory
        prefix: datastudioDir + '/lib/' + project.archDir + '/'
        files: {
            var items = []
            if (installMySQL) {
                items.push('plugins/soci/' + EnvUtils.libPrefix(qbs)
                           + 'libmysql' + EnvUtils.dylibExtension(qbs) + '*')
            }
            if (installOracle) {
                items.push('plugins/soci/' + EnvUtils.libPrefix(qbs)
                           + 'oci' + EnvUtils.dylibExtension(qbs) + '*')
            }
            return items
        }
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: moduleInstallDir
    }

    // modules - soci - sql
    Group {
        id: modules_soci_sql
        name: 'modules_soci_sql'
        condition: datastudioExists
        prefix: datastudioDir + '/lib/' + project.archDir + '/plugins/soci/'
        files: {
            var files = [], modules = []
            if (installEmpty && !module.soci.EMPTY_PRO_VALID) {
                modules.push('soci_empty')
            }
            if (installSQLite3 && !module.soci.SQLITE3_PRO_VALID) {
                modules.push('soci_sqlite3')
            }
            if (installMySQL && !module.soci.MYSQL_PRO_VALID) {
                modules.push('soci_mysql')
            }
            if (installODBC && !module.soci.ODBC_PRO_VALID) {
                modules.push('soci_odbc')
            }
            if (installOracle && !module.soci.ORACLE_PRO_VALID) {
                modules.push('soci_oracle')
            }
            if (installPostgreSQL && !module.soci.POSTGRESQL_PRO_VALID) {
                modules.push('soci_postgresql')
            }
            if (installDB2 && !module.soci.DB2_PRO_VALID) {
                modules.push('soci_db2')
            }
            if (installFireBird && !module.soci.FIREBIRD_PRO_VALID) {
                modules.push('soci_firebird')
            }
            modules.forEach(function(item){
                files.push(EnvUtils.libPrefix(qbs) + item + '*' + EnvUtils.dylibExtension(qbs) + '*')
            })
            return files
        }
        fileTags: [ name + '.in' ]
        qbs.install: true
        qbs.installPrefix: project.projectName
        qbs.installDir: moduleInstallDir + '/plugins/soci'
    }

    Rule {
        condition: datastudioExists && !isSelfDirectory
        inputs: modules_soci.fileTags.concat(modules_soci_sql.fileTags)
        Artifact {
            fileTags: [ 'library.out' ]
            filePath: FileInfo.joinPaths(project.sourceDirectory,
                                         FileInfo.relativePath(product.datastudioDir, input.filePath))
        }
        prepare: {
            var cmd = new JavaScriptCommand
            cmd.description = 'coping ' + input.fileName
            cmd.sourceCode = function() { File.copy(input.filePath, output.filePath) }
            return [ cmd ]
        }
    }
}
