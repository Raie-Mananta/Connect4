#include <stdio.h>

#define TAILLE_GRILLE 6

int scan_colonne(int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
	
	int entree_correcte = 0;
	
	int colonne;
	
	printf("Veuillez entrer la colonne souhaitée");
	
	while (!entree_correcte){
		if (scanf("%d",&colonne) == 1){
			if (colonne < 0 | colonne > 5){
				printf("Saisie incorrecte");
			}
			else{
				entree_correcte = 1;
			}
			
		}
		
		else{
			printf("Saisie incorrecte");
		}
	}
	
	return colonne;
	
}

int hauteur_colonne ( int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne ){
	int i = 0;
	int taille = 0;
	
	if (colonne < 0 | colonne > 5){
		return -2;
	}
	
	else{
		while(grille[i][colonne] != 0 & taille < 6){
			taille++;
			i++;
		}
		return taille;
	}
}

int poser_jeton (int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int joueur){
	
	int hauteur = hauteur_colonne(grille, colonne);
	
	if (hauteur == 6){
		return -3;
	}
	else if (hauteur == -2){
		return -2;
	}
	
	else{
		grille[hauteur][colonne] = joueur;
		return hauteur;
	}
}

void init_grille(int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
		int i;
		int j;
		
		for (i = 0; i < TAILLE_GRILLE; i++){
			for (j = 0; j < TAILLE_GRILLE; j++){
				grille[i][j] = 0;
			}
		}
	}

void affiche_grille(int grille[TAILLE_GRILLE][TAILLE_GRILLE]){
		int i;
		int j;
		
		for (i = TAILLE_GRILLE-1; i > -1; i--){
			printf("\n");
			for (j = 0; j < TAILLE_GRILLE	; j++){
				if (j != 0){
					if (grille[i][j] == 0){
						printf(" |");
					}
					
					else{
						if (grille[i][j] == 1){
							printf("X|");
						}
						else{
							printf("O|");
						}
					}
				}
				
				else{
					if (grille[i][j] == 0){
						printf("| |");
					}
					
					else{
						if (grille[i][j] == 1){
							printf("|X|");
						}
						else{
							printf("|O|");
						}
					}
				}
			}
		}
		printf("\n");
	}
	
int verifie_gagne(int grille[TAILLE_GRILLE][TAILLE_GRILLE], int colonne, int ligne, int joueur){
	
	int comptegauche = 0;
	int comptedroite = 0;
	
	int i;
	
	if (ligne - 3 >= 0){
		if (grille[ligne-1][colonne] == joueur & grille[ligne-2][colonne] == joueur & grille[ligne-3][colonne] == joueur){
			return 1;
		}
		
		else if (colonne - 3 >= 0){
			if (grille[ligne-1][colonne-1] == joueur & grille[ligne-2][colonne-2] == joueur & grille[ligne-3][colonne-3] == joueur){
				return 1;
			}	 
		}
		
		else if (colonne + 3 <= 5){
			if (grille[ligne-1][colonne+1] == joueur & grille[ligne-2][colonne+2] == joueur & grille[ligne-3][colonne+3] == joueur){
				return 1;
			}	 
		}
	}
	
	for (i = colonne - 1; i >= colonne - 3; i--){
		if (i < 0){
			break;
		}
		
		else{
			if (grille[ligne][i] == joueur){
				comptegauche++;
			}
			else{
				break;
			}
		}
	}
	
	for (i = colonne + 1; i <= colonne + 3; i++){
		if (i > 5){
			break;
		}
		
		else{
			if (grille[ligne][i] == joueur){
				comptedroite++;
			}
			else{
				break;
			}
		}
	}
	
	if (comptegauche + comptedroite >= 3){
		return 1;
	}
	
	else{
		return 0;
	}
	
}



int main () {
	
	int grille[TAILLE_GRILLE][TAILLE_GRILLE];
	
	int colonne;

	int ligne;

	int nbCoups = 0;

	int victJ1 = 0;

	int victJ2 = 0;

	int tourJoueur = 1;

	init_grille (grille);
	
	affiche_grille(grille);

	while (nbCoups < 36 & !victJ1 & !victJ2){
		if (tourJoueur == 1){
			printf("Tour du Joueur 1\n");
			colonne = scan_colonne(grille);
			ligne = poser_jeton(grille,colonne,1);
			victJ1 = verifie_gagne(grille,colonne,ligne,1);
			nbCoups++;
			affiche_grille(grille);
			tourJoueur = 2;
		}
		
		else{
			if (!victJ1){
				printf("Tour du Joueur 2\n");
				colonne = scan_colonne(grille);
				ligne = poser_jeton(grille,colonne,2);
				victJ2 = verifie_gagne(grille,colonne,ligne,2);
				nbCoups++;
				affiche_grille(grille);
				tourJoueur = 1;
			}
		}
	}
	
	if (victJ1){
		printf("Victoire du Joueur 1 !\n");
	}
	
	else if (victJ2){
		printf("Victoire du Joueur 2 !\n");
	}
	
	else{
		printf("Nombre de coups disponible dépassés, il y a donc égalité\n");
	}
	
}
