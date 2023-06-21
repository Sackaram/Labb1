#pragma once

// Viktor Hansson 
// 15/05/22
// Siktar p� C som betyg?

#include "Labyrint.h"
#include "Nod.h"
#include <vector>
#include <iostream>

class Labyrint
{
public:

    Labyrint();

    Labyrint(int bredd, int h�jd);

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
     Printar mazen som �r l�st
    */
    void PrintMazeSolved();

    /*
     L�ser mazen med en scuffed g�-v�nster algoritm, animerad eller ej
    */
    void G�V�nster_L�s(std::string = " ");

    /*
     Skapar en maze med DFS, animerad eller ej
    */
    void DFS_Skapa(std::string  animerad = " ");

    /*
     L�ser mazen med DFS, animerad eller ej
    */
    void DFS_L�s(std::string animerad = " ");

    /*
     Skapar en maze med BFS, animerad eller ej
    */
    void BFS_Skapa(std::string = " ");

    /*
     L�ser mazen med BFS, animerad eller ej
    */
    void BFS_L�s(std::string = " ");

private:
    long BREDD = 11;
    long H�JD = 11;

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
     Markerar alla noder som bes�kta
    */
    void AllaNoderBes�kta();

    /*
     Markerar alla noder som ICKE bes�kta
    */
    void AllaNoderIckeBes�kt();

    /*
     Markerar alla noder som snabbast = false;
    */
    void AllaNoderIckeSnabbast();
};

