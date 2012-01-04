#-------------------------------------------------
#
# Project created by QtCreator 2011-07-03T00:32:46
#
#-------------------------------------------------

QT       -= core

QT       -= gui

unix:!macx:TARGET = ../runtime_linux
macx:TARGET = ../runtime_mac
win32:TARGET = ../runtime_w32
#CONFIG   += console
#CONFIG   -= app_bundle

TEMPLATE = app

MOC_DIR = .moc
UI_DIR = .uic
RCC_DIR = .rcc
OBJECTS_DIR = .obj


INCLUDEPATH += common engine engine/entities engine/data engine/geometry \
    engine/managers \
    game \
    game/defaultmovements \
    game/defaultmovements/basemovements \
    game/interpreter \
    game/states \
    utils


SOURCES += \
    game/defaultmovements/basemovements/VehicleMovement.cpp \
    engine/geometry/Vector2.cpp \
    engine/data/VariableData.cpp \
    common/Util.cpp \
    game/states/TitleState.cpp \
    engine/managers/Timermanager.cpp \
    engine/entities/Tileset.cpp \
    engine/entities/Tilemap.cpp \
    engine/entities/Tile.cpp \
    engine/entities/Text.cpp \
    engine/entities/TeleportArea.cpp \
    game/defaultmovements/basemovements/StaticObject.cpp \
    engine/managers/StateManager.cpp \
    engine/entities/State.cpp \
    engine/data/SpriteRepresentation.cpp \
    engine/entities/Sprite.cpp \
    game/states/SplashState.cpp \
    engine/geometry/Sphere.cpp \
    utils/SpatialHashmap.cpp \
    engine/managers/SoundManager.cpp \
    engine/data/SkillData.cpp \
    engine/managers/ScrollManager.cpp \
    engine/entities/ScreenEffects.cpp \
    engine/entities/Screen.cpp \
    engine/geometry/Rectangle.cpp \
    engine/data/ProcedureData.cpp \
    engine/entities/PlayerData.cpp \
    game/defaultmovements/basemovements/PlatformerMovement.cpp \
    game/interpreter/ObjectFunctions.cpp \
    game/interpreter/ObjectFactory.cpp \
    game/defaultmovements/basemovements/NpcMovementObject.cpp \
    engine/entities/Music.cpp \
    game/defaultmovements/basemovements/MouseFollowMovement.cpp \
    engine/managers/ModalManager.cpp \
    engine/entities/Modal.cpp \
    game/states/MapState.cpp \
    Main.cpp \
    utils/List.cpp \
    engine/geometry/Line.cpp \
    game/defaultmovements/basemovements/ItemMovementObject.cpp \
    game/interpreter/Interpreter.cpp \
    engine/managers/InputManager.cpp \
    game/states/GameOverState.cpp \
    engine/data/GameObjectInstance.cpp \
    engine/data/GameObjectCreationData.cpp \
    engine/data/GameObjectClass.cpp \
    engine/data/GameObjectAnimation.cpp \
    common/GameObject.cpp \
    engine/managers/GameManager.cpp \
    common/GameData.cpp \
    engine/data/EventData.cpp \
    game/defaultmovements/basemovements/EnemyMovementObject.cpp \
    game/defaultmovements/basemovements/EightMovementObject.cpp \
    engine/entities/DialogueText.cpp \
    engine/data/DialogueItemData.cpp \
    engine/data/DialogueData.cpp \
    engine/entities/DialogBar.cpp \
    engine/entities/DamageDisplay.cpp \
    engine/entities/ChoiceText.cpp \
    game/defaultmovements/basemovements/BouncingBall.cpp \
    engine/data/BackgroundLayerData.cpp \
    engine/entities/BackgroundLayer.cpp \
    engine/data/BackgroundData.cpp \
    utils/AuxiliarMath.cpp \
    engine/data/AnimationData.cpp \
    game/defaultmovements/basemovements/AcceleratedParticle.cpp

HEADERS += \
    game/defaultmovements/basemovements/VehicleMovement.h \
    engine/geometry/Vector2.h \
    engine/data/VariableData.h \
    common/Util.h \
    game/states/TitleState.h \
    engine/managers/TimerManager.h \
    engine/entities/Tileset.h \
    engine/entities/Tilemap.h \
    engine/entities/Tile.h \
    engine/entities/Text.h \
    engine/entities/TeleportArea.h \
    game/defaultmovements/basemovements/StaticObject.h \
    engine/managers/StateManager.h \
    engine/entities/State.h \
    engine/data/SpriteRepresentation.h \
    engine/entities/Sprite.h \
    game/states/SplashState.h \
    engine/geometry/Sphere.h \
    utils/SpatialHashmap.h \
    engine/managers/SoundManager.h \
    engine/data/SkillData.h \
    engine/managers/ScrollManager.h \
    engine/entities/ScreenEffects.h \
    engine/entities/Screen.h \
    engine/geometry/Rectangle.h \
    engine/data/ProcedureData.h \
    engine/entities/PlayerData.h \
    game/defaultmovements/basemovements/PlatformerMovement.h \
    game/interpreter/ObjectFunctions.h \
    game/interpreter/ObjectFactory.h \
    game/defaultmovements/basemovements/NpcMovementObject.h \
    engine/entities/Music.h \
    game/defaultmovements/basemovements/MouseFollowMovement.h \
    engine/managers/ModalManager.h \
    engine/entities/Modal.h \
    game/states/MapState.h \
    utils/List.h \
    engine/geometry/Line.h \
    game/defaultmovements/basemovements/ItemMovementObject.h \
    game/interpreter/Interpreter.h \
    engine/managers/InputManager.h \
    game/states/GameOverState.h \
    engine/data/GameObjectInstance.h \
    engine/data/GameObjectCreationData.h \
    engine/data/GameObjectClass.h \
    engine/data/GameObjectAnimation.h \
    common/GameObject.h \
    engine/managers/GameManager.h \
    common/GameData.h \
    engine/data/EventData.h \
    game/defaultmovements/basemovements/EnemyMovementObject.h \
    game/defaultmovements/basemovements/EightMovementObject.h \
    engine/entities/DialogueText.h \
    engine/data/DialogueItemData.h \
    engine/data/DialogueData.h \
    engine/entities/DialogBar.h \
    engine/entities/DamageDisplay.h \
    common/CommonTypes.h \
    engine/entities/ChoiceText.h \
    game/defaultmovements/basemovements/BouncingBall.h \
    engine/data/BackgroundLayerData.h \
    engine/entities/BackgroundLayer.h \
    engine/data/BackgroundData.h \
    utils/AuxiliarMath.h \
    engine/data/AnimationData.h \
    game/defaultmovements/basemovements/AcceleratedParticle.h \
    utils/ArrayCreator.h



unix:INCLUDEPATH += /usr/local/include/SDL

unix:INCLUDEPATH += /usr/include/SDL

win32:INCLUDEPATH += C:\QtSDK\mingw\include\SDL

unix:!macx:LIBS += -L/usr/local/lib -lGL -lGLU -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lSDL_mixer -lSDL_image -g

win32:LIBS += -lMingw32 -lSDLmain -lSDL_mixer -lSDL_ttf -lSDL_mixer -lSDL_image -lSDL_gfx -lSDL

macx:LIBS += -L/usr/local/lib -lSDL -lSDLmain -lSDL_ttf -lSDL_gfx -lSDL_mixer -lSDL_image -framework Cocoa
