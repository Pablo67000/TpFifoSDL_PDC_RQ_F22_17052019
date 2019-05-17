#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

typedef struct ElementListe{
  SDL_Texture* tex;
  struct ElementListe* suivant;
}Element;

typedef struct ListeRepere{
  Element *debut;
  Element *fin;
  int taille;
}Liste;
//--------------------------------------
void initialisation (Liste *liste);
int insListeVide (Liste *liste, SDL_Texture* tex, SDL_Renderer* renderer);
int insFinListe (Liste *liste, Element *courant, SDL_Texture* tex);
int insListe (Liste *liste, SDL_Texture* tex,int pos);
void affiche (Liste * liste);
int initwindow(SDL_Window* window,char *title,int height, int width);
void loadimg(SDL_Texture* tex,char* path,SDL_Renderer* renderer);
//--------------------------------------
int main(int argc, char *argv[])
{
    Liste* liste;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* tex;
    liste=malloc(sizeof(Liste));
    initwindow(window,"TP",500,500);
    initialisation(liste);
    insListeVide(liste,tex,renderer);
    SDL_Delay(1500);
    affiche(liste);
    return 0;
}

void initialisation (Liste *liste){
  liste->debut = NULL;
  liste->fin = NULL;
  liste->taille = 0;
}

/* insertion dans une liste vide */
int insListeVide (Liste* liste, SDL_Texture* tex, SDL_Renderer* renderer){
  Element *nouveau_element=NULL;
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
    {return -1;}

  loadimg(tex,"./assets/chevreuiljonathan.png",renderer);
  nouveau_element->tex=tex;

  nouveau_element->suivant = NULL; //Le suivant n'existe pas
  liste->debut = nouveau_element; //Le nouvel élément est au début
  liste->fin = nouveau_element; //et à la fin de la liste
  (liste->taille)++; //La taille augmente de 1.
  return 0;
}

/*insertion à la fin de la liste */
int insFinListe (Liste * liste, Element * courant, SDL_Texture* tex){
  Element *nouveau_element;
  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
    return -1;

  nouveau_element->tex=tex;

  courant->suivant = nouveau_element;
  nouveau_element->suivant = NULL;

  liste->fin = nouveau_element;

  liste->taille++;
  return 0;
}

/* insertion à la position demandée */
int insListe (Liste * liste, SDL_Texture* tex, int pos){
  if (liste->taille < 2)
    return -1;
  if (pos < 1 || pos >= liste->taille)
    return -1;


  Element *courant;
  Element *nouveau_element;
  int i;

  if ((nouveau_element = (Element *) malloc (sizeof (Element))) == NULL)
    return -1;

  courant = liste->debut;
  for (i = 1; i < pos; ++i)
    courant = courant->suivant;
  if (courant->suivant == NULL)
    return -1;
  nouveau_element->tex=tex;

  nouveau_element->suivant = courant->suivant; //on met le nouvel élem après le courant
  courant->suivant = nouveau_element; //on met le courant avant le nv elem
  liste->taille++;
  return 0;
}

/* affichage de la liste */
void affiche (Liste * liste){
  Element *courant;
  courant = liste->debut;
  while (courant != NULL){
      printf ("%p - %d\n", courant, courant->tex);
      courant = courant->suivant;
  }
}

void loadimg(SDL_Texture* tex,char* path,SDL_Renderer* renderer){
    SDL_Rect r;
    SDL_Surface *image =NULL ;
// Chargement de l'image
    image = IMG_Load(path) ;
// Gestion des erreurs au niveau du chargement de l'image
    if (!image)
    {
        printf("IMG_Load : %s\n", IMG_GetError()) ;
    }
// Conversion de l'image en texture
    tex = SDL_CreateTextureFromSurface(renderer,image) ;
    SDL_FreeSurface(image) ;
    image = NULL ;
// Règle le rectangle à dessiner selon la taille de l'image source
    r.x = 0 ;
    r.y = 0 ;
// Dessine l'image entiere sur l'écran aux coordonnées x et y
    SDL_QueryTexture(tex,NULL,NULL,&r.w,&r.h) ;
    SDL_RenderCopy(renderer,tex,NULL,&r) ;
}

int initwindow(SDL_Window* window,char *title,int height, int width){
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        printf("Impossible d'initialiser la SDL ! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    else
    {
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf( "La fenetre n'a pas pu etre creee ! SDL_Error: %s\n", SDL_GetError() );
            return 0;
        }
    }
    return 0;
}
