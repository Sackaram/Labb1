

// Viktor Hansson 
// 15/05/22
// Siktar p� C som betyg?



#include <iostream>
#include "Labyrint.h"
#include "Nod.h"


enum L�sning
{ DFS, BFS, GUV , null};

void HuvudMeny(Labyrint &maze);

enum L�sning L�saLabyrint() {

	std::cout << std::endl;
	std::cout << "Hur vill du l�sa denna?" << std::endl;
	std::cout << "1 - DFS - Depth First Search" << std::endl;
	std::cout << "2 - BFS - Breadth First Search" << std::endl;
	std::cout << "3 - GUV -  G� upp eller v�nster" << std::endl;
	std::cout << "4 - Vill inte l�sa den" << std::endl;

	int val;
	std::cin >> val;
	
	if (val != 1 && val != 2 && val != 3 && val != 4)
	{
		system("CLS");
		std::cout << "Nu skrev du fel, vi provar igen";
		std::cin.clear();
		std::cin.ignore();
		return L�saLabyrint();
	}

	switch (val)
	{
	case 1:
		return DFS;
	case 2:
		return BFS;
	case 3:
		return GUV;
	case 4:
		return null;
	default:
		return null;
		break;
	}
}

bool Animerad() {

	std::cout << "Ska den vara animerad?" << std::endl;
	std::cout << "1 - ja" << std::endl;
	std::cout << "2 - nej" << std::endl;

	int val;
	std::cin >> val;

	if (val != 1 && val != 2)
	{
		return Animerad();
	}

	if (val == 1) { return true; }
	return false;
}

std::pair<int, int> H�mtaStorlek() {
	int bredd;
	int h�jd;
	std::cout << std::endl;
	std::cout << "B�de bredd och h�jd m�ste vara udda tal" << std::endl;
	std::cout << "Bredd: ";

	std::cin >> bredd;

	if (bredd == 0 || bredd <0 || bredd % 2 == 0)
	{
		system("CLS");
		std::cout << "Nu skrev du fel, vi provar igen";
		std::cin.clear();
		std::cin.ignore();
		return H�mtaStorlek();
	}
	
	std::cout << "H�jd: ";
	std::cin >> h�jd;

	if (h�jd == 0 || h�jd < 0 || h�jd % 2 == 0)
	{
		system("CLS");
		std::cout << "Nu skrev du fel, vi provar igen";
		std::cin.clear();
		std::cin.ignore();
		return H�mtaStorlek();
	}

	return { bredd,h�jd };
}

std::pair<int, int> LabyrintStorlek() {
	int bredd = 11;
	int h�jd = 11;

	std::cout << std::endl;
	std::cout << "Hur stor ska labyrinten vara?" << std::endl;
	std::cout << "1 - Default 11x11" << std::endl;
	std::cout << "2 - Jag best�mmer" << std::endl;
	std::cout << std::endl;

	int val;
	std::cin >> val;

	switch (val)
	{
	case 1:
		system("CLS");
		return { bredd,h�jd };
		break;
	case 2:
		system("CLS");	
		return H�mtaStorlek();
		break;
	default:
		system("CLS");
		std::cout << "nu blev det fel" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		return LabyrintStorlek();
		break;
	}

	return { bredd,h�jd };
}


