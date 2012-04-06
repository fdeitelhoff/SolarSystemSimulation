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
    model/solarsystem/solarsystem.cpp

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
    model/solarsystem/solarsystem.h

FORMS    += forms/main/mainwindow.ui \
    forms/simulation/simulationview.ui \
    forms/heavenlybody/heavenlybodyoverview.ui \
    forms/heavenlybody/heavenlybodydetails.ui

# UI_HEADERS_DIR += src/forms

# Das müssen wir noch irgendwie Plattform unabhängig machen.
LIBS += -L \
    "E:/Programme/QtSDK/mingw/freeglut/lib" \
    -lfreeglut

OTHER_FILES += \
    database/DDL.txt \
    database/heavenlybody.txt
