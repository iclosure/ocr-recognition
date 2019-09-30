import qbs
import '../ModuleBase.qbs' as ModuleBase

ModuleBase {
    moduleName: 'qscintilla'
    cpp.includePaths: [
        project.sourceDirectory + '/include',
        project.sourceDirectory + '/include/' + moduleName
    ]
    cpp.defines: [ 'QSCINTILLA_DLL', 'SCINTILLA_QT', 'SCI_LEXER' ]
}
