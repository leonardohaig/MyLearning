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
//    //===============图像形态学操作，结构元素（核） --start================================//
//    cv::Mat elementRect,elementCross,elementEllipse;
//
//    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
//    elementCross = cv::getStructuringElement(cv::MORPH_CROSS,cv::Size(3,3),cv::Point(-1,-1));
//    elementEllipse = cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(5,5),cv::Point(-1,-1));
//
//    std::cout<<"3X3矩形核:"<<std::endl<<elementRect<<std::endl;
//    std::cout<<"3X3十字交叉形核:"<<std::endl<<elementCross<<std::endl;
//    std::cout<<"5X5椭圆形核:"<<std::endl<<elementEllipse<<std::endl;
//
//
//    //自定义核（结构元素）
//    cv::Mat_<uchar> cross(5,5);
//    cv::Mat_<uchar> diamond(5,5);
//    cv::Mat_<uchar> x(5,5);
//    cv::Mat_<uchar> square(5,5);
//
//    // Creating the cross-shaped structuring element
//    cross <<
//          0, 0, 1, 0, 0,
//            0, 0, 1, 0, 0,
//            1, 1, 1, 1, 1,
//            0, 0, 1, 0, 0,
//            0, 0, 1, 0, 0;
//
//    // Creating the diamond-shaped structuring element
//    diamond <<
//            0, 0, 1, 0, 0,
//            0, 1, 1, 1, 0,
//            1, 1, 1, 1, 1,
//            0, 1, 1, 1, 0,
//            0, 0, 1, 0, 0;
//
//    // Creating the x-shaped structuring element
//    x <<
//      1, 0, 0, 0, 1,
//            0, 1, 0, 1, 0,
//            0, 0, 1, 0, 0,
//            0, 1, 0, 1, 0,
//            1, 0, 0, 0, 1;
//
//    // Creating the square-shaped structuring element
//    square <<
//           1, 1, 1, 1, 1,
//            1, 1, 1, 1, 1,
//            1, 1, 1, 1, 1,
//            1, 1, 1, 1, 1,
//            1, 1, 1, 1, 1;
//
//    int xnr = x.rows;
//    int xnl = x.cols;
//    for(int j = 0;j<xnr;j++)
//    {
//        char *data = x.ptr<char>(j);
//        for(int i = 0; i<xnl; i++)
//        {
//            int value = data[i];
//            std::cout<<value<<" ";
//        }
//        std::cout<<std::endl;
//    }
//
//    //===============图像形态学操作，结构元素（核） --end================================//


//    //===============腐蚀与膨胀操作 --start================================//
//    //首先读入图像,并二值化
//    cv::Mat srcImage = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);
//    cv::threshold(srcImage,srcImage,125,255,cv::THRESH_BINARY);
//
//    cv::imshow("srcImage",srcImage);
//
//
//    //获取进行形态学操作的核
//    cv::Mat elementRect;
//    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
//
//    //膨胀
//    cv::Mat dilateImage;
//    cv::dilate(srcImage,dilateImage,elementRect);
//    //cv::morphologyEx(srcImage,dilateImage,cv::MORPH_DILATE,elementRect);
//    cv::cvtColor(dilateImage,dilateImage,cv::COLOR_GRAY2BGR);
//    cv::putText(dilateImage,"dilate",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//    cv::imshow("dilateImage",dilateImage);
//
//
//    //腐蚀
//    cv::Mat erodeImage;
//    cv::erode(srcImage,erodeImage,elementRect);
//    //cv::morphologyEx(srcImage,dilateImage,cv::MORPH_ERODE,elementRect);
//    cv::cvtColor(erodeImage,erodeImage,cv::COLOR_GRAY2BGR);
//    cv::putText(erodeImage,"erode",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//    cv::imshow("erodeImage",erodeImage);
//
//    cv::hconcat(dilateImage,erodeImage,dilateImage);
//    cv::resize(dilateImage,dilateImage,cv::Size(),0.5,0.5);
//    cv::imshow("res",dilateImage);
//
//    cv::resize(srcImage,srcImage,cv::Size(),0.5,0.5);
//    cv::imwrite("srcImage.jpg",srcImage);
//    cv::imwrite("res.jpg",dilateImage);
//
//    //===============腐蚀与膨胀操作 --end================================//

