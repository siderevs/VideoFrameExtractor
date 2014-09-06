#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

static void onMouse(int event, int x, int y, int, void* puntero)
{
	if (event != EVENT_LBUTTONDOWN)
		return;

	Mat image = *((Mat *)puntero);
	imwrite("Gray_Image.jpg", image);
}

int main(int argc, char* argv[])
{
	VideoCapture cap("C:\\dev\\video.mp4"); // open the video file for reading

	if (!cap.isOpened())
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double fps = cap.get(CV_CAP_PROP_FPS);
	cout << "Frame per seconds : " << fps << endl;

	namedWindow("VideoOutput", CV_WINDOW_AUTOSIZE);
	Mat frame;
	setMouseCallback("VideoOutput", onMouse, &frame);
	while (1)
	{
		bool bSuccess = cap.read(frame);

		Mat dest;
		resize(frame, dest, Size(), 0.5, 0.5, INTER_LINEAR);

		if (!bSuccess)
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		imshow("VideoOutput", dest);
		if (waitKey(1000 / fps) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}