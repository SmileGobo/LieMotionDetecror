/*
 *  Copyright (c) 2011 Dmitry Suvorov <D.Suvorov90@gmail.com>
 */

#include "v_motion_detector.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include "debug.h"

const double VMotionDetector::MOTION_THRESHOLD = 10;
const double VMotionDetector::MIN_CONTOUR_AREA = 100;

VMotionDetector::VMotionDetector( const cv::Size& imageSize, double cycleTime) :
        m_previousImage( cv::Mat::zeros( imageSize, CV_8UC1 ) ),
        m_motionHistoryImage( imageSize, CV_32FC1 ),
        m_openingKernel( 5, 5, CV_8UC1 ),
        m_segmask( imageSize, CV_32FC1 ),
        m_maxMotionGradient( 1.5 * cycleTime ),
        m_motionHistoryDuration( 7 * cycleTime )
{
}


void VMotionDetector::detectMovingRegions( const cv::Mat& currentFrame, double timestamp,
                                           std::vector<cv::Rect>& targets , cv::Mat& mask )
{
   //Debug("11");
    cv::GaussianBlur( currentFrame, m_bluredImage, cv::Size( 3, 3 ), -1 );
   // Debug("22");
    cv::absdiff( m_bluredImage, m_previousImage, mask );
   // Debug("33");
    cv::threshold( mask, mask,  MOTION_THRESHOLD, 255, cv::THRESH_BINARY );
   // Debug("44");
    cv::morphologyEx( mask, mask, cv::MORPH_CLOSE, cv::Mat() );
    cv::morphologyEx( mask, mask, cv::MORPH_OPEN, m_openingKernel,
                      cv::Point( -1, -1 ), 1, cv::BORDER_CONSTANT, cv::Scalar( 0 ) );
    cv::updateMotionHistory( mask, m_motionHistoryImage, timestamp, m_motionHistoryDuration );
    cv::segmentMotion( m_motionHistoryImage, m_segmask, targets, timestamp, m_maxMotionGradient );
  //  Debug("22");
    std::vector<cv::Rect>::iterator endIt = targets.end( );
    for( std::vector<cv::Rect>::iterator it = targets.begin( ); it != endIt; ++it ) {
        if( cv::countNonZero( mask( * it ) ) < MIN_CONTOUR_AREA )
            targets.erase( it );
    }

    m_bluredImage.copyTo( m_previousImage );
}
