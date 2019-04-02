/*
 *  Copyright (c) 2011 Dmitry Suvorov <D.Suvorov90@gmail.com>
 */

#ifndef __V_MOTION_DETECTOR_H
#define __V_MOTION_DETECTOR_H

#include <opencv2/core/core.hpp>

class VMotionDetector
{
public:
    VMotionDetector( const cv::Size& imageSize, double cycleTime );

    void detectMovingRegions( const cv::Mat& currentFrame, double timestamp,
                              std::vector<cv::Rect>& targets , cv::Mat& mask );

    double getMotionHistoryDuration( ) const {
        return m_motionHistoryDuration;
    }

private:
    VMotionDetector& operator=( const VMotionDetector& );
    VMotionDetector( const VMotionDetector& );

    cv::Mat m_previousImage;
    cv::Mat m_motionHistoryImage;
    cv::Mat m_bluredImage;

    cv::Mat m_openingKernel;

    cv::Mat m_segmask;

    double m_maxMotionGradient;

    double m_motionHistoryDuration;

    static const double MOTION_THRESHOLD;
    static const double MIN_CONTOUR_AREA;
};

#endif // __V_MOTION_DETECTOR_H
