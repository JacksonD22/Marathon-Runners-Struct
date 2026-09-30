#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int NUMRUNNERS = 5;
const int NUMDAYS = 7;

struct runner{
	string name;
	double miles[NUMDAYS];
	double total;
	double average;
};

string getData();
bool readRunnerData(ifstream &file, string filename, runner runners[], int maxRunners);
void calculateResults(runner runners[], int runnerCount);
void displayResults(runner runners[], int runnerCount);

int main() {
	runner runners[NUMRUNNERS];
	int runnerCount = 0;
	ifstream file;

	string filename = getData();
	if (!readRunnerData(file, filename, runners, NUMRUNNERS)) {
		return 1;
	}
	runnerCount = readRunnerData(file, runners, runners, NUMRUNNERS);
	file.close();

	calculateResults(runners, runnerCount);
	displayResults(runners, runnerCount);

	return 0;
}

string getData() {
	string filename;
	cout << "Enter the name of the file" << endl;
	cin >> filename;
	return filename;
}

bool readRunnerData(ifstream& file, string filename, runner runners[], int maxRunners) {
	ifstream file;
	file.open(filename);

	if (!file) {
		cout << "Error, couldnt access file.\n";
		return false;
	}
	return true;

	int count = 0;
	while (count < maxRunners && file >> runners[count].name) {
		for (int j = 0; j < NUMDAYS; j++) {
			file >> runners[count].miles[j];
		}
		count++;
	}
}

void calculateResults(runner runners[], int runnerCount) {
	for (int i = 0; i < runnerCount; i++) {
		runners[i].total = 0;
		for (int j = 0; j < NUMDAYS; j++) {
			runners[i].total += runners[i].miles[j];
		}
		runners[i].average = runners[i].total / NUMDAYS;
	}
}

void displayResults(runner runners[], int runnerCount) 
{
	cout << left << setw(10) << "Runner";
	for (int j = 0; j < NUMDAYS; j++) {
		cout << right << setw(10) << ("Day " + to_string(j + 1));
	}
	cout << right << setw(10) << "Total" << setw(10) << "Average" << endl;

	for (int i = 0; i < runnerCount; i++) {
		cout << left << setw(10) << runners[i].name;
		for (int j = 0; j < NUMDAYS; j++) {
			cout << right << setw(10) << fixed << setprecision(2) << runners[i].miles[j];
		}
		cout << right << setw(10) << fixed << setprecision(2) << runners[i].total;
		cout << right << setw(10) << fixed << setprecision(2) << runners[i].average << endl;
	}
}