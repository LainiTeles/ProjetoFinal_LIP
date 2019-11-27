Imagem transposta (Imagem img){
    int i, j, k;

    Imagem img_trans;

    img_trans.largura = img.altura;
    img_trans.altura = img.largura;

    for(i=0; i<img_trans.altura; i++){
        for(j=0; j<img_trans.largura; j++){
            for(k=0; k<3; k++){
                img_trans.matriz[k][j][i] = img.matriz[k][i][j];
            }
        }
    }

    return img_trans;
}
