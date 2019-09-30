import qbs
import qbs.File
import qbs.FileInfo
import tools.EnvUtils

PackageProduct {
    name: 'com.smartsoft.desktop.modules'

    property stringList modules: [
        'jwt', 'log4cpp', 'qwt', 'protocore', 'protowidget'
    ]

    // protocore/parser/generator
    property bool installGenerator: true


    // soci
    property bool installSOCI: true
    property bool installSOCIAll: false
    property bool installEmpty: true
    property bool installSQLite: true
    property bool installMySQL: true
    property bool installODBC: true
    property bool installOracle: true
    property bool installPostgreSQL: true
    property bool installDB2: false
    property bool installFireBird: false

    // plugins - soci
    Group {
        name: 'data-plugins-soci'
        prefix: FileInfo.joinPaths(project.sourceDirectory, 'lib') + '/'
        files: {
            var items = []
            if (installSOCI) {
                items.push(EnvUtils.libPrefix(qbs) + 'soci_core' + EnvUtils.dylibExtension(qbs) + '*')
            }
            if (installMySQL) {
                items.push(EnvUtils.libPrefix(qbs) + 'plugins/soci/libmysql' + EnvUtils.dylibExtension(qbs) + '*')
            }
            if (installOracle) {
                items.push(EnvUtils.libPrefix(qbs) + 'plugins/soci/oci' + EnvUtils.dylibExtension(qbs) + '*')
            }
            return items
        }
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
    }

    // plugins - soci - sql
    Group {
        name: 'data-plugins-soci-sql'
        prefix: FileInfo.joinPaths(project.sourceDirectory, 'lib/plugins/soci') + '/'
        files: {
            var files = [], modules = [];
            if (installEmpty) modules.push('soci_empty')
            if (installSQLite) modules.push('soci_sqlite3')
            if (installMySQL) modules.push('soci_mysql')
            if (installODBC) modules.push('soci_odbc')
            if (installOracle) modules.push('soci_oracle')
            if (installPostgreSQL) modules.push('soci_postgresql')
            if (installDB2) modules.push('soci_db2')
            if (installFireBird) modules.push('soci_firebird')
            modules.forEach(function(item){
                files.push(EnvUtils.libPrefix(qbs) + item + EnvUtils.dylibExtension(qbs) + '*');
            })
            return files
        }
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'plugins/soci'
    }
    
    // modules

    Group {
        name: 'data-modules'
        prefix: FileInfo.joinPaths(project.sourceDirectory, 'lib') + '/'
        files: {
            var files = []
            modules.forEach(function(item){
                  files.push(item + EnvUtils.dylibSuffix(qbs, qbs.architecture) + '*');
              });
            return files;
        }
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
    }

    //  protocore/parser/generator

    Group {
        name: 'data-plugins-generator'
        prefix: FileInfo.joinPaths(project.sourceDirectory, 'lib/plugins/generator') + '/'
        files: {
            var items = []
            if (installGenerator) {
                items.push(EnvUtils.libPrefix(qbs) + 'generator' + EnvUtils.dylibExtension(qbs) + '*')
            }
            return items
        }
        qbs.install: true
        qbs.installPrefix: dataInstallPrefix
        qbs.installDir: 'plugins/generator'
    }
}
