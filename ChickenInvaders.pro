# Define the project and target
QT += core gui multimedia

# Define the application name and target
TARGET = ChickenInvaders
TEMPLATE = app

# Include the necessary modules
QT += widgets
QT = core gui multimedia widgets

# Source files
SOURCES += \
    main.cpp \
    src/Game.cpp \
    src/view/Bullet.cpp \
    src/view/Chicken.cpp \
    src/view/SpaceShip.cpp \
    src/view/Health.cpp \
    src/view/Score.cpp

# Header files
HEADERS += \
    src/Game.h \
    src/view/Bullet.h \
    src/view/Chicken.h \
    src/view/SpaceShip.h \
    src/view/Health.h \
    src/view/Score.h

# Resource files
RESOURCES += resources.qrc

# Additional compiler options
CONFIG += c++11