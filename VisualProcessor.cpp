#include "VisualProcessor.h"

VisualProcessor::VisualProcessor(int camera_device) {
    std::string face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_frontalface_default.xml");
    std::string eyes_cascade_name = cv::samples::findFile("haarcascades/haarcascade_eye.xml");
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
    {
        std::cout << "--(!)Error loading face cascade\n";
        return;
    };
    if( !eyes_cascade.load( eyes_cascade_name ) )
    {
        std::cout << "--(!)Error loading eyes cascade\n";
        return;
    };
    cv::VideoCapture capture;
    //-- 2. Read the video stream
    capture.open( camera_device );
    if ( ! capture.isOpened() )
    {
        std::cout << "--(!)Error opening video capture\n";
        return;
    }
}

VisualProcessor::~VisualProcessor() {

}

void VisualProcessor::processSnapshot() {

}