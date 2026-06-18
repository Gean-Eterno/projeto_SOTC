#include "Filtros.h"
#include <vector>

// Remove ruído usando filtro de mediana para artefatos e Gaussiano para suavização
Mat Filtros::removerRuido(const Mat& frame) {
    Mat resultado;
    medianBlur(frame, resultado, 3);
    GaussianBlur(resultado, resultado, Size(3, 3), 0);
    return resultado;
}

// Expansão de saturação via espaço HSV
Mat Filtros::coresVivas(const Mat& frame) {
    Mat hsv, resultado;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    std::vector<Mat> canais;
    split(hsv, canais);

    canais[1].convertTo(canais[1], CV_32F);
    canais[1] *= 1.50f;
    threshold(canais[1], canais[1], 255, 255, THRESH_TRUNC);
    canais[1].convertTo(canais[1], CV_8U);

    merge(canais, hsv);
    cvtColor(hsv, resultado, COLOR_HSV2BGR);
    return resultado;
}

// Ajuste de contraste via transformação linear (Alpha/Beta)
Mat Filtros::melhorarContraste(const Mat& frame) {
    Mat resultado;
    frame.convertTo(resultado, -1, 1.20, -15);
    return resultado;
}

// Realce de detalhes via Unsharp Masking
Mat Filtros::nitidez(const Mat& frame) {
    Mat blur, resultado;
    GaussianBlur(frame, blur, Size(0, 0), 2.0);
    addWeighted(frame, 2.2, blur, -1.2, 0, resultado);
    return resultado;
}