//    //===============腐蚀与膨胀操作 --start================================//
//    //首先读入图像,并二值化
//    cv::Mat srcImage = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);
//    cv::threshold(srcImage,srcImage,125,255,cv::THRESH_BINARY);
//
//    cv::imshow("srcImage",srcImage);
//
//
//    //获取进行形态学操作的核
//    cv::Mat elementRect;
//    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
//
//    //开运算
//    cv::Mat opendImage;
//    cv::morphologyEx(srcImage,opendImage,cv::MORPH_OPEN,elementRect);
//    cv::cvtColor(opendImage,opendImage,cv::COLOR_GRAY2BGR);
//    cv::putText(opendImage,"opendImage",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//
//    //闭运算
//    cv::Mat closedImage;
//    cv::morphologyEx(srcImage,closedImage,cv::MORPH_CLOSE,elementRect);
//    cv::cvtColor(closedImage,closedImage,cv::COLOR_GRAY2BGR);
//    cv::putText(closedImage,"closedImage",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//
//    cv::hconcat(opendImage,closedImage,opendImage);
//    cv::imshow("res",opendImage);
//
//    cv::resize(srcImage,srcImage,cv::Size(),0.5,0.5);
//    cv::resize(opendImage,opendImage,cv::Size(),0.5,0.5);
//
//    cv::imwrite("srcImage.jpg",srcImage);
//    cv::imwrite("opendImage.jpg",opendImage);
//    //===============腐蚀与膨胀操作 --end================================//



