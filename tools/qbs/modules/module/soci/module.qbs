import qbs
import qbs.File

Module {

    //readonly property bool SOCI_CXX_C11: true
    readonly property bool SOCI_DB2: false
    readonly property bool SOCI_EMPTY: probeSoci.SOCI_EMPTY
    readonly property bool SOCI_FIREBIRD: false
    readonly property bool SOCI_MYSQL: true
    readonly property bool SOCI_ODBC: true
    readonly property bool SOCI_ORACLE: true
    readonly property bool SOCI_POSTGRESQL: true
    readonly property bool SOCI_SQLITE3: probeSoci.SOCI_SQLITE3

    //
    readonly property string MYSQL_HOME: probeSoci.MYSQL_HOME
    readonly property string SQLITE3_HOME: probeSoci.SQLITE3_HOME
    readonly property string ORACLE_HOME: probeSoci.ORACLE_HOME
    readonly property string POSTGRESQL_HOME: probeSoci.POSTGRESQL_HOME
    readonly property string ODBC_HOME: probeSoci.ODBC_HOME

    readonly property bool DB2_FOUND: SOCI_DB2
    readonly property bool EMPTY_FOUND: SOCI_EMPTY
    readonly property bool FIREBIRD_FOUND: SOCI_FIREBIRD
    readonly property bool MYSQL_FOUND: SOCI_MYSQL && MYSQL_HOME
    readonly property bool ODBC_FOUND: SOCI_ODBC && ODBC_HOME
    readonly property bool ORACLE_FOUND: SOCI_ORACLE && ORACLE_HOME
    readonly property bool POSTGRESQL_FOUND: SOCI_POSTGRESQL && POSTGRESQL_HOME
    readonly property bool SQLITE3_FOUND: SOCI_SQLITE3 && SQLITE3_HOME

    readonly property bool DB2_PRO_VALID: probeSoci.DB2_PRO_VALID
    readonly property bool EMPTY_PRO_VALID: probeSoci.EMPTY_PRO_VALID
    readonly property bool FIREBIRD_PRO_VALID: probeSoci.FIREBIRD_PRO_VALID
    readonly property bool MYSQL_PRO_VALID: probeSoci.MYSQL_PRO_VALID
    readonly property bool ODBC_PRO_VALID: probeSoci.ODBC_PRO_VALID
    readonly property bool ORACLE_PRO_VALID: probeSoci.ORACLE_PRO_VALID
    readonly property bool POSTGRESQL_PRO_VALID: probeSoci.POSTGRESQL_PRO_VALID
    readonly property bool SQLITE3_PRO_VALID: probeSoci.SQLITE3_PRO_VALID

    Probe {
        id: probeSoci
        readonly property var _project: project
        readonly property var _qbs: qbs
        property bool SOCI_EMPTY: true
        property bool SOCI_SQLITE3: true
        property string MYSQL_HOME: undefined
        property string SQLITE3_HOME: undefined
        property string ORACLE_HOME: undefined
        property string POSTGRESQL_HOME: undefined
        property string ODBC_HOME: undefined
        //
        readonly property bool DB2_PRO_VALID: false
        readonly property bool EMPTY_PRO_VALID: true
        readonly property bool FIREBIRD_PRO_VALID: false
        readonly property bool MYSQL_PRO_VALID: false
        readonly property bool ODBC_PRO_VALID: false
        readonly property bool ORACLE_PRO_VALID: false
        readonly property bool POSTGRESQL_PRO_VALID: false
        readonly property bool SQLITE3_PRO_VALID: true
        configure: {
            const _3rdpartDir = _project.sourceDirectory + '/src/core/protocore/3rdpart'
            const backendsDir = _3rdpartDir + '/soci/backends'
            // db2
            // firebird
            // mysql
            MYSQL_HOME = function(){
                var path = 'C:/Program Files'
                if (_qbs.targetOS.contains("windows")) {
                    if (_qbs.architecture == 'x86') {
                        path += ' (x86)'
                    }
                }
                path += '/MySQL/MySQL Connector C 6.1'
                if (File.exists(path)) {
                    return path
                } else {
                    return undefined
                }
            }()
            MYSQL_PRO_VALID = MYSQL_HOME && function(){
                return File.exists(backendsDir + '/mysql/mysql.qbs')
            }()
            // sqlite3
            SQLITE3_HOME = function(){
                var path = _3rdpartDir + '/sqlite3'
                if (File.exists(path)) {
                    return path
                } else {
                    return undefined
                }
            }()
            // oracle
            ORACLE_HOME = function(){
                var path = 'C:/app/iclosure/product/11.2.0/client_1'
                if (File.exists(path)) {
                    return path
                } else {
                    return undefined
                }
            }()
            ORACLE_PRO_VALID = ORACLE_HOME && function(){
                return File.exists(backendsDir + '/oracle/oracle.qbs')
            }()
            // postgresql
            POSTGRESQL_HOME = function(){
                var path = 'C:/app/postgresql-10.5-1'
                if (File.exists(path)) {
                    return path
                } else {
                    return undefined
                }
            }()
            POSTGRESQL_PRO_VALID = POSTGRESQL_HOME && function(){
                return File.exists(backendsDir + '/postgresql/postgresql.qbs')
            }()
            // odbc
            ODBC_HOME = function() {
                var path = undefined
                if (File.exists(path)){
                    return path
                } else {
                    return undefined
                }
            }()
            ODBC_PRO_VALID = ODBC_HOME && function(){
                return File.exists(backendsDir + '/odbc/odbc.qbs')
            }()
        }
    }
}
