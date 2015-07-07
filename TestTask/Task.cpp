#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

IplImage* image = 0;

int main(int argc, char** argv)
{
	char* filename = argc == 2 ? argv[1] : "Circle.jpg";
	image = cvLoadImage(filename, CV_LOAD_IMAGE_GRAYSCALE);

	printf("[i] Filename: %s\n", filename);
	assert(image != 0);

	IplImage* src = cvLoadImage(filename);

	CvMemStorage* storage = cvCreateMemStorage(0);

	CvSeq* results = cvHoughCircles(image, storage, CV_HOUGH_GRADIENT, 8, image->width);

	printf("[i] Center coordinates:\n");
	for (int i = 0; i < results->total; i++)
	{
		float* p = (float*)cvGetSeqElem(results, i);
		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
		cvLine(src, pt, pt, CV_RGB(0xff, 0, 0), 8);
		printf("    Point %d: x = %d, y = %d\n", i, pt, pt);
	}

	printf("[i] Total count of circles - %d", results->total);
	cvNamedWindow("Centers of circles", 1);
	
	cvShowImage("Centers of circles", src);

	cvWaitKey(0);

	cvReleaseImage(&image);
	cvReleaseImage(&src);

	cvDestroyAllWindows();
	return 0;
}