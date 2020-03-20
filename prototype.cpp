//
// Created by FaridLenovo on 17.03.2020.
//
#include <cmath>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
//#include <opencv2/cudaimgproc.hpp>
#include <algorithm>

using namespace std;
using namespace cv;
//using namespace cv::cuda;


struct comparePointsX {
    bool operator() (cv::Point pt1, cv::Point pt2) { return (pt1.x < pt2.x);}
} compPointX;

struct comparePointsY {
    bool operator() (cv::Point pt1, cv::Point pt2) { return (pt1.y < pt2.y);}
} compPointY;

/*
 * Utility Function for distance calculation
 */
double distance(Point2f a, Point2f b) {
    return sqrt( pow(a.x - b.x,2) + pow(a.y - b.y, 2) );
}

static void help()
{
    cout << "This program demonstrates line finding with the Hough transform." << endl;
    cout << "Usage:" << endl;
    cout << "./CarpetPrototype <image_name>, Default is 513_Serapi.png\n" << endl;
}


int main(int argc, const char* argv[])
{
    // Necessary if display via WSL
    setenv("DISPLAY", "127.0.0.1:0", true);
    // If no input picture then use 513_Serapi.png
    const string filename = argc >= 2 ? argv[1] : "513_Serapi.png";

    Mat src = imread(filename, IMREAD_GRAYSCALE);
    Mat copy = imread(filename);
    Mat blurImage, mask, dst;

    // Catch if empty picture
    if (src.empty()) {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    // Smoothing with blur 3x3 Filter and binary threshold operator and save into mask
    blur(src, blurImage, Size(3,3));
    threshold( blurImage, mask, 55, 255, 1 );

    // Get the biggest bounding box in mask
    Rect2d bo;
    bo = boundingRect(mask);

    // Get the 4 corners of bounding box
    Point P1 = Point2i(bo.x, bo.y);
    Point P2 = Point2i(bo.x, bo.y + bo.height);
    Point P3 = Point2i(bo.x + bo.width, bo.y);
    Point P4 = Point2i(bo.x + bo.width, bo.y + bo.height);
    //cout << "P1 " << P1 << " P2 "<< P2 << " P3 " << P3 << " P4 "<< P4 << endl;

    // Draw red lines of the rectangle in the original image
    line(copy, P1, P2, Scalar(0,0,255),3,LINE_AA);
    line(copy, P2, P4, Scalar(0,0,255),3,LINE_AA);
    line(copy, P3, P1, Scalar(0,0,255),3,LINE_AA);
    line(copy, P3, P4, Scalar(0,0,255),3,LINE_AA);

    //cv::cvtColor(mask,dst,COLOR_GRAY2BGR);

    // Find all nonzero point from thresholded point cloud mask and store in list idx
    vector<Point2f> idx;
    findNonZero(mask,idx);
    Point2f cP1,cP2,cP3,cP4;

    // Function to optimize the nearest point, iterate over all nearby points
    for(Point2f&v:idx) {
        //cout << "Abstand : " << distance(P1,v) << endl;
        if ((v.x <= P1.x && v.y <= P1.y) && ( distance(P1, v) <= 100.0 ) ){
            cP1 = v;
            //cout << "Gef1";
        } else if ((v.x <= P1.x && v.y >= P1.y) && ( distance(P1, v) <= 100.0 )) {
            cP1 = v;
            //cout << "gef2";
        }
        else if ((v.x >= P1.x && v.y <= P1.y) && ( distance(P1, v) <= 100.0 )) {
            cP1 = v;
            //cout << "gef3";
        }
        // TODO
        //else if ((v.x >= P2.x && v.y <= P2.y) && ( distance(P2, v)<= 20 )) {
        //    cP1 = v;
        //}
    }


    for(Point2f&v:idx) {
        //cout << "Abstand : " << distance(P1,v) << endl;
        if ((v.x <= P2.x && v.y <= P2.y) && ( distance(P2, v) <= 40.0 ) ){
            cP2 = v;
            //cout << "Gef12";
        } else if ((v.x <= P2.x && v.y >= P2.y) && ( distance(P2, v)  <= 40.0 )) {
            cP2 = v;
            //cout << "Gef22";
        }
        else if ((v.x >= P2.x && v.y <= P2.y) && ( distance(P2, v) <= 40.0 )) {
            cP2 = v;
            //cout << "Gef32";
        }
        // TODO
        //else if ((v.x >= P2.x && v.y <= P2.y) && ( distance(P2, v)<= 20 )) {
        //    cP1 = v;
        //}
    }
/*
    for(Point2f&v:idx) {
        //cout << "Abstand : " << distance(P1,v) << endl;
        if ((v.x <= P3.x && v.y <= P3.y) && ( distance(P3, v)/100.0 <= 10.0 ) ){
            cP3 = v;
            cout << "Gef13";
        } else if ((v.x <= P3.x && v.y >= P3.y) && ( distance(P3, v) / 100.0 <= 10.0 )) {
            cP3 = v;
            cout << "Gef23";
        }
        else if ((v.x >= P3.x && v.y <= P3.y) && ( distance(P3, v) / 100.0 <= 10.0 )) {
            cP3 = v;
            cout << "Gef33";
        }
        //else if ((v.x >= P2.x && v.y <= P2.y) && ( distance(P2, v)<= 20 )) {
        //    cP1 = v;
        //}
    }
    */
/*
    for(Point2f&v:idx) {
        //cout << "Abstand : " << distance(P1,v) << endl;
        if ((v.x <= P4.x && v.y <= P4.y) && ( distance(P4, v)/100.0 <= 10.0 ) ){
            cP4 = v;
            cout << "Gef14";
        } else if ((v.x <= P4.x && v.y >= P4.y) && ( distance(P4, v) / 100.0 <= 10.0 )) {
            cP4 = v;
            cout << "Gef24";
        }
        else if ((v.x >= P4.x && v.y <= P4.y) && ( distance(P4, v) / 100.0 <= 10.0 )) {
            cP4 = v;
            cout << "Gef34";
        }
        //else if ((v.x >= P2.x && v.y <= P2.y) && ( distance(P2, v)<= 20 )) {
        //    cP1 = v;
        //}
    }
*/
    // If point cP1 is not found catch it with old rectangle point P1
    if (cP1.x == 0 && cP1.y == 0) {
        cP1.x = P1.x;
        cP1.y = P1.y;
    }
    // TODO nochmal kalibrieren mit Schachbrett
    double pixC_L = 980;
    double pixC_B = 960;
    //Point2f mase = Point2f(norm(cP2-Point2f(P4))/980,norm(cP1-cP2)/960);

    // Original Maße  2,78 m x 1,98 m
    Point2f mase = Point2f(distance(cP2, P4) / pixC_L, distance(cP1, cP2) / pixC_B);
    //Point2f mase = Point2f(norm(P2-P4) / pixC_L, norm(P1-P2) / pixC_B);
    cout << mase << endl;

    //cout << "Breite :" << norm(cP1-cP2) / 960;
    //cout << "Länge : " << norm(cP2-Point2f(P4)) / 980;

    /*
     * Draw initial points and optimized points in image with red and green circles
     *      P1 ------- P3
     *      |          |
     *      P2 ------- P4
     */
    circle(copy, P1,8,Scalar(0,255,0),6,8);
    circle(copy, cP1, 8,Scalar(0,0,255),6,LINE_AA);
    circle(copy, P2,8,Scalar(0,255,0),6,8);
    circle(copy, cP2, 8,Scalar(0,0,255),6,LINE_AA);
    circle(copy, P3,8,Scalar(0,255,0),6,8);
    circle(src, cP3, 8,Scalar(0,0,255),6,LINE_AA);
    circle(copy, P4,8,Scalar(0,255,0),6,8);
    circle(src, cP4, 8,Scalar(0,0,255),6,LINE_AA);

    //cout << "Abstand " << distance(P1,cP1);
    //circle(copy,counterMax, 8,Scalar(255,0,0),6,LINE_AA);

    /*
     *
     * int xmin, ymax;
    vector<Vec4i> lines_cpu;
    {
        const int64 start = getTickCount();

        cv::HoughLinesP(blurImage, lines_cpu, 1, CV_PI / 180, 50, 20, 10); //50,60,100

        const double timeSec = (getTickCount() - start) / getTickFrequency();
        cout << "CPU Time : " << timeSec * 1000 << " ms" << endl;
        cout << "CPU Found : " << lines_cpu.size() << endl;

    }
    vector<Vec2i> lines_y;
    vector<Vec2i> lines_x;
    for (size_t i = 0; i < lines_cpu.size(); ++i)
    {
        Vec4i l = lines_cpu[i];

        line(blurImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
        cout << "Coordinates of Lines : " << l[0] << " " << l[1] << " "
             << l[2] << " " << l[3] << endl;
        double orientation= atan2(l[1]-l[3],l[0] - l[2]);
        if ( abs(orientation*(180/CV_PI) )>45.0  && abs(orientation * (180/CV_PI)) < 135.0) {
            lines_y.emplace_back(Vec2i(l[0],l[1]));
            lines_y.emplace_back(Vec2i(l[2],l[3]));
        }
        else {
            lines_x.emplace_back(Vec2i(l[0],l[1]));
            lines_x.emplace_back(Vec2i(l[2],l[3]));
        }
    }

    sort(lines_x.begin(),lines_x.end(),compPointY);
    sort(lines_y.begin(),lines_y.end(),compPointX);
    cout << "X Lines" << endl;
    for(auto& v:lines_x) {
        cout << v << endl;
    }
    cout << "Y Lines" << endl;
    for(auto& v:lines_y){
        cout << v << endl;
    }
    double nx = lines_x.size(), ny = lines_y.size();
    double sumx = 0.0, sumy = 0.0;
    for(auto& v:lines_x) {
        sumx += v[1];
    }

    for(auto& v:lines_y) {
        sumy += v[0];
    }


    cout << "MittelPunkt : " << sumx/nx << " " << sumy / ny << endl;

    circle(dst_cpu,Point2f(sumx/nx,sumy/ny), 5,Scalar(0,0,255),2,LINE_AA);
    vector<Vec2f> leftVert, rightVert, upHoriz, botHoriz;
    for (auto&v: lines_x) {
        if (v[1] < sumx/nx)
            upHoriz.emplace_back(v);
        else
            botHoriz.emplace_back(v);
    }
    for (auto&v: lines_y) {
        if (v[0] < sumy/nx)
            leftVert.emplace_back(v);
        else
            rightVert.emplace_back(v);
    }

    cout << "Bottom Lines" << endl;
    for(auto& v:botHoriz) {
        cout << v << endl;
    }
    cout << "Up Lines" << endl;
    for(auto& v:upHoriz){
        cout << v << endl;
    }
    cout << "Right Lines" << endl;
    for(auto& v:rightVert) {
        cout << v << endl;
    }
    cout << "Left Lines" << endl;
    for(auto& v:leftVert){
        cout << v << endl;
    }
    for(auto&v:botHoriz){
        circle(dst_cpu,Point2f(v[0],v[1]), 5,Scalar(255,0,0),2,LINE_AA);
    }
    */

    // Show the images
    namedWindow("source", 0);
    namedWindow("thresh", 0);
    namedWindow("Box", 0);
    resizeWindow("source", 1280,800);
    resizeWindow("thresh", 1280,800);
    resizeWindow("Box", 1280,800);
    imshow("source", src);
    imshow("thresh", mask);
    imshow("Box", copy);
    waitKey();

    return 0;
}

