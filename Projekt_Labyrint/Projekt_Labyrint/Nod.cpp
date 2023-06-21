
// Viktor Hansson 
// 15/05/22
// Siktar på C som betyg?

#include "Nod.h"
#include <iostream>
#include <vector>
#include <string>


Nod* Nod::RandomGranne() {
    std::vector<Nod*> t;
    // Om det finns en nod uppåt, och den inte är en sten
    if (nodHöger && !nodHöger->besökt && !nodHöger->sten)
    {
        t.push_back(this->nodHöger);
    }
    if (nodVänster && !nodVänster->besökt && !nodVänster->sten)
    {
        t.push_back(this->nodVänster);
    }
    if (nodUppåt && !nodUppåt->besökt && !nodUppåt->sten)
    {
        t.push_back(this->nodUppåt);
    }
    if (nodNedåt && !nodNedåt->besökt && !nodNedåt->sten)
    {
        t.push_back(this->nodNedåt);
    }
    int k = t.size(); // "The pointer points to memory allocated on the stack"
    int random = rand() % k; // om jag lägger ihop dessa 3 rader i en och samma.... ??
    return t.at(random);       // return t.at(rand() % t.size());
}

void Nod::ÖppnaKoppling(Nod*& ett, Nod*& två) {
    if (ett->startNod) {} // Öppnar kopplingen mellan två noder, startnod har ingen "vägg" att öppna
    else if (ett->nodHöger == två) { ett->väggHöger->open = true; }
    else if (ett->nodVänster == två) { ett->väggVänster->open = true; }
    else if (ett->nodUppåt == två && !ett->nodUppåt->slutNod) { ett->väggUppåt->open = true; }
    else if (ett->nodNedåt == två) { ett->väggNedåt->open = true; }
}

bool Nod::HarObesöktaGrannarCreate() {
    //  Om nod till x finns OCH x inte är besökt och noden inte är sten
    if (nodHöger && !nodHöger->besökt && !nodHöger->sten ||
        nodVänster && !nodVänster->besökt && !nodVänster->sten ||
        nodUppåt && !nodUppåt->besökt && !nodUppåt->sten ||
        nodNedåt && !nodNedåt->besökt && !nodNedåt->sten)
    {
        return true;
    }
    else { return false; }
}

bool Nod::HarObesöktaGrannarSolve() {
    //  Om nod till x finns OCH x inte är besökt och noden inte är sten
    if (startNod || nodUppåt && nodUppåt->slutNod) { return true; }
    else if (nodHöger && !nodHöger->besökt && väggHöger && väggHöger->open ||
        nodVänster && !nodVänster->besökt && väggVänster && väggVänster->open ||
        nodUppåt && !nodUppåt->besökt && väggUppåt && väggUppåt->open ||
        nodNedåt && !nodNedåt->besökt && väggNedåt && väggNedåt->open)
    { return true; }
    else { return false; }
}

bool Nod::HarObesöktGranne(std::string riktning) {
    if (riktning == "Uppåt")
    {   // om det finns en nod uppåt och den inte är besökt
        if (nodUppåt && !nodUppåt->besökt) { return true; }
    }
    else if (riktning == "Höger")
    {
        if (nodHöger && !nodHöger->besökt) { return true; }
    }
    else if (riktning == "Nedåt")
    {
        if (nodNedåt && !nodNedåt->besökt) { return true; }
    }
    else if (riktning == "Vänster")
    {
        if (nodVänster && !nodVänster->besökt) { return true; }
    }
    return false;
}

bool Nod::HarÖppenVägg(std::string riktning) {
    if (riktning == "Uppåt")
    {   // om det finns en vägg uppåt och den är öppen
        if (väggUppåt && väggUppåt->open) { return true; }
    }
    else if (riktning == "Höger")
    {
        if (väggHöger && väggHöger->open) { return true; }
    }
    else if (riktning == "Nedåt")
    {
        if (väggNedåt && väggNedåt->open) { return true; }
    }
    else if (riktning == "Vänster")
    {
        if (väggVänster && väggVänster->open) { return true; }
    }
    return false;
}

std::string Nod::ToString() {
    if (startNod) { return "S"; }
    else if (slutNod) { return "E"; }
    else if (sten || wall && !open) { return "#"; }
    else if (besökt && snabbast)
    {
        return ("\x1B[31mo\033[0m");
    }
    else if (snabbast)
    {
        return ("\x1B[32mo\033[0m");
    }
    else { return " "; }
}

std::string Nod::ToStringSolved() {
    if (startNod) { return "S"; }
    else if (slutNod) { return "E"; }
    else if (besökt && !snabbast) { return ("\x1B[31mo\033[0m"); }
    else if (snabbast) { return ("\x1B[32mo\033[0m"); }
    else if (sten || wall && !open) { return "#"; }
    else { return " "; }
}

std::string Nod::ToStringAnimationSolve() {
    if (startNod) { return "S"; }
    else if (slutNod) { return "E"; }
    else if (besökt && !snabbast) { return ("\x1B[31mo\033[0m"); }
    else if (besökt && snabbast) { return ("\x1B[32mo\033[0m"); }

    else if (wall && !open)
    {
        return "#";
    }
    else
    {
        return " ";
    }
}

Nod::Nod() { }

Nod::Nod(bool wall) {
    this->wall = wall;
}

// väggar som inte kan öppnas, ligger runt om, och diagonalt mot noderna
Nod::Nod(bool wall, bool sten) {
    this->wall = wall;
    this->sten = sten;
}

