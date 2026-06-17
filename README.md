PROJETO SHADOW OF THE COLOSSUS REMASTER - OPENCV

Descrição
Este é um projeto de processamento digital de imagens desenvolvido em C++ utilizando a biblioteca OpenCV. O objetivo principal do sistema é aplicar técnicas matemáticas para simular a remasterização visual de um vídeo de gameplay do jogo Shadow of the Colossus. O programa melhora a nitidez, as cores e o contraste do vídeo rodando em tempo real, sem utilizar ferramentas de Inteligência Artificial.

Filtros Implementados no Pipeline
O código lê o vídeo e passa os frames por uma esteira com quatro filtros processados em sequência:

Remoção de Ruído: Utiliza o desfoque Gaussiano para limpar a imagem inicial e remover chuviscos e artefatos de compressão do vídeo original.

Cores Vivas: O sistema converte a imagem para o espaço de cor LAB. Isso permite amplificar a saturação dos canais de cores de forma isolada, sem distorcer ou estourar a iluminação da cena.

Melhoria de Contraste: Aplica a técnica CLAHE (Equalização de Histograma Adaptativa). Esse filtro recupera detalhes visuais que ficam escondidos nas sombras do jogo, mas com uma supressão de altas luzes para evitar que o céu claro fique estourado na tela.

Nitidez: O toque final utiliza a técnica de Unsharp Masking. O algoritmo realça as bordas e os contornos das texturas, dando o aspecto final de Alta Definição (HD) para o jogo.

Como Executar o Projeto

Pré-requisitos:
Para rodar este código no seu computador, você precisa ter um ambiente Linux configurado com o compilador C++ (GCC/G++), o CMake para gerenciar a compilação e a biblioteca OpenCV 4 instalada.

Passo a Passo:

Primeiro, clone o repositório para a sua máquina através do terminal usando o link do projeto.

Segundo, você precisará ter o vídeo original baixado. Abra o arquivo main.cpp no seu editor e altere o caminho de diretório indicado na função VideoCapture para o local exato onde o vídeo está salvo no seu computador.

Terceiro, abra o terminal na pasta raiz do projeto, crie uma pasta chamada build e rode o comando do CMake para preparar os arquivos. Depois, rode o comando Make para compilar o código.

Por fim, basta executar o arquivo final gerado no terminal para ver a interface abrindo com a comparação do antes e depois rodando na tela.
