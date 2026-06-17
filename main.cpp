#include <iostream>
#include <opencv2/opencv.hpp>
#include "Filtros.h"

using namespace std;
using namespace cv;

int main() {
    Filtros filtros;

    // Caminho do arquivo de vídeo configurado para o Gean
    VideoCapture video("/home/gean/CLionProjects/TrabalhoFinal/VideoSOTC.mp4");

    if (!video.isOpened()) {
        cerr << "Erro ao abrir o arquivo de vídeo!" << endl;
        return -1;
    }

    double fps = video.get(CAP_PROP_FPS);
    if (fps <= 0) fps = 30.0;

    // Constantes do pipeline (resolução de processamento alta)
    const int larguraProc = 960;
    const int larguraExibicao = 1920; // Variável corrigida!

    Mat frameOriginal, frameBase, frameProc, frameLado, frameFinal;

    namedWindow("SOTC Remaster", WINDOW_NORMAL | WINDOW_KEEPRATIO);

    // Loop de processamento
    while (true) {
        video.read(frameOriginal);
        if (frameOriginal.empty()) break;

        // Redimensiona o frame para processamento leve
        resize(frameOriginal, frameBase, Size(larguraProc, (int)(frameOriginal.rows * (double)larguraProc / frameOriginal.cols)));

        // Aplica o pipeline de filtros
        frameProc = filtros.removerRuido(frameBase);
        frameProc = filtros.coresVivas(frameProc);
        frameProc = filtros.melhorarContraste(frameProc);
        frameProc = filtros.nitidez(frameProc);

        // Junta as imagens lado a lado
        hconcat(frameBase, frameProc, frameLado);

        // Escala para a tela final e desenha os textos
        resize(frameLado, frameFinal, Size(larguraExibicao, (int)(frameLado.rows * (double)larguraExibicao / frameLado.cols)));

        putText(frameFinal, "ANTES", Point(30, 50), FONT_HERSHEY_SIMPLEX, 1.2, Scalar(255, 255, 255), 2);
        putText(frameFinal, "DEPOIS", Point((larguraExibicao / 2) + 30, 50), FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 255, 0), 2);

        imshow("SOTC Remaster", frameFinal);

        // WaitKey controla a velocidade, considerando a aceleração de 30% (1.30)
        if (waitKey(1000 / (fps * 1.30)) == 27) break;
    }

    video.release();
    destroyAllWindows();
    return 0;
}