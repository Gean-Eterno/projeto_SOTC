#ifndef FILTROS_H
#define FILTROS_H

#include <opencv2/opencv.hpp>

using namespace cv;

class Filtros {
public:
    Mat removerRuido(const Mat& frame);
    Mat coresVivas(const Mat& frame);
    Mat melhorarContraste(const Mat& frame);
    Mat nitidez(const Mat& frame);
};

#endif // FILTROS_H