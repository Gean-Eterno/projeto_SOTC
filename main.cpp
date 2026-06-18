#include <iostream>
#include <opencv2/opencv.hpp>
#include "Filtros.h"

using namespace std;
using namespace cv;

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
    cout << " [ESC] - Sair\n";
    cout << "=============================================\n";
}

int main() {
    Filtros filtros;
    //Caminho do video
    VideoCapture video("/home/gean/CLionProjects/TrabalhoFinal/VideoSOTC.mp4");

    if (!video.isOpened()) {
        cerr << "[FATAL] Falha ao abrir stream de vídeo." << endl;
        return -1;
    }

    double fpsOriginal = video.get(CAP_PROP_FPS);
    if (fpsOriginal <= 0) fpsOriginal = 30.0;

    double larguraOriginal = video.get(CAP_PROP_FRAME_WIDTH);
    double alturaOriginal = video.get(CAP_PROP_FRAME_HEIGHT);
    const int resolucaoHD = 1280;
    Size tamanhoDisplay(resolucaoHD, (int)(alturaOriginal * resolucaoHD / larguraOriginal));

    Mat frameOriginal, frameProc, frameFinal;
    namedWindow("SOTC Remaster Engine", WINDOW_NORMAL | WINDOW_KEEPRATIO);

    bool apRuido = false, apCores = false, apContraste = false, apNitidez = false;

    exibirMenu();

    int delay = 1000 / (fpsOriginal * 1.30);

    while (true) {
        video.read(frameOriginal);

        if (frameOriginal.empty()) {
            video.set(CAP_PROP_POS_FRAMES, 0);
            continue;
        }

        resize(frameOriginal, frameProc, tamanhoDisplay, 0, 0, INTER_LINEAR);

        if (apRuido) frameProc = filtros.removerRuido(frameProc);
        if (apCores) frameProc = filtros.coresVivas(frameProc);
        if (apContraste) frameProc = filtros.melhorarContraste(frameProc);
        if (apNitidez) frameProc = filtros.nitidez(frameProc);

        frameFinal = frameProc.clone();

        // HUD Inferior
        int hBar = 40;
        Mat hud = frameFinal(Rect(0, frameFinal.rows - hBar, frameFinal.cols, hBar));
        hud *= 0.25;

        string status = "STATUS: ";
        if (!apRuido && !apCores && !apContraste && !apNitidez) {
            status += "ORIGINAL";
            putText(frameFinal, status, Point(20, frameFinal.rows - 12), 0, 0.6, Scalar(150, 150, 150), 2);
        } else {
            if (apRuido) status += "[1] Ruido ";
            if (apCores) status += "[2] Cores ";
            if (apContraste) status += "[3] Contraste ";
            if (apNitidez) status += "[4] Nitidez ";
            putText(frameFinal, status, Point(20, frameFinal.rows - 12), 0, 0.6, Scalar(0, 255, 150), 2);
        }

        imshow("SOTC Remaster Engine", frameFinal);

        char key = (char)waitKey(delay);
        if (key == 27) break;
        else if (key == '1') apRuido = !apRuido;
        else if (key == '2') apCores = !apCores;
        else if (key == '3') apContraste = !apContraste;
        else if (key == '4') apNitidez = !apNitidez;
        else if (key == '5') apRuido = apCores = apContraste = apNitidez = true;
        else if (key == '0') apRuido = apCores = apContraste = apNitidez = false;
    }
    video.release();
    destroyAllWindows();
    return 0;
}