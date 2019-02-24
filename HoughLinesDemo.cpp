//
// Created by liheng on 2019/2/24.
// Program:霍夫直线检测示例
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
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(mat_canny, lines, 1, CV_PI / 180, 150, 0, 0);

    // draw line
    std::cout << "line number: " << lines.size() << std::endl;
    for (size_t i = 0; i < lines.size(); i++)
    {
        cv::Vec2f linex = lines[i];
        std::cout << "radius: " << linex[0] <<", angle: " << 180 / CV_PI * linex[1] << std::endl;
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(mat_color, pt1, pt2, cv::Scalar(0, 255, 0), 2);
    }
    cv::imshow("gray", mat_gray);
    cv::imshow("binary", mat_binary);
    cv::imshow("canny", mat_canny);
    cv::imshow("color", mat_color);
    cv::waitKey(0);

    cv::imwrite("res.jpg",mat_color);

    return 0;
}
