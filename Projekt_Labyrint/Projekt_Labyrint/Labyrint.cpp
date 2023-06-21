
// Viktor Hansson 
// 15/05/22
// Siktar p� C som betyg?

#include "Labyrint.h"
#include "Nod.h"
#include <vector>
#include <iostream>
#include <thread>
#include <string>


Labyrint::Labyrint() {
    StartNod();
    SlutNod();
}

Labyrint::Labyrint(int bredd, int h�jd) {

    BREDD = bredd;
    H�JD = h�jd;
    StartNod();
    SlutNod();
}

// anv�nds f�r att jag anv�nder bara en 'labyrint' i Main()
void Labyrint::ResetMaze() {
    BREDD = 11;
    H�JD = 11;
    StartNod();
    SlutNod();
    vect.clear();
    TryckInNoder();
    KopplaVector();
    AllaNoderIckeBes�kt();
}



void Labyrint::PrintMaze() {

    for (size_t i = 0; i < H�JD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            
            std::cout << vect[i][j].ToString();
            
        }
        std::cout << std::endl;
    }
}

void Labyrint::PrintMazeAnimerad(std::vector<std::vector<Nod>>& vect, Nod*& nuvarande) {
    for (size_t i = 0; i < H�JD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {                                // -> Detta s� att sista eller f�rsta noden inte representeras som * 
            if (&vect[i][j] == nuvarande && vect[i][j].nodUpp�t && !vect[i][j].nodUpp�t->slutNod && !&vect[i][j].startNod)
            {
                std::cout << "*";
            }
            else
            {
                std::cout << vect[i][j].ToStringAnimationSolve();
            }
        }
        std::cout << std::endl;
    }
}

void Labyrint::PrintMazeSolved() {
    for (size_t i = 0; i < H�JD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            std::cout << vect[i][j].ToStringSolved();
        }
        std::cout << std::endl;
    }
}

