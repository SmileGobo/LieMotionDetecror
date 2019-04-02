#ifndef FRAMEVIEW_H
#define FRAMEVIEW_H

#include <QObject>
#include <opencv2/highgui/highgui.hpp>
#include "datatypes.h"
class FrameView : public QObject
{
Q_OBJECT
public:
    FrameView(const QString &win_name);
    virtual ~FrameView();
public slots:
    void RefreshFrame(const cv::Mat &n_frame);
    void DrawMotion(const RectList& rect,const cv::Mat &n_frame);

private:
    QString m_win_name;
};

#endif // FRAMEVIEW_H
