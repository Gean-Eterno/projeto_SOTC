#include <iostream>
#include <opencv2/opencv.hpp>
#include "Filtros.h"

using namespace std;
using namespace cv;

// Imprime o menu de opções no terminal
void exibirMenu() {
    cout << "\n=============================================\n";
    cout << "      ENGINE DE REMASTERIZACAO - SOTC        \n";
    cout << "=============================================\n";
    cout << " [1] - Ruído \n";
    cout << " [2] - Cores  \n";
    cout << " [3] - Contraste\n";
    cout << " [4] - Nitidez\n";
    cout << " [5] - ATIVAR TUDO \n";
    cout << " [0] - DESLIGAR TUDO  \n";
    cout << " [S] - Salvar Imagem\n";
    cout << " [ESC] - Sair\n";
    cout << "=============================================\n";
}

int main() {
    Filtros filtros;

    // Abre o arquivo de vídeo
    VideoCapture video("/home/gean/CLionProjects/TrabalhoFinal/VideoSOTC.mp4");

    if (!video.isOpened()) {
        cerr << "[FATAL] Falha ao abrir stream de vídeo." << endl;
        return -1;
    }

    // Pega o FPS original do vídeo (usa 30 como fallback se não detectar)
    double fpsOriginal = video.get(CAP_PROP_FPS);
    if (fpsOriginal <= 0) fpsOriginal = 30.0;

    // Calcula o tamanho do display mantendo a proporção em 1280px de largura
    double larguraOriginal = video.get(CAP_PROP_FRAME_WIDTH);
    double alturaOriginal  = video.get(CAP_PROP_FRAME_HEIGHT);
    const int resolucaoHD  = 1280;
    Size tamanhoDisplay(resolucaoHD, (int)(alturaOriginal * resolucaoHD / larguraOriginal));

    Mat frameOriginal, frameProc, frameFinal;
    namedWindow("SOTC Remaster Engine", WINDOW_NORMAL | WINDOW_KEEPRATIO);

    // Flags que controlam quais filtros estão ativos
    bool apRuido = false, apCores = false, apContraste = false, apNitidez = false;

    exibirMenu();

    // Calcula o delay entre frames (levemente acelerado em 1.3x)
    int delay = 1000 / (fpsOriginal * 1.30);

    while (true) {
        video.read(frameOriginal);

        // Se acabou o vídeo, reinicia do começo
        if (frameOriginal.empty()) {
            video.set(CAP_PROP_POS_FRAMES, 0);
            continue;
        }

        // Redimensiona para HD mantendo proporção
        resize(frameOriginal, frameProc, tamanhoDisplay, 0, 0, INTER_LINEAR);

        // Aplica apenas os filtros que estão ligados
        if (apRuido)    frameProc = filtros.removerRuido(frameProc);
        if (apCores)    frameProc = filtros.coresVivas(frameProc);
        if (apContraste) frameProc = filtros.melhorarContraste(frameProc);
        if (apNitidez)  frameProc = filtros.nitidez(frameProc);

        frameFinal = frameProc.clone();

        // Desenha o HUD na parte inferior: uma barra escurecida com o status
        int hBar = 40;
        Mat hud = frameFinal(Rect(0, frameFinal.rows - hBar, frameFinal.cols, hBar));
        hud *= 0.25; // Escurece a região da barra

        // Monta o texto de status com os filtros ativos
        string status = "STATUS: ";
        if (!apRuido && !apCores && !apContraste && !apNitidez) {
            status += "ORIGINAL";
            putText(frameFinal, status, Point(20, frameFinal.rows - 12),
                    0, 0.6, Scalar(150, 150, 150), 2); // Cinza = sem filtro
        } else {
            if (apRuido)     status += "[1] Ruido ";
            if (apCores)     status += "[2] Cores ";
            if (apContraste) status += "[3] Contraste ";
            if (apNitidez)   status += "[4] Nitidez ";
            putText(frameFinal, status, Point(20, frameFinal.rows - 12),
                    0, 0.6, Scalar(0, 255, 150), 2); // Verde = filtro ativo
        }

        imshow("SOTC Remaster Engine", frameFinal);

        // Lê o teclado e alterna os filtros
        char key = (char)waitKey(delay);
        if      (key == 27)           break;                                         // ESC → sai
        else if (key == '1')          apRuido    = !apRuido;
        else if (key == '2')          apCores    = !apCores;
        else if (key == '3')          apContraste = !apContraste;
        else if (key == '4')          apNitidez  = !apNitidez;
        else if (key == '5')          apRuido = apCores = apContraste = apNitidez = true;  // Liga tudo
        else if (key == '0')          apRuido = apCores = apContraste = apNitidez = false; // Desliga tudo
        else if (key == 's' || key == 'S') {
            imwrite("resultado_processado.jpg", frameFinal);
            cout << "[SISTEMA] Imagem capturada e salva como resultado_processado.jpg" << endl;
        }
    }

    video.release();
    destroyAllWindows();
    return 0;
}