void Labyrint::G�V�nster_L�s(std::string animerad) {
    AllaNoderIckeBes�kt();
    AllaNoderIckeSnabbast();

    Nod* nuvarandeNod;
    nuvarandeNod = &vect[startNod.first][startNod.second];

    std::vector<Nod*> stack;
    stack.push_back(nuvarandeNod);

    while (!stack.empty())
    {
        nuvarandeNod = stack.back();  // nuvarandeNod = startnoden
        nuvarandeNod->bes�kt = true;

        if (animerad == "Animerad")
        {
            system("CLS");
            PrintMazeAnimerad(vect, nuvarandeNod);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (nuvarandeNod->slutNod) { break; }

        if (nuvarandeNod->HarObes�ktaGrannarSolve())
        {
            if (nuvarandeNod->HarObes�ktGranne("Upp�t") && nuvarandeNod->Har�ppenV�gg("Upp�t") ||
                nuvarandeNod->nodUpp�t && nuvarandeNod->nodUpp�t->slutNod ||
                nuvarandeNod->nodUpp�t && nuvarandeNod->startNod)
            {
                stack.push_back(nuvarandeNod->nodUpp�t);
            }
            else if (nuvarandeNod->HarObes�ktGranne("V�nster") && nuvarandeNod->Har�ppenV�gg("V�nster"))
            {
                stack.push_back(nuvarandeNod->nodV�nster);
            }
            else if (nuvarandeNod->HarObes�ktGranne("H�ger") && nuvarandeNod->Har�ppenV�gg("H�ger"))
            {
                stack.push_back(nuvarandeNod->nodH�ger);
            }
            else if (nuvarandeNod->HarObes�ktGranne("Ned�t") && nuvarandeNod->Har�ppenV�gg("Ned�t"))
            {
                stack.push_back(nuvarandeNod->nodNed�t);
            }
        }
        else
        {
            stack.pop_back();
        }
    }
}

void Labyrint::DFS_Skapa(std::string animerad) {
   
    TryckInNoder();
    KopplaVector();

    std::vector<Nod*> stack;
    Nod* nuvarandeNod;
    nuvarandeNod = &vect[startNod.first][startNod.second]; // nuvarande nod pekar p� start noden

    nuvarandeNod->bes�kt = true;
    stack.push_back(nuvarandeNod);

    while (!stack.empty())
    {
        nuvarandeNod = stack.back();
        stack.pop_back();

        if (nuvarandeNod->startNod)
        {
            nuvarandeNod = nuvarandeNod->nodUpp�t;
            nuvarandeNod->bes�kt = true;
            stack.push_back(nuvarandeNod);
        }
        else if (nuvarandeNod->HarObes�ktaGrannarCreate())
        {
            stack.push_back(nuvarandeNod);
            Nod* granne;
            granne = nuvarandeNod->RandomGranne();
            nuvarandeNod->�ppnaKoppling(nuvarandeNod, granne);
            granne->bes�kt = true;
            stack.push_back(granne);

            if (animerad == "Animerad")
            {
                system("CLS");
                PrintMaze();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }
}

void Labyrint::DFS_L�s(std::string animerad) {
    Nod* nuvarandeNod;
    nuvarandeNod = &vect[startNod.first][startNod.second]; // nuvarande nod pekar p� start noden
    std::vector<Nod*> stack;
    stack.push_back(nuvarandeNod);

    AllaNoderIckeBes�kt();
    AllaNoderIckeSnabbast();
    nuvarandeNod->bes�kt = true;


    while (stack.size() != 0)
    {
        nuvarandeNod = stack.back();
        stack.pop_back();
        nuvarandeNod->bes�kt = true;

        if (animerad == "Animerad")
        {
            system("CLS");
            PrintMazeAnimerad(vect, nuvarandeNod);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (nuvarandeNod->slutNod )
        {
            stack.push_back(nuvarandeNod);
            for (size_t i = 0; i < stack.size() - 1; i++)
            {
                stack[i]->snabbast = true;
            }
            if (animerad == "Animerad") { system("CLS"); PrintMazeAnimerad(vect, nuvarandeNod); }
            break;
        }
        else
        {
            if (nuvarandeNod->HarObes�ktaGrannarSolve())
            {
                stack.push_back(nuvarandeNod);
                
                std::vector<Nod*> temp;
                if (nuvarandeNod->HarObes�ktGranne("Upp�t") && nuvarandeNod->Har�ppenV�gg("Upp�t") ||
                    nuvarandeNod->nodUpp�t && nuvarandeNod->nodUpp�t->slutNod ||
                    nuvarandeNod->nodUpp�t && nuvarandeNod->startNod)
                {
                    temp.push_back(nuvarandeNod->nodUpp�t);
                }
                else if (nuvarandeNod->HarObes�ktGranne("H�ger") && nuvarandeNod->Har�ppenV�gg("H�ger"))
                {
                    temp.push_back(nuvarandeNod->nodH�ger);
                }
                else if (nuvarandeNod->HarObes�ktGranne("Ned�t") && nuvarandeNod->Har�ppenV�gg("Ned�t"))
                {
                    temp.push_back(nuvarandeNod->nodNed�t);
                }
                else if (nuvarandeNod->HarObes�ktGranne("V�nster") && nuvarandeNod->Har�ppenV�gg("V�nster"))
                {
                    temp.push_back(nuvarandeNod->nodV�nster);
                }

                while (!temp.empty())
                {
                    int k = rand() % temp.size();
                    stack.push_back(temp.at(k));
                    temp.erase(temp.begin() + k);
                }
                
            }
        }
    }
}

void Labyrint::BFS_L�s(std::string animerad) {

    AllaNoderIckeBes�kt();
    AllaNoderIckeSnabbast();

    Nod* nuvarandeNod;
    std::vector<Nod*> stack;

    nuvarandeNod = vect[startNod.first][startNod.second].nodUpp�t;
    stack.push_back(nuvarandeNod);


    while (!stack.empty())
    {
        if (animerad == "Animerad")
        {
            system("CLS");
            PrintMazeAnimerad(vect, nuvarandeNod);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        for (Nod* x : stack) {

            nuvarandeNod = stack.front();
            nuvarandeNod->bes�kt = true;
            
            /*stack.erase(stack.begin());*/
            if (nuvarandeNod->nodUpp�t && nuvarandeNod->nodUpp�t->slutNod)
            {
                stack.clear();
                break;
            }
            if (nuvarandeNod->HarObes�ktaGrannarSolve())
            {
                // ta bort N fr�n S
                for (size_t i = 0; i < stack.size(); i++)
                {
                    if (stack[i] == nuvarandeNod)
                    {
                        stack.erase(stack.begin() + i);
                    }
                }
                // L�gg till alla obes�kta grannar fr�n N till S
                if (nuvarandeNod->HarObes�ktGranne("Upp�t") && nuvarandeNod->Har�ppenV�gg("Upp�t") ||
                    nuvarandeNod->nodUpp�t && nuvarandeNod->nodUpp�t->slutNod ||
                    nuvarandeNod->nodUpp�t && nuvarandeNod->startNod)
                {
                    nuvarandeNod->nodUpp�t->bes�kt = true;
                    stack.push_back(nuvarandeNod->nodUpp�t);
                }
                if (nuvarandeNod->HarObes�ktGranne("H�ger") && nuvarandeNod->Har�ppenV�gg("H�ger"))
                {
                    nuvarandeNod->nodH�ger->bes�kt = true;
                    stack.push_back(nuvarandeNod->nodH�ger);
                }
                if (nuvarandeNod->HarObes�ktGranne("Ned�t") && nuvarandeNod->Har�ppenV�gg("Ned�t"))
                {
                    nuvarandeNod->nodNed�t->bes�kt = true;
                    stack.push_back(nuvarandeNod->nodNed�t);
                }
                if (nuvarandeNod->HarObes�ktGranne("V�nster") && nuvarandeNod->Har�ppenV�gg("V�nster"))
                {
                    nuvarandeNod->nodV�nster->bes�kt = true;
                    stack.push_back(nuvarandeNod->nodV�nster);
                }
            }

            else
            {
                for (size_t i = 0; i < stack.size(); i++)
                {
                    if (stack[i] == nuvarandeNod)
                    {
                        stack.erase(stack.begin() + i);
                    }
                }
            }
        }
    }
}

void Labyrint::BFS_Skapa(std::string animerad) {

    
    TryckInNoder();
    KopplaVector();

    Nod* nuvarandeNod;
    nuvarandeNod = &vect[startNod.first][startNod.second];
    nuvarandeNod->bes�kt = true;
    std::vector<Nod*> stack;
    stack.push_back(nuvarandeNod);

    while (!stack.empty())
    {
        if (animerad == "Animerad")
        {
            system("CLS");
            PrintMaze();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        int o = stack.size();
        for (size_t i = 0; i < o; i++)
        {

            if (stack[i]->HarObes�ktaGrannarCreate())
            {
                std::vector<Nod*> temp;
                int s = rand() % 4;
                if (s == 0 && stack[i]->HarObes�ktGranne("Upp�t"))
                {
                    stack[i]->�ppnaKoppling(stack[i], stack[i]->nodUpp�t);
                    stack[i]->nodUpp�t->bes�kt = true;
                    stack.push_back(stack[i]->nodUpp�t);
                }
                else if (s == 1 && stack[i]->HarObes�ktGranne("H�ger"))
                {
                    stack[i]->�ppnaKoppling(stack[i], stack[i]->nodH�ger);
                    stack[i]->nodH�ger->bes�kt = true;
                    stack.push_back(stack[i]->nodH�ger);
                }
                else if (s == 2 && stack[i]->HarObes�ktGranne("Ned�t"))
                {
                    stack[i]->�ppnaKoppling(stack[i], stack[i]->nodNed�t);
                    stack[i]->nodNed�t->bes�kt = true;
                    stack.push_back(stack[i]->nodNed�t);
                }
                else if (s == 3 && stack[i]->HarObes�ktGranne("V�nster"))
                {
                    stack[i]->�ppnaKoppling(stack[i], stack[i]->nodV�nster);
                    stack[i]->nodV�nster->bes�kt = true;
                    stack.push_back(stack[i]->nodV�nster);
                }
                /*while (!temp.empty())
                {
                    int k = rand() % temp.size();
                    stack.push_back(temp.at(k));
                    temp.erase(temp.begin() + k);
                }*/
            }
            else
            {
                stack.erase(stack.begin() + i);
                o--;
            }
        }
    }
}


void Labyrint::StartNod() { startNod.first = H�JD - 1; startNod.second = UddaTalUppTill(BREDD - 1); };   //l�ngst ned, n�st l�ngst till v�nster
void Labyrint::SlutNod() { slutNod.first = 0; slutNod.second = UddaTalUppTill(BREDD - 1); };  //l�ngst upp, n�st l�ngst till h�ger


int Labyrint::UddaTalUppTill(int a) {
    // anv�nds f�r att slumpa fram start/slut positioner 
    int k = rand() % (a + 1);
    while (k % 2 == 0)
    {
        k = UddaTalUppTill(a);
    }
    return k;
}

void Labyrint::KopplaVector() {
    
    // Denna kopplar ihop noderna s� att deras nod* pekar p� grannarna, f�r som default �r dom bara nullptrs
    for (size_t i = 1; i < H�JD; i++)      // Koppla till h�ger
    {
        for (size_t j = 1; j < BREDD - 2; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodH�ger = &vect[i][j + 2];
                vect[i][j].v�ggH�ger = &vect[i][j + 1];
            }
        }
    }

    for (size_t i = 1; i < H�JD; i++)      // Koppla till v�nster
    {
        for (size_t j = 3; j < BREDD; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodV�nster = &vect[i][j - 2];
                vect[i][j].v�ggV�nster = &vect[i][j - 1];
            }
        }
    }

    for (size_t i = 3; i < H�JD; i++)      // Koppla till upp�t
    {
        for (size_t j = 1; j < BREDD; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodUpp�t = &vect[i - 2][j];
                vect[i][j].v�ggUpp�t = &vect[i - 1][j];
            }
        }
    }

    for (size_t i = 1; i < H�JD - 2; i++)      // Koppla till ned�t
    {
        for (size_t j = 1; j < BREDD; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodNed�t = &vect[i + 2][j];
                vect[i][j].v�ggNed�t = &vect[i + 1][j];
            }
        }
    }

    vect[startNod.first][startNod.second].startNod = true;
    vect[startNod.first][startNod.second].nodUpp�t = &vect[startNod.first - 1][startNod.second]; // start nod pekar upp p� r�tt
    vect[startNod.first][startNod.second].nodUpp�t->nodNed�t = &vect[startNod.first][startNod.second]; // noden ovan pekar ned p� start

    vect[slutNod.first][slutNod.second].slutNod = true;
    vect[slutNod.first][slutNod.second].sten = false;
    vect[slutNod.first][slutNod.second].nodNed�t = &vect[slutNod.first + 1][slutNod.second]; // slut noden pekar ned p� r�tt
    vect[slutNod.first][slutNod.second].nodNed�t->nodUpp�t = &vect[slutNod.first][slutNod.second]; // noden nedan pekar upp p� r�tt
}

void Labyrint::TryckInNoder() {
    // Fyller vect med noder, med stenar runt om, och varannan rad bara med v�ggar
    // och varanan rad har varanan index en v�gg, och en nod
    for (size_t i = 0; i < H�JD; i++)
    {
        vect.push_back(std::vector<Nod>());
        for (size_t j = 0; j < BREDD; j++)
        {
            if (i == 0 || i == H�JD - 1)
            {
                Nod nod(true, true);
                vect[i].push_back(nod);
            }
            else if (j == 0 || j == BREDD - 1)
            {
                Nod nod(true, true);
                vect[i].push_back(nod);
            }
            else if (i % 2 != 0)
            {
                if (j % 2 != 0)
                {
                    Nod nod;
                    vect[i].push_back(nod);
                }
                else
                {
                    Nod nod(true);
                    vect[i].push_back(nod);
                }
            }
            else
            {
                if (j % 2 == 0)
                {
                    Nod nod(true, true);
                    vect[i].push_back(nod);
                }
                else
                {
                    Nod nod(true);
                    vect[i].push_back(nod);
                }
            }
        }
    }
}

void Labyrint::AllaNoderBes�kta() {
    for (size_t i = 0; i < H�JD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            if (!vect[i][j].wall)
            {
                vect[i][j].bes�kt = true;
            }
        }
    }
}

void Labyrint::AllaNoderIckeBes�kt() {
    for (size_t i = 0; i < H�JD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            vect[i][j].bes�kt = false;
        }
    }
}

void Labyrint::AllaNoderIckeSnabbast() {
    for (size_t i = 0; i < H�JD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            vect[i][j].snabbast = false;
        }
    }
}





