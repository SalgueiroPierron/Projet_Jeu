#include <SDL/SDL.h>

/**
 * Structure de données d'un Kart.
 */

typedef struct s_kart{
  Sprite sprite;
  doubleCoord coord;
  int rotation;
  double vitesse;
}  s_kart_t, *voiture_t;


/**
 * Retourne un kart vide.
 */
voiture_t new_kart_empty();

/**
 * Retourne un kart ayant kart, rotation et vitesse pour valeurs.
 */
voiture_t new_voiture(Sprite sprite, int rotation, double vitesse);

/**
 * Vérifie si le carte est vide.
 */
int is_empty(voiture_t voiture);

/**
 * Retourne le SDL_Rect du kart.
 */
Sprite sprite(voiture_t voiture);

/**
 * Retourne la rotation du kart.
*/
int rotation(voiture_t voiture);

/**
 * Retourne la vitesse du kart.
 */
double vitesse(voiture_t voiture);

/**
 * Change le SDL_Rect du kart.
 */
void change_sprite(voiture_t* voiture, Sprite sprite);

/**
 * Retourne la rotation du kart.
*/
void change_rotation(voiture_t* voiture, double rotation);

void add_rotation(voiture_t* voiture, double rotat);

void accelerer(voiture_t* voiture);

/**
 * Retourne la vitesse du kart.
 */
void change_vitesse(voiture_t* voiture, double vitesse);

/**
 *Libère la mémoire allouée pour le kart.
 */
void free_kart(voiture_t voiture);

/****************************************************
 * Partie specifique aux fonctions de déplacements.
 *****************************************************/

/**
 * Fait avancer le kart.
 * Augmente progressivement la vitesse du kart jusqu'à atteindre la vitesse MAX.
 */
void avancer(double* vx, double* vy, voiture_t* voiture);

/**
 * Fait reculer le kart.
 * Diminue progressivement la vitesse du kart jusqu'à atteindre la vitesse MIN.
 */
void reculer(double *vx, double*vy, voiture_t* voiture);

/**
 * Fait pivoter le kart.
 * Modifie la rotation du kart pour le faire pivoter sur la gauche ou la droite
 * (rotat = 1 -> Gauche / rotat = 0 -> Droite)
 */
void pivoter(voiture_t* voiture, int rotat, bool mouv);

/**
 * Rend le kart passif.
 * Rapproche progressivement la vitesse de 0.
 * Si la vitesse est négative, celle-ci augmente, sinon elle diminue.
 */
void passiv(double* vx, double* vy, voiture_t* voiture);
