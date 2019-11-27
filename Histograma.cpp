void histograma(Imagem img, Imagem& img_out){

    int cont[256][3], somatorio = 0;

    img_out = img;

    for(int i = 0; i < 256; i++){
        for(int j = 0; j < 3; j++){
            cont[i][j] = 0;
        }
    }

    for(int i = 0; i < img.altura; i++){
        for(int j = 0; j < img.largura; j++){
            for(int k = 0; k < 3; k++){
                cont[img.matriz[k][j][i]][k] ++;
            }
        }
    }

    for(int i = 0; i < img.altura; i++){
        for(int j = 0; j < img.largura; j++){
            for(int k = 0; k < 3; k++){
                for(int l = 0; l <= img.matriz[k][j][i]; l++){
                    somatorio+=cont[l][k];
                }
                img_out.matriz[k][j][i] = somatorio*255/(img.altura*img.largura);
                somatorio = 0;
            }
        }
    }
}
