# 🎮 SOTC Remaster Engine

Este é um projeto acadêmico de Processamento Digital de Imagens (PDI) desenvolvido em **C++** utilizando a biblioteca **OpenCV**. O objetivo do software é simular uma *Engine* de remasterização em tempo real, aplicando algoritmos de aprimoramento visual a um vídeo de gameplay clássico (*Shadow of the Colossus*).

## 🚀 Funcionalidades e Pipeline de Filtros

O sistema processa o vídeo frame a frame e permite a ativação condicional de 4 filtros matemáticos avançados:

* **[1] Redução de Ruído:** Utiliza Filtro de Mediana aliado à Suavização Gaussiana para derreter granulações e artefatos de compressão, sem prejudicar a estrutura do cenário.
* **[2] Expansão de Cores:** Atua de forma isolada no espaço de cor **HSV** (canal de Saturação), aplicando ganhos com *clipping* de segurança para evitar estourar a imagem.
* **[3] Contraste Cinemático:** Utiliza transformação linear (Alpha e Beta) para correção de brilho, aprofundando os tons escuros (remoção de névoa) e expandindo o alcance dinâmico (luzes).
* **[4] Nitidez (Unsharp Masking):** Isola e amplifica as altas frequências da imagem original para gerar micro-contraste nas bordas, aprimorando texturas de pedras e folhagens.

O projeto conta também com um **HUD (On-Screen Display)** que exibe o status dos filtros ativos e uma telemetria de desempenho em tempo real (**FPS** e **Latência em ms**).

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (Standard 14+)
* **Visão Computacional:** OpenCV 4.x
* **Build System:** CMake

## 💻 Como Compilar e Executar

Certifique-se de ter o compilador C++, CMake e a biblioteca OpenCV instalados e configurados no seu ambiente Linux.

**1. Clone o repositório:**
    git clone https://github.com/seu-usuario/seu-repositorio.git
    cd seu-repositorio

**2. Compile o projeto:**
Você pode abrir a pasta diretamente na sua IDE (como o CLion) ou compilar via terminal:
    mkdir build
    cd build
    cmake ..
    make

**3. Configuração do Vídeo:**
Certifique-se de que o arquivo `VideoSOTC.mp4` está no caminho correto configurado no arquivo `main.cpp` antes da execução.

**4. Execute a Engine:**
    ./TrabalhoFinal

## ⌨️ Controles em Tempo Real

Com a janela de vídeo em foco, utilize as seguintes teclas para interagir com a Engine:

| Tecla | Ação |
| :---: | :--- |
| `1` | Ativa/Desativa Filtro de Ruído |
| `2` | Ativa/Desativa Expansão de Cores |
| `3` | Ativa/Desativa Contraste Cinemático |
| `4` | Ativa/Desativa Nitidez (Unsharp Mask) |
| `5` | **ATIVAR PIPELINE COMPLETO** (Todos os filtros) |
| `0` | **DESLIGAR PIPELINE** (Retorna ao vídeo original) |
| `ESC` | Encerra a aplicação com segurança |

---
*Desenvolvido como Trabalho Final para a disciplina de Processamento de Imagens.*
