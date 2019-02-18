//====================================================================//
// Created by liheng on 19-2-18.
//Program:图像形态学操作
//Data:2019.2.18
//Author:liheng
//Version:V1.0
//====================================================================//

#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat elementRect,elementCross,elementEllipse;

    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
    elementCross = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(3,3),cv::Point(-1,-1));
    elementEllipse = cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(5,5),cv::Point(-1,-1));

    std::cout<<"3X3矩形核:"<<std::endl<<elementRect<<std::endl;
    std::cout<<"3X3十字交叉形核:"<<std::endl<<elementCross<<std::endl;
    std::cout<<"5X5椭圆形核:"<<std::endl<<elementEllipse<<std::endl;

    return 0;
}

