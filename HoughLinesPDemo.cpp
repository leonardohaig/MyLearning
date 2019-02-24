//
// Created by liheng on 2019/2/24.
// Program:霍夫P直线检测示例
//Data:2019.2.24
//Author:liheng
//Version:V1.0
//
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

int main()
{
    std::string img_path;
    cv::Mat mat_color;
    cv::Mat mat_gray;
    cv::Mat mat_binary;
    cv::Mat mat_canny;

    img_path = "../pictures/000177.png";
    mat_color = cv::imread(img_path, 1);
    mat_gray = cv::imread(img_path, 0);

    //形态学闭运算
    cv::Mat elementRect;
    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
    cv::morphologyEx(mat_gray,mat_gray,cv::MORPH_CLOSE,elementRect);

    // binary
    cv::threshold(mat_gray, mat_binary, 125, 255.0, cv::THRESH_BINARY);

    // detect edge
    cv::Canny(mat_binary, mat_canny, 50, 125, 3);

    // detect line
    std::vector<cv::Vec4i> lines;
    HoughLinesP(mat_canny,lines,1,CV_PI/180,100,10,50);

    // draw line
    for (size_t i = 0; i < lines.size(); i++)
    {
        cv::Vec4i& linex = lines[i];
        int dx=linex[2]-linex[0];
        int dy=linex[2]-linex[1];
        double angle = atan2(double(dy),dx) * 180 /CV_PI;
        //if (abs(angle) <= 20)
        //    continue;

        line(mat_color, cv::Point(linex[0], linex[1]), cv::Point(linex[2], linex[3]), cv::Scalar(0, 255, 0), 2);
    }

    cv::imshow("gray",   mat_gray);
    cv::imshow("binary", mat_binary);
    cv::imshow("canny", mat_canny);
    cv::imshow("color", mat_color);
    cv::waitKey(0);

    cv::imwrite("res.jpg",mat_color);
    return 0;
}

