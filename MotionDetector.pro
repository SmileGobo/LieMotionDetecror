TEMPLATE = app
TARGET = MotionDetector
LIBS += -lopencv_video
LIBS += -lopencv_highgui
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_calib3d
LIBS += -lboost_thread
HEADERS += v_motion_detector.h \
    debug.h \
    motiondetectorhelper.h
SOURCES += v_motion_detector.cpp \
    motiondetectorhelper.cpp
SOURCES += main.cpp
