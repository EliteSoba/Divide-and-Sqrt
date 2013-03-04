#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

void showMenu();
void divide();
int intSize(int num);
int mostSig(int num);
int pow(int base, int power);
void printGap(int num);
string toString(int num);
void sqrt();
int solve(int Q, int Z);
int sigBig(int num);

//TODO: DESIGN DOCUMENT
int main() {
	
	string temp; //Input
	
	do { //Display menu and read choice
		showMenu();
		cin >> temp;
		switch (tolower(temp[0])) {
			case 'd': divide(); break;
			case 'r': sqrt(); break;
			case 'q': break;
			default: cout << "That is not an option!\n";
		}
	}
	while (tolower(temp[0]) != 'q');
/////////////////////////////////////////
	return 0;
}

void showMenu() { //Prints out the menu options
	cout << "Please enter one of the following commands:\n";
	cout << "\t(d) Long division\n";
	cout << "\t(r) Long square root\n";
	cout << "\t(q) Quit\n";
}

void divide() { //Divides two numbers
	//Input numbers and validate data
	int divisor, dividend, quotient;
	cout << "Enter the divisor: ";
	cin >> divisor;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "Error: Invalid Input. Int expected" << endl;
		return;
	}
	if (divisor < 0 || divisor > 1000000000) {
		cerr << "Error: Input out of expected range" << endl;
		return;
	}
	if (divisor == 0) {
		cerr << "Error: Divide by zero" << endl;
		return;
	}
	
	cout << "Enter the dividend: ";
	cin >> dividend;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "Error: Invalid Input. Int expected" << endl;
		return;
	}
	if (dividend < 0 || dividend > 1000000000) {
		cerr << "Error: Input out of expected range" << endl;
		return;
	}
	cout << endl;
	
	//Prints the first line of the output (the quotient)
	quotient = dividend / divisor;
	printGap(intSize(divisor) + 3 + intSize(dividend) - intSize(quotient));
	cout << quotient << endl;
	
	//Prints out the format setup
	printGap(intSize(divisor) + 1);
	cout << "/";
	for (int i = 0; i <= intSize(dividend); i++)
		cout << "-";
	cout << endl;
	cout << divisor << " | " << dividend << endl;
	
	//Prints out the work you need to show to get credit
	//Some ideas/concepts/parts borrowed from HW2 example
	int Z = 0, N = intSize(quotient), out;
	int dSize = intSize(dividend);
	string Q = toString(quotient);
	for (unsigned int i = 0; i < Q.size(); i++) {
		Z = (int)(Q[i] - '0');
		N--;
		quotient -= Z * pow(10, N);
		
		//Prints number being subtracted and formatting spaces
		if (Z != 0)
			printGap(intSize(divisor) + 3 + dSize - intSize(divisor * Z * pow(10, N)));
		else
			printGap(intSize(divisor) + 3 + intSize(out) - 1 + dSize - intSize(dividend));
		cout << divisor * Z << endl;
		
		//Prints '-'s
		printGap(intSize(divisor) + 3 + i);
		for(int j = i; j < dSize; j++)
			cout << "-";
		cout << endl; 
		
		//Determines "difference" of the two terms being subtracted or whatever you would call it.
		if (i == 0 && N != 0)
			out = atoi(toString(dividend).substr(0, dSize - Q.size() + 2).c_str()) - divisor * Z * 10;
		else if (N != 0)
			out = atoi(toString(dividend).substr(0, intSize(out) + 1).c_str()) - (divisor * Z * 10);
		else
			out = dividend - divisor * Z;
		
		//Math in progress
		dividend -= divisor * Z * pow(10, N);
		
		//Prints "Difference"
		printGap(intSize(divisor) + 3 + dSize - intSize(dividend));
		cout << out << endl;
	}
	
}

int intSize(int num) { //Returns the length of an int
	int size;
	for (size = 1; num >= 10; size++)
		num /= 10;
	return size;
}

int mostSig(int num) { //Returns the most significant digit of an int
	while (num > 10)
		num /= 10;
	return num;
}

int pow(int base, int power) { //int version of pow method in cmath
	int product = 1;
	for (int i = 0; i < power; i++)
		product *= base;
	return product;
}

