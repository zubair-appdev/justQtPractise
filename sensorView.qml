import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Rectangle {
    width: 800
    height: 500
    color: "lightgray"

    ColumnLayout
    {
        anchors.fill: parent

        RowLayout
        {
            spacing: 20
            Button
            {
                id:myButton
                Layout.fillWidth: true
                text: "Click"

                onClicked: {
                    myLabel.text = "World"
                }

            }

            Label
            {
                Layout.preferredWidth: 80
                Layout.preferredHeight: myButton.height
                id: myLabel
                color: "blue"
                text: "Hello"

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                background: Rectangle{
                    color : "yellow"
                    border.color : "black"
                    border.width : 2
                    radius : 3
                }
            }

        }

        ListView
        {
            width: 300
            height: 200

            model: sensorModel

            delegate: Text {
                text: model.display
                height: 30
            }


        }

        Item {
            Layout.fillHeight: true
        }
    }
}
