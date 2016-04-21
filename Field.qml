import QtQuick 2.0

Item {
    function clearField()
    {
        scaleAble = true
        noughtImage.visible = false
        crossImage.visible = false
        greyImage.visible = false
    }
    function setNought()
    {
        scaleAble = false
        noughtImage.visible = true
        crossImage.visible = false
        greyImage.visible = false
    }
    function setCross()
    {
        scaleAble = false
        noughtImage.visible = false
        crossImage.visible = true
        greyImage.visible = false
    }
    function setGrey()
    {
        scaleAble = false
        noughtImage.visible = false
        crossImage.visible = false
        greyImage.visible = true
    }
    function setEmpty()
    {
        scaleAble = false
        noughtImage.visible = false
        crossImage.visible = false
        greyImage.visible = false
    }

    id: field
    property bool scaleAble: true
    height: parent.parent.height/3
    width: parent.parent.width/3
    signal fieldClicked

    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        height: parent.height
        width: parent.width
        //color: "yellow"

        border.color: "black"
        border.width: parent.height*0.01
        opacity: 1.0
        MouseArea {
            anchors.fill: parent
            onClicked: {
                field.fieldClicked();
            }
            hoverEnabled: true
            onEntered: {
                if (field.scaleAble == true)
                {
                    field.scale = 1.1
                    field.z = 100
                }
            }
            onExited: {
                field.scale = 1.0
                field.z = 0
            }
        }
        Image {
            id: noughtImage
            height: Math.min(parent.height,parent.width)*0.9
            width: Math.min(parent.height,parent.width)*0.9
            anchors.centerIn: parent
            source: "nought.png"
            opacity: 0.9
            visible: false
        }
        Image {
            id: crossImage
            height: Math.min(parent.height,parent.width)*0.9
            width: Math.min(parent.height,parent.width)*0.9
            anchors.centerIn: parent
            source: "cross.png"
            opacity: 1
            visible: false
        }
        Image {
            id: greyImage
            height: Math.min(parent.height,parent.width)*0.9
            width: Math.min(parent.height,parent.width)*0.9
            anchors.centerIn: parent
            source: "grey.png"
            opacity: 1
            visible: false
        }
    }
}
