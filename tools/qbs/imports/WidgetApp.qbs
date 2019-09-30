import qbs
import qbs.File
import qbs.FileInfo
import tools.EnvUtils

CppApp {
    type: base.concat([ 'translation' ])
    consoleApplication: false

    Depends { name: "Qt.core" }
    Depends { name: "Qt.gui" }
    Depends { name: 'Qt.widgets' }
    Depends {
        name: "Qt"
        submodules: Qt.gui.defaultQpaPlugin
        condition: linkDefaultQpaPlugin && Qt.gui.defaultQpaPlugin
    }

    property bool linkDefaultQpaPlugin: Qt.gui.isStaticLibrary

    // translation
    property path langPath: sourceDirectory + '/resource/lang'
    property pathList noRecursivePaths: []
    property pathList recursivePaths: []
    property stringList translationFileTags: [ 'hpp', 'cpp' ]
    property stringList translations: []
    property bool defaultTranslation: false

    Rule {
        id: rule
        condition: defaultTranslation && translations.length > 0
        multiplex: true
        inputs: translationFileTags
        Artifact { fileTags: [ 'translation' ] }
        prepare: {
            var commands = []
            // translation
            var commandTranslation = EnvUtils.createTranslationCommand(product)
            if (commandTranslation) {
                commands.push(commandTranslation)
            }
            // install_name_tool
            var commandsInstallName = EnvUtils.createInstallNameCommands(product)
            if (commandsInstallName) {
                commands = commands.concat(commandsInstallName)
            }
            return commands
        }
    }
}
