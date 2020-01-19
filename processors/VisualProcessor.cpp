#include "VisualProcessor.h"

namespace visualData {
	std::vector<cv::Rect*> global_faces;
	std::vector<cv::Rect*> global_palms;
	std::vector<cv::Rect*> global_bodies;
	std::mutex visual_lock;
}

VisualProcessor::VisualProcessor(int camera_device) {
	// Load the cascades
	//std::string face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_fullbody.xml");
	//std::string face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_fist.xml");
    std::string face_cascade_name = cv::samples::findFile("haarcascades/haarcascade_frontalface_default.xml");
    std::string eyes_cascade_name = cv::samples::findFile("haarcascades/haarcascade_eye.xml");
    
    if(!face_cascade.load(face_cascade_name)) {
        std::cout << "ERROR: Unable to Load Face Cascade";
        return;
    };
    if(!eyes_cascade.load(eyes_cascade_name)) {
        std::cout << "ERROR: Unable to Load Eye Cascade";
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

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces);
    for(size_t i = 0; i < faces.size(); i++) {
        cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
        cv::ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2), 
        	0, 0, 360, cv::Scalar( 255, 0, 255 ), 4);
        cv::Mat faceROI = frame_gray( faces[i]);
        // In each face, detect eyes
        std::vector<cv::Rect> eyes;
        eyes_cascade.detectMultiScale( faceROI, eyes);
        for(size_t j = 0; j < eyes.size(); j++) {
            cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, 
            	faces[i].y + eyes[j].y + eyes[j].height/2);
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25);
            cv::circle( frame, eye_center, radius, cv::Scalar( 255, 0, 0 ), 4);
        }
    }

    deepCopyRect(visualData::global_faces, faces);

    //-- Show what you got
    cv::namedWindow("Capture - Face Detection", cv::WINDOW_AUTOSIZE);
    cv::imshow("Capture - Face Detection", frame);
    cv::waitKey(10);
}

void VisualProcessor::deepCopyRect(std::vector<cv::Rect*> global, std::vector<cv::Rect> local) {
	visualData::visual_lock.lock();
	std::vector<cv::Rect*>::iterator itr = global.begin();
	while(itr < global.end()) {
		cv::Rect_<int>* rec = *itr;
		delete(&rec);
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
