//Darwin Nelson
//UID 203883479

//Iterated Prisoner's Dilemma

/*Rules:
There is a set of 100 prisoners, who share up to 4 crimes with up to 4 neighboring prisoners 
in a 10x10 grid.

Each person can rat out the other, for 2 years of jail, with the other getting 10
years of jail. If both rat each other out, then they both get 5 years in jail.
If neither takes the deal, they both get 3 years of jail. After each iteration
the person will switch from defector to cooperator or cooperator to defector if
the total sentence for that person from all four crimes in last iteration was 20+ 
years. Each person is an accomplice with the adjacent squares.

C is a person who doesn't rat out his neighbors, D is a prisoner who does.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//Function prototypes

void clearArray (string grid[][12], int size);
//Clears array by setting all values in the grid to some constant character other 
//than C or D.

void assignInitialValues (string grid[][12], int size); 
//Where each square in the grid is randomly assigned the value "C" for 
//cooperator or "D" for defector.

void iterate(string grid[][12], int size);
//Where each square in the grid is modified according to the rules provided above.

double percentageOfCooperation(string grid[][12], int size);
//Determines the percentage of Cooperators at the end.

void printPercentage (double percentage);
//Prints the percentage of cooporators after fixed number (10,000) iterations.

void printGrid(string grid[][12]){
	for(int i = 0; i < 12; i++){
		for(int j = 0; j< 12; j++){
			cout<<grid[i][j]<<" ";}
		cout<<endl;}
	cout<<endl;}

int main()
{
	string preGrid[12][12];  
	int nTrials = 10000;

	clearArray(preGrid, 12);

	assignInitialValues(preGrid, 12);
	
	for (int i = 0; i < nTrials; i++){
		if(i == 0)
			printGrid(preGrid);
		if(i == 1)
			printGrid(preGrid);
	iterate(preGrid, 12);
	}
	
	percentageOfCooperation(preGrid, 12);

	printPercentage(percentageOfCooperation(preGrid, 12));	
}

void clearArray(string grid[][12], int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			grid[i][j] = "*";
		}
}
void assignInitialValues (string grid[][12], int size)
{
	//Randomly choose C or D
	string status;
	int choose;
	//srand (time(0)); 
	for (int i = 1; i < size-1; i++)//Each row of grid but not boundaries
	{
		for (int k = 1; k < size-1; k++)//Each column of grid but not boundaries
		{
			choose = rand()%2;//choose a random between 0 or 1
			if (choose == 0)
				status = "C";
			else
				status = "D";

			grid[i][k] = status;
		}
	}
}
void iterate(string grid[][12], int size)
{	
	const int betrayed = 10; //If a prisoner of C next to D
	const int betrayer = 2; //If a prisoner of D next to C
	const int friends = 3; //If a prisoner of C next to C
	const int attrition = 5; //If a prisoner of D next to D

	
	//Copies the entire array to a temporary error, to assign the new iteration with each 
	//prisoner check when years of jail is equal to or greater than 20
	string tempGrid[12][12];
	for (int i = 1; i < size-1; i++)
		for (int j = 1; j < size-1; j++)
			tempGrid[i][j] = grid[i][j];

	//Checks non-boundary cases of the grid, e.g. between indicies 1 and 10
	for (int i = 1; i < 11; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			int yearsOfJail = 0;
			//For each person, modify his jail time.
			if (grid[i][j] == "C")
			{	
				//The case the person is a cooperator, add 10 years of jail to 
				//this person if his friends rat him out. Otherwise add 3.
			
				//Check the square left
				if (grid[i][j-1] == "D")
					yearsOfJail += betrayed;
				else if (grid[i][j-1] == "C")
					yearsOfJail += friends;

				//Check the square below
				if (grid[i+1][j] == "D")
					yearsOfJail += betrayed;
				else if (grid[i+1][j] == "C")
					yearsOfJail += friends;

				//Check the square right
				if (grid[i][j+1] == "D")
					yearsOfJail += betrayed; 
				else if (grid[i][j+1] == "C")
					yearsOfJail += friends;

				//Check the square above
				if (grid[i-1][j] == "D")
					yearsOfJail += betrayed;
				else if (grid[i-1][j] == "C")
					yearsOfJail +=friends;
			}
			else if (grid[i][j] == "D")
			{	
				//Case where the person is a defector. If his friend rats him out 
				//then the person gets 5 years of jail. If his friend doesn't rat
				//him out, he gets 2.
			
				//Check the square left
				if (grid[i][j-1] == "D")
					yearsOfJail += attrition;
				else if (grid[i][j-1] == "C")
					yearsOfJail += betrayer;

				//Check the square below
				if (grid[i+1][j] == "D")
					yearsOfJail += attrition;
				else if (grid[i+1][j] == "C")
					yearsOfJail += betrayer;

				//Check the square right
				if (grid[i][j+1] == "D")
					yearsOfJail += attrition; 
				else if (grid[i][j+1] == "C")
					yearsOfJail += betrayer;

				//Check the square above
				if (grid[i-1][j] == "D")
					yearsOfJail += attrition;
				else if (grid[i-1][j] == "C")
					yearsOfJail += betrayer;
			}

			//Changes each prisoner in the temporary grid during iteration
		if (yearsOfJail >= 20 && grid[i][j] == "C")
			tempGrid[i][j] = "D";
		else if (yearsOfJail >= 20 && grid[i][j] == "D")
			tempGrid[i][j] = "C";
		}
	}
	//After completing entire array, change our grid to temporary grid which 
	//has been changed to the new array during iteration
	
	for (int i = 1; i < 11; i++)
		for (int j = 1; j < 11;j++)
			grid[i][j] = tempGrid [i][j];
}

double percentageOfCooperation(string grid[][12], int size)
{
	double count = 0;
	for (int i = 1; i < size-1; i++)
		for (int j = 1; j < size-1; j++)
			if (grid[i][j] == "C")
				count++;
	return count;
}
void printPercentage (double percentage) 
{
	cout<<"The percentage of cooperators is "<<percentage<<"%\n";
}
