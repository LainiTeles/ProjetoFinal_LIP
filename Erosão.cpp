void erosao(Imagem img, Imagem& img_out){

    img_out.largura = img.largura;
    img_out.altura = img.altura;

    for(int i = 0; i < img.altura; i++){
        for(int j = 0; j < img.largura; j++){
            for(int k = 0; k < 3; k++){
                if((img.matriz[k][j][i] + img.matriz[k][j][i+1] + img.matriz[k][j+1][i] + img.matriz[k][j+1][i+1]) == 4*255){
                    img_out.matriz[k][j][i] = 255;
                }
                else{
                    img_out.matriz[k][j][i] = 0;
                }
            }
        }
    }
}
