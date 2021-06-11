import qbs.base 1.0

Project {
    name: "qutIM"

    property string qutim_version_major: '0'
    property string qutim_version_minor: '4'
    property string qutim_version_release: '0'
    property string qutim_version_patch: '0'
    property string qutim_version: qutim_version_major + '.' + qutim_version_minor + '.' + qutim_version_release + '.' + qutim_version_patch
    property bool declarativeUi: false
    /**
     * Use: just pass project.addressSanitizer:true as qbs resolve/build parameter
     */
    property bool addressSanitizer: false

    /**
     * Property to disable rpaths entirely (useful for linux distros like Fedora)
     */
    property bool useRPaths: true

    property var additionalCppDefines: []

    property string shareDir: qutim_share_path

    property string qutim_qml_path: "bin"
    property string qutim_plugin_path: {
        if (qbs.targetOS.contains('osx'))
            return "bin/qutim.app/Contents/PlugIns";
        else if (qbs.targetOS.contains('windows'))
            return "bin/plugins"
        else
            return "lib/qutim/plugins";
    }
    property string qutim_bin_path: "bin"
    property string qutim_lib_path: "lib"
    property string qutim_libexec_path: {
        if (qbs.targetOS.contains('windows'))
            return "bin";
        else
            return "lib";
    }
    property string qutim_share_path: {
        if (qbs.targetOS.contains("osx"))
            return "bin/qutim.app/Contents/Resources/share";
        else if (qbs.targetOS.contains("linux"))
            return "share/apps/qutim";
        else
            return "share";
    }

    /**
     * For installing qutim icons in /usr/share/icons
     */
    property string qutim_system_share_path: "share"
    
    property string bin_path: qutim_bin_path
    property string lib_path: qutim_libexec_path
    property string qml_path: qutim_share_path + '/qml'

    property var pluginTags: {
        var tags = [ "desktop", "core" ];
        return tags.concat(qbs.targetOS);
    }
    property bool singleProfile: true

    Properties {
        condition: qbs.targetOS.contains("osx")
        qutim_qml_path: "bin/qutim.app/Contents/MacOs/qml"
    }

    qbsSearchPaths: "."

    references: [
        "src/3rdparty/3rdparty.qbs",
        "src/bin/bin.qbs",
        "src/lib/libqutim.qbs",
		"src/plugins/plugins.qbs",
        "src/qml/qutimplugin.qbs",
        "src/share/share.qbs",
    ]
}

