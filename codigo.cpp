#include <iostream>
using namespace std;

const int MAX = 600;
const int SMAX = 100;

struct RGB{
    int vermelho;
    int verde;
    int azul;
};

struct Imagem{
    int largura;
    int altura;
    RGB image[3][MAX][MAX];
};

int main(){
    char opcao;

    cout << "###### MENU ######\n";
    cout << "# Selecione a edicao desejada: \n";
    cout << "  1 -> Funcao Verde\n";
    cout << "  2 -> Funcao Amarela\n";
    cout << "  3 -> Funcao Azul\n";
    cout << "  4 -> Funcao vermelha\n";
    cout << "  S -> Funcao Sair\n";

    cin >> opcao;

    switch(opcao){
        case '1':
            cout << "Insira nome do arquivo imagem:\n";
            //cin >> arq;
            /*if( @ == "p3"){
                if( @ <= 512 && @ <= 512){
                    funcao verde();
                }
            }*/

            break;

        case '2':
            cout << "Insira nome do arquivo imagem:\n";
            //cin >> arq;
            /*if( @ == "p3"){
                if( @ <= 512 && @ <= 512){
                    funcao amarela();
                }
            }*/
            break;

        case '3':
            cout << "Insira nome do arquivo imagem:\n";
            //cin >> arq;
            /*if( @ == "p3"){
                if( @ <= 512 && @ <= 512){
                    funcao azul();
                }
            }*/
            break;

        case '4':
            cout << "Insira nome do arquivo imagem:\n";
            //cin >> arq;
            /*if( @ == "p3"){
                if( @ <= 512 && @ <= 512){
                    funcao verde();
                }
            }*/
            break;

        case 'S':
            //funcao sair();
            break;

        default:
            cout << "Opcao invalida";
    }

return 0;
}
