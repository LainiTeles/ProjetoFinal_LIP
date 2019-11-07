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

//FUNÇÃO PRINCIPAL
int main(){
    Imagem img;
    Imagem img_out;
    char opcao;
    char nome_out[] = "arq_out.ppm";

    char nome[SMAX];
    cout << "Insira nome do arquivo imagem:\n";
    cin >> nome;

    if(abre_img(nome,img)){ //VERIFICA SE O ARQUIV FOI ABERTO E RECEBEU OS DADOS DA IMAGEM .

        cout << "###### MENU ######\n";
        cout << "# Selecione a edicao desejada:\n";
        cout << "  1 -> Escala de Cinza\n";

        cin >> opcao;

        switch(opcao){
            case '1':
                converte_para_cinza(img,img_out);

                salva_img(nome_out,img_out);

                break;

            default:
                cout << "Opcao invalida, tente novamente." << endl;
        }
    }
    else{
        cout << "Arquivo invalido, tente novamente." << endl;
    }

return 0;
}

bool abre_img(char nome[], Imagem& img){
    fstream arq;
    char tipo[] = "P3";
    char validacao[SMAX];

    arq.open(nome);

    if(!arq.is_open()){ //VERIFICA SE ABRIU CORRETAMENTE.
        return false;
    }
    else{
        //LÊ DADOS DO ARQUIVO.
        arq >> validacao;
        arq >> img.altura;
        arq >> img.largura;

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
void salva_img(char nome_out[], Imagem img_out){
    ofstream arq_out;
    arq_out.open(nome_out);

    if(arq_out.is_open()){ //VERIFICA SE ABRIU CORRETAMENTE.

        arq_out << "P3" << endl;
        arq_out << img_out.altura << " ";
        arq_out << img_out.largura << endl; //IMPRIME NO AQUIRVO DE SAÍDA OS DADOS DA IMAGEM RESULTANTE.
        arq_out << 255 << endl;

        for(int i=0; i<img_out.altura; i++){
            for(int j=0; j<img_out.largura; j++){
                for(int k=0; k<3; k++){
                    arq_out << img_out.matriz[k][j][i];
                }
            }

        arq_out << endl;
        }
    }
    
    cout << "Imagem salva em: " << nome_out << endl;
    arq_out.close(); //FECHAR ARQUIVO COM IMAGEM RESULTANTE.
}
