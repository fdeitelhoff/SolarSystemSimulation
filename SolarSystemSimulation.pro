#-------------------------------------------------
#
# Project created by QtCreator 2012-04-05T21:42:37
#
#-------------------------------------------------

QT       += core gui sql opengl

TARGET = SolarSystemSimulation
TEMPLATE = app


SOURCES += main.cpp \
    forms/main/mainwindow.cpp \
    OpenGL/glvector.cpp \
    OpenGL/glpoint.cpp \
    OpenGL/glperspective.cpp \
    OpenGL/glmatrix.cpp \
    OpenGL/gllight.cpp \
    OpenGL/glcube.cpp \
    OpenGL/glcolorrgba.cpp \
    OpenGL/glbody.cpp \
    forms/simulation/simulationview.cpp \
    forms/heavenlybody/heavenlybodyoverview.cpp \
    model/heavenlybody/heavenlybodymodel.cpp \
    data/heavenlybody/heavenlybodyrepository.cpp \
    database/postgresqldatabase.cpp \
    forms/heavenlybody/heavenlybodydetails.cpp \
    model/heavenlybody/heavenlybodytablemodel.cpp \
    model/heavenlybody/heavenlybody.cpp \
    data/solarsystem/solarsystemrepository.cpp \
    model/solarsystem/solarsystem.cpp \
    model/solarsystem/solarsystemheavenlybody.cpp \
    forms/solarsystem/solarsystemoverview.cpp \
    model/solarsystem/solarsystemmodel.cpp \
    model/solarsystem/solarsystemtablemodel.cpp \
    forms/solarsystem/solarsystemdetails.cpp \
    model/heavenlybody/heavenlybodycomboboxmodel.cpp \
    model/solarsystem/solarsystemheavenlybodytablemodel.cpp \
    data/exceptions/deleteentityfailedexception.cpp \
    model/exceptions/propertynotvalidexception.cpp \
    simulation/solarsystemsimulation.cpp \
    visualization/heavenlybody/heavenlybody3d.cpp \
    visualization/heavenlybody/star3d.cpp \
    visualization/heavenlybody/planet3d.cpp \
    visualization/orbit/orbit3d.cpp \
    database/exceptions/databaseconnectionfailedexception.cpp \
    data/exceptions/sqlqueryexception.cpp \
    data/exceptions/entitynotuniqueexception.cpp

HEADERS  += forms/main/mainwindow.h \
    OpenGL/glvector.h \
    OpenGL/glpoint.h \
    OpenGL/glperspective.h \
    OpenGL/glmatrix.h \
    OpenGL/gllight.h \
    OpenGL/glcube.h \
    OpenGL/glcolorrgba.h \
    OpenGL/glbody.h \
    OpenGL/GL/glut.h \
    OpenGL/GL/freeglut_std.h \
    OpenGL/GL/freeglut_ext.h \
    OpenGL/GL/freeglut.h \
    forms/simulation/simulationview.h \
    forms/heavenlybody/heavenlybodyoverview.h \
    model/heavenlybody/heavenlybodymodel.h \
    data/heavenlybody/heavenlybodyrepository.h \
    database/postgresqldatabase.h \
    forms/heavenlybody/heavenlybodydetails.h \
    model/heavenlybody/heavenlybodytablemodel.h \
    model/heavenlybody/heavenlybody.h \
    data/solarsystem/solarsystemrepository.h \
    model/solarsystem/solarsystem.h \
    model/solarsystem/solarsystemheavenlybody.h \
    forms/solarsystem/solarsystemoverview.h \
    model/solarsystem/solarsystemmodel.h \
    model/solarsystem/solarsystemtablemodel.h \
    forms/solarsystem/solarsystemdetails.h \
    model/heavenlybody/heavenlybodycomboboxmodel.h \
    model/solarsystem/solarsystemheavenlybodytablemodel.h \
    data/exceptions/deleteentityfailedexception.h \
    model/exceptions/propertynotvalidexception.h \
    simulation/solarsystemsimulation.h \
    visualization/heavenlybody/heavenlybody3d.h \
    visualization/heavenlybody/star3d.h \
    visualization/heavenlybody/planet3d.h \
    visualization/orbit/orbit3d.h \
    database/exceptions/databaseconnectionfailedexception.h \
    data/exceptions/sqlqueryexception.h \
    data/exceptions/entitynotuniqueexception.h

FORMS    += forms/main/mainwindow.ui \
    forms/simulation/simulationview.ui \
    forms/heavenlybody/heavenlybodyoverview.ui \
    forms/heavenlybody/heavenlybodydetails.ui \
    forms/solarsystem/solarsystemoverview.ui \
    forms/solarsystem/solarsystemdetails.ui

# UI_HEADERS_DIR += src/forms

# Seperate the Win32 and Unix freeglut libs.
win32   {   LIBS += -L \
            "E:/Programme/QtSDK/mingw/freeglut/lib" \
            #"/OpenGL/freeglut/win32" \
            -lfreeglut
        }

unix    {   LIBS += -lglut \
            -lGL \
            -lGLU
        }

OTHER_FILES += \
    database/DDL.txt \
    database/heavenlybody.txt \
    database/solarsystem.txt \
    database/solarsystemtoheavenlybody.txt \
    OpenGL/freeglut/win32/libfreeglut_static.a \
    OpenGL/freeglut/win32/libfreeglut.a