void printGap(int num) { //Prints num ' 's; used for formatting
	for (int i = 0; i < num; i++)
		cout << " ";
}

string toString(int num) { //Converts passed num to string
	stringstream ss;
	ss << num;
	string S;
	ss >> S;
	return S;	
}

void sqrt() { //Finds the square root of a number
	//Input number and validate data
	int num;
	cout << "Enter a number to square root: ";
	cin >> num;
	
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		cerr << "Error: Invalid Input. Int expected" << endl;
		return;
	}
	if (num < 0 || num > 1000000000) {
		cerr << "Error: Input out of expected range" << endl;
		return;
	}
	
	//Borrowed the algorithm from the site
	
	//Gets the big digits from the inputted number
	vector<int> bigs;
	int temp = num;
	while (temp > 0) {
		bigs.insert(bigs.begin(), temp % 100);
		temp /= 100;
	}
	//Safety buffer
	for (int i = 0; i < 8; i++)
		bigs.push_back(0);
	
	vector<int> work;
	int Z = 0, N = (intSize(num) + 1)/2, Q = 0, M = 0;
	double X = num;
	while (M < 8) {
		int D = bigs[M];
		Z = 100 * Z + D;
		N--;
		X -= D * pow(100.0, N);
		int T = solve(Q,Z);
		work.push_back(Z);
		work.push_back(T * (20 * Q + T));
		Z -= T * (20 * Q + T);
		Q = 10 * Q + T;
		M++;
	}
	work.push_back(Z);
	
	//Formats output with decimal, etc.
	stringstream ss;
	ss << Q;
	string S;
	ss >> S;
	S.insert(((intSize(num)+1)/2), "."); //Converts decimal number to decimal :D
	
	//Prints root above the square root sign
	if (atof(S.c_str()) == atoi(S.c_str())) { //If num is a perfect square
		float f = atof(S.c_str());
		stringstream sss;
		sss << f;
		sss >> S;
		cout << "  ";
		for (N = 0; N < S.size(); N++)
			cout << " " << S[N];
		cout << "\n /";
		if (atoi(S.c_str()) < 10 && num > 10)
			cout << "---";
		else
			for (unsigned int i = 0; i < S.size(); i++)
				cout << "--";
	}
	else { //If num is not a perfect square
		cout << "    ";
		for (N = 0; N < (intSize(num)+1)/2; N++)
			cout << S[N] << " ";
		if (S[N] == '.') {
			cout << (char)8 << "." << S[N+1];
			for (N = N+2; N < S.size(); N++)
				cout << " " << S[N];
		}
		cout << "\n /-";
		for(unsigned int i = 1; i < S.size(); i++)
			cout << "--";
	}
	cout << "\nv  " << num << endl;
	int extra = 0;
	work.insert(work.begin(),num);
	
	//Shows "work" to get credit
	//HARDCODING FTW
	//AKA printing spaces is difficult
	for(unsigned int i = 2; i < work.size(); i+=2) {
		printGap(3 + extra);
		cout << work[i] << endl;
		
		printGap(3 + extra);
		if (atof(S.c_str()) != atoi(S.c_str()))
			for (unsigned int x = extra; x <= 2*S.size()-3; x++)
				cout << "-";
		else {
		if (atoi(S.c_str()) < 10 && num < 10)
			cout << "-";
		else
			for (unsigned int x = extra; x < intSize(num); x++)
				cout << "-";
		}
		cout << endl;
		
		if (intSize(work[i+1])-2 < intSize(work[i-1]))
			extra+=intSize(work[i-1])-intSize(work[i+1])+2;
		if (i+2 >= work.size() || work[i+1] == 0)
			extra -= 2;
		printGap(3 + extra);
		cout << work[i+1] << endl;
		
		if (work[i+1] == 0)
			break;
		if (intSize(work[i+1]) > intSize(work[i+2]) && i+2 < work.size())
			printGap(intSize(work[i+1])-intSize(work[i+2]));
	}
}

int solve(int Q, int Z) { //Solves for T such that T * (20*Q + T) <= Z
	int i;
	for (i = 1; i <= 10; i++)
		if (i * (20 * Q + i) > Z)
			return i - 1;
	return 0;
}

int sigBig(int num) { //Returns the most significant big-digit of num
	while (num >= 100)
		num /= 100;
	return num;
}

