void rotaciona(Imagem img, Imagem& img_out){
    img_out.largura = img.altura;
    img_out.altura = img.largura;

    for(int i=0; i<img_out.altura; i++){
        for(int j=0; j<img_out.largura; j++){
            for(int k=0; k<3; k++){
                img_out.matriz[k][j][i] = img.matriz[k][img_out.altura-i-1][j];
            }
        }
    }
}
