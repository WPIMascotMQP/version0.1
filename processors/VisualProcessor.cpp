#include "VisualProcessor.h"

namespace visualData {
    std::vector<std::vector<cv::Rect*>*> history_faces;
    std::vector<std::vector<cv::Rect*>*> history_bodies;
	std::mutex visual_lock;
    unsigned int history_length = 5;
}

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

    phases[0] = std::make_tuple(&face_cascade, &visualData::history_faces);
    phases[1] = std::make_tuple(&body_cascade, &visualData::history_bodies);
    currentPhase = -1;
}

VisualProcessor::~VisualProcessor() {

}

void VisualProcessor::startThread() {
	kill = false;
	pthread = std::thread(&VisualProcessor::processWrapper, this);
}


void VisualProcessor::process() {
    changePhase();
    auto start = std::chrono::system_clock::now();
	if(!capture.read(frame)) {
		std::cout << "ERROR: Unable to Capture Frame";
	}
	if(frame.empty()) {
		std::cout << "ERROR: Frame is empty";
	}

	// Setup
	cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, CV_BGRA2BGR);
    cv::cvtColor(frame_gray, frame_gray, CV_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    std::vector<cv::Rect> objects;
    cv::CascadeClassifier classifier = *currentClassifier;
    display(objects, classifier, cv::Scalar(255, 0, 255), frame, frame_gray);
    deepCopyRect(*currentHistory, objects);

    //-- Show what you got
    cv::namedWindow("Capture - Face Detection", cv::WINDOW_AUTOSIZE);
    cv::imshow("Capture - Face Detection", frame);
    cv::waitKey(10);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << elapsed_seconds.count() << std::endl;
}

void VisualProcessor::display(std::vector<cv::Rect> objects, cv::CascadeClassifier cascade, cv::Scalar color, cv::Mat frame, cv::Mat sample) {
    cascade.detectMultiScale(sample, objects);
    for(size_t i = 0; i < objects.size(); i++) {
        cv::Point center(objects[i].x + objects[i].width/2, objects[i].y + objects[i].height/2);
        cv::ellipse(frame, center, cv::Size( objects[i].width/2, objects[i].height/2), 
            0, 0, 360, color, 4);
    }
}

void VisualProcessor::deepCopyRect(std::vector<std::vector<cv::Rect*>*> history, std::vector<cv::Rect> local) {
	visualData::visual_lock.lock();
    std::vector<cv::Rect*>* new_history = new std::vector<cv::Rect*>();
    std::vector<cv::Rect>::iterator itr_local = local.begin();
    while(itr_local < local.end()) {
        cv::Rect_<int> rec = *itr_local;
        cv::Rect_<int>* new_rec = new cv::Rect(rec.x, rec.y, rec.width, rec.height);
        new_history->push_back(new_rec);
        itr_local++;
    }
    history.push_back(new_history);
    if(history.size() > visualData::history_length) {
        std::vector<std::vector<cv::Rect*>*>::iterator itr_history = history.begin();
        std::vector<cv::Rect_<int>*>* old_history = *itr_history;
        std::vector<cv::Rect*>::iterator itr_old = old_history->begin();
        while(itr_old < old_history->end()) {
            cv::Rect_<int>* rec = *itr_old;
            delete(rec);
            itr_old = old_history->erase(itr_old); 
        }
        delete(old_history);
    }
	visualData::visual_lock.unlock();
}

void VisualProcessor::changePhase() {
    currentPhase++;
    if(currentPhase >= sizeof(phases)/sizeof(*phases)) {
        currentPhase = 0;
    }
    std::tie(currentClassifier, currentHistory) = phases[currentPhase];
}

// Credit https://codeyarns.com/2015/08/27/depth-and-type-of-matrix-in-opencv/
std::string VisualProcessor::getMatDepth(cv::Mat mat)
{
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

//Credit https://codeyarns.com/2015/08/27/depth-and-type-of-matrix-in-opencv/
std::string VisualProcessor::getMatType(cv::Mat mat)
{
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