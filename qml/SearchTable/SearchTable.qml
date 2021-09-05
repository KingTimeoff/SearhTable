import QtQuick 2.12
import QtQuick.Controls 2.12
import SearchTableBase 1.0
Item {

    TableView
    {
        id: table
        anchors.fill: parent
        contentWidth: parent.width * 2
        contentHeight: parent.height * 2

        model:SearchTableBaseModel{


        }
        delegate: Component{
            Rectangle{
                implicitWidth: 75
                implicitHeight: 25
                border.color: "black"
                border.width: 0.5
            }
        }
    }
    Component.onCompleted: {
        console.log(table.contentWidth,table.contentWidth)
    }
}
