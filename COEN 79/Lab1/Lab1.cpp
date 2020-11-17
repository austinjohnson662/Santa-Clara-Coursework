#include <iostream>
#include <string>
#include <fstream>

int program1();
int program2();
int program3();
int program4();


int main() {
	program1();
	program2();
	program3();
	program4();
	return 0;
}

//precondition: Enter a string
//postcondition: prints the number of alpha numeric characters and the number of non alpha numeric characters
//loops through the array. if the a given character is alpha numeric it increments alphaNum and vice versa for nAlphaNum. then prints it.
int program1() {

	//stores inserted value into the string uVal
	std::cout << "Insert string: ";
	std::string uVal;
	std::getline(std::cin, uVal);	

	int alphaNum = 0, nAlphaNum = 0;
	std::string::iterator i;
	for (i = uVal.begin(); i != uVal.end(); i++) {
		if (isalnum(*i))
			alphaNum++;
		else
			nAlphaNum++;
	}
	std::cout << "Alphanumeric: " << alphaNum << "\n";
	std::cout << "non-Alphanumeric: " << nAlphaNum << "\n";
	return 0;
}

//Pre-condition: stream needs to be numbers with no spaces
//post-condition: prints the numbers in the reverse order
//Iterates through the array outside in using the swap function with a pivot point in the middle.
int program2() {
	std::string uString;
	int check = 1, i;
	while (check) {
		check = 0;
		std::cout << "Enter 10 digit string (no spaces): ";
		std::cin >> uString;
		for (i = 0; i < uString.length(); i++) {
			if (isdigit(uString[i]) == 0)
				check = 1;
		}
		if (uString.length() != 10) {
			check = 1;
		}
		if (check)
			std::cout << "Must be 10 digits\n";
	}
	
	int n = uString.length();
	for (int i = 0; i < n / 2; i++)
		std::swap(uString[i], uString[n - i - 1]);
	
	std::cout << uString << "\n";
	return 0;
}

//precondition: have text file available named "InputStream.txt"
//postcondition: Erases all non-alpabetical letters and prints all words over the size of 10 letters in uppercase
//Goes through the text line by line. Iterates through each strings' array until it gets to the end of the line.
//Keeps track of the current word. once it reaches a space or eol symbolizing the end of a word. If the length > 10 it prints. Clears the word after.
int program3() {

	std::string word, line;
	std::ifstream myfile;
	myfile >> std::noskipws;
	char c;
	int i;
	
	myfile.open("InputStream.txt");
	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			for (i = 0; i < line.length(); i++){
				c = line[i];
				if (c == ' ') {
					if (word.size() >= 10) {
						std::cout << word << "\n";
					}
					word.clear();
				}
				else if (isalpha(c)) {
					c = toupper(c);
					word += c;
				}
			}
			if (word.size() >= 10) {
				std::cout << word << "\n";
			}
			word.clear();
		}

	}

	
	return 0;
}

//precondition: enter lowercase y or n
//postcondition: continously guesses the number until the user says yes. prints the amount of guesses it took.
//guesses every number from 1 to 20 sequentially. checks the users input. while loop ensures that each number gets a readable input before moving on.
//if y, print the steps and return. if n, leave the input loop and try the next number.
int program4() {
	std::string input;

	std::cout << "Think of a number between 1 and 20.\n";
	
	int i, j, check = 1, count = 0;
	for (i = 1; i < 21; i++) {
		while (check) {
			std::cout << "Is the number " << i << "? y or n ";
			std::cin >> input;
			for (j = 0; j < input.size(); j++) {
				input[j] = std::tolower(input[j]);
			}
			if ((input.compare("y") == 0) || (input.compare("yes")==0)) {
				check = 0;
				count++;
				std::cout << "I found the number in " << count << " steps\n";
				return 1;
			}
			else if ((input.compare("n") == 0) || (input.compare("no") == 0)) {
				check = 0;
				count++;
			}
			else {
				std::cout << "please type y or n\n";
				count++;
			}
		}
		check = 1;
	}
	std::cout << "Your number was not between 1 and 20.\n";
	return 0;
}