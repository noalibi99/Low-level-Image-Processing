//
//  image_utils.c
//  Low_level_Image_processing
//
/*
Réalisé par:    Mohammed EL HIMAR          BDCC1
                Aya ECHBANI EL IDRISSI     CCN1
*/
//

#include "image_utils.h"

RGB_image* image_init(int R, int H, int L){
    RGB_image* img = (RGB_image *)malloc(sizeof(RGB_image));
    img->R = R; img->H = H; img->L = L;
    img->pixels = (unsigned char***)malloc(3*sizeof(unsigned char**));
    for(int i = 0; i < 3; i++){
        /* On considere R:0, G:1, B:2 */
        img->pixels[i] = (unsigned char**)malloc(R*H*sizeof(unsigned char*));
        for(int j = 0; j < R*H; j++){
            img->pixels[i][j] = (unsigned char*)malloc(R*L*sizeof(unsigned char));
        }
    }
    //Returns the image filled with garbage values
    return img;
}

void free_image(RGB_image* img){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < img->R*img->H; j++){
            free(img->pixels[i][j]);
        }
        free(img->pixels[i]);
    }
    free(img->pixels);
    free(img);
    img = NULL;
}

RGB_image* random_image(int R, int H, int L){
    srand(time(NULL)); // donner un seed au generateur
    RGB_image* img = image_init(R, H, L);
    for(int i = 0; i < img->R*img->H; i++){
        for(int j = 0; j < img->R*img->L; j++){
            img->pixels[0][i][j] = rand() % 256; // R
            img->pixels[1][i][j] = rand() % 256; // G
            img->pixels[2][i][j] = rand() % 256; // B
        }
    }
    return img;
}

// Le saisie au clavier ce n'est pas vraiment utile

RGB_image* saisie_clavier(int R, int H, int L){
    RGB_image* img = image_init(R, H, L);
    printf("Entrez une valeur entre 0 et 255 pour chaque couleur (R, G, B)");
    unsigned char r, g, b;
    for(int i = 0; i < img->R*img->H; i++){
        for(int j = 0; j < img->R*img->L; j++){
            do {
                printf("Veuillez entrer une valeur entre 0 et 255 pour chaque couleur R, G, B.\n");
                printf("(%d, %d) = ", i, j);
                scanf("%hhu %hhu %hhu", &r, &g, &b);
            } while (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255);
            img->pixels[0][i][j] = r;
            img->pixels[1][i][j] = g;
            img->pixels[2][i][j] = b;
        }
    }
    return img;
}


/*
 lire une image ppm qui est la plus simple representation d'une image sous forme d'un tableau. et alors utiliser que les fonctions primitives de C sans recours au bibliotheque.
*/
RGB_image* lire_image(const char *filename){
    FILE* f = fopen(filename, "r");
    if(!f){
        printf("Allocation Error!");
        exit(EXIT_FAILURE);
    }
    char header[3];
    fscanf(f, "%s", header);
    if(strcmp(header, "P3")){
        printf("not a ppm file!");
        return NULL;
    }
    int H, L, prof;
    fscanf(f, "%d %d", &L, &H);
    fscanf(f, "%d", &prof);
    
    RGB_image* img = image_init(1, H, L);
    int r, g, b;
    for(int i = 0; i < img->R*img->H; i++){
        for(int j = 0; j < img->R*img->L; j++){
            fscanf(f, "%d %d %d", &r, &g, &b);
            img->pixels[0][i][j] = (unsigned char)r; // R
            img->pixels[1][i][j] = (unsigned char)g; // G
            img->pixels[2][i][j] = (unsigned char)b; // B
        }
    }
    fclose(f);
    return img;
}
/* cette fonction nous permet d'obtenir la composante de base d'une coleur donnée. Ainsi, obtenir une image de niveau de gris */
unsigned char** get_channel(RGB_image* img, int channel_idx){
    unsigned char** channel_data = (unsigned char **)malloc(img->R*img->H*sizeof(unsigned char*));
    for(int i = 0; i < img->R*img->H; i++){
        channel_data[i] = (unsigned char*)malloc(img->R*img->L*sizeof(unsigned char));
    }
    
    for(int i = 0; i < img->R*img->H; i++){
        for(int j = 0; j < img->R*img->L; j++){
            channel_data[i][j] = img->pixels[channel_idx][i][j];
        }
    }
    return channel_data;
}

RGB_image* afficher_composante(RGB_image* img, int channel_idx){
    RGB_image *single_channel = image_init(img->R, img->H, img->L);
    
    for(int i = 0; i < img->R*img->H; i++){
        for(int j = 0; j < img->R*img->L; j++){
            single_channel->pixels[channel_idx][i][j] = img->pixels[channel_idx][i][j];
            for (int c = 0; c < 3; c++) {
                if (c != channel_idx) {
                    single_channel->pixels[c][i][j] = 0;
                }
            }
        }
    }
    
    return single_channel;
}

