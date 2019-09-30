var File = require('qbs.File')
var FileInfo = require('qbs.FileInfo')
var Environment = require('qbs.Environment')
var Utilities = require('qbs.Utilities')

function isNewQbs(qbs) {
    return Utilities.versionCompare(qbs.version, "1.10.0") >= 0
}

function hasDefinesBase(qbs) {
    return isNewQbs(qbs)
}

function cleanPath(path) {
    if (FileInfo.cleanPath) {
        return FileInfo.cleanPath(path)
    } else {
        return path
    }
}

function jframeDir(project) {
    var path = projectDir(project, 'jframework', 'JFRAME_DIR')
    return path
}

function datastudioDir(project) {

    var path = projectDir(project, 'datastudio', 'DATASTUDIO_DIR')
    if (!FileInfo.cleanPath) {
        path = FileInfo.joinPaths(project.sourceDirectory,
                                  FileInfo.relativePath(project.sourceDirectory, path + '/'))
        if (path.endsWith('/.')) {
            path = path.substring(0, path.length - 2)
        }
    }
    return path
}

function validatePath(path, projectName) {
    if (File.exists(qbsFilePath(path, projectName))) {
        return cleanPath(path)
    } else {
        return undefined
    }
}

function projectDir(project, projectName, envName) {
    if (project.projectName === projectName) {
        return project.sourceDirectory
    }
    // from environment
    if (envName !== undefined) {
        var path = validatePath(Environment.getEnv(envName), projectName)
        if (path !== undefined) {
            return path
        }
    }
    // from 3rdpart
    path = FileInfo.joinPaths(project.sourceDirectory, '..', '3rdpart', projectName)
    path = validatePath(path, projectName)
    if (path !== undefined) {
        return path
    }
    // from ../..?
    path = FileInfo.joinPaths(project.sourceDirectory, '..', '..', projectName)
    path = validatePath(path, projectName)
    if (path !== undefined) {
        return path
    }
    // from ../../..?
    path = FileInfo.joinPaths(project.sourceDirectory, '..', '..',  '..', projectName)
    path = validatePath(path, projectName)
    if (path !== undefined) {
        return path
    }
    // from sourceDirectory
    path = validatePath(project.sourceDirectory, projectName)
    if (path !== undefined) {
        return path
    }
    // from /..?
    path = FileInfo.joinPaths(project.sourceDirectory, '..', projectName)
    path = validatePath(path, projectName)
    if (path !== undefined) {
        return path
    }

    return project.sourceDirectory
}

function qbsFilePath(path, projectName) {
    return path + '/' + projectName + '.qbs'
}

function ifwDir() {
    return FileInfo.fromWindowsSeparators(Environment.getEnv('QTIFW_DIR'))
}

function datastudioCoreDir(project) {
    return FileInfo.joinPaths(datastudioDir(project), 'src', 'core')
}

function jframe3rdpartVisible(project) {
    return (project.buildQuote && File.exists(jframe3rdpartDir(project) + '/3rdpart.qbs'))
}

function datastudioCoreVisible(project) {
    return (project.buildQuote && File.exists(datastudioCoreDir(project) + '/core.qbs'))
}

function jframe3rdpartPrefix(project) {
    return jframe3rdpartVisible(project) ? '' : '3rdpart'
}

function datastudioCorePrefix(project) {
    return datastudioCoreVisible(project) ? '' : 'core'
}

function execSuffix(qbs) {
    var targetOS = qbs.targetOS
    if (targetOS.contains('windows')) {
        return '.exe'
    } else if (targetOS.contains('darwin')) {
        return ''
    } else if (targetOS.contains('linux')) {
        return ''
    } else {
        return ''
    }
}

function libPrefix(qbs) {
    var targetOS = qbs.targetOS
    if (targetOS.contains('windows')) {
        return ''
    } else if (targetOS.contains('darwin')) {
        return 'lib'
    } else if (targetOS.contains('linux')) {
        return 'lib'
    } else {
        return ''
    }
}

function libExtension(qbs, isDylib) {
    var targetOS = qbs.targetOS
    if (targetOS.contains('windows')) {
        return '.lib'
    } else if (targetOS.contains('darwin')) {
        return isDylib ? '.so' : '.a'
    } else if (targetOS.contains('linux')) {
        return isDylib ? '.so' : '.a'
    } else {
        return ''
    }
}

