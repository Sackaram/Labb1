#pragma once

// Viktor Hansson 
// 15/05/22
// Siktar på C som betyg?

#include <string>


struct Nod
{
    Nod* nodHöger = nullptr;
    Nod* nodVänster = nullptr;
    Nod* nodUppåt = nullptr;
    Nod* nodNedåt = nullptr;

    Nod* väggHöger = nullptr;
    Nod* väggVänster = nullptr;
    Nod* väggUppåt = nullptr;
    Nod* väggNedåt = nullptr;


    bool kopplingHöger = false;
    bool kopplingVänster = false;
    bool kopplingUppåt = false;
    bool kopplingNedåt = false;

    bool startNod = false;
    bool slutNod = false;

    bool snabbast = false;
    bool besökt = false;

    bool sten = false;
    bool wall = false;
    bool open = false;

    /*
    Returnerar en nod* som pekar på en random granne.
    Kollar inte om en granne finns!
    */
    Nod* RandomGranne();

    /*
    Öppnar en "vägg" mellan två noder
    */
    void ÖppnaKoppling(Nod*& ett, Nod*& två);

    /*
    True om noden har obesökta grannar
    */
    bool HarObesöktaGrannarCreate();

    /*
    True om noden har obesökta grannar
    */
    bool HarObesöktaGrannarSolve();

    /*
    True om noden har obesökta grannar
    */
    bool HarObesöktGranne(std::string riktning);

    /*
    True om noden har vägg(ar) som är open
    */
    bool HarÖppenVägg(std::string riktning);

    std::string ToString();

    std::string ToStringSolved();

    std::string ToStringAnimationSolve();

    Nod();

    /*
    Skapar väggar som ska kunna öppnas
    */
    Nod(bool wall);
    /*
    Skapar väggar som inte ska öppnas
    */
    Nod(bool wall, bool sten);
};

