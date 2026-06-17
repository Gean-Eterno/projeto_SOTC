#include "Filtros.h"
#include <vector>

Mat Filtros::nitidez(const Mat& frame) {
    Mat blur, resultado;
    // Implementação de máscara de nitidez (Unsharp Masking)
    GaussianBlur(frame, blur, Size(0, 0), 1.5);
    addWeighted(frame, 1.8, blur, -0.8, 0, resultado);
    return resultado;
}

Mat Filtros::coresVivas(const Mat& frame) {
    Mat lab, resultado;
    // Converter para espaço de cor Lab para manipular saturação sem estourar luz
    cvtColor(frame, lab, COLOR_BGR2Lab);

    std::vector<Mat> canais;
    split(lab, canais);

    // Converte para float para manipular os canais de cor (a e b)
    canais[1].convertTo(canais[1], CV_32F);
    canais[2].convertTo(canais[2], CV_32F);

    // Amplifica a saturação afastando as cores do cinza neutro (128)
    canais[1] = (canais[1] - 128.0f) * 1.40f + 128.0f;
    canais[2] = (canais[2] - 128.0f) * 1.40f + 128.0f;

    // Volta para formato de 8 bits
    canais[1].convertTo(canais[1], CV_8U);
    canais[2].convertTo(canais[2], CV_8U);

    merge(canais, lab);
    cvtColor(lab, resultado, COLOR_Lab2BGR);
    return resultado;
}

Mat Filtros::melhorarContraste(const Mat& frame) {
    Mat lab, resultado;
    cvtColor(frame, lab, COLOR_BGR2Lab);

    std::vector<Mat> canais;
    split(lab, canais);

    // CLAHE: Realce de contraste local para recuperar detalhes em sombras
    Ptr<CLAHE> clahe = createCLAHE(2.0, Size(8, 8));
    clahe->apply(canais[0], canais[0]);

    // Supressão de altas luzes no canal L para não estourar o céu
    canais[0].convertTo(canais[0], -1, 0.93, -12);

    merge(canais, lab);
    cvtColor(lab, resultado, COLOR_Lab2BGR);

    return resultado;
}

Mat Filtros::removerRuido(const Mat& frame) {
    Mat resultado;
    // Filtro Gaussiano leve para manter o desempenho em tempo real
    GaussianBlur(frame, resultado, Size(3, 3), 0);
    return resultado;
}   