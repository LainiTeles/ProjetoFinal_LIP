void binariza(Imagem img, Imagem& img_out, int limiar){
    int i, j, k;

    converte_para_cinza(img, img_out);

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
