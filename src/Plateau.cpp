#include "Plateau.h"
#include <iostream>
#include <errno.h>
#include <string.h>
#include <cassert>

using namespace std;

// Constructeur
Plateau::Plateau() {
    initialiserPlateau();
    initialiserPriopriete();
    initialiserCartesExam();
    initialiserCartesVieEtu();
}

// Destructeur
Plateau::~Plateau() {
    for (size_t t = 0; t < TodoProprietes.size(); ++t) {
        delete TodoProprietes[t];
    }
    for (size_t i = 0; i < cases.size(); ++i) {
        delete cases[i];
    }
    for (size_t i = 0; i < Examens.size(); ++i) {
        delete Examens[i];
    }
    for (size_t i = 0; i < VieEtu.size(); ++i) {
        delete VieEtu[i];
    }
    Examens.clear();
    VieEtu.clear();
    cases.clear();
    TodoProprietes.clear();
}

// Initialise le plateau Monopoly de 40 cases
void Plateau::initialiserPlateau() {
    string noms[40] = {
        "Depart",                     // 0

        "Cafétéria Déambulatoire",    // Marron
        "Examens",                    // Community Chest
        "Cafétéria Astrée",           // Marron
        "Partiel Surprise",           // Taxe

        "Arrêt Université Lyon 1",    // Arrêt de Tram

        "AML Lyon 1",                 // Bleu Clair
        "Vie Étudiante",              // Chance
        "BDE STAPS Lyon 1",           // Bleu Clair
        "BDE Santé Lyon 1",           // Bleu Clair

        "Rattrapages",                // Prison

        "Licence Mathématiques",      // Rose
        "Restaurant Universitaire",   // Compagnie
        "Licence Informatique",       // Rose
        "Licence PCSI",               // Rose

        "Arrêt Gaston Berger",        // Arrêt de Tram
        
        "BUT Génie Civil", 
        "Examens",  
        "BUT Génie Électrique",       // Orange
        "BUT Informatique",           // Orange
        
                         
                   

        "Parc Quai43",                // Parking

        "Campus La Doua",             // Rouge
        "Vie Étudiante",              // Chance
        "Campus Bourg-en-Bresse",         // Rouge
        "Campus Rockefeller",     // Rouge
 
        "Arrêt INSA",                 // Arrêt de Tram

        "Polytech Lyon",              // Jaune
        "ISPB – Pharmacie ",          // Jaune
        "Distributeur Automatique",   // Compagnie
        "Master Informatique",        // Jaune

        "Allez en Rattrapages",      // Allez en Prison

        "Centre de Recherche en Neurosciences", // Vert
        "Laboratoire de Biométrie et Biologie Évolutive",     // Vert
        "Examens",                    // Community Chest
        "Institut Lumière Matière",   // Vert
        

        "Arrêt IUT Feyssine",        // Arrêt de Tram

        "Vie Étudiante",              // Chance
        "Présidence de l’Université", // Bleu Foncé
        "CVEC",                       // Taxe
        "Conseil d’Administration Lyon 1",    // Bleu Foncé
    };
    for (int i = 0; i < 40; ++i) {
        cout << "Creation case " << noms[i] << " n°" << i << endl;
        cases.push_back(new Case(noms[i] , i ));
    }
}

