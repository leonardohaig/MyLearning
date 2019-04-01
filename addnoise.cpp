//====================================================================//
// Created by liheng on 19-4-1.
//Program:给图像添加椒盐噪声以及高斯噪声
//Data:2019.4.1
//Author:liheng
//Version:V1.0
//====================================================================//

#include <opencv2/opencv.hpp>
#include <random>
#include <iostream>

// 添加椒盐噪声
//输入参数：m--需要添加椒盐噪声的图像.CV_8UC1或者CV_8UC3类型
//        SNR--信噪比，信号数据/噪声点 的比例0-1之间
//输出参数：m--添加椒盐噪声的图像
//返回值：无
void addSaltNoise(cv::Mat &m, float SNR);
// 添加Gaussian噪声
//输入参数：m--需要添加高斯噪声的图像.CV_8UC1或者CV_8UC3类型
//        mu--高斯噪声均值
//        sigma--高斯噪声方差
//输出参数：m--添加高斯噪声后图像
//返回值：无
void addGaussianNoise(cv::Mat &m, int mu, int sigma);


int main()
{
    cv::Mat src = cv::imread("../pictures/lena.jpg");

//    //信噪比比0,0.3,0.7,1的图像
//    cv::Mat dst0 = src.clone();
//    cv::Mat dst03 = src.clone();
//    cv::Mat dst07 = src.clone();
//    cv::Mat dst1 = src.clone();
//
//    addSaltNoise(dst0,0);
//    cv::putText(dst0,"SNR:0",cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.8,cv::Scalar(0,255,0),2);
//
//    addSaltNoise(dst03,0.3);
//    cv::putText(dst03,"SNR:0.3",cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.8,cv::Scalar(0,255,0),2);
//
//    addSaltNoise(dst07,0.7);
//    cv::putText(dst07,"SNR:0.7",cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.8,cv::Scalar(0,255,0),2);
//
//    addSaltNoise(dst1,1);
//    cv::putText(dst1,"SNR:1",cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.8,cv::Scalar(0,255,0),2);
//
//
//    cv::hconcat(dst0,dst03,dst0);
//    cv::hconcat(dst07,dst1,dst07);
//    cv::vconcat(dst0,dst07,dst0);
//
//    cv::imshow("src",src);
//    cv::imshow("saltNoist",dst0);
//
//    cv::imwrite("saltNoist.jpg",dst0);
//
//    cv::waitKey(0);


    cv::Mat dst = src.clone();
    addGaussianNoise(dst,64,40);

    cv::Mat diff = dst - src;


    cv::imshow("src",src);

    cv::putText(dst,"dst",cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.8,cv::Scalar(0,255,0),2);
    cv::imshow("dst",dst);

    cv::putText(diff,"diff",cv::Point(0,20),cv::FONT_HERSHEY_SIMPLEX,0.8,cv::Scalar(0,255,0),2);
    cv::imshow("diff",diff);

    cv::hconcat(dst,diff,dst);
    cv::imshow("dd",dst);

    cv::imwrite("dst.jpg",dst);
    cv::waitKey(0);


    return 0;
}


void addSaltNoise(cv::Mat &m, float SNR)
{
    assert( (CV_8UC1 == m.type() || CV_8UC3 == m.type()) );
    assert( (SNR>=0-FLT_EPSILON && SNR<=1+FLT_EPSILON) );

    // 随机数产生器
    std::random_device rd; //种子
    std::mt19937 gen(rd()); // 随机数引擎

    auto cols = m.cols;
    auto rows = m.rows;
    auto nChannel = m.channels();

    int NP = cols*rows*(1-SNR);

    //盐噪声
    for (int i = 0; i < NP; i++)
    {
        auto row = static_cast<int>(gen() % rows);
        auto col = static_cast<int>(gen() % cols);

        auto p = m.ptr<uchar>(row);

        int noiseVale = 0;
        if( gen()%2 )
            noiseVale = 0;//椒噪声
        else
            noiseVale = 255;//盐噪声

        if( nChannel == 1)
        {
            p[col] = noiseVale;
        }
        else if( nChannel == 3 )
        {
            p[3*col] = noiseVale;
            p[3*col+1] = noiseVale;
            p[3*col+2] = noiseVale;
        }
    }
}

void addGaussianNoise(cv::Mat &m, int mu, int sigma)
{
    // 产生高斯分布随机数发生器
    std::random_device rd;
    std::mt19937 gen(rd());

    std::normal_distribution<> d(mu, sigma);
    //std::normal_distribution<> d(mu, 0.8);

    auto rows = m.rows; // 行数
    auto cols = m.cols * m.channels(); // 列数

    for (int i = 0; i < rows; i++)
    {
        auto p = m.ptr<uchar>(i); // 取得行首指针
        for (int j = 0; j < cols; j++)
        {
            //随机产生符合高斯分布的随机数，然后将该值和图像原有的像素值相加，并将得到的和压缩到[0,255]区间内
            auto tmp = p[j] + d(gen);
            tmp = tmp > 255 ? 255 : tmp;
            tmp = tmp < 0 ? 0 : tmp;
            p[j] = tmp;
        }
    }
}