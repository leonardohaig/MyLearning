//====================================================================//
// Created by liheng on 19-3-6.
//Program:图像灰度直方图示例,及动态调整“竖条”数量，观察直方图效果
//Data:2019.3.6
//Author:liheng
//Version:V1.0
//====================================================================//

#include <opencv2/opencv.hpp>


cv::Mat src;//需要计算直方图的灰度图像
cv::Mat histimg;//进行直方图展示的图
cv::MatND hist;//计算得到的直方图结果

int histSize = 50;     // 划分HIST的初始个数，越高越精确

//滚动条函数
void HIST(int t,void*)
{
    char string[10];

    if(histSize==0)
    {
        printf("直方图条数不能为零！\n");
    }
    else
    {
        int dims = 1;
        float hranges[2] = {0, 255};
        const float *ranges[1] = {hranges};   // 这里需要为const类型
        int channels = 0;

        histimg.create(512,256*4,CV_8UC3);
        histimg.setTo(cv::Scalar(0,0,0));

        //计算图像的直方图
        calcHist(&src, 1, &channels, cv::Mat(), hist, dims, &histSize, ranges);    // cv 中是cvCalcHist
        //normalize(hist, hist, 0, histimg.rows*0.5, NORM_MINMAX, -1, Mat());//将直方图归一化，防止某一条过高，显示不全


        double maxVal = 0;
        cv::Point maxLoc;
        cv::minMaxLoc(hist, NULL, &maxVal, NULL, &maxLoc);//寻找最大值及其位置


        double bin_w =(double) histimg.cols / histSize;  // histSize: 条的个数，则 bin_w 为条的宽度
        double bin_u = (double)histimg.rows/ maxVal;  // maxVal: 最高条的像素个数，则 bin_u 为单个像素的高度

        // 画直方图
        for(int i=0;i<histSize;i++)
        {
            cv::Point p0=cv::Point(i*bin_w,histimg.rows);

            float binValue = hist.at<float>(i);           //   注意hist中是float类型
            cv::Point p1=cv::Point((i+1)*bin_w,histimg.rows-binValue*bin_u);

            cv::rectangle(histimg,p0,p1,cv::Scalar(0,255,0),2,8,0);
        }

        //曲线形式的直方图
        for (int i = 0; i < histSize; i++)
        {
            cv::line(histimg,
                    cv::Point(bin_w*i+bin_w/2, histimg.rows-hist.at<float>(i)*bin_u),
                    cv::Point(bin_w*(i+1)+bin_w/2, histimg.rows-hist.at<float>(i+1)*bin_u),
                    cv::Scalar(255, 0, 0), 2, 8, 0);//bin_w/2是为了保证折现位于直方图每条的中间位置
        }

        //画纵坐标刻度（像素个数）
        int kedu=0;
        for(int i=1;kedu<maxVal;i++)
        {
            kedu=i*maxVal/10;
            sprintf(string,"%d",kedu);//把一个整数转换为字符串
            //在图像中显示文本字符串
            cv::putText(histimg, string , cv::Point(0,histimg.rows-kedu*bin_u), cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,255,255),1);

            cv::line( histimg,cv::Point(0,histimg.rows-kedu*bin_u),cv::Point(histimg.cols-1,histimg.rows-kedu*bin_u),cv::Scalar(0,0,255));
        }
        //画横坐标刻度（像素灰度值）
        kedu=0;
        for(int i=1;kedu<256;i++)
        {
            kedu=i*20;
            sprintf(string,"%d",kedu);//把一个整数转换为字符串
            //在图像中显示文本字符串
            putText(histimg, string , cv::Point(kedu*(histimg.cols / 256),histimg.rows), cv::FONT_HERSHEY_SIMPLEX,0.5,cv::Scalar(0,255,255),2);
        }

        cv::imshow( "Histogram", histimg );
    }
}

int main( int argc, char** argv )
{

    src = cv::imread("../pictures/lena.jpg",0);

    cv::namedWindow( "src", 1);
    cv::imshow( "src", src);
    cv::namedWindow( "Histogram", 1 );

    int maxvalue = 256;
    cv::createTrackbar( "histSize", "src", &histSize, maxvalue, HIST );
    HIST(0,0);
    while( 1 )
    {
        char key = cv::waitKey(10);
        if( 27 == key )
            break;
    }



    cv::destroyWindow("src");
    cv::destroyWindow("Histogram");

    return 0;
}