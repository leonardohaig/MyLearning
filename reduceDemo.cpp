//====================================================================//
// Created by liheng on 19-7-2.
//Program:reduce()函数
//Data:2019.7.2
//Author:liheng
//Version:V1.0
//====================================================================//

#include <opencv2/opencv.hpp>
#include <iostream>

//int main()
//{
//
//    cv::Mat srcMat = (cv::Mat_<uchar >(3,3) <<
//            225, 38, 22,
//            67, 44, 12,
//            89, 65, 63);
//
//    std::cout<<"srcMat="<<std::endl;
//    std::cout << srcMat << std::endl;
//
//    cv::Mat output;
//
//    //输出每列的最大值
//    cv::reduce(srcMat, output, 0, cv::REDUCE_MAX);
//    std::cout<<"Maximum value of each col:"<<std::endl;
//    std::cout << output << std::endl;
//
//    //输出每行的最小值
//    cv::reduce(srcMat, output, 1, cv::REDUCE_MIN);
//    std::cout<<"Minimum value of each row:"<<std::endl;
//    std::cout << output << std::endl;
//
//    //输出每列的均值
//    cv::reduce(srcMat, output, 0, cv::REDUCE_AVG);
//    std::cout<<"Average value of each col:"<<std::endl;
//    std::cout << output << std::endl;
//
//    //输出每列的和
//    //Note:此时需要指定输出矩阵的类型，求和时，uchar值的和可能会超过其表示范围，所以需要显式指定类型
//    cv::reduce(srcMat, output, 0, cv::REDUCE_SUM,CV_32SC1);
//    std::cout<<"Summation value of each col:"<<std::endl;
//    std::cout << output << std::endl;
//
//    return 0;
//}

int main()
{
    cv::Mat srcImage = cv::imread("../pictures/123.bmp",cv::IMREAD_GRAYSCALE);
    cv::imwrite("11234.jpg",srcImage);
    cv::Mat histImage;
    cv::reduce(srcImage,histImage,0,cv::REDUCE_AVG);

    cv::Mat histShowImage(srcImage.size(),CV_8UC3,cv::Scalar(0,0,0));
    for(int i=0; i<histShowImage.cols-1;++i)
    {
        cv::line(histShowImage,cv::Point(i,histImage.at<uchar >(0,i)),\
        cv::Point(i+1,histImage.at<uchar >(0,i+1)),cv::Scalar(0,0,255),2);
    }

    cv::flip(histShowImage,histShowImage,0);

    cv::cvtColor(srcImage,srcImage,cv::COLOR_GRAY2BGR);
    cv::addWeighted(srcImage,0.5,histShowImage,0.8,0,histShowImage);
    cv::imshow("histLine",histShowImage);
    cv::waitKey(0);
    cv::imwrite("1123.jpg",histShowImage);


    return 0;
}