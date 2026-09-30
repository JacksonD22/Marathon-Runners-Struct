#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int NUMRUNNERS = 50;
const int NUMDAYS = 7;

struct runner{
	string name = "unknown";
	double miles[NUMDAYS] = { 0 };
	double total = 0;
	double average = 0;
};

string getData();
bool openFile(ifstream &file, string filename);
int readRunnerData(ifstream& file, runner runners[], int maxRunners);
void calculateResults(runner runners[], int runnerCount);
void displayResults(runner runners[], int runnerCount);

int main() {
	runner runners[NUMRUNNERS];
	int runnerCount = 0;
	ifstream file;

	string filename = getData();
	if (!openFile(file, filename)) {
		return 1;
	}
	runnerCount = readRunnerData(file, runners, NUMRUNNERS);
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

bool openFile(ifstream& file, string filename) {
	file.open(filename);

	if (!file) {
		cout << "Error, couldnt access file.\n";
		return false;
	}
	return true;
}

int readRunnerData(ifstream& file, runner runners[], int maxRunners) {
	int count = 0;

	while (count < maxRunners && file >> runners[count].name) {
		for (int j = 0; j < NUMDAYS; j++) {
			file >> runners[count].miles[j];
		}
		count++;
	}

	string extra;
	if (count == maxRunners && file >> extra) {
		cout << "File exceeds runner limit'\n";
	}
	return count;
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