//====================================================================//
// Created by liheng on 19-3-12.
//Update Content:添加直方图规定化示例
//Data:2019.3.17
//Author:liheng
//Version:V2.0
//----------------------------------------------------------------------//
//Program:直方图均衡化Demo，演示采用自定义的函数实现均衡化和采用OpenCV函数实现均衡化
//Data:2019.3.12
//Author:liheng
//Version:V1.0
//====================================================================//

#include <opencv2/opencv.hpp>

//===================================================================//
//Histogram1D 计算一幅灰度图像的直方图，该类是对OpenCV的简单封装，参考网上资料
//Histogram1D提供了两个方法：
// getHistogram返回统计直方图的数组，默认计算的灰度范围是[0,255]；
// getHistogramImage将图像的直方图以线条的形式画出来，并返回包含直方图的图像
//应用示例：
//    Histogram1D hist;
//    Mat histImg;
//    histImg = hist.getHistogramImage(image);
//
//    imshow("Image", image);
//    imshow("Histogram", histImg);
//===================================================================//
class Histogram1D
{
private:
    int histSize[1]; // 项的数量
    float hranges[2]; // 统计像素的最大值和最小值
    const float* ranges[1];
    int channels[1]; // 仅计算一个通道

public:
    Histogram1D()
    {
        // 准备1D直方图的参数
        histSize[0] = 256;
        hranges[0] = 0.0f;
        hranges[1] = 255.0f;
        ranges[0] = hranges;
        channels[0] = 0;
    }

    cv::MatND getHistogram(const cv::Mat &image)
    {
        cv::MatND hist;
        // 计算直方图
        cv::calcHist(&image ,// 要计算图像的
                 1,                // 只计算一幅图像的直方图
                 channels,        // 通道数量
                 cv::Mat(),            // 不使用掩码
                 hist,            // 存放直方图
                 1,                // 1D直方图
                 histSize,        // 统计的灰度的个数
                 ranges);        // 灰度值的范围
        return hist;
    }

    cv::Mat getHistogramImage(const cv::Mat &image)
    {
        cv::MatND hist = getHistogram(image);

        // 最大值，最小值
        double maxVal = 0.0f;
        double minVal = 0.0f;

        cv::minMaxLoc(hist, &minVal, &maxVal);

        //显示直方图的图像
        cv::Mat histImg(histSize[0], histSize[0], CV_8UC1, cv::Scalar(255));

        // 设置最高点为nbins的90%
        int hpt = static_cast<int>(0.9 * histSize[0]);
        //每个条目绘制一条垂直线
        for (int h = 0; h < histSize[0]; h++)
        {
            float binVal = hist.at<float>(h);
            int intensity = static_cast<int>(binVal * hpt / maxVal);
            // 两点之间绘制一条直线
            cv::line(histImg, cv::Point(h, histSize[0]), cv::Point(h, histSize[0] - intensity), cv::Scalar::all(0),4);
        }
        return histImg;
    }
};


//===================================================================//
//自定义直方图均衡化函数，作用和equalizeHist()函数一致
//===================================================================//
void equalization_self(const cv::Mat &src, cv::Mat &dst)
{
    Histogram1D hist1D;
    cv::MatND hist = hist1D.getHistogram(src);

    hist /= (src.rows * src.cols); // 对得到的灰度直方图进行归一化
    float cdf[256] = { 0 }; // 灰度的累积概率
    cv::Mat lut(1, 256, CV_8U); // 灰度变换的查找表
    for (int i = 0; i < 256; i++)
    {
        // 计算灰度级的累积概率
        if (i == 0)
            cdf[i] = hist.at<float>(i);
        else
            cdf[i] = cdf[i - 1] + hist.at<float>(i);

        lut.at<uchar>(i) = static_cast<uchar>(255 * cdf[i]); // 创建灰度的查找表
    }

    cv::LUT(src, lut, dst); // 应用查找表，进行灰度变化，得到均衡化后的图像

}


