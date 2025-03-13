//
//  image_utils.h
//  Low_level_Image_processing
//
/*
Réalisé par:    Mohammed EL HIMAR          BDCC1
                Aya ECHBANI EL IDRISSI     CCN1
*/
//

#ifndef image_utils_h
#define image_utils_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int R, H, L;
    unsigned char ***pixels;
}RGB_image;

RGB_image* image_init(int R, int H, int L);
void free_image(RGB_image* img);
RGB_image* random_image(int R, int H, int L);
RGB_image* lire_image(const char *filename);
RGB_image* saisie_clavier(int R, int H, int L);
RGB_image* afficher_composante(RGB_image* img, int channel_idx);
unsigned char** get_channel(RGB_image* img, int channel_idx);
unsigned char** get_grayscale_image(RGB_image* img);
void enregistrer_image(const char *filename, RGB_image *img);
void enregistrer_pgm(const char *filename, unsigned char **matrix, int height, int width);
RGB_image* mean_blur(RGB_image* img, int kernel_size);
RGB_image* flip_V(RGB_image* img);
RGB_image* flip_H(RGB_image* img);
RGB_image* negative(RGB_image* img);

#endif /* image_utils_h */
