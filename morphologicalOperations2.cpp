//====================================================================//
// Created by liheng on 19-2-19.
//====================================================================//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

char output[] = "Morphlogy_image";
Mat dst, src;
void Morphlogy_Operators(int, void*);
int element_size = 3;
int max_size = 21;
int main(int argc, char**argv)
{
    src = cv::imread("../pictures/000177.png",cv::IMREAD_GRAYSCALE);
    if (!src.data)
    {
        printf("could not load image...\n");
        return -1;
    }
    namedWindow("input image", cv::WINDOW_AUTOSIZE);
    imshow("input image", src);

    namedWindow(output, cv::WINDOW_AUTOSIZE);
    //轨迹条或滑动条（Trackbar）的控件工具
    createTrackbar("elementSIZE:", output, &element_size, max_size, Morphlogy_Operators);
    //参数一、trackbarname：滑动空间的名称；参数二、winname：滑动空间用于依附的图像窗口的名称；数三、value：初始化阈值；参数四、count：滑动控件的刻度范围；参数五、TrackbarCallback是回调函数
    Morphlogy_Operators(0, 0);

    waitKey(0);
    return 0;
}
//各种形态学操作
void Morphlogy_Operators(int, void*)
{
    int s = element_size + 1;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
    //结构元素的定义：形状 (MORPH_RECT \MORPH_CROSS（交叉形） \MORPH_ELLIPSE)；结构元素大小；锚点 默认是Point(-1, -1)意思就是中心像素


    //膨胀
    //dilate(src,dst,kernel);

    //腐蚀
    //erode(src, dst, kernel);

    //形态学操作（开、闭、形态学梯度、顶帽、黑帽）
    morphologyEx(src, dst, MORPH_BLACKHAT, kernel);
    //第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可。图像位深应该为以下五种之一：CV_8U, CV_16U,CV_16S, CV_32F 或CV_64F。
    //第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
    //第三个参数，int类型的op，表示形态学运算的类型，可以是如下之一的标识符：
    //MORPH_OPEN – 开运算（Opening operation）：先腐蚀后膨胀，去掉小对象
    //MORPH_CLOSE – 闭运算（Closing operation）：先膨胀后腐蚀，可以填充一些小的空洞（fill hole）
    //MORPH_GRADIENT - 形态学梯度（Morphological gradient）：膨胀后的图减去腐蚀后的图(设置恰当的参数可以得到目标的大致边缘)
    //MORPH_TOPHAT - “顶帽”（“Top hat”）：原图像与开操作之间的差值图像(可以用来观察开运算除去了哪些小目标)
    //MORPH_BLACKHAT - “黑帽”（“Black hat“）：闭操作图像与源图像的差值图像（可以观察闭运算的效果）
    //第四个参数：结构元素即形态学运算的内核
    //第五个参数，Point类型的anchor，锚的位置，其有默认值（ - 1， - 1），表示锚位于中心。
    //第六个参数，int类型的iterations，迭代使用函数的次数，默认值为1。
    //第七个参数，int类型的borderType，用于推断图像外部像素的某种边界模式。注意它有默认值BORDER_ CONSTANT。
    //第八个参数，const Scalar&类型的borderValue，当边界为常数时的边界值，有默认值morphologyDefaultBorderValue()，一般我们不用去管他。需要用到它时，可以看官方文档

    imshow(output, dst);

    return;
}
