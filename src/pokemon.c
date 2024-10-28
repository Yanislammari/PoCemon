#include <stdlib.h>
#include <string.h>
#include "includes/database.h"
#include "includes/pokemon.h"

Pokemon* get_pokemons(int* count) {
    sqlite3* db = init_database();
    char* sql = "SELECT id, nom, pv, atk, def, vitesse, type, sprite FROM Pokemon";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    Pokemon* pokemons = malloc(sizeof(Pokemon) * 100);
    int index = 0;

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        char* nom = (char*) sqlite3_column_text(stmt, 1);
        int pv = sqlite3_column_int(stmt, 2);
        int atk = sqlite3_column_int(stmt, 3);
        int def = sqlite3_column_int(stmt, 4);
        int vitesse = sqlite3_column_int(stmt, 5);
        char* type = (char*) sqlite3_column_text(stmt, 6);
        char* sprite = (char*) sqlite3_column_text(stmt, 7);

        pokemons[index].id = id;
        pokemons[index].nom = strdup(nom);
        pokemons[index].current_pv = pv;
        pokemons[index].total_pv = pv;
        pokemons[index].atk = atk;
        pokemons[index].def = def;
        pokemons[index].vitesse = vitesse;
        pokemons[index].type = strdup(type);
        pokemons[index].sprite = strdup(sprite);

        index++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    *count = index;
    return pokemons;
}

void free_pokemons(Pokemon* pokemons, int count) {
    for(int i = 0; i < count; i++) {
        free(pokemons[i].nom);
        free(pokemons[i].type);
        free(pokemons[i].sprite);
    }
    free(pokemons);
}