void Plateau::initialiserCartesExam() {
    Examens.push_back(new Carte("Réussis ton examen : avance de 3 cases", 3, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Erreur d'examen : recule de 2 cases", -2, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Bonus de révision : avance de 1 case", 1, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Perds ton sujet : recule de 1 case", -1, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Rattrapages : va en prison", 0, Carte::PRISON));

    Examens.push_back(new Carte("Major de promo : gagne 300€", 300, Carte::ARGENT));
    Examens.push_back(new Carte("Copie ratée : perds 150€", -150, Carte::ARGENT));
    Examens.push_back(new Carte("Prof absent : rien ne se passe", 0, Carte::AVANTAGE));
    Examens.push_back(new Carte("Examen facile : avance de 2 cases", 2, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Stress total : recule de 3 cases", -3, Carte::DEPLACEMENT));

    Examens.push_back(new Carte("Fraude détectée : va en prison", 0, Carte::PRISON));
    Examens.push_back(new Carte("Mention bien : gagne 200€", 200, Carte::ARGENT));
    Examens.push_back(new Carte("Révision intense : avance de 4 cases", 4, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Sujet incompris : recule de 2 cases", -2, Carte::DEPLACEMENT));
    Examens.push_back(new Carte("Les jurys vous valide votre semestres n'allez pas au rattrapages", 0, Carte::LIBERATION));
}

void Plateau::initialiserCartesVieEtu() {
    VieEtu.push_back(new Carte("Fête étudiante : avance de 2 cases", 2, Carte::DEPLACEMENT));
    VieEtu.push_back(new Carte("Maladie soudaine : recule de 3 cases", -3, Carte::DEPLACEMENT));
    VieEtu.push_back(new Carte("Stage réussi : gagne 200€", 200, Carte::ARGENT));
    VieEtu.push_back(new Carte("Panne de vélo : recule de 1 case", -1, Carte::DEPLACEMENT));

    VieEtu.push_back(new Carte("Job étudiant : gagne 100€", 100, Carte::ARGENT));
    VieEtu.push_back(new Carte("Amende transport : perds 50€", -50, Carte::ARGENT));
    VieEtu.push_back(new Carte("Soirée réussie : avance de 1 case", 1, Carte::DEPLACEMENT));
    VieEtu.push_back(new Carte("Nuit blanche : recule de 2 cases", -2, Carte::DEPLACEMENT));

    VieEtu.push_back(new Carte("Bourse reçue : gagne 300€", 300, Carte::ARGENT));
    VieEtu.push_back(new Carte("Loyer à payer : perds 200€", -200, Carte::ARGENT));
    VieEtu.push_back(new Carte("Colocation sympa : gagne 50€", 50, Carte::ARGENT));
    VieEtu.push_back(new Carte("Retard en cours : recule de 1 case", -1, Carte::DEPLACEMENT));
}

void Plateau::initialiserPriopriete()
{
    // sécurité
    if (cases.size() != 40) {
        cerr << "Erreur Cases pas initialisée : " << strerror(errno) << endl;
        return;
    }

    // ===== MARRON =====
    Propriete* p1 = new Propriete(cases[1], 100, 25, 1, Propr, MARRON);
    TodoProprietes.push_back(p1);
    cases[1]->setPropriete(p1);

    Propriete* p2 = new Propriete(cases[3], 100, 25, 1, Propr, MARRON);
    TodoProprietes.push_back(p2);
    cases[3]->setPropriete(p2);

    // ===== BLEU CIEL =====
    Propriete* p3 = new Propriete(cases[6], 120, 30, 1, Propr, BLEUCIEL);
    TodoProprietes.push_back(p3);
    cases[6]->setPropriete(p3);

    Propriete* p4 = new Propriete(cases[8], 120, 30, 1, Propr, BLEUCIEL);
    TodoProprietes.push_back(p4);
    cases[8]->setPropriete(p4);

    Propriete* p5 = new Propriete(cases[9], 120, 30, 1, Propr, BLEUCIEL);
    TodoProprietes.push_back(p5);
    cases[9]->setPropriete(p5);

    // ===== ROSE =====
    Propriete* p6 = new Propriete(cases[11], 140, 35, 1, Propr, ROSE);
    TodoProprietes.push_back(p6);
    cases[11]->setPropriete(p6);

    Propriete* p7 = new Propriete(cases[13], 140, 35, 1, Propr, ROSE);
    TodoProprietes.push_back(p7);
    cases[13]->setPropriete(p7);

    Propriete* p8 = new Propriete(cases[14], 140, 35, 1, Propr, ROSE);
    TodoProprietes.push_back(p8);
    cases[14]->setPropriete(p8);

    // ===== ORANGE =====
    Propriete* p9 = new Propriete(cases[16], 160, 40, 1, Propr, ORANGE);
    TodoProprietes.push_back(p9);
    cases[16]->setPropriete(p9);

    Propriete* p10 = new Propriete(cases[18], 160, 40, 1, Propr, ORANGE);
    TodoProprietes.push_back(p10);
    cases[18]->setPropriete(p10);

    Propriete* p11 = new Propriete(cases[19], 160, 40, 1, Propr, ORANGE);
    TodoProprietes.push_back(p11);
    cases[19]->setPropriete(p11);

    // ===== ROUGE =====
    Propriete* p12 = new Propriete(cases[21], 180, 45, 1, Propr, ROUGE);
    TodoProprietes.push_back(p12);
    cases[21]->setPropriete(p12);

    Propriete* p13 = new Propriete(cases[23], 180, 45, 1, Propr, ROUGE);
    TodoProprietes.push_back(p13);
    cases[23]->setPropriete(p13);

    Propriete* p14 = new Propriete(cases[24], 180, 45, 1, Propr, ROUGE);
    TodoProprietes.push_back(p14);
    cases[24]->setPropriete(p14);

    // ===== JAUNE =====
    Propriete* p15 = new Propriete(cases[26], 200, 50, 1, Propr, JAUNE);
    TodoProprietes.push_back(p15);
    cases[26]->setPropriete(p15);

    Propriete* p16 = new Propriete(cases[27], 200, 50, 1, Propr, JAUNE);
    TodoProprietes.push_back(p16);
    cases[27]->setPropriete(p16);

    Propriete* p17 = new Propriete(cases[29], 200, 50, 1, Propr, JAUNE);
    TodoProprietes.push_back(p17);
    cases[29]->setPropriete(p17);

    // ===== VERT =====
    Propriete* p18 = new Propriete(cases[31], 220, 55, 1, Propr, VERT);
    TodoProprietes.push_back(p18);
    cases[31]->setPropriete(p18);

    Propriete* p19 = new Propriete(cases[32], 220, 55, 1, Propr, VERT);
    TodoProprietes.push_back(p19);
    cases[32]->setPropriete(p19);

    Propriete* p20 = new Propriete(cases[34], 220, 55, 1, Propr, VERT);
    TodoProprietes.push_back(p20);
    cases[34]->setPropriete(p20);

    // ===== BLEU FONCE =====
    Propriete* p21 = new Propriete(cases[37], 250, 60, 1, Propr, BLEUFONCE);
    TodoProprietes.push_back(p21);
    cases[37]->setPropriete(p21);

    Propriete* p22 = new Propriete(cases[39], 300, 75, 1, Propr, BLEUFONCE);
    TodoProprietes.push_back(p22);
    cases[39]->setPropriete(p22);

    // ===== GARES =====
    int gares[] = {5, 15, 25, 35};
    for(int i=0;i<4;i++) {
        Propriete* g = new Propriete(cases[gares[i]], 200, 25, 1, Gares);
        TodoProprietes.push_back(g);
        cases[gares[i]]->setPropriete(g);
    }

    // ===== SERVICES PUBLICS =====
    int services[] = {12, 28};
    for(int i=0;i<2;i++) {
        Propriete* s = new Propriete(cases[services[i]], 150, 40, 1, ServicePublique);
        TodoProprietes.push_back(s);
        cases[services[i]]->setPropriete(s);
    }

    cout << "Toutes les propriétés ont été initialisées et associées aux cases !" << endl;
}


const Case* Plateau::getCase(int index) const {
    if (index < 0 || index >= (int)cases.size()) {
        return nullptr;
    }
    return cases[index];
}

Case* Plateau::getCase(int index) {
    if (index < 0 || index >= (int)cases.size()) {
        return nullptr;
    }
    return cases[index];
}

int Plateau::getNbCases() const {
    return cases.size();
}

const vector<Carte*>& Plateau::getExamens() const { return Examens; }
const vector<Carte*>& Plateau::getVieEtu() const { return VieEtu; }

void Plateau::TestRegression() {
    cout << "=== TestRegression Plateau ===" << endl;
    Plateau p;

    assert(p.getCase(0) != nullptr);
    assert(p.getCase(39) != nullptr);

    assert(p.getCase(0)->getNom() == "Depart");
    assert(p.getCase(10)->getNom() == "Rattrapages");
    assert(p.getCase(30)->getNom() == "Allez en Rattrapages");
    assert(p.getCase(39)->getNom() == "Présidence de l’Université");

    assert(p.getCase(1)->getNom() == "Cafétéria Déambulatoire");
    assert(p.getCase(3)->getNom() == "Cafétéria Astrée");
    assert(p.getCase(6)->getNom() == "AML Lyon 1");
    assert(p.getCase(11)->getNom() == "Licence Mathématiques");
    assert(p.getCase(16)->getNom() == "BUT Informatique");
    assert(p.getCase(21)->getNom() == "Campus La Doua");
    assert(p.getCase(26)->getNom() == "Master Informatique");
    assert(p.getCase(31)->getNom() == "Institut Lumière Matière");
    assert(p.getCase(38)->getNom() == "CVEC");

    assert(p.getCase(7)->getNom() == "Vie Étudiante");
    assert(p.getCase(2)->getNom() == "Examens");
    assert(p.getCase(18)->getNom() == "Examens");
    assert(p.getCase(32)->getNom() == "Laboratoire de Biométrie et Biologie Évolutive");
    assert(p.getCase(37)->getNom() == "Conseil d’Administration Lyon 1");

    assert(p.getCase(-1) == nullptr);
    assert(p.getCase(40) == nullptr);
    assert(p.getCase(100) == nullptr);

    cout << "Tous les tests de regression Plateau ont reussi !" << endl;
}