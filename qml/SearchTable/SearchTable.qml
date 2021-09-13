import QtQuick
import QtQuick.Controls 2.15
import SearchTableModel 1.0

Rectangle{
    id:root
    readonly property TableSettings settings: TableSettings{}
    readonly property SearchTableModel  model: tableModel
    color: "lightgrey"


    TableView
    {
        id: table
        property Rectangle lastItem

        width: parent.width - settings.verticalHeaderWidth
        height: parent.height - settings.horizontalHeaderHeight
        contentWidth: parent.width * 2 - settings.verticalHeaderWidth
        contentHeight: parent.height * 2 - settings.horizontalHeaderHeight
        x: parent.x + settings.verticalHeaderWidth
        y: parent.y + settings.horizontalHeaderHeight
        z:0
        interactive: false

        columnSpacing: settings.columnSpacing
        rowSpacing: settings.rowSpacing
        reuseItems: true
        model:  SearchTableModel{id: tableModel}

        onRowsChanged: {
            deselectCell()
        }
        onColumnsChanged: {
            deselectCell()
        }

        MouseArea
        {
            z:0
            id: tableArea
            anchors.fill: parent
            onClicked: {
                if(tableModel.selectItem != null)
                    deselectCell()
            }
        }


        delegate:
            Loader{
            sourceComponent:ItemDelegate{
                z:1
                id: itemModel

                background: Rectangle{
                    id:cellRect
                    implicitWidth: settings.cellWidth
                    implicitHeight: settings.cellHeight
                    border.width: settings.borderWidth
                    border.color: settings.borderDeselectColor
                }

                contentItem: TextEdit{
                    id: textEdit
                    text: model.display ? model.display : ""
                    width: settings.cellWidth
                    height: settings.cellHeight
                    enabled: false
                    onEditingFinished: {
                        if(model != null){
                            model.edit = text
                            enabled = false
                            focus = false
                        }
                    }
                }
                onDoubleClicked: {
                    textEdit.enabled = true
                    textEdit.focus = true

                }
                onClicked: {
                    background.border.color = settings.borderSelectColor
                    if(tableModel.selectItem && tableModel.selectItem != itemModel){
                        deselectCell()
                    }
                    tableModel.selectItem = itemModel
                }
            }
        }
    }
    TableHeader{
        syncTable: table
        tableModel: tableModel
    }

    function deselectCell()
    {
        if(tableModel.selectItem){
            tableModel.selectItem.background.border.color = settings.borderDeselectColor
            tableModel.selectItem.contentItem.focus = false
        }

    }
}
