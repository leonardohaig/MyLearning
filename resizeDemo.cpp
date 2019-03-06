//====================================================================//
// Created by liheng on 19-3-2.
//Program:图像缩放操作
//Data:2019.3.2
//Author:liheng
//Version:V1.0
//====================================================================//

#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat srcMat = (cv::Mat_<char>(3,3) <<
            234, 38, 22,
            67, 44, 12,
            89, 65, 63);

    //std::cout<<srcMat<<std::endl;
    cv::Mat dstMat;

    srcMat = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);
    cv::imshow("src",srcMat);

    cv::resize(srcMat,dstMat,cv::Size(640,480),0,0,cv::INTER_NEAREST);

    cv::cvtColor(dstMat,dstMat,cv::COLOR_GRAY2BGR);
    cv::putText(dstMat,"INTER_NEAREST",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);


    cv::Mat dst1 = dstMat.clone();
    cv::resize(srcMat,dstMat,cv::Size(640,480),0,0,cv::INTER_CUBIC);

    cv::cvtColor(dstMat,dstMat,cv::COLOR_GRAY2BGR);
    cv::putText(dstMat,"INTER_CUBIC",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);

    cv::hconcat(dst1,dstMat,dstMat);

    cv::imshow("INTER_CUBIC",dstMat);

    cv::imwrite("src.jpg",srcMat);

    cv::waitKey(0);

    return 0;
}