import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import SearchTable 1.0

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    title: qsTr("Hello World")

    SearchTable{
        id: searchTable
        width: parent.width
        height: parent.height
        x: 0
        y: 0
    }

    header: ToolBar{
        RowLayout{
            anchors.fill: parent
            ToolButton{
                text: "AppendRow"
                onClicked: searchTable.model.appendRows(1)
            }
            ToolButton{
                text: "AppendColumn"
                onClicked: searchTable.model.appendColumns(1)

            }
            ToolButton{
                text: "RemoveLastRow"
                onClicked: searchTable.model.removeLastRow()

            }

            ToolButton{
                text: "RemoveLastColumn"
                onClicked: searchTable.model.removeLastColumn()

            }


        }
    }

}
