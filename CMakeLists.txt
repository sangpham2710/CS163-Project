cmake_minimum_required(VERSION 3.5)

project(CS163-Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        Trie.h
        Map.h
        CSV.h

        IDictionary.h
        IFavorite.h
        IHistory.h

        Dictionary.h
        DictionaryDataStructure.h
        Favorite.h
        History.h

        App.h

        widgetsearch.h
        widgetsearch.cpp
        widgetsearch.ui

        widgetdefinition.h
        widgetdefinition.cpp
        widgetdefinition.ui

        widgetfavorite.h
        widgetfavorite.cpp
        widgetfavorite.ui

        widgetfavoritedefinition.h
        widgetfavoritedefinition.cpp
        widgetfavoritedefinition.ui

        widgetgame.h
        widgetgame.cpp
        widgetgame.ui

        dialogaddnewword.h
        dialogaddnewword.cpp
        dialogaddnewword.ui

        dialogeditword.h
        dialogeditword.cpp
        dialogeditword.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CS163-Project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CS163-Project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CS163-Project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CS163-Project
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CS163-Project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CS163-Project PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CS163-Project)
endif()


