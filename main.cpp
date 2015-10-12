#define G_THRESH 1


#include "cv.h"
#include "highgui.h"

void cvEllipseAxis(CvBox2D box, CvPoint2D32f pt[4]);
int main(int argc, char** argv)
{

	IplImage* img = cvLoadImage(argv[1]);
	IplImage* gray_img;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* Contour[10];


	CvContourScanner Collection;
	CvBox2D Ellipse[10];

	CvPoint2D32f Pt_A[4], Pt_B[4];

	int number = 0;

	cvNamedWindow("Fish", CV_WINDOW_AUTOSIZE);

	gray_img = cvCreateImage(cvGetSize(img), 8, 1);


	cvCvtColor(img, gray_img, CV_BGR2GRAY);
	cvThreshold(gray_img, gray_img, G_THRESH, 255, CV_THRESH_BINARY);


	cvThreshold(gray_img, gray_img, G_THRESH, 255, CV_THRESH_BINARY);

	cvDilate(gray_img, gray_img, NULL, 3);
	cvErode(gray_img, gray_img, NULL, 5);
	cvSmooth(gray_img,gray_img,3);

	Collection = cvStartFindContours(gray_img, storage,sizeof(CvContour),CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));


	Contour[0] = cvFindNextContour(Collection);
	Contour[1] = cvFindNextContour(Collection);
	Contour[2] = cvFindNextContour(Collection);

	cvEndFindContours(&Collection);

	Ellipse[0] = cvFitEllipse2(Contour[1]);
	Ellipse[1] = cvFitEllipse2(Contour[2]);


	cvEllipseBox(gray_img, Ellipse[0], CV_RGB(255, 255, 255));
	cvEllipseBox(gray_img, Ellipse[1], CV_RGB(255, 255, 255));

	cvEllipseAxis(Ellipse[0], Pt_A);
	cvEllipseAxis(Ellipse[1], Pt_B);

	cvLine(gray_img, cvPoint(Pt_A[1].x, Pt_A[1].y), cvPoint(Pt_A[3].x, Pt_A[3].y), CV_RGB(255, 255, 255), 2);
	cvLine(gray_img, cvPoint(Pt_B[1].x, Pt_B[1].y), cvPoint(Pt_B[3].x, Pt_B[3].y), CV_RGB(255, 255, 255), 2);


	cvShowImage("Fish", gray_img);
	cvWaitKey(0);
	cvReleaseImage(&gray_img);
	cvReleaseImage(&img);
	cvDestroyWindow("Fish");

	return 0;
}

void cvEllipseAxis(CvBox2D box, CvPoint2D32f pt[4]) //?????????,???????
{

	double d1, d2;
	CvPoint2D32f tp[4];
	cvBoxPoints(box,tp);
	d1 = (tp[1].x - tp[0].x)*(tp[1].x - tp[0].x) + (tp[1].y - tp[0].y)*(tp[1].y - tp[0].y);
	d2 = (tp[1].x - tp[2].x)*(tp[1].x - tp[2].x) + (tp[1].y - tp[2].y)*(tp[1].y - tp[2].y);
	if (d1<d2)
	{
		pt[1].x = 0.5*(tp[0].x + tp[1].x);
		pt[1].y = 0.5*(tp[0].y + tp[1].y);

		pt[2].x = 0.5*(tp[1].x + tp[2].x);
		pt[2].y = 0.5*(tp[1].y + tp[2].y);

		pt[3].x = 0.5*(tp[2].x + tp[3].x);
		pt[3].y = 0.5*(tp[2].y + tp[3].y);

		pt[0].x = 0.5*(tp[3].x + tp[0].x);
		pt[0].y = 0.5*(tp[3].y + tp[0].y);
	}
	else
	{
		pt[0].x = 0.5*(tp[0].x + tp[1].x);
		pt[0].y = 0.5*(tp[0].y + tp[1].y);
		pt[1].x = 0.5*(tp[1].x + tp[2].x);
		pt[1].y = 0.5*(tp[1].y + tp[2].y);
		pt[2].x = 0.5*(tp[2].x + tp[3].x);
		pt[2].y = 0.5*(tp[2].y + tp[3].y);
		pt[3].x = 0.5*(tp[3].x + tp[0].x);
		pt[3].y = 0.5*(tp[3].y + tp[0].y);
	}
}
