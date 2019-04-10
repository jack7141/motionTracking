#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    VideoCapture cam(2);
    Mat image1,image2;
    while (true) {
        cam.read(image1);
        Mat grayimage1,grayimage2;
        cvtColor(image1,grayimage1,COLOR_RGB2GRAY);
        cam.read(image2);
        cvtColor(image2,grayimage2,COLOR_RGB2GRAY);
        Mat diffImage;
        //compare two images
        absdiff(grayimage1,grayimage2,diffImage);
        inRange(diffImage, Scalar(0, 0, 255), Scalar(179, 255, 255), diffImage);
        Mat thresholdimage;
        threshold(diffImage, thresholdimage, 20, 255, THRESH_BINARY_INV);
//        imshow("thresholdimage",thresholdimage);
//        imshow("diffImage",diffImage);
        blur(thresholdimage,thresholdimage,Size(3, 3));
        vector<vector<Point>> contours,largestContour;

        Rect bounding_rect;
        vector<Vec4i> hierachy;

        Mat Temp;
        thresholdimage.copyTo(Temp);
        imshow("Temp",Temp);
        findContours(Temp,contours,hierachy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
        bool objectDetect = false;
        if (contours.size()>0) objectDetect = true;
        else objectDetect = false;
        if (objectDetect) {

            largestContour.push_back(contours.at(contours.size()-1));
            bounding_rect = boundingRect(largestContour.at(0));

            int xpos = bounding_rect.x + bounding_rect.width/2;
            int ypos = bounding_rect.y + bounding_rect.height/2;

            circle(image1,Point(xpos,ypos),20,Scalar(0,255,0),2);
            line(image1,Point(xpos,ypos),Point(xpos,ypos-20),Scalar(255,255,0),2);
            line(image1,Point(xpos,ypos),Point(xpos,ypos+20),Scalar(255,255,0),2);
            line(image1,Point(xpos,ypos),Point(xpos-20,ypos),Scalar(0,255,255),2);
            line(image1,Point(xpos,ypos),Point(xpos+20,ypos),Scalar(0,255,255),2);


            putText(image1,"Tracking object <"+ to_string(xpos)+"," +to_string(ypos) +">",Point(xpos,ypos),1,1,Scalar(255,255,255));

        }
        imshow("image1",image1);
        if (waitKey(1)==27) break;

    }
}


