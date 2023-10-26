#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generateRandomNums(vector<vector<int>> &numbers, int roof)
{
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		for (unsigned int j = 0; j < numbers[i].size(); j++)
		{
			numbers[i][j] = rand() % roof + 1;
		}

	}
}

void displayTwoDimentionalVector(vector<vector<int>> &numbers)
{
	cout << endl;
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		cout << "(";
		for (unsigned int j = 0; j < numbers[i].size(); j++)
		{
			j == numbers[i].size() - 1 ?
				cout << numbers[i][j] :
				cout << numbers[i][j] << ",";
		}
		cout << ")" << endl;
	}
	cout << endl;
}

vector<int> compute—hromosomes(vector<vector<int>> numbers, int roof)
{
	vector<int> chroms;
	cout << endl;
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		int a = 0;
		for (unsigned int j = 0; j < numbers[i].size(); j++)
		{
			a += (j+1) * numbers[i][j];
		}
		cout << "| " << a << " - " << roof << " | = " << a - roof << endl; // it shouldn't be here, but it was neÒessary for lab report
		chroms.push_back(a - roof);
	}
	return chroms;
}

void displayProbs(vector<int> numbers, float div) 
{
	cout << endl;
	for (int x: numbers)
	{
		cout << "(1/" << x << ")/" << div << " = " << 100 * ((1.f / x) / div) << "%" << endl;
	}
	
}

void probabilityOfParents(vector<int> numbers)
{
	float div = 0;
	for (int x: numbers)
	{
		div += (1.f / x);
	}
	displayProbs(numbers, div);
	
}

vector<vector<int>> computeChild(vector<vector<int>>& parents, vector<vector<int>>& numbers)
{
	vector<vector<int>> child(numbers.size(), vector<int>());

	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		for (unsigned int j = 0; j < numbers[i].size(); j++)
		{
			child[i].push_back(numbers[parents[i].back() - 1][j]);
		}
	}

	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		for (unsigned int j = 0; j < numbers[i].size(); j++)
		{
			int num = parents[i].front() - 1;

			if (i == 0 && j == 0 || i == 3 && j == 0) {
				child[i][j] = numbers[num][j];
			}
			else if (i == 1 && j == 0 || i == 4 && j == 0) {
				child[i][j] = numbers[num][j];
				child[i][j+1] = numbers[num][j+1];
			}
			else if(i == 2 && j == 3)
			{
				child[i][j-3] = numbers[num][j-3];
				child[i][j-2] = numbers[num][j-2];
				child[i][j-1] = numbers[num][j-1];
			}
		}
	}

	return child;
}

void displaySplitLine(vector<vector<int>> const& parents, vector<vector<int>> const& numbers, bool isFather)
{
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		cout << "(";
for (unsigned int j = 0; j < numbers[i].size(); j++)
{
	int num = isFather ? numbers[parents[i].front() - 1][j] :
		numbers[parents[i].back() - 1][j];

	if (j == numbers[i].size() - 1) {
		cout << num;
	}
	else {
		if (i == 0 && j == 0 || i == 3 && j == 0 ||
			i == 1 && j == 1 || i == 4 && j == 1 || i == 2 && j == 2)
		{
			cout << num << " | ";
		}
		else cout << num << ",";
	}
}
cout << ")" << endl;
	}
	cout << endl;
}

void displayFamily(vector<vector<int>> const& parents, vector<vector<int>> const& numbers, vector<vector<int>>& child)
{
	bool isFather = true;

	cout << "chromosomeFather" << endl;
	displaySplitLine(parents, numbers, isFather);

	cout << "chromosomeMother" << endl;
	displaySplitLine(parents, numbers, !isFather);

	cout << "chromosomeChild" << endl;
	displayTwoDimentionalVector(child);
}

void generateRandomNums(vector<vector<int>>& parentsSimulation)
{
	for (unsigned int i = 0; i < parentsSimulation.size(); i++)
	{
		for (unsigned int j = 0; j < parentsSimulation[i].size(); j++)
		{
			parentsSimulation[i][j] = rand() % parentsSimulation.size() + 1;
		}

	}
}

int computeAvgVector(vector<int> a)
{
	int sum = 0;
	for (int x : a) sum += x;
	return sum / a.size();
}

void diophantine_equation() 
{
	cout << "Diophantine equation for genetic algorithm : a + 2b + 3c + 4d = " << endl << endl;
	int roof = 0;
	int rows = 5, cols = 4;
	vector<vector<int>> numbers(rows, vector<int>(cols));
	
	cout << "Enter the result of the diophantine expression: ";
	cin >> roof;
	
	cout << endl << "Random numbers: " << endl;
	generateRandomNums(numbers, roof); // generate random numbers for the first generation of chromosomes 
	displayTwoDimentionalVector(numbers);
	
	cout << endl << "Coefficients: " << endl; 
	vector<int> chroms = compute—hromosomes(numbers, roof);

	cout << endl << "Probabilities of parents: " << endl;
	probabilityOfParents(chroms);

	vector<vector<int>> parentsSimulation(5, vector<int>(2));
	generateRandomNums(parentsSimulation);
	displayTwoDimentionalVector(parentsSimulation);

	vector<vector<int>> child = computeChild(parentsSimulation, numbers);
	displayFamily(parentsSimulation, numbers, child);

	vector<int> chroms2 = compute—hromosomes(child, roof);
	
	int avgChildren = computeAvgVector(chroms2);
	int avgParents = computeAvgVector(chroms);

	cout << "\nThe average fitness of the offspring turned out to be " << avgChildren 
		<< ", while the parents had this coefficient equal to " << avgParents 
		<< "\n\nContinuing in this way, one chromosome will eventually reach a survival rate of 0,"
		<< " i.e.become a solution.Systems with a larger population(for example, 50 instead of 5)" 
		<< " converge to the desired level(0) more quicklyand stably.\n\n";
}

int main()
{
	srand((unsigned int)time(0));
	diophantine_equation();

	return 0;
}