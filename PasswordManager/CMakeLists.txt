cmake_minimum_required(VERSION 3.16)
project(addressbook LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/itemviews/addressbook")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(BSO)
qt_add_executable(addressbook
    adddialog.cpp adddialog.h
    passwordwidget.cpp passwordwidget.h
    main.cpp
    mainwindow.cpp mainwindow.h
    newentrytab.cpp newentrytab.h
    tablemodel.cpp tablemodel.h
    mongodbcreator.cpp mongodbcreator.h
)

set_target_properties(addressbook PROPERTIES
    WIN64_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(addressbook PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS addressbook
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
