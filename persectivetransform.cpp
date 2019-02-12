//====================================================================//
// Created by liheng on 19-2-12.
//Program:将逆透视变换后的坐标点转换到原图中
//Data:2019.2.12
//Author:liheng
//Version:V1.0
//====================================================================//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

int main()
{
    //首先读入图像
    cv::Mat srcImage = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);

    //定义源点和目标点,源点为正常读入的图像的点，目标点为转换后的鸟瞰图上的对应点
    cv::Point2f srcPoints[4],dstPoints[4];
    srcPoints[0] = cv::Point2f(369,375);
    srcPoints[1] = cv::Point2f(545,221);
    srcPoints[2] = cv::Point2f(650,221);
    srcPoints[3] = cv::Point2f(793,375);

    dstPoints[0] = cv::Point2f(339,375);
    dstPoints[1] = cv::Point2f(339,211);
    dstPoints[2] = cv::Point2f(823,211);
    dstPoints[3] = cv::Point2f(823,375);

    //求解变换矩阵
    cv::Mat m_persctiveMat = cv::getPerspectiveTransform(srcPoints,dstPoints);//读入图像转换为鸟瞰图的矩阵
    cv::Mat m_unPersctiveMat =cv::getPerspectiveTransform(dstPoints,srcPoints);//鸟瞰图到原始图像的转换矩阵

    //求解鸟瞰图
    cv::Mat birdViewImage;
    cv::warpPerspective(srcImage,birdViewImage,m_persctiveMat,cv::Size(srcImage.cols,srcImage.rows),cv::INTER_LINEAR);


    //鸟瞰图车道线上的两点.Note:此处为了简单，仅选择2点进行变换
    std::vector<cv::Point2f> leftLine,rightLine;
    leftLine.push_back(cv::Point2f(661,0));
    leftLine.push_back(cv::Point2f(366,376));

    rightLine.push_back(cv::Point2f(1097,0));
    rightLine.push_back(cv::Point2f(883,376));

    //求解其在原始图像上对应的坐标
    std::vector<cv::Point2f> unWarpedLeftLine,unWarpedRightLine;
    cv::perspectiveTransform(leftLine,unWarpedLeftLine,m_unPersctiveMat);
    cv::perspectiveTransform(rightLine,unWarpedRightLine,m_unPersctiveMat);

    //线段可视化
    cv::cvtColor(srcImage,srcImage,CV_GRAY2BGR);
    cv::line(srcImage,unWarpedLeftLine[0],unWarpedLeftLine[1],cv::Scalar(0,255,0),2);
    cv::line(srcImage,unWarpedRightLine[0],unWarpedRightLine[1],cv::Scalar(0,255,0),2);

    cv::cvtColor(birdViewImage,birdViewImage,CV_GRAY2BGR);
    cv::line(birdViewImage,leftLine[0],leftLine[1],cv::Scalar(0,255,0),2);
    cv::line(birdViewImage,rightLine[0],rightLine[1],cv::Scalar(0,255,0),2);

    cv::imshow("srcImage",srcImage);
    cv::imshow("birdViewImage",birdViewImage);
    cv::waitKey(0);


    return 0;
}