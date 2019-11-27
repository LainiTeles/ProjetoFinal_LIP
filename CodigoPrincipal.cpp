#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;

const int MAX = 600;
const int SMAX = 100;

//TIPO ESTRUTURADO
struct Imagem{
    int largura;
    int altura;
    int matriz[3][MAX][MAX];
};

//FUNÇÕES
bool abre_img(char nome[], Imagem& img);
void converte_para_cinza(Imagem img, Imagem& img_out);
void salva_img(char nome_out[], Imagem img_out);
void rotaciona(Imagem img_in, Imagem& img_out);
void erosao(Imagem img, Imagem& img_out);
void binariza(Imagem img, Imagem& img_out, int limiar);
Imagem transposta (Imagem img);
void histograma(Imagem img, Imagem& img_out);

//FUNÇÃO PRINCIPAL
int main(){
    int limiar;
    Imagem img;
    Imagem img_out;
    char opcao;
    char nome_out[] = "arq_out.ppm";

    char nome[SMAX];

    cout << "Insira nome do arquivo imagem:\n";
    cin >> nome;
    cout << endl;

do{ //LAÇO INFINITO DO MENU.

    if(abre_img(nome,img)){ //VERIFICA SE O ARQUIVO FOI ABERTO E RECEBEU OS DADOS DA IMAGEM .

        cout << "###### MENU ######\n";
        cout << "# Selecione a edicao desejada:\n";
        cout << endl;
        cout << "  1 -> Escala de Cinza\n";
        cout << "  2 -> Rotaciona(anti_horario)\n";
        cout << "  3 -> Erosao \n";
        cout << "  4 -> Histograma \n";
        cout << "  5 -> Binariza \n";
        cout << "  6 -> Faz a Transposta \n";
        cout << "  7 -> Inserir Nova Imagem \n";
        cout << "  8 -> Sair \n";

        cin >> opcao;

        switch(opcao){
            case '1':
                converte_para_cinza(img,img_out);

                salva_img(nome_out,img_out);

                break;

            case '2':
                rotaciona(img,img_out);

                salva_img(nome_out,img_out);

                break;

           case '3':
                erosao(img,img_out);

                salva_img(nome_out,img_out);

                break;

            case '4':
                histograma(img,img_out);

                salva_img(nome_out,img_out);

                break;

            case '5':
                cout << "Insira o limiar, entre 0 e 255: \n";
                cin >> limiar;

                binariza(img,img_out,limiar);

                salva_img(nome_out,img_out);

                break;

            case '6':
                img_out = transposta(img);

                salva_img(nome_out,img_out);

               break;

            case '7':
                cout <<"Insira o nome do novo arquivo imagem: \n";
                cin >> nome;
                cout << endl;

               break;

            case '8':

               break;

            default:
                cout << "Opcao invalida, tente novamente." << endl;
        }
    }
    else{
        cout << "Arquivo invalido, tente novamente inserindo o nome de um arquivo imagem valido: " << endl;
        cin >> nome;
        cout << endl;

    }

}while(opcao != '8'); //CONDICAO DO LACO DO MENU.

return 0;
}

bool abre_img(char nome[], Imagem& img){
    fstream arq;
    char tipo[] = "P3";
    char validacao[SMAX];
    int pixelmax;

    arq.open(nome);

    if(!arq.is_open()){ //VERIFICA SE ABRIU CORRETAMENTE.
        return false;
    }
    else{
        //LÊ DADOS DO ARQUIVO.
        arq >> validacao;
        arq >> img.largura;
        arq >> img.altura;
        arq >> pixelmax;

    }
    if(img.altura > 512 || img.largura > 512 || strcmp(validacao,tipo)!=0 ){ //VERIFICA SE O ARQUIVO É VALIDO.
           return false;
    }
    else{
        //LÊ A MATRIZ DE DADOS DA IMAGEM.
        for(int i = 0; i<img.altura; i++){
            for(int j = 0; j<img.largura; j++){
                for(int k = 0; k<3; k++){
                    arq >> img.matriz[k][j][i];
                }
            }
        }
    }

 arq.close(); //FECHA ARQUIVO COM IMAGEM ORIGEM.
 return true;
}

void converte_para_cinza(Imagem img, Imagem& img_out){
    float media = 0.0;

    //IMAGEM RESULTANTE RECEBE OS CAMPOS DA IMAGEM ORIGINAL.
    img_out = img;

    for(int i = 0; i<img.altura; i++){
        for(int j = 0; j<img.largura; j++){
            for(int k = 0; k<3; k++){
                media += img.matriz[k][j][i];

            }
            media /= 3;

            for(int k=0; k<3; k++){
                //IMAGEM RESULTADO RECEBE VALOR DA MEDIA.
                img_out.matriz[k][j][i] = media;
            }
            media = 0.0;
        }
    }
}

