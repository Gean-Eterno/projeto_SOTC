#include "Filtros.h"
#include <vector>

// Remove ruído do frame em duas etapas:
// Primeiro a mediana elimina pixels isolados fora do padrão (sal e pimenta),
// depois o Gaussiano suaviza o que sobrou sem borrar demais
Mat Filtros::removerRuido(const Mat& frame) {
    Mat resultado;
    medianBlur(frame, resultado, 3);                    // Elimina ruído pontual
    GaussianBlur(resultado, resultado, Size(3, 3), 0);  // Suaviza o restante
    return resultado;
}

// Deixa as cores mais vivas aumentando a saturação no espaço HSV
// HSV separa cor (H), intensidade (S) e brilho (V), o que facilita mexer só na saturação
Mat Filtros::coresVivas(const Mat& frame) {
    Mat hsv, resultado;
    cvtColor(frame, hsv, COLOR_BGR2HSV); // Converte BGR → HSV

    std::vector<Mat> canais;
    split(hsv, canais); // Separa os 3 canais: H, S, V

    // Aumenta o canal S (saturação) em 50%
    canais[1].convertTo(canais[1], CV_32F);  // Converte para float para não perder precisão
    canais[1] *= 1.50f;                       // Multiplica saturação por 1.5
    threshold(canais[1], canais[1], 255, 255, THRESH_TRUNC); // Corta valores acima de 255
    canais[1].convertTo(canais[1], CV_8U);   // Volta para inteiro de 8 bits

    merge(canais, hsv);                       // Junta os canais de volta
    cvtColor(hsv, resultado, COLOR_HSV2BGR);  // Converte HSV → BGR
    return resultado;
}

// Aumenta contraste com uma fórmula simples: pixel_novo = pixel * alpha + beta
// Alpha > 1 aumenta contraste, beta negativo escurece um pouco as sombras
Mat Filtros::melhorarContraste(const Mat& frame) {
    Mat resultado;
    frame.convertTo(resultado, -1, 1.20, -15); // alpha=1.20, beta=-15
    return resultado;
}

// Aplica Unsharp Masking: subtrai uma versão borrada do frame original
// O que sobra são as bordas e detalhes, que ficam mais evidentes
Mat Filtros::nitidez(const Mat& frame) {
    Mat blur, resultado;
    GaussianBlur(frame, blur, Size(0, 0), 2.0);       // Cria versão borrada
    addWeighted(frame, 2.2, blur, -1.2, 0, resultado); // original*2.2 - blur*1.2
    return resultado;
}