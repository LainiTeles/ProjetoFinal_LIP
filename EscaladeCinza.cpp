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
