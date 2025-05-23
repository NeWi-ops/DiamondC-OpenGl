#pragma once
#include <vector>
#include <utility>

class MapGenerator {
public:
    MapGenerator(int largeur, int hauteur);
    void genererCarte();
    void afficherCarte() const;

    std::pair<int, int>& getPositionJoueur();
    std::vector<std::vector<int>>& getCarte();
    int getLargeur() const;
    int getHauteur() const;



private:
    int m_largeur;
    int m_hauteur;
    std::vector<std::vector<int> > m_carte;
    std::pair<int, int> m_positionJoueur;

    void appliquerReglesAutomate();
    std::vector<std::pair<int, int> > trouverCasesVides() const;
    void placerElements(int nb, int valeur);
    void trouverPointDeDepartJoueur();
    bool estAssezLoinDesEnnemis(int x, int y, int distanceMin) const;
};

