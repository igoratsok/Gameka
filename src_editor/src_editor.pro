TEMPLATE = app
TARGET = ../gameka
INCLUDEPATH += .
QT += core \
    gui \
    xml


MOC_DIR = .moc
UI_DIR = .uic
RCC_DIR = .rcc
OBJECTS_DIR = .obj
HEADERS += maincontroller.h \
    mapeditorcontroller.h \
    wizardcontroller.h \
    optionscontroller.h \
    eventseditorcontroller.h \
    builder.h \
    mainwindow.h \
    tilesetdock.h \
    tilemapview.h \
    tilemapscene.h \
    mainwindowwidget.h \
    tilesetscene.h \
    tilesetview.h \
    mapselectdock.h \
    tileitem.h \
    tilemapgridvisual.h \
    tilesetlinesgenerator.h \
    tilesetgridvisual.h \
    gamedata.h \
    tileset.h \
    map.h \
    newprojectwindow.h \
    configstabwidget.h \
    configstabwindow.h \
    configstilesetwidget.h \
    configsgeneralwidget.h \
    newmapwindow.h \
    newmapwindowgeneralwidget.h \
    configsobjectswidget.h \
    newmapwindowtilesetwidget.h \
    point.h \
    configsnewobjectwindow.h \
    gameobject.h \
    messageboxes.h \
    configsobjgenericwidget.h \
    configsobjdadosgeraiswidget.h \
    configsobjhabilidadeswidget.h \
    configsobjphysicswidget.h \
    newmapwindowobjectwidget.h \
    objectsdock.h \
    objectgraphicsitem.h \
    gameobjectinstance.h \
    titlescreendata.h \
    configsimportdialog.h \
    editorconstants.h \
    tilesetcolmapscene.h \
    soundpickerdialog.h \
    sprite.h \
    gameobjectanimation.h \
    neweventareadialog.h \
    newteleportareadialog.h \
    teleportarea.h \
    teleportareagraphicsitem.h \
    configsobjnpcbehaviorwidget.h \
    configsobjattributeswidget.h \
    configsobjitem.h \
    configsbackgrounds.h \
    configsanimations.h \
    animationdata.h \
    animationgraphicsscene.h \
    animationgraphicsitem.h \
    configsobjanimationchooserwindow.h \
    background.h \
    backgroundlayer.h \
    backgroundsgraphicsscene.h \
    backgroundpickerdialog.h \
    skilldata.h \
    skill.h \
    configsobjnewskilldialog.h \
    eventswidget.h \
    proceduredata.h \
    eventdata.h \
    neweventdialog.h \
    eventcombodataprovider.h \
    eventattributedata.h \
    variabledata.h \
    newvariabledialog.h \
    specialcombovaluedata.h \
    easynewgameobjectdialog.h \
    newdialoguedialog.h \
    dialoguedata.h \
    dialogueitemdata.h \
    music.h \
    undochangetilecommand.h \
    about.h \
    datawriter.h \
    dataloader.h \
    imagecolorpicker.h \
    imagecolorpickerscene.h \
    welcomescreen.h