/*Une autre méthode pour obtenir une image en niveaux de gris consiste à utiliser une somme pondérée des composantes de couleur, où chaque composant (rouge, vert, bleu) est multiplié par un coefficient spécifique afin de tenir compte de l'impact perceptuel de chaque couleur sur la luminosité de l'image.*/
unsigned char** get_grayscale_image(RGB_image* img){
    unsigned char** grayscale = (unsigned char **)malloc(img->R*img->H*sizeof(unsigned char*));
    for(int i = 0; i < img->R*img->H; i++){
        grayscale[i] = (unsigned char*)malloc(img->R*img->L*sizeof(unsigned char));
    }
    
    double R, G, B;
    R = 0.2989; G = 0.5870; B = 0.1140;
    for(int i = 0; i < img->R*img->H; i++){
        for(int j = 0; j < img->R*img->L; j++){
            grayscale[i][j] = img->pixels[0][i][j]*R;
            grayscale[i][j] += img->pixels[1][i][j]*G;
            grayscale[i][j] += img->pixels[2][i][j]*B;
        }
        // pixel = sum(R*const_r+G*const_g+B*const_b) 0<pixel<255
    }
    return grayscale;
}

void enregistrer_image(const char *filename, RGB_image *img) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        exit(EXIT_FAILURE);
    }

    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n", img->L, img->H);
    fprintf(f, "255\n");

    for (int i = 0; i < img->R * img->H; i++) {
        for (int j = 0; j < img->R * img->L; j++) {
            fprintf(f, "%d %d %d ", img->pixels[0][i][j], img->pixels[1][i][j], img->pixels[2][i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("PPM file '%s' has been written successfully.\n", filename);
}

void enregistrer_pgm(const char *filename, unsigned char **matrix, int height, int width) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error: Failed to open file '%s'.\n", filename);
        return;
    }

    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", width, height);
    fprintf(f, "255\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(f, "%d ", matrix[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("PGM file '%s' has been written successfully.\n", filename);
}

RGB_image* mean_blur(RGB_image* img, int kernel_size) {
    RGB_image* blurred_img = image_init(img->R, img->H, img->L);

    int offset = kernel_size / 2;
    
    for (int i = 0; i < img->H; i++) {
        for (int j = 0; j < img->L; j++) {

            int sum_r = 0, sum_g = 0, sum_b = 0;
            int count = 0;

            for (int ki = -offset; ki <= offset; ki++) {
                for (int kj = -offset; kj <= offset; kj++) {
                    int x = i + ki;
                    int y = j + kj;
                    
                    if (x >= 0 && x < img->H && y >= 0 && y < img->L) {
                        sum_r += img->pixels[0][x][y];
                        sum_g += img->pixels[1][x][y];
                        sum_b += img->pixels[2][x][y];
                        count++;
                    }
                }
            }

            blurred_img->pixels[0][i][j] = sum_r / count;
            blurred_img->pixels[1][i][j] = sum_g / count;
            blurred_img->pixels[2][i][j] = sum_b / count;
        }
    }

    return blurred_img;
}

RGB_image* flip_H(RGB_image* img) {
    RGB_image* flipped = image_init(img->R, img->H, img->L);

    for (int i = 0; i < img->H; i++) {
        for (int j = 0; j < img->L; j++) {
            flipped->pixels[0][i][j] = img->pixels[0][img->H - 1 - i][j];
            flipped->pixels[1][i][j] = img->pixels[1][img->H - 1 - i][j];
            flipped->pixels[2][i][j] = img->pixels[2][img->H - 1 - i][j];
        }
    }

    return flipped;
}

RGB_image* flip_V(RGB_image* img) {
    RGB_image* flipped = image_init(img->R, img->H, img->L);

    for (int i = 0; i < img->H; i++) {
        for (int j = 0; j < img->L; j++) {
            flipped->pixels[0][i][j] = img->pixels[0][i][img->L - 1 - j];
            flipped->pixels[1][i][j] = img->pixels[1][i][img->L - 1 - j];
            flipped->pixels[2][i][j] = img->pixels[2][i][img->L - 1 - j];
        }
    }

    return flipped;
}

RGB_image* negative(RGB_image* img){
    RGB_image* negative = image_init(img->R, img->H, img->L);
    for(int i = 0; i < img->H; i++){
        for(int j = 0; j < img->L; j++){
            negative->pixels[0][i][j] = 255 - img->pixels[0][i][j];
            negative->pixels[1][i][j] = 255 - img->pixels[1][i][j];
            negative->pixels[2][i][j] = 255 - img->pixels[2][i][j];
        }
    }
    return negative;
}
