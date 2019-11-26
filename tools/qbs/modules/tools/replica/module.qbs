import qbs
import qbs.FileInfo

Module {
    id: root

    Depends { name: "Qt.core"; cpp.link: false }

    readonly property path qtBinDir: Qt.core.binPath
    property bool source: true
    property bool replica: true
    property bool merge: false
    property stringList outFiles: []

    FileTagger {
        patterns: "*.rep"
        fileTags: ["repc-rep"]
    }

    Rule {
        condition: source
        inputs: ["repc-rep"]
        Artifact {
            filePath: product.buildDirectory + "/qt.headers/repc_" + FileInfo.baseName(input.fileName) + "_source.h"
            fileTags: ["hpp"]
        }
        prepare: {
            var command = new Command()
            command.description = "repc " + input.fileName
            command.program = product.Qt.core.binPath + "/repc"
            command.arguments = ["-i", "rep", "-o", "source", input.filePath, output.filePath]
            return command
        }
    }

    Rule {
        condition: replica
        inputs: ["repc-rep"]
        Artifact {
            filePath: product.buildDirectory + "/qt.headers/repc_" + FileInfo.baseName(input.fileName) + "_replica.h"
            fileTags: ["hpp"]
        }
        prepare: {
            var command = new Command()
            command.description = "repc " + input.fileName
            command.program = product.Qt.core.binPath + "/repc"
            command.arguments = ["-i", "rep", "-o", "replica", input.filePath, output.filePath]
            return command
        }
    }

    Rule {
        condition: merge
        inputs: ["repc-rep"]
        Artifact {
            filePath: product.buildDirectory + "/qt.headers/repc_" + FileInfo.baseName(input.fileName) + "_merge.h"
            fileTags: ["hpp"]
        }
        prepare: {
            var command = new Command()
            command.description = "repc " + input.fileName
            command.program = product.Qt.core.binPath + "/repc"
            command.arguments = ["-i", "rep", "-o", "merge", input.filePath, output.filePath]
            return command
        }
    }
}