//    //===============形态学梯度 --start================================//
//    //首先读入图像,并二值化
//    cv::Mat srcImage = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);
//    cv::threshold(srcImage,srcImage,125,255,cv::THRESH_BINARY);
//
//    cv::imshow("srcImage",srcImage);
//
//    //获取进行形态学操作的核
//    cv::Mat elementRect;
//    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));
//
//    //膨胀
//    cv::Mat dilateImage;
//    cv::dilate(srcImage,dilateImage,elementRect);
//    //cv::morphologyEx(srcImage,dilateImage,cv::MORPH_DILATE,elementRect);
//
//    //腐蚀
//    cv::Mat erodeImage;
//    cv::erode(srcImage,erodeImage,elementRect);
//    //cv::morphologyEx(srcImage,dilateImage,cv::MORPH_ERODE,elementRect);
//
//
//    //1.计算基本梯度：膨胀后的图像减去腐蚀后的图像
//    cv::Mat basicGradient;
//    cv::subtract(dilateImage, erodeImage, basicGradient, cv::Mat());
//    //cv::morphologyEx(srcImage,basicGradient,cv::MORPH_GRADIENT,elementRect);//两者等效
//    cv::imshow("basicGradient", basicGradient);
//
//    //2.计算内部梯度：原图像减去腐蚀之后的图像
//    cv::Mat internalGradientImg;
//    cv::subtract(srcImage, erodeImage, internalGradientImg, cv::Mat());
//    cv::imshow("internalGradientImg", internalGradientImg);
//
//    //3.计算外部梯度：膨胀后的图像减去原图像
//    cv::Mat externalGradientImg;
//    cv::subtract(dilateImage, srcImage, externalGradientImg, cv::Mat());
//    cv::imshow("externalGradientImg", externalGradientImg);
//
//    //4.方向梯度：使用X方向与Y方向的直线作为结构元素---------
//    //cv::Mat hse = getStructuringElement(cv::MORPH_RECT, cv::Size(srcImage.cols / 16, 1),cv::Point(-1,-1));
//    //cv::Mat vse = getStructuringElement(cv::MORPH_RECT, cv::Size(1, srcImage.rows / 16),cv::Point(-1,-1));
//    cv::Mat hse = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 1),cv::Point(-1,-1));
//    cv::Mat vse = getStructuringElement(cv::MORPH_RECT, cv::Size(1, 3),cv::Point(-1,-1));
//    cv::Mat  xDirectImg, yDirectImg;
//    //4.1 X 方向梯度：膨胀与腐蚀之后得到图像求差值
//    cv::erode(srcImage, erodeImage, hse);
//    cv::dilate(srcImage, dilateImage, hse);
//    cv::subtract(dilateImage, erodeImage, xDirectImg, cv::Mat());
//    cv::imshow("xDirectImg", xDirectImg);
//    //cv::imshow("dilateImage",dilateImage);
//    //cv::imshow("erodeImage",erodeImage);
//    //4.2 Y 方向梯度：膨胀与腐蚀之后得到图像求差值
//    cv::erode(srcImage, erodeImage, vse);
//    cv::dilate(srcImage, dilateImage, vse);
//    cv::subtract(dilateImage, erodeImage, yDirectImg, cv::Mat());
//    cv::imshow("yDirectImg", yDirectImg);
//
//
//    cv::resize(basicGradient,basicGradient,cv::Size(),0.5,0.5);
//    cv::cvtColor(basicGradient,basicGradient,cv::COLOR_GRAY2BGR);
//    cv::putText(basicGradient,"basicGradient",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//    cv::imwrite("basicGradient.jpg",basicGradient);
//
//    cv::resize(internalGradientImg,internalGradientImg,cv::Size(),0.5,0.5);
//    cv::cvtColor(internalGradientImg,internalGradientImg,cv::COLOR_GRAY2BGR);
//    cv::putText(internalGradientImg,"internalGradientImg",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//
//    cv::resize(externalGradientImg,externalGradientImg,cv::Size(),0.5,0.5);
//    cv::cvtColor(externalGradientImg,externalGradientImg,cv::COLOR_GRAY2BGR);
//    cv::putText(externalGradientImg,"externalGradientImg",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//    cv::hconcat(internalGradientImg,externalGradientImg,internalGradientImg);
//    cv::imwrite("internalGradientImg.jpg",internalGradientImg);
//
//    cv::resize(xDirectImg,xDirectImg,cv::Size(),0.5,0.5);
//    cv::cvtColor(xDirectImg,xDirectImg,cv::COLOR_GRAY2BGR);
//    cv::putText(xDirectImg,"xDirectImg",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//
//    cv::resize(yDirectImg,yDirectImg,cv::Size(),0.5,0.5);
//    cv::cvtColor(yDirectImg,yDirectImg,cv::COLOR_GRAY2BGR);
//    cv::putText(yDirectImg,"yDirectImg",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
//    cv::hconcat(xDirectImg,yDirectImg,xDirectImg);
//    cv::imwrite("xDirectImg.jpg",xDirectImg);
//
//    //===============形态学梯度 --end================================//

    //===============顶帽、黑帽变换 --start================================//
    //首先读入图像
    cv::Mat srcImage = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);
    //cv::threshold(srcImage,srcImage,125,255,cv::THRESH_BINARY);

    cv::imshow("srcImage",srcImage);

    //获取进行形态学操作的核
    cv::Mat elementRect;
    elementRect = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3),cv::Point(-1,-1));

    //顶帽、黑帽
    cv::Mat topHatImage;
    cv::morphologyEx(srcImage,topHatImage,cv::MORPH_TOPHAT,elementRect,cv::Point(-1,-1));
    cv::imshow("topHatImage",topHatImage);
    ////再进一步，既然已经可以提取这个图的背景，那么通过背景与二值化图像异或，即可提取前景。
    //cv::Mat bit_xor;
    //cv::threshold(srcImage,srcImage,125,255,cv::THRESH_BINARY);
    //bitwise_xor(srcImage, topHatImage, bit_xor);
    //imshow("异或", bit_xor);


    cv::Mat blackHatImage;
    cv::morphologyEx(srcImage,blackHatImage,cv::MORPH_TOPHAT,elementRect,cv::Point(-1,-1));
    cv::imshow("blackHatImage",blackHatImage);

    cv::cvtColor(topHatImage,topHatImage,cv::COLOR_GRAY2BGR);
    cv::putText(topHatImage,"topHatImage",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
    cv::resize(topHatImage,topHatImage,cv::Size(),0.5,0.5);

    cv::cvtColor(blackHatImage,blackHatImage,cv::COLOR_GRAY2BGR);
    cv::putText(blackHatImage,"blackHatImage",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
    cv::resize(blackHatImage,blackHatImage,cv::Size(),0.5,0.5);

    cv::hconcat(topHatImage,blackHatImage,topHatImage);
    cv::imwrite("topHatImage.jpg",topHatImage);

    cv::imwrite("srcImage.jpg",srcImage);

    //===============顶帽、黑帽变换 --end================================//
    cv::waitKey(0);
    return 0;
}

