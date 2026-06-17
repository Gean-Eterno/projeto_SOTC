#include <iostream>
#include <opencv2/opencv.hpp>
#include "Filtros.h"

using namespace std;
using namespace cv;

// Função simples para imprimir o menu no terminal
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
    const int larguraExibicao = 1920;

    Mat frameOriginal, frameBase, frameProc, frameLado, frameFinal;

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

        // Se o video acabar, ele reinicia automaticamente pra você ter tempo de testar o menu
        if (frameOriginal.empty()) {
            video.set(CAP_PROP_POS_FRAMES, 0);
            continue;
        }

        resize(frameOriginal, frameBase, Size(larguraProc, (int)(frameOriginal.rows * (double)larguraProc / frameOriginal.cols)));

        // A imagem processada começa exatamente igual à original
        frameProc = frameBase.clone();

        // O SISTEMA DE ESCOLHA: Só aplica o filtro se a variável correspondente for verdadeira
        if (aplicarRuido) frameProc = filtros.removerRuido(frameProc);
        if (aplicarCores) frameProc = filtros.coresVivas(frameProc);
        if (aplicarContraste) frameProc = filtros.melhorarContraste(frameProc);
        if (aplicarNitidez) frameProc = filtros.nitidez(frameProc);

        hconcat(frameBase, frameProc, frameLado);

        resize(frameLado, frameFinal, Size(larguraExibicao, (int)(frameLado.rows * (double)larguraExibicao / frameLado.cols)));

        putText(frameFinal, "ORIGINAL", Point(30, 50), FONT_HERSHEY_SIMPLEX, 1.2, Scalar(255, 255, 255), 2);
        putText(frameFinal, "PROCESSADO", Point((larguraExibicao / 2) + 30, 50), FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0, 255, 0), 2);

        // Feedback visual na tela para o professor ver quais filtros você escolheu
        string statusFiltros = "Filtros Ativos: ";
        if (!aplicarRuido && !aplicarCores && !aplicarContraste && !aplicarNitidez) statusFiltros += "NENHUM";
        if (aplicarRuido) statusFiltros += "Ruido | ";
        if (aplicarCores) statusFiltros += "Cores | ";
        if (aplicarContraste) statusFiltros += "Contraste | ";
        if (aplicarNitidez) statusFiltros += "Nitidez";

        putText(frameFinal, statusFiltros, Point((larguraExibicao / 2) + 30, 100), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 255, 255), 2);

        imshow("SOTC Remaster", frameFinal);

        // MENU INTERATIVO: Captura qual tecla o usuário apertou
        char tecla = (char)waitKey(1000 / (fps * 1.30));

        // Encerra o programa de forma adequada
        if (tecla == 27) { // 27 é o código da tecla ESC
            cout << "Encerrando o programa de forma adequada..." << endl;
            break;
        }
        // Alterna os filtros (se tava ligado, desliga; se tava desligado, liga)
        else if (tecla == '1') aplicarRuido = !aplicarRuido;
        else if (tecla == '2') aplicarCores = !aplicarCores;
        else if (tecla == '3') aplicarContraste = !aplicarContraste;
        else if (tecla == '4') aplicarNitidez = !aplicarNitidez;

        // Atalhos rapidos
        else if (tecla == '5') aplicarRuido = aplicarCores = aplicarContraste = aplicarNitidez = true;
        else if (tecla == '0') aplicarRuido = aplicarCores = aplicarContraste = aplicarNitidez = false;
    }

    video.release();
    destroyAllWindows();
    return 0;
}