#include "frameview.h"
#include "debug.h"
FrameView::FrameView(const QString &win_name):m_win_name(win_name)
{
    cv::namedWindow(m_win_name.toStdString());
}

FrameView::~FrameView(){
    cv::destroyWindow(m_win_name.toStdString());
}

void FrameView::RefreshFrame(const cv::Mat &n_frame){
    //Debug("!!!!");
    cv::imshow(m_win_name.toStdString(),n_frame);
}

void FrameView::DrawMotion(const RectList& rects,const cv::Mat &n_frame){
    //Debug("121312");
    cv::Mat img(n_frame);
    for (int i=0;i<rects.size();++i){
        cv::Rect rect(rects[i]);
        cv::rectangle(img, rect, cv::Scalar( 255, 255, 0 ) );
    }
    RefreshFrame(img);
}
