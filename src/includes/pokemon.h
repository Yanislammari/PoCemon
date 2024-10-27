#ifndef POCEMON_POKEMON_H
#define POCEMON_POKEMON_H

typedef struct{
    int id;
    char* nom;
    int current_pv;
    int total_pv;
    int atk;
    int def;
    int vitesse;
    char* type;
    char* sprite;
} Pokemon;

Pokemon* get_pokemons(int* count);
void free_pokemons(Pokemon* pokemons, int count);

#endif
