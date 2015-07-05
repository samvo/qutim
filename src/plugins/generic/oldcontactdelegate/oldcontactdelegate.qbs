import "../GenericPlugin.qbs" as GenericPlugin

GenericPlugin {
    sourcePath: ''
    type: ['installed_content', 'dynamiclibrary']

    Depends { name: "qutim-simplecontactlist" }
    Depends { name: "Qt.xml" }
    Depends { name: "artwork" }

    cpp.includePaths: [
        product.path,
        'settings',
    ]

    Group {
        fileTags: [ "artwork" ]
        artwork.basePath: '.'
        prefix: "olddelegate/"
        files: '**'
    }
}
