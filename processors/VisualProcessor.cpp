#include "VisualProcessor.h"

// Global Trackers that holds visual data
namespace visualData {
    VisualTrackerManager face_manager;
    VisualTrackerManager body_manager;
    std::mutex visual_lock;
}

/**
 CONSTRUCTOR
 @param camera_device The hardware camera number
 */
VisualProcessor::VisualProcessor(int camera_device) {
	// Load the cascades
    std::string face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_frontalface_default.xml");
    std::string body_cascade_name = cv::samples::findFile("haarcascades/haarcascade_fullbody.xml");

    if(!face_cascade.load(face_cascade_name)) {
        std::cout << "ERROR: Unable to Load Face Cascade";
        return;
    };
    if(!body_cascade.load(body_cascade_name)) {
        std::cout << "ERROR: Unable to Load Face Cascade";
        return;
    };

    // Read the video stream
    capture.open(camera_device);
    if (!capture.isOpened()) {
        std::cout << "ERROR: Unable to get Video Capture";
        return;
    }

    kill = false;

    phases[0] = std::make_tuple(&face_cascade, &visualData::face_manager);
    phases[1] = std::make_tuple(&body_cascade, &visualData::body_manager);
    currentPhase = -1;
}

/**
 DECONSTRUCTOR
 */
VisualProcessor::~VisualProcessor() {

}

/**
 Starts the processing thread for the visual procesor
 */
void VisualProcessor::startThread() {
	kill = false;
	pthread = std::thread(&VisualProcessor::processWrapper, this);
}

/**
 The actual processing thread
 Takes a snapshot from the capture device, detects one of the cascades
 based on the phase and adds that data to the VisualTrackerManagers
 */
void VisualProcessor::process() {
    changePhase();
    //auto start = std::chrono::system_clock::now();
	if(!capture.read(frame)) {
		std::cout << "ERROR: Unable to Capture Frame";
	}
	if(frame.empty()) {
		std::cout << "ERROR: Frame is empty";
	}

	// Setup
	cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    // Detect obejcts
    std::vector<cv::Rect> objects;
    currentClassifier->detectMultiScale(frame_gray, objects, 1.5);
    currentManager->addRects(objects);

    // Get rects from trackers
    visualData::visual_lock.lock();
    std::vector<cv::Rect*>* faces = visualData::face_manager.getRects();
    std::vector<cv::Rect*>* bodies = visualData::body_manager.getRects();
    visualData::visual_lock.unlock();

    // Display Rects on frame
    display(faces, cv::Scalar(255, 0, 255), frame);
    display(bodies, cv::Scalar(0, 0, 255), frame);
    deleteVector(faces);
    deleteVector(bodies);

    //-- Show what you got
    cv::namedWindow("Capture - Face Detection", cv::WINDOW_AUTOSIZE);
    cv::imshow("Capture - Face Detection", frame);
    cv::waitKey(10);
    /*auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << elapsed_seconds.count() << std::endl;*/
}

/**
 Displays the given rects on the given frame
 @param objects The objects to display on the frame
 @param color The cv color to show the ellipse as
 @param frame The frame to paint the ellipse on
 */
void VisualProcessor::display(std::vector<cv::Rect*>* objects, cv::Scalar color, cv::Mat frame) {
    std::vector<cv::Rect*>::iterator itr = objects->begin();
    while(itr < objects->end()) {
        cv::Rect_<int>* rect = *itr;
        cv::Point center(rect->x + rect->width/2, rect->y + rect->height/2);
        cv::ellipse(frame, center, cv::Size(rect->width/2, rect->height/2), 
            0, 0, 360, color, 4);
        itr++;
    }
}

/**
 Deletes the given vector of rects
 @param objects The vector of rects to delete
 */
void VisualProcessor::deleteVector(std::vector<cv::Rect*>* objects) {
    std::vector<cv::Rect*>::iterator itr = objects->begin();
    while(itr < objects->end()) {
        cv::Rect_<int>* rect = *itr;
        delete(rect);
        itr = objects->erase(itr);
    }
    delete(objects);
}

/**
 Changes the current phase of the processor to the next
 */
void VisualProcessor::changePhase() {
    currentPhase++;
    if(currentPhase >= sizeof(phases)/sizeof(*phases)) {
        currentPhase = 0;
    }
    std::tie(currentClassifier, currentManager) = phases[currentPhase];
}

/**
 Credit https://codeyarns.com/2015/08/27/depth-and-type-of-matrix-in-opencv/
 Gets the depth of the given cv::Mat
 To only be used for debugging
 @param mat The Mat to get the depth of
 */
std::string VisualProcessor::getMatDepth(cv::Mat mat) {
    const int depth = mat.depth();

    switch (depth)
    {
    case CV_8U:  return "CV_8U";
    case CV_8S:  return "CV_8S";
    case CV_16U: return "CV_16U";
    case CV_16S: return "CV_16S";
    case CV_32S: return "CV_32S";
    case CV_32F: return "CV_32F";
    case CV_64F: return "CV_64F";
    default:
        return "Invalid depth type of matrix!";
    }
}

/**
 Credit https://codeyarns.com/2015/08/27/depth-and-type-of-matrix-in-opencv/
 Gets the type of the given cv::Mat
 To only be used for debugging
 @param mat The mat to get the type of
 */
std::string VisualProcessor::getMatType(cv::Mat mat) {
    const int mtype = mat.type();

    switch (mtype)
    {
    case CV_8UC1:  return "CV_8UC1";
    case CV_8UC2:  return "CV_8UC2";
    case CV_8UC3:  return "CV_8UC3";
    case CV_8UC4:  return "CV_8UC4";

    case CV_8SC1:  return "CV_8SC1";
    case CV_8SC2:  return "CV_8SC2";
    case CV_8SC3:  return "CV_8SC3";
    case CV_8SC4:  return "CV_8SC4";

    case CV_16UC1: return "CV_16UC1";
    case CV_16UC2: return "CV_16UC2";
    case CV_16UC3: return "CV_16UC3";
    case CV_16UC4: return "CV_16UC4";

    case CV_16SC1: return "CV_16SC1";
    case CV_16SC2: return "CV_16SC2";
    case CV_16SC3: return "CV_16SC3";
    case CV_16SC4: return "CV_16SC4";

    case CV_32SC1: return "CV_32SC1";
    case CV_32SC2: return "CV_32SC2";
    case CV_32SC3: return "CV_32SC3";
    case CV_32SC4: return "CV_32SC4";

    case CV_32FC1: return "CV_32FC1";
    case CV_32FC2: return "CV_32FC2";
    case CV_32FC3: return "CV_32FC3";
    case CV_32FC4: return "CV_32FC4";

    case CV_64FC1: return "CV_64FC1";
    case CV_64FC2: return "CV_64FC2";
    case CV_64FC3: return "CV_64FC3";
    case CV_64FC4: return "CV_64FC4";

    default:
        return "Invalid type of matrix!";
    }
}