//===================================================================//
//自定义直方图规定化函数
//===================================================================//
void hist_specify(const cv::Mat &src, const cv::Mat &dst,cv::Mat &result)
{
    Histogram1D hist1D;
    cv::MatND src_hist = hist1D.getHistogram(src);
    cv::MatND dst_hist = hist1D.getHistogram(dst);

    float src_cdf[256] = { 0 };
    float dst_cdf[256] = { 0 };

    // 源图像和目标图像的大小不一样，要将得到的直方图进行归一化处理
    src_hist /= (src.rows * src.cols);
    dst_hist /= (dst.rows * dst.cols);

    // 计算原始直方图和规定直方图的累积概率
    for (int i = 0; i < 256; i++)
    {
        if (i == 0)
        {
            src_cdf[i] = src_hist.at<float>(i);
            dst_cdf[i] = dst_hist.at<float>(i);
        }
        else
        {
            src_cdf[i] = src_cdf[i - 1] + src_hist.at<float>(i);
            dst_cdf[i] = dst_cdf[i - 1] + dst_hist.at<float>(i);
        }
    }

    // 累积概率的差值
    float diff_cdf[256][256];
    for (int i = 0; i < 256; i++)
        for (int j = 0; j < 256; j++)
            diff_cdf[i][j] = fabs(src_cdf[i] - dst_cdf[j]);

    // 构建灰度级映射表
    cv::Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; i++)
    {
        // 查找源灰度级为ｉ的映射灰度
        //　和ｉ的累积概率差值最小的规定化灰度
        float min = diff_cdf[i][0];
        int index = 0;
        for (int j = 1; j < 256; j++)
        {
            if (min > diff_cdf[i][j])
            {
                min = diff_cdf[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = static_cast<uchar>(index);
    }

    // 应用查找表，做直方图规定化
    LUT(src, lut, result);
}

int main()
{
    /*
     * 直方图均衡化示例
    //cv::Mat src = cv::imread("../pictures/lena.jpg",0);
    cv::Mat src = cv::imread("../pictures/000177.png",0);

    cv::Mat dst_equalize,dst_self;


    cv::equalizeHist(src,dst_equalize);

    equalization_self(src,dst_self);


    cv::imshow("srcImage",src);


    Histogram1D hist;
    cv::Mat histImg = hist.getHistogramImage(src);

    cv::Mat histImg_self = hist.getHistogramImage(dst_equalize);


    cv::imshow("srcHistogram", histImg);
    cv::imshow("dstHistogram", histImg_self);





    cv::cvtColor(dst_equalize,dst_equalize,cv::COLOR_GRAY2BGR);
    cv::cvtColor(dst_self,dst_self,cv::COLOR_GRAY2BGR);

    cv::putText(dst_equalize,"opencv_equalize",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);
    cv::putText(dst_self,"dst_self",cv::Point(0,30),cv::FONT_HERSHEY_SIMPLEX,1.2,cv::Scalar(0,255,0),2);

    cv::hconcat(dst_equalize,dst_self,dst_equalize);
    cv::resize(dst_equalize,dst_equalize,cv::Size(),0.5,0.5);
    cv::imshow("dst",dst_equalize);

    cv::waitKey(0);


    */

    cv::Mat src = cv::imread("../pictures/lena.jpg",0);
    cv::Mat dst_hist = cv::imread("../pictures/000177.png",0);
    cv::Mat dst;
    hist_specify(src,dst_hist,dst);


    Histogram1D hist;
    cv::Mat srchistImg = hist.getHistogramImage(src);
    cv::Mat dsthistImg = hist.getHistogramImage(dst_hist);
    cv::Mat src_dsthistImg = hist.getHistogramImage(dst);


    cv::imshow("src",src);
    cv::imshow("dst",dst);
    cv::imshow("srchistImg",srchistImg);
    cv::imshow("dsthistImg",dsthistImg);
    cv::imshow("src_dsthistImg",src_dsthistImg);

    cv::waitKey(0);



    return 0;
}