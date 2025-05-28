void init_mechant(int ngh);

void afficher_mechant();

SDL_Rect setRectMechant(SDL_Rect Point);

void deplacement_mechant();

int goM(int direction);

void regulation_vitesse(int i);

void mechantMort();

void contact();

void addChamp(int x, int y);
void grow();

void addBowser(int x, int y);
int goB(int direction);
void contactB();