import QtQuick 2.5
import QtQuick.Controls 2.0

Item {

    Connections {
        target: engine
        onSendModel: {
            listView.model = model
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: null
        delegate: Rectangle {
            width: listView.width
            height: 100
//            height: 180
            border.color: modelData.color
            border.width: 5
            Column {
                width: parent.width * 0.9
                height: parent.height * 0.9
                anchors.centerIn: parent
                spacing: 10
                Row {
                    width: parent.width
                    height: 30
                    Item {
                        width: parent.width / 2
                        height: parent.height
                        Text {
                            text: modelData.name
                            color: modelData.color
                            font.pixelSize: parent.height
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }
                    Item {
                        width: parent.width / 2
                        height: parent.height
                        Button {
                            height: parent.height
                            width: height
                            text: "X"
                            anchors.right: parent.right
                            onClicked: {
                                engine.deleteItem(modelData.id, modelData.parentFrame);
                            }
                        }
                    }
                }

                Button {
                    text: "Закрыть бокс"
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        engine.closedFrame(modelData.id)
                    }
                }

//                CheckBox {
//                    text: "Нет на кадре"
//                    checked: modelData.noFrame
//                    onCheckStateChanged: {
//                        engine.closedFrame(modelData.id)
//                    }
//                }
//                CheckBox {
//                    text: "Далеко"
//                    checked: modelData.far

//                }
//                CheckBox {
//                    text: "Перекрыт"
//                    checked: modelData.blocked
//                }
            }
        }
    }
}
