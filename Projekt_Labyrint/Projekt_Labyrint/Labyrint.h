#pragma once

// Viktor Hansson 
// 15/05/22
// Siktar på C som betyg?

#include "Labyrint.h"
#include "Nod.h"
#include <vector>
#include <iostream>

class Labyrint
{
public:

    Labyrint();

    Labyrint(int bredd, int höjd);

    /*
     Resettar alla noder i mazen
    */
    void ResetMaze();

    /*
     Printar mazen till konsoll
    */
    void PrintMaze();

    /*
     Printar mazen animerat till konsollen
    */
    void PrintMazeAnimerad(std::vector<std::vector<Nod>>& vect, Nod*& nuvarande);

    /*
     Printar mazen som är löst
    */
    void PrintMazeSolved();

    /*
     Löser mazen med en scuffed gå-vänster algoritm, animerad eller ej
    */
    void GåVänster_Lös(std::string = " ");

    /*
     Skapar en maze med DFS, animerad eller ej
    */
    void DFS_Skapa(std::string  animerad = " ");

    /*
     Löser mazen med DFS, animerad eller ej
    */
    void DFS_Lös(std::string animerad = " ");

    /*
     Skapar en maze med BFS, animerad eller ej
    */
    void BFS_Skapa(std::string = " ");

    /*
     Löser mazen med BFS, animerad eller ej
    */
    void BFS_Lös(std::string = " ");

private:
    long BREDD = 11;
    long HÖJD = 11;

    std::pair<int, int> startNod;
    std::pair<int, int> slutNod;

    void StartNod();
    void SlutNod(); 
    std::vector<std::vector<Nod>> vect;

    /*
     Returnerar ett udda heltal <= a
    */
    int UddaTalUppTill(int a);

    /*
     Kopplar ihop noderna som de ska..
    */
    void KopplaVector();

    /*
     Trycker in noder i vectorn
    */
    void TryckInNoder();

    /*
     Markerar alla noder som besökta
    */
    void AllaNoderBesökta();

    /*
     Markerar alla noder som ICKE besökta
    */
    void AllaNoderIckeBesökt();

    /*
     Markerar alla noder som snabbast = false;
    */
    void AllaNoderIckeSnabbast();
};

