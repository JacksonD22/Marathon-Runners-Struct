#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int NUMRUNNERS = 5;
const int NUMDAYS = 7;

struct runner{
	string name;
	double miles[DAYS];
	double total;
	double average;
};

string getData();
bool readRunnerData(ifstream file, string filename);
void calculateResults();
void displayResults();

int main() {
	runner runners[NUMRUNNERS];
	int runnerCount = 0;
	ifstream file;

	string filename = getData();
	if (!readRunnerData(file, filename)) {
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

bool readRunnerData(ifstream file, string filename) {
	ifstream file;
	file.open(filename);

	if (!file) {
		cout << "Error, couldnt access file.\n";
		return false;
	}
	return true;
}

void calculateResults(double miles[][DAYS], double total[], double averages[], const int numRunners, const int numDays) {
	for (int i = 0; i < numRunners; i++) {
		total[i] = 0;
		for (int j = 0; j < numDays; j++) {
			total[i] += miles[i][j];
		}
		averages[i] = total[i] / numDays;
	}
}

void displayResults(string names[], double miles[][DAYS], double total[], double averages[], const int numRunners, const int numDays) {
	cout << left << setw(10) << "Runner";
	for (int j = 0; j < numDays; j++) {
		cout << right << setw(10) << ("Day " + to_string(j + 1));
	}
	cout << right << setw(10) << "Total" << setw(10) << "Average" << endl;

	for (int i = 0; i < numRunners; i++) {
		cout << left << setw(10) << names[i];
		for (int j = 0; j < numDays; j++) {
			cout << right << setw(10) << fixed << setprecision(2) << miles[i][j];
		}
		cout << right << setw(10) << fixed << setprecision(2) << total[i];
		cout << right << setw(10) << fixed << setprecision(2) << averages[i] << endl;
	}
}