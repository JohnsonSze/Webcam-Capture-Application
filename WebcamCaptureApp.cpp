#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <ctime>

class WebcamCaptureApp {
public:
    WebcamCaptureApp() : windowName("Webcam Capture"), isRunning(true) {
        cap.open(0);
        if (!cap.isOpened()) {
            std::cerr << "Error: Could not open webcam." << std::endl;
            isRunning = false;
        }
    }

    void start() {
        if (isRunning) {
            cv::namedWindow(windowName, cv::WINDOW_NORMAL);
            run();
        }
    }

    void stop() {
        cap.release();
        cv::destroyAllWindows();
    }

private:
    cv::VideoCapture cap;
    std::string windowName;
    cv::Mat frame;
    bool isRunning;

    void captureFrame() {
        std::string filename = generateRandomFileName() + ".png";
        cv::imwrite(filename, frame);
        std::cout << "Screenshot saved as " << filename << std::endl;
    }

    void run() {
        while (isRunning) {
            cap >> frame;
            if (frame.empty()) {
                std::cerr << "Error: Could not capture frame." << std::endl;
                break;
            }

            cv::imshow(windowName, frame);

            char key = (char)cv::waitKey(30);
            if (key == 'q' || key == 'Q') {
                isRunning = false;
            } else if (key == 'd' || key == 'D') {
                captureFrame();
            }
        }
        stop();
    }

    std::string generateRandomFileName() {
        std::srand(std::time(nullptr));
        std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::string filename;
        for (int i = 0; i < 10; ++i) {
            filename += chars[std::rand() % chars.size()];
        }
        return filename;
    }
};

int main() {
    WebcamCaptureApp app;
    app.start();
    return 0;
}
