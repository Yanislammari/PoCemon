CREATE TABLE Pokemon(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom VARCHAR(20) NOT NULL,
    pv INT NOT NULL,
    atk INT NOT NULL,
    def INT NOT NULL,
    vitesse INT NOT NULL,
    type VARCHAR(10) NOT NULL,
    sprite VARCHAR(255)
);
INSERT INTO Pokemon(nom, pv, atk, def, vitesse, type, sprite) VALUES
('Bulbizarre', 90, 49, 24, 45, 'Plante', '../assets/sprite/pokemon/bulbizarre.png'),
('Salamèche', 78, 52, 21, 65, 'Feu', '../assets/sprite/pokemon/salameche.png'),
('Carapuce', 88, 48, 32, 43, 'Eau', '../assets/sprite/pokemon/carapuce.png'),
('Pikachu', 70, 55, 20, 90, 'Électrik', '../assets/sprite/pokemon/pikachu.png'),
('Sabelette', 80, 50, 25, 90, 'Sol', '../assets/sprite/pokemon/sabelette.png'),
('Miaouss', 80, 45, 35, 90, 'Normal', '../assets/sprite/pokemon/miaouss.png'),
('Caninos', 90, 51, 20, 60, 'Feu', '../assets/sprite/pokemon/caninos.png'),
('Ptitard', 80, 50, 20, 90, 'Eau', '../assets/sprite/pokemon/ptitard.png'),
('Abra', 75, 50, 15, 90, 'Psy', '../assets/sprite/pokemon/abra.png'),
('Canarticho', 104, 40, 25, 60, 'Vol', '../assets/sprite/pokemon/canarticho.png'),
('Magnéti', 70, 35, 35, 45, 'Acier', '../assets/sprite/pokemon/magneti.png');

CREATE TABLE Sauvegarde(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom VARCHAR(10) NOT NULL,
    x INT NOT NULL,
    y INT NOT NULL
);

CREATE TABLE Pokemon_Sauvegarde(
    id_pokemon INT,
    id_sauvegarde INT,
    current_pv INT NOT NULL,
    total_pv INT NOT NULL,
    sprite VARCHAR(255),
    PRIMARY KEY (id_pokemon, id_sauvegarde),
    FOREIGN KEY (id_pokemon) REFERENCES Pokemon(id),
    FOREIGN KEY (id_sauvegarde) REFERENCES Sauvegarde(id)
);