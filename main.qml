import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    id: window
    title: "Noughts and Crosses"
    height: 600
    width: 800
    visible: true

    Rectangle {
        id: fields
        anchors.left: parent.left
        height: parent.height
        width: parent.width*0.7

        Grid {

            rows: 3
            columns: 3

            Field {
            }
            Field {
            }
            Field {
            }
            Field {
            }
            Field {
            }
            Field {
            }
            Field {
            }
            Field {
            }
            Field {
            }
        }
    }
    Rectangle {
        id: scores
        anchors.right: parent.right
        height: parent.height
        width: parent.width*0.3
        gradient: Gradient {
            GradientStop { position: 0.0; color: "red" }
            GradientStop { position: 0.5; color: "grey" }
            GradientStop { position: 1.0; color: "lightblue" }
        }
        Rectangle {
            function switchPlayer()
            {
                if (noughtImage.visible == true)
                {
                    noughtImage.visible = false
                    crossImage.visible = true
                } else
                {
                    noughtImage.visible = true
                    crossImage.visible = false
                }
            }
            signal nextRound
            id: nextPlayer
            anchors.top: parent.top
            anchors.topMargin: parent.height*0.2
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height*0.25
            width: parent.width*0.6
            opacity: 1

            Image {
                id: noughtImage
                height: Math.min(parent.height,parent.width)*0.9
                width: Math.min(parent.height,parent.width)*0.9
                anchors.centerIn: parent
                source: "nought.png"
                opacity: 0.9
                visible: true
            }
            Image {
                id: crossImage
                height: Math.min(parent.height,parent.width)*0.9
                width: Math.min(parent.height,parent.width)*0.9
                anchors.centerIn: parent
                source: "cross.png"
                opacity: 0.9
                visible: false
            }
            Text {
                id: nextPlayerText
                anchors.bottom: parent.top
                anchors.bottomMargin: parent.height*0.12
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Next player:"
                font.pointSize: Math.max(parent.height*0.12,parent.width*0.12)
                color: "white"
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    nextPlayer.scale = 1.2
                    nextPlayer.z = 100
                    nextPlayerText.text = "Next round!"
                    nextPlayerText.color = "black"
                }
                onClicked: {
                    nextPlayer.nextRound()
                }

                onExited: {
                    nextPlayer.scale = 1.0
                    nextPlayer.z = 0
                    nextPlayerText.text = "Next player:"
                    nextPlayerText.color = "white"
                }
            }
        }
        Rectangle {
            function updateScore(noughtScore, crossScore)
            {
                noughtScoreText.text = noughtScore
                crossScoreText.text = crossScore
            }

            id: score
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.15
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height*0.25
            width: parent.width*0.6
            opacity: 1
            Text {
                id: scoreText
                anchors.bottom: parent.top
                anchors.bottomMargin: parent.height*0.12
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Score:"
                font.pointSize: Math.max(parent.height*0.12,parent.width*0.12)
                color: "white"
            }
            Image {
                id: noughtPlayer
                height: Math.min(parent.height,parent.width)*0.4
                width: Math.min(parent.height,parent.width)*0.4
                anchors.left: parent.left
                anchors.leftMargin: Math.min(parent.height,parent.width)*0.05
                anchors.top: parent.top
                anchors.topMargin: Math.min(parent.height,parent.width)*0.07
                source: "nought.png"
                opacity: 0.9
            }
            Image {
                id: crossPlayer
                height: Math.min(parent.height,parent.width)*0.4
                width: Math.min(parent.height,parent.width)*0.4
                anchors.right: parent.right
                anchors.rightMargin: Math.min(parent.height,parent.width)*0.05
                anchors.top: parent.top
                anchors.topMargin: Math.min(parent.height,parent.width)*0.07
                source: "cross.png"
                opacity: 0.9
            }
            Text {
                id: noughtScoreText
                anchors.left: parent.left
                anchors.leftMargin:
                {
                    if (parseInt(text)>9)
                    {
                        Math.min(parent.height,parent.width)*0.03
                    } else {
                        Math.min(parent.height,parent.width)*0.1
                    }
                }
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.min(parent.height,parent.width)*0.07
                text: "0"
                font.pointSize: Math.min(parent.height,parent.width)*0.25
                color: "black"
            }
            Text {
                id: vs
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.min(parent.height,parent.width)*0.07
                text: "-"
                font.pointSize: Math.min(parent.height,parent.width)*0.3
                color: "black"
            }
            Text {
                id: crossScoreText
                anchors.right: parent.right
                anchors.rightMargin: {
                    if (parseInt(text)>9)
                    {
                        Math.min(parent.height,parent.width)*0.03
                    } else {
                        Math.min(parent.height,parent.width)*0.1
                    }
                }
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Math.min(parent.height,parent.width)*0.07
                text: "0"
                font.pointSize: Math.min(parent.height,parent.width)*0.25
                color: "black"
            }
        }

    }

}
