import QtQuick 1.0
import com.nokia.meego 1.0
import com.nokia.extras 1.0

Page {
    id: root
    anchors.margins: 10
    property bool modified: false
    property bool acceptableInput: true
    signal saved
    property QtObject impl
    property QtObject controller
    function save() { impl.save(); }
    function load() { impl.load(); }
   
    tools: SettingsToolBarLayout {
        id: toolBarLayout
        page: root
        acceptableInput: root.acceptableInput
    }
}
