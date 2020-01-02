import QtQuick 2.0
import QtQuick.Controls 1.4
import QtMultimedia 5.12

import "../Utils/Resources.js" as Rsrc
import "../Utils/Utils.js" as Utils

Item {
    anchors.fill: parent

    signal close
    signal load(int row)

    MouseArea {
        anchors.fill: parent
    }

    SoundEffect {
        id: soundEffect
        source: Rsrc.SOUND_BUTTON_2
    }

    // layout holder
    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 400
        height: 400
        border.color: "black"
        border.width: 3

        // top layout
        Rectangle {
            id: rectangle
            width: 400
            height: 68
            border.color: parent.border.color
            border.width: parent.border.width

            gradient: Gradient {
                GradientStop {position: 0.0; color: "#28313B"}
                GradientStop { position: 1.0; color: "#93968E"}
            }

            Text {
                id: element3
                width: 400
                height: 68
                color: "white"
                text: "Saved Games"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
            }
        }

        // middle layout
        Rectangle
        {
            anchors.top: parent.top
            anchors.topMargin: rectangle.height
            width: parent.width
            height: 272
            border.color: "black"
            border.width: 3

            TableView {
                id: table
                anchors.top: parent.top
                anchors.topMargin: 3
                anchors.left: parent.left
                anchors.leftMargin: 3
                width: parent.width - 6
                height: parent.height - 6

                TableViewColumn {
                    role: "number"
                    title: "Number"
                    width: 60
                    resizable: false
                }
                TableViewColumn {
                    role: "date"
                    title: "Date"
                    resizable: false
                    width: 242
                }
                TableViewColumn {
                    role: "time"
                    title: "Time Played"
                    resizable: false
                    width: 90
                }
                model: listModel

                ListModel {
                    id: listModel
                }
            }
        }

        // bottom layout
        Rectangle {
            anchors.bottom: parent.bottom
            color: "black"
            width: rectangle.width
            height: 60

            Button {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 80
                text: "Load"
                onClicked: {
                    soundEffect.play();
                    var r = listModel.get(table.currentRow);
                    if (r) {
                        load(r.number - 1);
                    }
                }
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 80
                text: "Close"
                onClicked: {
                    soundEffect.play();
                    close()
                }
            }
        }
    }

    // signal from Menu.cpp: sendSavedGamesInfo
    function savedGamesDates(info)
    {
        listModel.clear();

        var games = info['Games'];

        games.forEach(function(item, index){
            listModel.append({number: index + 1
                            , date: item['Date']
                            , time: Utils.formatTime(item['TimeElapsed'])})
        });
    }

} // item
