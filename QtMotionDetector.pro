# -------------------------------------------------
# Project created by QtCreator 2012-09-05T16:17:25
# -------------------------------------------------
QT += sql
QT -= gui
TARGET = QtMotionDetector
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    v_motion_detector.cpp \
    captureframehelper.cpp \
    exception.cpp \
    frameview.cpp \
    qmotiondetectorwrapper.cpp \
    framedirwriter.cpp \
    framesaver.cpp \
    motionlogger.cpp
OTHER_FILES += cap_file
HEADERS += v_motion_detector.h \
    debug.h \
    captureframehelper.h \
    exception.h \
    frameview.h \
    qmotiondetectorwrapper.h \
    framedirwriter.h \
    framesaver.h \
    datatypes.h \
    motionlogger.h \
    RegistryTemplate.h
LIBS += -lopencv_video \
    -lopencv_highgui \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_flann \
    -lopencv_objdetect \
    -lopencv_calib3d \
    -lopencv_features2d \
    -lavformat \
    -lswscale
