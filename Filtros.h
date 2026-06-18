#ifndef FILTROS_H
#define FILTROS_H

#include <opencv2/opencv.hpp>

using namespace cv;

// Classe que agrupa os 4 filtros de imagem disponíveis
class Filtros {
public:
    Mat removerRuido(const Mat& frame);    // Suaviza artefatos visuais
    Mat coresVivas(const Mat& frame);      // Aumenta a saturação das cores
    Mat melhorarContraste(const Mat& frame); // Ajusta brilho e contraste
    Mat nitidez(const Mat& frame);         // Realça bordas e detalhes
};

#endif // FILTROS_H