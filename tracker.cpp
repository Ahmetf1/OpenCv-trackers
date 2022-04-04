#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <filesystem>

int main(int argc, char** argv) {
    std::string trackerTypes[8] = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};

    int tracker_number; // tracker_number specify the tracking alghoritm in the order of the list above
    std::string video_path;
    bool save;
    if (argc < 3) {            
        std::cout << "enter parameters\n"
                     "param1: tracker number\n"
                     "available trackers: {BOOSTING, MIL, KCF, TLD, MEDIANFLOW, GOTURN, MOSSE, CSRT}\n"
                     "param2: video_path\n"
                     "param3: want to save 1 or 0" << std::endl;
        return -1;
    }
    else {
        tracker_number = atoi(argv[1]);
        video_path = std::string(argv[2]);
        int int_save = atoi(argv[3]);
        save = true ? (int_save == 1) : false;
    }

    cv::Ptr<cv::Tracker> tracker;

    switch (tracker_number)
    {
    case 0:
        //tracker = cv::TrackerBoosting::create();
        break;
    case 1:
        tracker = cv::TrackerMIL::create();
        break;
    case 2:
        tracker = cv::TrackerKCF::create();
        break;
    case 3:
        //tracker = cv::TrackerTLD::create();
        break;
    case 4:
        //tracker = cv::TrackerMedianFlow::create();
        break;
    case 5:
        tracker = cv::TrackerGOTURN::create();
        break;
    case 6:
        //tracker = cv::TrackerMOSSE::create();
        break;
    case 7:
        tracker = cv::TrackerCSRT::create();
        break;
    default:
        break;
    }

    cv::Rect2i roi;
    cv::Mat frame;

    cv::VideoCapture cap(video_path);
    cap >> frame;

    roi = cv::selectROI("tracker", frame);
    tracker -> init(frame, roi);

    // to save video
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cv::VideoWriter video("outcpp.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(frame_width,frame_height));


    while (cv::waitKey(1) !=27 && frame.rows!=0 && frame.cols!=0)
    {
        cap >> frame;
        if (frame.empty())
            break;
        tracker -> update(frame, roi);
        rectangle(frame, roi, cv::Scalar( 100, 100, 100 ), 2, 1 );
        if (save);
            video.write(frame);
        imshow("tracker",frame);
    }
    return 0;    
}