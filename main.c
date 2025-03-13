//
//  main.c
//  Low_level_Image_processing
//
/*
Réalisé par:    Mohammed EL HIMAR          BDCC1
                Aya ECHBANI EL IDRISSI     CCN1
*/

#include <stdio.h>
#include "image_utils.h"

void afficher_menu(){
    printf("\n----- Menu -----\n");
    printf("1. Charger une image (PPM)\n");
    printf("2. Générer une image aléatoire\n");
    printf("3. Saisir une image sur clavier\n");
    printf("4. Afficher une seule composante\n");
    printf("5. Obtenir une image niveau de gris\n");
    printf("6. Applique le filtre flou moyen (Mean Blur)\n");
    printf("7. Effectuer une symétrie verticale (Flip Verical)\n");
    printf("8. Effectuer une symétrie horizontale (Flip Horizontal)\n");
    printf("9. Obtenir l'image en négatif\n");
    printf("10. Quitter\n");
    printf("----------------\n");
    printf("Entrez votre choix : ");
}

int main(int argc, const char * argv[]) {
    RGB_image* img = NULL;
    int choix, H, L;
    char filename[50];
    
    while(1){
        afficher_menu();
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                if (img) free_image(img);
                printf("Entrez le nom du fichier: ");
                scanf("%s", filename);
                img = lire_image(filename);
                printf("L'image est chargée avec succès!");
                break;
            case 2:
                printf("Entrez H, L:");
                scanf("%d, %d", &H, &L);
                RGB_image* rand_img = random_image(1, H, L);
                enregistrer_image("output/random_image.ppm", rand_img);
                free_image(rand_img);
                break;
            case 3:
                printf("Entrez H, L:");
                scanf("%d, %d", &H, &L);
                RGB_image* user_input = saisie_clavier(1, H, L);
                enregistrer_image("output/user_input.ppm", user_input);
                free_image(user_input);
                break;
            case 4:
                if(!img){
                    printf("Chargez une image PPM d'abord!");
                    break;
                }
                int channel_idx;
                printf("R:0, G:1, B:2");
                scanf("%d", &channel_idx);
                RGB_image* single_channel = afficher_composante(img, channel_idx);
                enregistrer_image("output/single_channel.ppm", single_channel);
                free_image(single_channel);
                break;
            case 5:
                if(!img){
                    printf("Chargez une image PPM d'abord!");
                    break;
                }
                unsigned char** grayscale = get_grayscale_image(img);
                enregistrer_pgm("output/niveaux_de_gris.ppm", grayscale, img->H, img->L);
                break;
            case 6:
                if(!img){
                    printf("Chargez une image PPM d'abord!");
                    break;
                }
                int kernel_size;
                printf("Entrez la taille du noyau: ");
                scanf("%d", &kernel_size);
                RGB_image* blurred_img = mean_blur(img, kernel_size);
                enregistrer_image("output/blurred_image.ppm", blurred_img);
                free_image(blurred_img);
                break;
            case 7:
                if(!img){
                    printf("Chargez une image PPM d'abord!");
                    break;
                }
                RGB_image* flipped_img = flip_V(img);
                enregistrer_image("output/flipped_V_image.ppm", flipped_img);
                free_image(flipped_img);
                break;
            case 8:
                if(!img){
                    printf("Chargez une image PPM d'abord!");
                    break;
                }
                flipped_img = flip_H(img);
                enregistrer_image("output/flipped_H_image.ppm", flipped_img);
                free_image(flipped_img);
            case 9:
                if(!img){
                    printf("Chargez une image PPM d'abord!");
                    break;
                }
                RGB_image* negative_img = negative(img);
                enregistrer_image("output/negative_image.ppm", negative_img);
                free_image(negative_img);
                break;
            case 10:
                if (img) free_image(img);
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }
    return 0;
}
