#ifndef DATATYPES_H
#define DATATYPES_H

#include <QMetaType>

#include <QVector>
#include <opencv2/core/core.hpp>
#include "RegistryTemplate.h"
#include "captureframehelper.h"

typedef QVector<cv::Mat> FrameList;
typedef QVector<cv::Rect> RectList;


Q_DECLARE_METATYPE(cv::Mat)
Q_DECLARE_METATYPE(cv::Rect)

Q_DECLARE_METATYPE(RectList)
typedef Registry<CaptureFrameHelper> RegistryCapture;

#endif // DATATYPES_H
