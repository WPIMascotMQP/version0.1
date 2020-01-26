#include "VisualProcessor.h"

namespace visualData {
	std::vector<cv::Rect*> global_faces;
	std::vector<cv::Rect*> global_palms;
	std::vector<cv::Rect*> global_bodies;
	std::mutex visual_lock;
}

VisualProcessor::VisualProcessor(int camera_device) {
	// Load the cascades
    std::string face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_frontalface_default.xml");
    std::string eyes_cascade_name = cv::samples::findFile("haarcascades/haarcascade_eye.xml");
    std::string palm_cascade_name = cv::samples::findFile("haarcascades/haarcascade_fist.xml");
    std::string body_cascade_name = cv::samples::findFile("haarcascades/haarcascade_upperbody.xml");
    
    if(!face_cascade.load(face_cascade_name)) {
        std::cout << "ERROR: Unable to Load Face Cascade";
        return;
    };
    if(!eyes_cascade.load(eyes_cascade_name)) {
        std::cout << "ERROR: Unable to Load Eye Cascade";
        return;
    };
    if(!palm_cascade.load(palm_cascade_name)) {
        std::cout << "ERROR: Unable to Palm Eye Cascade";
        return;
    };
    if(!body_cascade.load(body_cascade_name)) {
        std::cout << "ERROR: Unable to Body Eye Cascade";
        return;
    };
    
    // Read the video stream
    capture.open(camera_device);
    if (!capture.isOpened()) {
        std::cout << "ERROR: Unable to get Video Capture";
        return;
    }

    kill = false;
}

VisualProcessor::~VisualProcessor() {

}

void VisualProcessor::startThread() {
	kill = false;
	pthread = std::thread(&VisualProcessor::processWrapper, this);
}


void VisualProcessor::process() {
	if(!capture.read(frame)) {
		std::cout << "ERROR: Unable to Capture Frame";
	}
	if(frame.empty()) {
		std::cout << "ERROR: Frame is empty";
	}

	// Setup
	cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    std::vector<cv::Rect> faces;
    display(faces, face_cascade, cv::Scalar(255, 0, 255), frame, frame_gray);
    deepCopyRect(visualData::global_faces, faces);

    /*std::vector<cv::Rect> palms;
    display(palms, palm_cascade, cv::Scalar(255, 0, 0), frame, frame_gray);
    deepCopyRect(visualData::global_palms, palms);*/

    /*std::vector<cv::Rect> bodies;
    display(bodies, body_cascade, cv::Scalar(0, 0, 255), frame, frame_gray);
    deepCopyRect(visualData::global_bodies, bodies);*/

    //cv::resize(frame, frame, cv::Size(800,800));

    //-- Show what you got
    cv::namedWindow("Capture - Face Detection", cv::WINDOW_AUTOSIZE);
    cv::imshow("Capture - Face Detection", frame);
    cv::waitKey(10);
}

void VisualProcessor::display(std::vector<cv::Rect> objects, cv::CascadeClassifier cascade, cv::Scalar color, cv::Mat frame, cv::Mat frame_gray) {
    cascade.detectMultiScale(frame_gray, objects);
    for(size_t i = 0; i < objects.size(); i++) {
        cv::Point center(objects[i].x + objects[i].width/2, objects[i].y + objects[i].height/2);
        cv::ellipse(frame, center, cv::Size( objects[i].width/2, objects[i].height/2), 
            0, 0, 360, color, 4);
    }
}

void VisualProcessor::deepCopyRect(std::vector<cv::Rect*> global, std::vector<cv::Rect> local) {
	visualData::visual_lock.lock();
	std::vector<cv::Rect*>::iterator itr = global.begin();
	while(itr < global.end()) {
		cv::Rect_<int>* rec = *itr;
		delete(rec);
		itr = global.erase(itr); 
	}
	std::vector<cv::Rect>::iterator itr_l = local.begin();
	while(itr_l < local.end()) {
		cv::Rect_<int> rec = *itr_l;
		cv::Rect_<int>* new_rec = new cv::Rect(rec.x, rec.y, rec.width, rec.height);
		global.push_back(new_rec);
		itr_l++;
	}
	visualData::visual_lock.unlock();
}
