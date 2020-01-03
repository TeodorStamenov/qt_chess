QT += quick \
        websockets \
        core \
        multimedia \
        concurrent

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#           ENGINE_PATH=\\\"$$PWD/../engine/stockfish.exe\\\"

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/communication/commands/ClAskPossibleMovesCmd.cpp \
    source/communication/commands/ClEngineMakeMoveCmd.cpp \
    source/communication/commands/ClMakeMoveCmd.cpp \
    source/communication/commands/ClNewGameCmd.cpp \
    source/communication/commands/SrvMoveResultCmd.cpp \
    source/communication/commands/SrvNewGameOkCmd.cpp \
    source/communication/commands/SrvPossibleMovesCmd.cpp \
    source/logic/CapturedPieces.cpp \
    source/logic/EngineProcess.cpp \
    source/logic/InGameMenu.cpp \
    source/logic/Menu.cpp \
    source/logic/SavedGames.cpp \
    source/main.cpp \
    source/logic/Board.cpp \
    source/logic/GameManager.cpp \
    source/protomessages/ClAskPossibleMoves.pb.cc \
    source/protomessages/ClEngineMakeMove.pb.cc \
    source/protomessages/ClHandshake.pb.cc \
    source/protomessages/ClMakeMove.pb.cc \
    source/protomessages/ClNewGame.pb.cc \
    source/protomessages/SrvHandshake.pb.cc \
    source/protomessages/SrvMoveResult.pb.cc \
    source/protomessages/SrvNewGameOk.pb.cc \
    source/protomessages/SrvPossibleMoves.pb.cc \
    source/utils/Logger.cpp \
    source/communication/Buffer.cpp \
    source/communication/commands/ClHandshakeCmd.cpp \
    source/communication/commands/SrvHandshakeCmd.cpp \
    source/communication/ConnectionHandler.cpp \
    source/communication/CommandCreator.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/communication/commands/ClAskPossibleMovesCmd.h \
    source/communication/commands/ClEngineMakeMoveCmd.h \
    source/communication/commands/ClMakeMoveCmd.h \
    source/communication/commands/ClNewGameCmd.h \
    source/communication/commands/ProtoCommands.h \
    source/communication/commands/SrvMoveResultCmd.h \
    source/communication/commands/SrvNewGameOkCmd.h \
    source/communication/commands/SrvPossibleMovesCmd.h \
    source/logic/Board.h \
    source/logic/CapturedPieces.h \
    source/logic/EngineProcess.h \
    source/logic/GameManager.h \
    source/logic/InGameMenu.h \
    source/logic/Menu.h \
    source/logic/SavedGames.h \
    source/protomessages/ClAskPossibleMoves.pb.h \
    source/protomessages/ClEngineMakeMove.pb.h \
    source/protomessages/ClHandshake.pb.h \
    source/protomessages/ClMakeMove.pb.h \
    source/protomessages/ClNewGame.pb.h \
    source/protomessages/SrvHandshake.pb.h \
    source/protomessages/SrvMoveResult.pb.h \
    source/protomessages/SrvNewGameOk.pb.h \
    source/protomessages/SrvPossibleMoves.pb.h \
    source/utils/GameResult.h \
    source/utils/Logger.h \
    source/communication/Buffer.h \
    source/communication/ConnectionHandler.h \
    source/communication/CommandCreator.h \
    source/communication/commands/CommandI.h \
    source/communication/commands/CommandIds.h \
    source/communication/commands/ClHandshakeCmd.h \
    source/communication/commands/SrvHandshakeCmd.h \
    source/communication/commands/CommandImpl.h \
    source/communication/CommandHandlerI.h \
    source/utils/PossibleMoves.h

win32: LIBS += -L$$PWD/../../../protobuf/lib/ -llibprotobuf

INCLUDEPATH += $$PWD/../../../protobuf/include/ \
                source/
DEPENDPATH += $$PWD/../../../protobuf/include/

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../protobuf/lib/libprotobuf.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../protobuf/lib/libprotobuf.a
