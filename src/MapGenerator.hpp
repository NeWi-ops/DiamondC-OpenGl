#pragma once
#include <vector>
#include <utility>
#include <queue>
// #include "Joueur.hpp"
class Joueur; // Forward declaration pour éviter les dépendances circulaires

class MapGenerator {
public:
    MapGenerator(int largeur, int hauteur);
    void genererCarte();
    void afficherCarte() const;

    std::pair<int, int>& getPositionJoueur();
    const std::vector<std::vector<int>>& getCarte() const;
    std::vector<std::vector<int>>& getCarte();
    int getLargeur() const;
    int getHauteur() const;
    std::vector<std::pair<int, int>>& getPositionEnnemis();
    void deplacerEnnemis(const std::vector<std::vector<int>>& flow_field, Joueur& joueur);

    //void deplacerEnnemis(const std::vector<std::vector<int>>& flow_field, Joueur& joueur, float delta);
    std::vector<std::vector<int>> generer_le_flow_field();
    std::vector<std::pair<float, float>> m_positionEnnemisFloat;

//const std::vector<std::pair<float, float>>& getPositionEnnemisFloat() const { return m_positionEnnemisFloat; };



private:
    int m_largeur;
    int m_hauteur;
    std::vector<std::vector<int> > m_carte;
    std::pair<int, int> m_positionJoueur;
    std::vector<std::pair<int, int> > m_positionEnnemis;

    void appliquerReglesAutomate();
    std::vector<std::pair<int, int> > trouverCasesVides() const;
    void placerElements(int nb, int valeur);
    void trouverPointDeDepartJoueur();
    bool estAssezLoinDesEnnemis(int x, int y, int distanceMin) const;

    std::vector<int> m_casesSousEnnemis;
    
};

