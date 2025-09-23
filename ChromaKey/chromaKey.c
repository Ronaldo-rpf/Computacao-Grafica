#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief Estrutura contendo os valores RGB de um pixel.
typedef struct {
    int R;
    int G;
    int B;
} RGB;

FILE *arqBackground, *arqForeground, *arqFinal;
int Rk, Gk, Bk, limSup, limInf;

int maiorRGB;
int nLinBack, nColBack;
int nLinFore, nColFore;
char tipo[4];

RGB **imgBack, **imgFore;

/// @brief Abre as imagens e recebe os valores da chave e dos limites.
void abrirArquivos(int argc, char **argv);

/// @brief Verifica as informações dos cabeçalhos das imagens.
void lerCabecalhoImagens();

/// @brief Armazena os pixels das imagens em matrizes.
void lerImagens();

/// @brief Retorna a distância de um pixel até os valores de chave.
int distanciaEuclidiana(int R, int G, int B);

/// @brief Processa a imagem final aplicando o chroma key.
void chromaKey();

/// @brief Fecha os arquivos.
void fecharArquivos();

int main(int argc, char **argv) {
    abrirArquivos(argc, argv);
    lerCabecalhoImagens();
    lerImagens();
    chromaKey();
    fecharArquivos();
    return 0;
}

void abrirArquivos(int argc, char **argv) {
    if (argc <= 8) {
        printf("Forma correta de entrada: <Nome do programa> <Imagem de background> <Imagem de foreground> <Imagem de "
               "saida> <Rk> <Gk> <Bk> <Limite superior> <Limite inferior>\n");
        exit(1);
    }
    if ((arqBackground = fopen(argv[1], "r")) == NULL) {
        printf("Erro ao abrir imagem de background.\n");
        exit(1);
    }
    if ((arqForeground = fopen(argv[2], "r")) == NULL) {
        printf("Erro ao abrir imagem de foreground.\n");
        exit(1);
    }
    if ((arqFinal = fopen(argv[3], "w")) == NULL) {
        printf("Erro ao abrir imagem de saida.\n");
        exit(1);
    }
    Rk = atoi(argv[4]);
    Gk = atoi(argv[5]);
    Bk = atoi(argv[6]);
    limSup = atoi(argv[7]);
    limInf = atoi(argv[8]);
    limSup *= limSup;
    limInf *= limInf;
    return;
}

void lerCabecalhoImagens() {
    int temp;
    fscanf(arqForeground, "%s", tipo);
    fscanf(arqForeground, "%d %d", &nColFore, &nLinFore);
    fscanf(arqForeground, "%d", &temp);

    fscanf(arqBackground, "%s", tipo);
    fscanf(arqBackground, "%d %d", &nColBack, &nLinBack);
    fscanf(arqBackground, "%d", &maiorRGB);

    if (nColFore > nColBack) {
        printf("Erro: Imagem de foreground maior que imagem de background.\n");
        exit(1);
    }
    if (nLinFore > nLinBack) {
        printf("Erro: Imagem de foreground maior que imagem de background.\n");
        exit(1);
    }
    return;
}

void lerImagens() {
    imgBack = (RGB **)calloc(nLinBack, sizeof(RGB *));
    imgFore = (RGB **)calloc(nLinFore, sizeof(RGB *));
    if (imgBack == NULL || imgFore == NULL) {
        printf("Erro ao alocar imagem final.\n");
        exit(1);
    }
    for (int i = 0; i < nLinBack; i++) {
        imgBack[i] = (RGB *)calloc(nColBack, sizeof(RGB));
        if (imgBack[i] == NULL) {
            printf("Erro ao alocar imagem final.\n");
            exit(1);
        }
    }
    for (int i = 0; i < nLinFore; i++) {
        imgFore[i] = (RGB *)calloc(nColFore, sizeof(RGB));
        if (imgFore[i] == NULL) {
            printf("Erro ao alocar imagem final.\n");
            exit(1);
        }
    }

    for (int i = 0; i < nLinBack; i++) {
        for (int j = 0; j < nColBack; j++) {
            fscanf(arqBackground, "%d", &imgBack[i][j].R);
            fscanf(arqBackground, "%d", &imgBack[i][j].G);
            fscanf(arqBackground, "%d", &imgBack[i][j].B);
        }
    }

    for (int i = 0; i < nLinFore; i++) {
        for (int j = 0; j < nColFore; j++) {
            fscanf(arqForeground, "%d", &imgFore[i][j].R);
            fscanf(arqForeground, "%d", &imgFore[i][j].G);
            fscanf(arqForeground, "%d", &imgFore[i][j].B);
        }
    }
    return;
}

int distanciaEuclidiana(int R, int G, int B) {
    return (pow((R - Rk), 2) + pow((G - Gk), 2) + pow((B - Bk), 2));
}

void chromaKey() {
    fprintf(arqFinal, "%s\n", tipo);
    fprintf(arqFinal, "%d %d\n", nColFore, nLinFore);
    fprintf(arqFinal, "%d\n", maiorRGB);
    int d;
    RGB media;
    for (int i = 0; i < nLinFore; i++) {
        for (int j = 0; j < nColFore; j++) {
            d = distanciaEuclidiana(imgFore[i][j].R, imgFore[i][j].G, imgFore[i][j].B);
            if (d < limInf) {
                fprintf(arqFinal, "%d\n", imgBack[i][j].R);
                fprintf(arqFinal, "%d\n", imgBack[i][j].G);
                fprintf(arqFinal, "%d\n", imgBack[i][j].B);
            } else if (d > limSup) {
                fprintf(arqFinal, "%d\n", imgFore[i][j].R);
                fprintf(arqFinal, "%d\n", imgFore[i][j].G);
                fprintf(arqFinal, "%d\n", imgFore[i][j].B);
            } else {
                media.R = (imgFore[i][j].R + imgBack[i][j].R) / 2;
                media.G = (imgFore[i][j].G + imgBack[i][j].G) / 2;
                media.B = (imgFore[i][j].B + imgBack[i][j].B) / 2;
                fprintf(arqFinal, "%d\n", media.R);
                fprintf(arqFinal, "%d\n", media.G);
                fprintf(arqFinal, "%d\n", media.B);
            }
        }
    }
    return;
}

void fecharArquivos() {
    fclose(arqBackground);
    fclose(arqForeground);
    fclose(arqFinal);
    return;
}