void SkapaLabyrintMeny(Labyrint &maze) {
	std::cout << std::endl;
	std::cout << "Vilken metod ska anv�ndas f�r att generera?" << std::endl;
	std::cout << "1 - BFS - Breadth First Search" << std::endl;
	std::cout << "2 - DFS - Depth First Search" << std::endl;
	std::cout << "3 - Avsluta - Tillbaks till huvud menyn" << std::endl;
	std::cout << std::endl;
	
	int val;
	std::cin >> val;

	switch (val)
	{
	case 1:{  // BFS VALD
		system("CLS");
		std::pair<int, int> storlek = LabyrintStorlek();
		Labyrint maze(storlek.first, storlek.second);
		if (Animerad())
		{
			maze.BFS_Skapa("Animerad");
			maze.PrintMaze();
		}
		else
		{
			maze.BFS_Skapa();
			maze.PrintMaze();
		}

		std::cout << std::endl;
		L�sning temp = L�saLabyrint();
		switch (temp)
		{
		case 0:
			system("CLS");
			if (Animerad()) { maze.DFS_L�s("Animerad");}
			else { maze.DFS_L�s(); maze.PrintMazeSolved(); }
			std::cout << std::endl;
			HuvudMeny(maze);
			break;
		case 1:
			system("CLS");
			if (Animerad()) { maze.BFS_L�s("Animerad"); }
			else { maze.BFS_L�s(); maze.PrintMazeSolved(); }
			std::cout << std::endl;
			HuvudMeny(maze);
			break;
		case 2:
			system("CLS");
			if (Animerad()) { maze.G�V�nster_L�s("Animerad"); }
			else { maze.G�V�nster_L�s(); maze.PrintMazeSolved(); }
			std::cout << std::endl;
			HuvudMeny(maze);
			break;
		case null:
			system("CLS");
			HuvudMeny(maze);
			break;
		default:
			break;
		}
		
		HuvudMeny(maze);
		break;
	}
	case 2:{  // DFS vald
		system("CLS");
		std::pair<int, int> storlek = LabyrintStorlek();
		Labyrint maze(storlek.first, storlek.second);
		if (Animerad())
		{
			maze.DFS_Skapa("Animerad");
			maze.PrintMaze();
		}
		else
		{
			maze.DFS_Skapa();
			maze.PrintMaze();
		}
		std::cout << std::endl;
		L�sning temp = L�saLabyrint();
		switch (temp)
		{
		case 0:
			system("CLS");
			if (Animerad()) { maze.DFS_L�s("Animerad"); }
			else { maze.DFS_L�s(); maze.PrintMazeSolved(); }
			std::cout << std::endl;
			HuvudMeny(maze);
			break;
		case 1:
			system("CLS");
			if (Animerad()) { maze.BFS_L�s("Animerad"); }
			else { maze.BFS_L�s(); maze.PrintMazeSolved(); }
			std::cout << std::endl;
			HuvudMeny(maze);
			break;
		case 2:
			system("CLS");
			if (Animerad()) { maze.G�V�nster_L�s("Animerad"); }
			else { maze.G�V�nster_L�s(); maze.PrintMazeSolved(); }
			std::cout << std::endl;
			HuvudMeny(maze);
			break;
		case null:
			system("CLS");
			HuvudMeny(maze);
			break;
		default:
			break;
		}
	}
	case 3:{
		system("CLS");
		maze.ResetMaze();
		HuvudMeny(maze);
		break;
	}
	default:{
		system("CLS");
		std::cout << "nu blev det fel" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		SkapaLabyrintMeny(maze);
		break;
	}
	}

}

void HuvudMeny(Labyrint &maze){
	std::cout << std::endl;
	std::cout << "Labyrint skapning" << std::endl;
	std::cout << "1 - Visa mig en slumpad labyrint" << std::endl;
	std::cout << "2 - Jag vill skapa en labyrint" << std::endl;
	std::cout << "3 - Avsluta" << std::endl;
	std::cout << std::endl;
	
	int val;
	std::cin >> val;

	switch (val)
	{
	case 1:
		system("CLS");
		maze.ResetMaze();
		if (rand() % 2 == 0) {
			maze.DFS_Skapa();
			maze.PrintMaze();
			std::cout << std::endl;
			HuvudMeny(maze);
		}
		else {
			maze.BFS_Skapa();
			maze.PrintMaze();
			std::cout << std::endl;
			HuvudMeny(maze);
		}
		break; 
	case 2:
		system("CLS");
		SkapaLabyrintMeny(maze);
		break;
	
	case 3:
		exit(0);
		break;
	default:
		system("CLS");
		std::cout << "nu blev det fel" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		HuvudMeny(maze);
		break;
	}
	
	HuvudMeny(maze);
}


int main()
{
	SetConsoleOutputCP(1252);
	srand(time(NULL));

	Labyrint maze(13,13);
	HuvudMeny(maze);
	


}