SOURCES += main.cpp \
    maincontroller.cpp \
    mapeditorcontroller.cpp \
    wizardcontroller.cpp \
    optionscontroller.cpp \
    eventseditorcontroller.cpp \
    builder.cpp \
    mainwindow.cpp \
    tilesetdock.cpp \
    tilemapview.cpp \
    tilemapscene.cpp \
    mainwindowwidget.cpp \
    tilesetscene.cpp \
    tilesetview.cpp \
    mapselectdock.cpp \
    tileitem.cpp \
    tilemapgridvisual.cpp \
    tilesetlinesgenerator.cpp \
    tilesetgridvisual.cpp \
    gamedata.cpp \
    tileset.cpp \
    map.cpp \
    newprojectwindow.cpp \
    configstabwidget.cpp \
    configstabwindow.cpp \
    configstilesetwidget.cpp \
    configsgeneralwidget.cpp \
    newmapwindow.cpp \
    newmapwindowgeneralwidget.cpp \
    configsobjectswidget.cpp \
    newmapwindowtilesetwidget.cpp \
    point.cpp \
    configsnewobjectwindow.cpp \
    gameobject.cpp \
    messageboxes.cpp \
    configsobjgenericwidget.cpp \
    configsobjdadosgeraiswidget.cpp \
    configsobjhabilidadeswidget.cpp \
    configsobjphysicswidget.cpp \
    newmapwindowobjectwidget.cpp \
    objectsdock.cpp \
    objectgraphicsitem.cpp \
    gameobjectinstance.cpp \
    titlescreendata.cpp \
    configsimportdialog.cpp \
    editorconstants.cpp \
    tilesetcolmapscene.cpp \
    soundpickerdialog.cpp \
    sprite.cpp \
    gameobjectanimation.cpp \
    neweventareadialog.cpp \
    newteleportareadialog.cpp \
    teleportarea.cpp \
    teleportareagraphicsitem.cpp \
    configsobjnpcbehaviorwidget.cpp \
    configsobjattributeswidget.cpp \
    configsobjitem.cpp \
    configsbackgrounds.cpp \
    configsanimations.cpp \
    animationdata.cpp \
    animationgraphicsscene.cpp \
    animationgraphicsitem.cpp \
    configsobjanimationchooserwindow.cpp \
    background.cpp \
    backgroundlayer.cpp \
    backgroundsgraphicsscene.cpp \
    backgroundpickerdialog.cpp \
    skilldata.cpp \
    skill.cpp \
    configsobjnewskilldialog.cpp \
    eventswidget.cpp \
    proceduredata.cpp \
    eventdata.cpp \
    neweventdialog.cpp \
    eventcombodataprovider.cpp \
    eventattributedata.cpp \
    variabledata.cpp \
    newvariabledialog.cpp \
    specialcombovaluedata.cpp \
    easynewgameobjectdialog.cpp \
    newdialoguedialog.cpp \
    dialoguedata.cpp \
    dialogueitemdata.cpp \
    music.cpp \
    undochangetilecommand.cpp \
    about.cpp \
    datawriter.cpp \
    dataloader.cpp \
    imagecolorpicker.cpp \
    imagecolorpickerscene.cpp \
    welcomescreen.cpp
FORMS += mainwindow.ui \
    newprojectwindow.ui \
    configstabwidget.ui \
    configstabwindow.ui \
    configstilesetwidget.ui \
    configsgeneralwidget.ui \
    newmapwindow.ui \
    newmapwindowgeneralwidget.ui \
    configsobjectswidget.ui \
    newmapwindowtilesetwidget.ui \
    configsnewobjectwindow.ui \
    configsobjgenericwidget.ui \
    configsobjdadosgeraiswidget.ui \
    configsobjhabilidadeswidget.ui \
    configsobjphysicswidget.ui \
    newmapwindowobjectwidget.ui \
    objectsdock.ui \
    configsimportdialog.ui \
    soundpickerdialog.ui \
    neweventareadialog.ui \
    newteleportareadialog.ui \
    configsobjnpcbehaviorwidget.ui \
    configsobjattributeswidget.ui \
    configsobjitem.ui \
    configsbackgrounds.ui \
    configsanimations.ui \
    configsobjanimationchooserwindow.ui \
    backgroundpickerdialog.ui \
    configsobjnewskilldialog.ui \
    eventswidget.ui \
    neweventdialog.ui \
    newvariabledialog.ui \
    easynewgameobjectdialog.ui \
    newdialoguedialog.ui \
    about.ui \
    imagecolorpicker.ui \
    welcomescreen.ui


TRANSLATIONS = ../translations/gameka_tr_en.qph

unix:!macx:LIBS += -L/usr/local/lib -lGL -lGLU -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lSDL_mixer

win32:LIBS += -lMingw32 -lSDLmain -lSDL_mixer -lSDL

macx:LIBS += -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lSDL_mixer -framework Cocoa

RESOURCES += ../resources.qrc
