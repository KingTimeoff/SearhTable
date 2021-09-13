import QtQuick 2.15
import QtQuick.Controls 2.15
import SearchTableModel 1.0

Item {

    property TableView syncTable
    property  SearchTableModel tableModel: null
    readonly property TableSettings settings: TableSettings{}
    z:0

    anchors.fill: syncTable.parent

    ListView
    {
        id: horizontalHeader
        x: syncTable.x
        y: syncTable.y - settings.verticalHeaderWidth - settings.rowSpacing
        z: 0
        width: syncTable.columns * settings.cellWidth  + settings.columnSpacing * syncTable.columns * 4
        height: settings.horizontalHeaderHeight

        model: syncTable.columns > 0  ? syncTable.columns : 1
        orientation: Qt.Horizontal
        spacing: settings.columnSpacing
        interactive: false

        delegate: Loader{
            sourceComponent: ItemDelegate{
                z:1
                id: horizontalItemDelegate

                height: horizontalHeader.height
                background: Rectangle{

                    implicitWidth: settings.cellWidth
                    implicitHeight:   settings.horizontalHeaderHeight
                }
                contentItem: TextEdit{
                    id: horizontalTextEdit
                    text:  tableModel.headerData(index,Qt.Horizontal) ? tableModel.headerData(index,Qt.Horizontal) :   ""
                    width:  settings.cellWidth
                    height:  settings.horizontalHeaderHeight
                    enabled: false

                    verticalAlignment: TextEdit.AlignVCenter
                    horizontalAlignment: TextEdit.AlignHCenter

                    onEditingFinished: {
                        tableModel.setHeaderData(index,Qt.Horizontal,text)
                        horizontalTextEdit.enabled = false
                        horizontalTextEdit.focus = false
                    }
                }

                onDoubleClicked: {
                    horizontalTextEdit.enabled = true
                    horizontalTextEdit.focus = true

                }
                onClicked: {
                    background.border.color = settings.borderSelectColor
                    if(tableModel.selectItem != null && tableModel.selectItem != horizontalItemDelegate){
                        deselectCell()
                    }
                    tableModel.selectItem = horizontalItemDelegate
                }
            }
        }

    }
    ListView
    {
        z: 0
        id: verticalHeader
        x:syncTable.x - settings.verticalHeaderWidth - settings.columnSpacing
        y: syncTable.y

        width: settings.verticalHeaderWidth
        height: syncTable.rows * settings.cellHeight + settings.rowSpacing * syncTable.rows * 4
        contentHeight: syncTable.rows * settings.cellHeight
        contentWidth: settings.verticalHeaderWidth

        model: syncTable.rows > 0 ? syncTable.rows : 1
        orientation: Qt.Vertical

        spacing: settings.rowSpacing
        interactive: false

        delegate: Loader{
            sourceComponent:ItemDelegate{
                z:1
                id: verticalItemDelegate
                width: verticalHeader.width

                background: Rectangle{

                    implicitWidth:  settings.verticalHeaderWidth
                    implicitHeight:  settings.cellHeight
                }
                contentItem: TextEdit{
                    id: verticalTextEdit
                    text:  tableModel.headerData(index,Qt.Vertical) ? tableModel.headerData(index,Qt.Vertical) : ""
                    width: settings.verticalHeaderWidth
                    height:  settings.cellHeight
                    enabled: false
                    verticalAlignment: TextEdit.AlignVCenter
                    horizontalAlignment: TextEdit.AlignHCenter
                    onEditingFinished: {
                        tableModel.setHeaderData(index,Qt.Vertical,text)
                        verticalTextEdit.enabled = false
                        verticalTextEdit.focus = false
                    }
                }

                onDoubleClicked: {
                    verticalTextEdit.enabled = true
                    verticalTextEdit.focus = true

                }
                onClicked: {
                    background.border.color = settings.borderSelectColor
                    if(tableModel.selectItem != null && tableModel.selectItem != verticalItemDelegate){
                        deselectCell()
                    }
                    tableModel.selectItem = verticalItemDelegate
                }
            }
        }
    }

    function deselectCell()
    {
        tableModel.selectItem.background.border.color = settings.borderDeselectColor
        tableModel.selectItem.contentItem.focus = false
    }
}