function dylibExtension(qbs) {
    var targetOS = qbs.targetOS
    if (targetOS.contains('windows')) {
        return '.dll'
    } else if (targetOS.contains('darwin')) {
        return '.dylib'
    } else if (targetOS.contains('linux')) {
        return '.so'
    } else {
        return ''
    }
}

function dylibExtensionFuzzy(qbs) {
    var targetOS = qbs.targetOS
    if (targetOS.contains('windows')) {
        return '.dll'
    } else if (targetOS.contains('darwin')) {
        return '.*dylib'
    } else if (targetOS.contains('linux')) {
        return '.so*'
    } else {
        return ''
    }
}

function dylibSuffix(qbs, architecture) {
    var suffix = dylibExtensionFuzzy(qbs)
    if (qbs.buildVariant === 'debug') {
        suffix = 'd' + suffix
    }
    if (architecture === 'x86_64') {
        suffix = '64' + suffix
    }
    return suffix
}

function libFullName(product, targetName, variantSuffix, isDylib) {
    var name = libPrefix(product.qbs) + targetName + variantSuffix
    return name + libExtension(product.qbs, isDylib)
}

function incDylibFuzzy(qbs, recursive, name, architecture) {
    var suffix = dylibExtensionFuzzy(qbs)
    if (qbs.buildVariant === 'debug') {
        suffix = 'd' + suffix
    } else {
        suffix = '[^d]' + suffix
    }
    if (architecture === 'x86_64') {
        suffix = '64' + suffix
    } else {
        suffix = '[^(64)]' + suffix
    }
    suffix = '*' + suffix
    if (name) {
        suffix = name + suffix
    }
    if (recursive) {
        return '**/' + suffix
    } else {
        return suffix
    }
}

function excDylibFuzzy(qbs, recursive, name) {
    var suffix = dylibExtensionFuzzy(qbs)
    if (qbs.buildVariant === 'debug') {
        suffix = '*[^d]' + suffix
    } else {
        suffix = '*d' + suffix
    }
    if (name) {
        suffix = name + suffix
    }
    if (recursive) {
        return '**/' + suffix
    } else {
        return suffix
    }
}

function frameworkSuffix(qbs) {
    return '.framework'
}

function createTranslationCommand(product) {
    var args = []
    // no-recursive
    if (product.noRecursivePaths.length > 0) {
        args.push('-no-recursive')
        product.noRecursivePaths.forEach(function(item){
            args.push(item)
        })
    }
    args.push('-recursive')
    // recursive
    if (product.recursivePaths.length > 0) {
        product.recursivePaths.forEach(function(item){
            args.push(item)
        })
    } else {
        args.push(product.sourceDirectory)
    }
    // others
    args.push('-no-obsolete')
    // ts
    if (product.translations.length > 0) {
        args.push('-ts')
        product.translations.forEach(function(item){
            var filePath = FileInfo.joinPaths(product.langPath, item)
            var path = FileInfo.path(filePath)
            if (!File.exists(path)) {
                File.makePath(path)
            }
            args.push(filePath)
        })
    }
    // create command
    var command = new Command(product.Qt.core.binPath + '/lupdate', args)
    command.description = 'generating translation file...'
    return command
}

function createInstallNameCommands(product) {
    if (!product.qbs.targetOS.contains('darwin')) {
        return undefined
    }

    if (!product.pairInstallNames || !(product.pairInstallNames instanceof Array)) {
        return undefined
    }

    var commands = []

    for (var pairInstallName in product.pairInstallNames) {
        if ((pairInstallName instanceof Array) && pairInstallName.length === 3) {
            var oldName = pairInstallName[0]
            var newName = pairInstallName[1]
            var targetName = pairInstallName[1]
            var args = []
            args.push('-change')
            args.push(oldName)
            args.push(newName)
            args.push(targetName)
            var command = new Command('install_name_tool', args)
            command.description = '(install_name_tool) change ' + oldName + ' to ' + newName
            commands.push(command)
        } else {
            console.warn('warning: install name is invalid and should be a array of length 3 (' + pairInstallName + ')')
        }
    }

    if (commands.length === 0) {
        return undefined
    }

    return commands
}

function createLreleaseCommands(product, filePath) {
    var args = []
    //
    args.push('-compress')
    args.push('-nounfinished')
    args.push('-removeidentical')
    // ts file
    args.push(filePath)
    // create command
    var cmd = new Command(product.Qt.core.binPath + '/lrelease', args)
    cmd.description = 'generating qm file for translation...'
    return [ cmd ]
}
