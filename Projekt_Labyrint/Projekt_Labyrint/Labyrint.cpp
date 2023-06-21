
// Viktor Hansson 
// 15/05/22
// Siktar på C som betyg?

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

Labyrint::Labyrint(int bredd, int höjd) {

    BREDD = bredd;
    HÖJD = höjd;
    StartNod();
    SlutNod();
}

// används för att jag använder bara en 'labyrint' i Main()
void Labyrint::ResetMaze() {
    BREDD = 11;
    HÖJD = 11;
    StartNod();
    SlutNod();
    vect.clear();
    TryckInNoder();
    KopplaVector();
    AllaNoderIckeBesökt();
}



void Labyrint::PrintMaze() {

    for (size_t i = 0; i < HÖJD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            
            std::cout << vect[i][j].ToString();
            
        }
        std::cout << std::endl;
    }
}

void Labyrint::PrintMazeAnimerad(std::vector<std::vector<Nod>>& vect, Nod*& nuvarande) {
    for (size_t i = 0; i < HÖJD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {                                // -> Detta så att sista eller första noden inte representeras som * 
            if (&vect[i][j] == nuvarande && vect[i][j].nodUppåt && !vect[i][j].nodUppåt->slutNod && !&vect[i][j].startNod)
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
    for (size_t i = 0; i < HÖJD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            std::cout << vect[i][j].ToStringSolved();
        }
        std::cout << std::endl;
    }
}

void Labyrint::GåVänster_Lös(std::string animerad) {
    AllaNoderIckeBesökt();
    AllaNoderIckeSnabbast();

    Nod* nuvarandeNod;
    nuvarandeNod = &vect[startNod.first][startNod.second];

    std::vector<Nod*> stack;
    stack.push_back(nuvarandeNod);

    while (!stack.empty())
    {
        nuvarandeNod = stack.back();  // nuvarandeNod = startnoden
        nuvarandeNod->besökt = true;

        if (animerad == "Animerad")
        {
            system("CLS");
            PrintMazeAnimerad(vect, nuvarandeNod);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (nuvarandeNod->slutNod) { break; }

        if (nuvarandeNod->HarObesöktaGrannarSolve())
        {
            if (nuvarandeNod->HarObesöktGranne("Uppåt") && nuvarandeNod->HarÖppenVägg("Uppåt") ||
                nuvarandeNod->nodUppåt && nuvarandeNod->nodUppåt->slutNod ||
                nuvarandeNod->nodUppåt && nuvarandeNod->startNod)
            {
                stack.push_back(nuvarandeNod->nodUppåt);
            }
            else if (nuvarandeNod->HarObesöktGranne("Vänster") && nuvarandeNod->HarÖppenVägg("Vänster"))
            {
                stack.push_back(nuvarandeNod->nodVänster);
            }
            else if (nuvarandeNod->HarObesöktGranne("Höger") && nuvarandeNod->HarÖppenVägg("Höger"))
            {
                stack.push_back(nuvarandeNod->nodHöger);
            }
            else if (nuvarandeNod->HarObesöktGranne("Nedåt") && nuvarandeNod->HarÖppenVägg("Nedåt"))
            {
                stack.push_back(nuvarandeNod->nodNedåt);
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
    nuvarandeNod = &vect[startNod.first][startNod.second]; // nuvarande nod pekar på start noden

    nuvarandeNod->besökt = true;
    stack.push_back(nuvarandeNod);

    while (!stack.empty())
    {
        nuvarandeNod = stack.back();
        stack.pop_back();

        if (nuvarandeNod->startNod)
        {
            nuvarandeNod = nuvarandeNod->nodUppåt;
            nuvarandeNod->besökt = true;
            stack.push_back(nuvarandeNod);
        }
        else if (nuvarandeNod->HarObesöktaGrannarCreate())
        {
            stack.push_back(nuvarandeNod);
            Nod* granne;
            granne = nuvarandeNod->RandomGranne();
            nuvarandeNod->ÖppnaKoppling(nuvarandeNod, granne);
            granne->besökt = true;
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

void Labyrint::DFS_Lös(std::string animerad) {
    Nod* nuvarandeNod;
    nuvarandeNod = &vect[startNod.first][startNod.second]; // nuvarande nod pekar på start noden
    std::vector<Nod*> stack;
    stack.push_back(nuvarandeNod);

    AllaNoderIckeBesökt();
    AllaNoderIckeSnabbast();
    nuvarandeNod->besökt = true;


    while (stack.size() != 0)
    {
        nuvarandeNod = stack.back();
        stack.pop_back();
        nuvarandeNod->besökt = true;

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
            if (nuvarandeNod->HarObesöktaGrannarSolve())
            {
                stack.push_back(nuvarandeNod);
                
                std::vector<Nod*> temp;
                if (nuvarandeNod->HarObesöktGranne("Uppåt") && nuvarandeNod->HarÖppenVägg("Uppåt") ||
                    nuvarandeNod->nodUppåt && nuvarandeNod->nodUppåt->slutNod ||
                    nuvarandeNod->nodUppåt && nuvarandeNod->startNod)
                {
                    temp.push_back(nuvarandeNod->nodUppåt);
                }
                else if (nuvarandeNod->HarObesöktGranne("Höger") && nuvarandeNod->HarÖppenVägg("Höger"))
                {
                    temp.push_back(nuvarandeNod->nodHöger);
                }
                else if (nuvarandeNod->HarObesöktGranne("Nedåt") && nuvarandeNod->HarÖppenVägg("Nedåt"))
                {
                    temp.push_back(nuvarandeNod->nodNedåt);
                }
                else if (nuvarandeNod->HarObesöktGranne("Vänster") && nuvarandeNod->HarÖppenVägg("Vänster"))
                {
                    temp.push_back(nuvarandeNod->nodVänster);
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

void Labyrint::BFS_Lös(std::string animerad) {

    AllaNoderIckeBesökt();
    AllaNoderIckeSnabbast();

    Nod* nuvarandeNod;
    std::vector<Nod*> stack;

    nuvarandeNod = vect[startNod.first][startNod.second].nodUppåt;
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
            nuvarandeNod->besökt = true;
            
            /*stack.erase(stack.begin());*/
            if (nuvarandeNod->nodUppåt && nuvarandeNod->nodUppåt->slutNod)
            {
                stack.clear();
                break;
            }
            if (nuvarandeNod->HarObesöktaGrannarSolve())
            {
                // ta bort N från S
                for (size_t i = 0; i < stack.size(); i++)
                {
                    if (stack[i] == nuvarandeNod)
                    {
                        stack.erase(stack.begin() + i);
                    }
                }
                // Lägg till alla obesökta grannar från N till S
                if (nuvarandeNod->HarObesöktGranne("Uppåt") && nuvarandeNod->HarÖppenVägg("Uppåt") ||
                    nuvarandeNod->nodUppåt && nuvarandeNod->nodUppåt->slutNod ||
                    nuvarandeNod->nodUppåt && nuvarandeNod->startNod)
                {
                    nuvarandeNod->nodUppåt->besökt = true;
                    stack.push_back(nuvarandeNod->nodUppåt);
                }
                if (nuvarandeNod->HarObesöktGranne("Höger") && nuvarandeNod->HarÖppenVägg("Höger"))
                {
                    nuvarandeNod->nodHöger->besökt = true;
                    stack.push_back(nuvarandeNod->nodHöger);
                }
                if (nuvarandeNod->HarObesöktGranne("Nedåt") && nuvarandeNod->HarÖppenVägg("Nedåt"))
                {
                    nuvarandeNod->nodNedåt->besökt = true;
                    stack.push_back(nuvarandeNod->nodNedåt);
                }
                if (nuvarandeNod->HarObesöktGranne("Vänster") && nuvarandeNod->HarÖppenVägg("Vänster"))
                {
                    nuvarandeNod->nodVänster->besökt = true;
                    stack.push_back(nuvarandeNod->nodVänster);
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
    nuvarandeNod->besökt = true;
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

            if (stack[i]->HarObesöktaGrannarCreate())
            {
                std::vector<Nod*> temp;
                int s = rand() % 4;
                if (s == 0 && stack[i]->HarObesöktGranne("Uppåt"))
                {
                    stack[i]->ÖppnaKoppling(stack[i], stack[i]->nodUppåt);
                    stack[i]->nodUppåt->besökt = true;
                    stack.push_back(stack[i]->nodUppåt);
                }
                else if (s == 1 && stack[i]->HarObesöktGranne("Höger"))
                {
                    stack[i]->ÖppnaKoppling(stack[i], stack[i]->nodHöger);
                    stack[i]->nodHöger->besökt = true;
                    stack.push_back(stack[i]->nodHöger);
                }
                else if (s == 2 && stack[i]->HarObesöktGranne("Nedåt"))
                {
                    stack[i]->ÖppnaKoppling(stack[i], stack[i]->nodNedåt);
                    stack[i]->nodNedåt->besökt = true;
                    stack.push_back(stack[i]->nodNedåt);
                }
                else if (s == 3 && stack[i]->HarObesöktGranne("Vänster"))
                {
                    stack[i]->ÖppnaKoppling(stack[i], stack[i]->nodVänster);
                    stack[i]->nodVänster->besökt = true;
                    stack.push_back(stack[i]->nodVänster);
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


void Labyrint::StartNod() { startNod.first = HÖJD - 1; startNod.second = UddaTalUppTill(BREDD - 1); };   //längst ned, näst längst till vänster
void Labyrint::SlutNod() { slutNod.first = 0; slutNod.second = UddaTalUppTill(BREDD - 1); };  //längst upp, näst längst till höger


int Labyrint::UddaTalUppTill(int a) {
    // används för att slumpa fram start/slut positioner 
    int k = rand() % (a + 1);
    while (k % 2 == 0)
    {
        k = UddaTalUppTill(a);
    }
    return k;
}

void Labyrint::KopplaVector() {
    
    // Denna kopplar ihop noderna så att deras nod* pekar på grannarna, för som default är dom bara nullptrs
    for (size_t i = 1; i < HÖJD; i++)      // Koppla till höger
    {
        for (size_t j = 1; j < BREDD - 2; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodHöger = &vect[i][j + 2];
                vect[i][j].väggHöger = &vect[i][j + 1];
            }
        }
    }

    for (size_t i = 1; i < HÖJD; i++)      // Koppla till vänster
    {
        for (size_t j = 3; j < BREDD; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodVänster = &vect[i][j - 2];
                vect[i][j].väggVänster = &vect[i][j - 1];
            }
        }
    }

    for (size_t i = 3; i < HÖJD; i++)      // Koppla till uppåt
    {
        for (size_t j = 1; j < BREDD; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodUppåt = &vect[i - 2][j];
                vect[i][j].väggUppåt = &vect[i - 1][j];
            }
        }
    }

    for (size_t i = 1; i < HÖJD - 2; i++)      // Koppla till nedåt
    {
        for (size_t j = 1; j < BREDD; j++)
        {
            if (i % 2 != 0 && j % 2 != 0)
            {
                vect[i][j].nodNedåt = &vect[i + 2][j];
                vect[i][j].väggNedåt = &vect[i + 1][j];
            }
        }
    }

    vect[startNod.first][startNod.second].startNod = true;
    vect[startNod.first][startNod.second].nodUppåt = &vect[startNod.first - 1][startNod.second]; // start nod pekar upp på rätt
    vect[startNod.first][startNod.second].nodUppåt->nodNedåt = &vect[startNod.first][startNod.second]; // noden ovan pekar ned på start

    vect[slutNod.first][slutNod.second].slutNod = true;
    vect[slutNod.first][slutNod.second].sten = false;
    vect[slutNod.first][slutNod.second].nodNedåt = &vect[slutNod.first + 1][slutNod.second]; // slut noden pekar ned på rätt
    vect[slutNod.first][slutNod.second].nodNedåt->nodUppåt = &vect[slutNod.first][slutNod.second]; // noden nedan pekar upp på rätt
}

void Labyrint::TryckInNoder() {
    // Fyller vect med noder, med stenar runt om, och varannan rad bara med väggar
    // och varanan rad har varanan index en vägg, och en nod
    for (size_t i = 0; i < HÖJD; i++)
    {
        vect.push_back(std::vector<Nod>());
        for (size_t j = 0; j < BREDD; j++)
        {
            if (i == 0 || i == HÖJD - 1)
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

void Labyrint::AllaNoderBesökta() {
    for (size_t i = 0; i < HÖJD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            if (!vect[i][j].wall)
            {
                vect[i][j].besökt = true;
            }
        }
    }
}

void Labyrint::AllaNoderIckeBesökt() {
    for (size_t i = 0; i < HÖJD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            vect[i][j].besökt = false;
        }
    }
}

void Labyrint::AllaNoderIckeSnabbast() {
    for (size_t i = 0; i < HÖJD; i++)
    {
        for (size_t j = 0; j < BREDD; j++)
        {
            vect[i][j].snabbast = false;
        }
    }
}





