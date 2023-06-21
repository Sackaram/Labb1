
// Viktor Hansson 
// 15/05/22
// Siktar p� C som betyg?

#include "Nod.h"
#include <iostream>
#include <vector>
#include <string>


Nod* Nod::RandomGranne() {
    std::vector<Nod*> t;
    // Om det finns en nod upp�t, och den inte �r en sten
    if (nodH�ger && !nodH�ger->bes�kt && !nodH�ger->sten)
    {
        t.push_back(this->nodH�ger);
    }
    if (nodV�nster && !nodV�nster->bes�kt && !nodV�nster->sten)
    {
        t.push_back(this->nodV�nster);
    }
    if (nodUpp�t && !nodUpp�t->bes�kt && !nodUpp�t->sten)
    {
        t.push_back(this->nodUpp�t);
    }
    if (nodNed�t && !nodNed�t->bes�kt && !nodNed�t->sten)
    {
        t.push_back(this->nodNed�t);
    }
    int k = t.size(); // "The pointer points to memory allocated on the stack"
    int random = rand() % k; // om jag l�gger ihop dessa 3 rader i en och samma.... ??
    return t.at(random);       // return t.at(rand() % t.size());
}

void Nod::�ppnaKoppling(Nod*& ett, Nod*& tv�) {
    if (ett->startNod) {} // �ppnar kopplingen mellan tv� noder, startnod har ingen "v�gg" att �ppna
    else if (ett->nodH�ger == tv�) { ett->v�ggH�ger->open = true; }
    else if (ett->nodV�nster == tv�) { ett->v�ggV�nster->open = true; }
    else if (ett->nodUpp�t == tv� && !ett->nodUpp�t->slutNod) { ett->v�ggUpp�t->open = true; }
    else if (ett->nodNed�t == tv�) { ett->v�ggNed�t->open = true; }
}

bool Nod::HarObes�ktaGrannarCreate() {
    //  Om nod till x finns OCH x inte �r bes�kt och noden inte �r sten
    if (nodH�ger && !nodH�ger->bes�kt && !nodH�ger->sten ||
        nodV�nster && !nodV�nster->bes�kt && !nodV�nster->sten ||
        nodUpp�t && !nodUpp�t->bes�kt && !nodUpp�t->sten ||
        nodNed�t && !nodNed�t->bes�kt && !nodNed�t->sten)
    {
        return true;
    }
    else { return false; }
}

bool Nod::HarObes�ktaGrannarSolve() {
    //  Om nod till x finns OCH x inte �r bes�kt och noden inte �r sten
    if (startNod || nodUpp�t && nodUpp�t->slutNod) { return true; }
    else if (nodH�ger && !nodH�ger->bes�kt && v�ggH�ger && v�ggH�ger->open ||
        nodV�nster && !nodV�nster->bes�kt && v�ggV�nster && v�ggV�nster->open ||
        nodUpp�t && !nodUpp�t->bes�kt && v�ggUpp�t && v�ggUpp�t->open ||
        nodNed�t && !nodNed�t->bes�kt && v�ggNed�t && v�ggNed�t->open)
    { return true; }
    else { return false; }
}

bool Nod::HarObes�ktGranne(std::string riktning) {
    if (riktning == "Upp�t")
    {   // om det finns en nod upp�t och den inte �r bes�kt
        if (nodUpp�t && !nodUpp�t->bes�kt) { return true; }
    }
    else if (riktning == "H�ger")
    {
        if (nodH�ger && !nodH�ger->bes�kt) { return true; }
    }
    else if (riktning == "Ned�t")
    {
        if (nodNed�t && !nodNed�t->bes�kt) { return true; }
    }
    else if (riktning == "V�nster")
    {
        if (nodV�nster && !nodV�nster->bes�kt) { return true; }
    }
    return false;
}

bool Nod::Har�ppenV�gg(std::string riktning) {
    if (riktning == "Upp�t")
    {   // om det finns en v�gg upp�t och den �r �ppen
        if (v�ggUpp�t && v�ggUpp�t->open) { return true; }
    }
    else if (riktning == "H�ger")
    {
        if (v�ggH�ger && v�ggH�ger->open) { return true; }
    }
    else if (riktning == "Ned�t")
    {
        if (v�ggNed�t && v�ggNed�t->open) { return true; }
    }
    else if (riktning == "V�nster")
    {
        if (v�ggV�nster && v�ggV�nster->open) { return true; }
    }
    return false;
}

std::string Nod::ToString() {
    if (startNod) { return "S"; }
    else if (slutNod) { return "E"; }
    else if (sten || wall && !open) { return "#"; }
    else if (bes�kt && snabbast)
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
    else if (bes�kt && !snabbast) { return ("\x1B[31mo\033[0m"); }
    else if (snabbast) { return ("\x1B[32mo\033[0m"); }
    else if (sten || wall && !open) { return "#"; }
    else { return " "; }
}

std::string Nod::ToStringAnimationSolve() {
    if (startNod) { return "S"; }
    else if (slutNod) { return "E"; }
    else if (bes�kt && !snabbast) { return ("\x1B[31mo\033[0m"); }
    else if (bes�kt && snabbast) { return ("\x1B[32mo\033[0m"); }

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

// v�ggar som inte kan �ppnas, ligger runt om, och diagonalt mot noderna
Nod::Nod(bool wall, bool sten) {
    this->wall = wall;
    this->sten = sten;
}

