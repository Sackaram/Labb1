#pragma once

// Viktor Hansson 
// 15/05/22
// Siktar p� C som betyg?

#include <string>


struct Nod
{
    Nod* nodH�ger = nullptr;
    Nod* nodV�nster = nullptr;
    Nod* nodUpp�t = nullptr;
    Nod* nodNed�t = nullptr;

    Nod* v�ggH�ger = nullptr;
    Nod* v�ggV�nster = nullptr;
    Nod* v�ggUpp�t = nullptr;
    Nod* v�ggNed�t = nullptr;


    bool kopplingH�ger = false;
    bool kopplingV�nster = false;
    bool kopplingUpp�t = false;
    bool kopplingNed�t = false;

    bool startNod = false;
    bool slutNod = false;

    bool snabbast = false;
    bool bes�kt = false;

    bool sten = false;
    bool wall = false;
    bool open = false;

    /*
    Returnerar en nod* som pekar p� en random granne.
    Kollar inte om en granne finns!
    */
    Nod* RandomGranne();

    /*
    �ppnar en "v�gg" mellan tv� noder
    */
    void �ppnaKoppling(Nod*& ett, Nod*& tv�);

    /*
    True om noden har obes�kta grannar
    */
    bool HarObes�ktaGrannarCreate();

    /*
    True om noden har obes�kta grannar
    */
    bool HarObes�ktaGrannarSolve();

    /*
    True om noden har obes�kta grannar
    */
    bool HarObes�ktGranne(std::string riktning);

    /*
    True om noden har v�gg(ar) som �r open
    */
    bool Har�ppenV�gg(std::string riktning);

    std::string ToString();

    std::string ToStringSolved();

    std::string ToStringAnimationSolve();

    Nod();

    /*
    Skapar v�ggar som ska kunna �ppnas
    */
    Nod(bool wall);
    /*
    Skapar v�ggar som inte ska �ppnas
    */
    Nod(bool wall, bool sten);
};

