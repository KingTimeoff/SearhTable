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
    header: ToolBar{
        RowLayout{
            anchors.fill: parent
            Rectangle{
                id: rectGridButton
                Layout.fillHeight: true
                Layout.minimumWidth: 25
                border.color: "lightgrey"
                ToolButton{
                    id: sizeTable
                    anchors.fill: parent
                    text:"t"
                    onClicked: {
                        rectGrid.visible = rectGrid.visible  ? false : true
                    }
                }

                Rectangle{
                    id: rectGrid
                    width: 100
                    height: 100
                    x: rectGridButton.x
                    y: rectGridButton.y + rectGridButton.height - 2
                    visible: false
                    border.width: 0.5
                    border.color: "lightgrey"

                    Grid{
                        anchors.fill: parent
                        contentHeight: height
                        contentWidth: width
                        interactive: false
                        model: 30
                        columnSpacing: 5
                        rowSpacing: 5

                        Rectangle{
                            border.color: "grey"
                            implicitHeight: 10
                            implicitWidth:  10
                            MouseArea{
                                anchors.fill: parent

                            }

                        }
                    }

                }
                onFocusChanged: {
                    rectGrid.visible = false
                }
            }
        }
    }
    Rectangle{
        id: focusRect
        anchors.fill: parent



        SearchTable{
            width: parent.width
            height: parent.height
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked: {
                focusRect.focus = true
            }
        }
    }
}
