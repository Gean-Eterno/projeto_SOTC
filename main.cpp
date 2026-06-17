#include <iostream>
#include <opencv2/opencv.hpp>
#include "Filtros.h"

using namespace std;
using namespace cv;

// Função para imprimir o menu no terminal do Debian
void exibirMenu() {
    cout << "\n=============================================\n";
    cout << "      MENU DE INTERACAO - SOTC REMASTER      \n";
    cout << "=============================================\n";
    cout << "Controles durante a exibicao do video:\n";
    cout << " [1] - Ativar/Desativar: Remocao de Ruido\n";
    cout << " [2] - Ativar/Desativar: Cores Vivas\n";
    cout << " [3] - Ativar/Desativar: Melhorar Contraste\n";
    cout << " [4] - Ativar/Desativar: Nitidez\n";
    cout << " [5] - Ligar TODOS os filtros (HD Completo)\n";
    cout << " [0] - Desligar TODOS os filtros\n";
    cout << " [ESC] - Encerrar o programa adequadamente\n";
    cout << "=============================================\n";
}

int main() {
    Filtros filtros;

    // Caminho do arquivo de vídeo
    VideoCapture video("/home/gean/CLionProjects/TrabalhoFinal/VideoSOTC.mp4");

    if (!video.isOpened()) {
        cerr << "Erro ao abrir o arquivo de vídeo!" << endl;
        return -1;
    }

    double fps = video.get(CAP_PROP_FPS);
    if (fps <= 0) fps = 30.0;

    const int larguraProc = 960;
    // Largura de exibição para uma única tela (HD limpo e nítido)
    const int larguraExibicao = 1280;

    // Removemos o frameLado, pois não vamos mais juntar as imagens
    Mat frameOriginal, frameBase, frameProc, frameFinal;

    namedWindow("SOTC Remaster", WINDOW_NORMAL | WINDOW_KEEPRATIO);

    // VARIAVEIS DO MENU: Começam todas desligadas (false)
    bool aplicarRuido = false;
    bool aplicarCores = false;
    bool aplicarContraste = false;
    bool aplicarNitidez = false;

    // Mostra o menu no terminal antes de abrir a janela
    exibirMenu();

    while (true) {
        video.read(frameOriginal);

        // Se o video acabar, ele reinicia automaticamente
        if (frameOriginal.empty()) {
            video.set(CAP_PROP_POS_FRAMES, 0);
            continue;
        }

        resize(frameOriginal, frameBase, Size(larguraProc, (int)(frameOriginal.rows * (double)larguraProc / frameOriginal.cols)));

        // A imagem processada começa exatamente igual à original
        frameProc = frameBase.clone();

        // O SISTEMA DE ESCOLHA
        if (aplicarRuido) frameProc = filtros.removerRuido(frameProc);
        if (aplicarCores) frameProc = filtros.coresVivas(frameProc);
        if (aplicarContraste) frameProc = filtros.melhorarContraste(frameProc);
        if (aplicarNitidez) frameProc = filtros.nitidez(frameProc);

        // Agora redimensionamos direto o frame processado para a tela final (sem juntar lado a lado)
        resize(frameProc, frameFinal, Size(larguraExibicao, (int)(frameProc.rows * (double)larguraExibicao / frameProc.cols)));

        // Status dos filtros na tela
        string statusFiltros = "Filtros Ativos: ";
        if (!aplicarRuido && !aplicarCores && !aplicarContraste && !aplicarNitidez) statusFiltros += "NENHUM (Video Original)";
        if (aplicarRuido) statusFiltros += "Ruido | ";
        if (aplicarCores) statusFiltros += "Cores | ";
        if (aplicarContraste) statusFiltros += "Contraste | ";
        if (aplicarNitidez) statusFiltros += "Nitidez";

        // Coloquei o texto no canto superior esquerdo pra ficar elegante
        putText(frameFinal, statusFiltros, Point(20, 40), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2);

        imshow("SOTC Remaster", frameFinal);

        // MENU INTERATIVO: Captura qual tecla o usuário apertou
        char tecla = (char)waitKey(1000 / (fps * 1.30));

        if (tecla == 27) { // ESC
            cout << "Encerrando o programa de forma adequada..." << endl;
            break;
        }
        else if (tecla == '1') aplicarRuido = !aplicarRuido;
        else if (tecla == '2') aplicarCores = !aplicarCores;
        else if (tecla == '3') aplicarContraste = !aplicarContraste;
        else if (tecla == '4') aplicarNitidez = !aplicarNitidez;
        else if (tecla == '5') aplicarRuido = aplicarCores = aplicarContraste = aplicarNitidez = true;
        else if (tecla == '0') aplicarRuido = aplicarCores = aplicarContraste = aplicarNitidez = false;
    }

    video.release();
    destroyAllWindows();
    return 0;
}