void rotaciona(Imagem img, Imagem& img_out){
  
    img_out.largura = img.altura;
    img_out.altura = img.largura; //IMAGEM RESULTADO RECEBE DIMENSOES.

    for(int i=0; i<img_out.altura; i++){
        for(int j=0; j<img_out.largura; j++){
            for(int k=0; k<3; k++){
                img_out.matriz[k][j][i] = img.matriz[k][img_out.altura-i-1][j];
            }
        }
    }
}

void erosao(Imagem img, Imagem& img_out){

    img_out.largura = img.largura;
    img_out.altura = img.altura; // IMAGEM RESULTENTE RECEBE A DIMENSAO.

    for(int i = 0; i < img.altura; i++){
        for(int j = 0; j < img.largura; j++){
            for(int k = 0; k < 3; k++){
                if((img.matriz[k][j][i] + img.matriz[k][j][i+1] + img.matriz[k][j+1][i] + img.matriz[k][j+1][i+1]) == 4*255){
                    //VERIFICA SE OS VALORES DOS PIXELS ONDE ESTA LOCALIZADA A MATRIZ FILTRO É IGUAL A 255.
                    img_out.matriz[k][j][i] = 255;
                }
                else{
                    img_out.matriz[k][j][i] = 0;
                }
            }
        }
    }
}

void histograma(Imagem img, Imagem& img_out){

    int cont[256][3], somatorio = 0;

    img_out = img;

    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 3; j++){
            cont[i][j] = 0;
        }
    } //ZERA O VETOR CONTADOR, SEM LIXO DE MEMORIA.

    for(int i = 0; i < img.altura; i++){
        for(int j = 0; j < img.largura; j++){
            for(int k = 0; k < 3; k++){
                cont[img.matriz[k][j][i]][k] ++;
            }
        }
    } //IMPLEMENTÇÃO DO VETOR CONTADOR.

    for(int i = 0; i < img.altura; i++){
        for(int j = 0; j < img.largura; j++){
            for(int k = 0; k < 3; k++){
                for(int l = 0; l <= img.matriz[k][j][i]; l++){
                    somatorio+=cont[l][k]; //SOMATORIO ATE IM DADO PIXEL.
                } 
                img_out.matriz[k][j][i] = somatorio*255/(img.altura*img.largura); 
                //DADO PIXEL RECEBE RESULTADO DA OPERAÇÃO DE EQUALIZAÇÃO.
                somatorio = 0;
            }
        }
    }
}

void binariza(Imagem img, Imagem& img_out, int limiar){
    int i, j, k;

    converte_para_cinza(img, img_out); // TODAS AS CORES POSSUEM O MESMO VALOR.

    for(i=0; i<img.altura; i++){
        for(j=0; j<img.largura; j++){
            for(k=0; k<3; k++){
                if(img_out.matriz[k][j][i] >= limiar){
                    img_out.matriz[k][j][i] = 255;
                }
                else{
                    img_out.matriz[k][j][i] = 0;
                }
            }
        }
    }
}

Imagem transposta (Imagem img){
    int i, j, k;

    Imagem img_trans;

    img_trans.largura = img.altura;
    img_trans.altura = img.largura;

    for(i=0; i<img_trans.altura; i++){
        for(j=0; j<img_trans.largura; j++){
            for(k=0; k<3; k++){
                img_trans.matriz[k][j][i] = img.matriz[k][i][j];
                //A TRANSPOSTA RECEBE O PIXEL INVERSO EM NUMERO DE LINHA E COLUNA.
            }
        }
    }

    return img_trans;
}

void salva_img(char nome_out[], Imagem img_out){
    ofstream arq_out;
    arq_out.open(nome_out);

    if(arq_out.is_open()){ //VERIFICA SE ABRIU CORRETAMENTE.

        arq_out << "P3" << endl;
        arq_out << img_out.largura << " ";
        arq_out << img_out.altura << endl; //IMPRIME NO AQUIRVO DE SAÍDA OS DADOS DA IMAGEM RESULTANTE.
        arq_out << 255 << endl;

        for(int i=0; i<img_out.altura; i++){
            for(int j=0; j<img_out.largura; j++){
                for(int k=0; k<3; k++){
                    arq_out << img_out.matriz[k][j][i] << " ";
                }
            }

        arq_out << endl;
        }
    }

    cout << "Imagem salva em: " << nome_out << endl;
    cout << endl;
    arq_out.close(); //FECHAR ARQUIVO COM IMAGEM RESULTANTE.
}
