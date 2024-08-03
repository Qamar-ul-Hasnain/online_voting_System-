#include <iostream>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include<fstream>
using namespace std;

class Voter {
protected:
	struct Node {
		char name[40];
		char number[12];
		char password[4];
		int hasVoted;
		Node* left;
		Node* right;
	};
	Node* root;
	char n[40];
	char num[12];
	char pass[4];
	int hvt;


	Node* insertNode(char* name, char* num, char* password,int HasVoted, Node* root ) {
		if (root == NULL) {
			root = new Node();
			strcpy_s(root->name, name);
			strcpy_s(root->number, num);
			strcpy_s(root->password, password);
			root->hasVoted = HasVoted;
			root->left = root->right = NULL;
			return root;
		}
		else if (strcmp(root->name, name) == 0) {
			cout << "Name is Already Present " << endl;
			return NULL;
		}
		else if (strcmp(root->name, name) > 0) {
			root->left = insertNode(name, num, password, HasVoted, root->left);
		}
		else {
			root->right = insertNode(name, num, password, HasVoted, root->right);  // Change this line
		}
		return root;
	}

	Node* inorderPre(Node* node) {
		while (node->right != nullptr)
			node = node->right;

		return node;
	}

	Node* deleteNode(Node* root, char* name, char* pass) {
		if (root == nullptr)
		{
			return root;
		}

		if (strcmp(root->name, name ) > 0 && strcmp(root->password, pass) > 0 )
		{
			root->left = deleteNode(root->left, name, pass);
		}
		else if (strcmp(root->name, name) < 0 && strcmp(root->password, pass) < 0)
		{
			root->right = deleteNode(root->right, name, pass);
		}
		else {
			if (root->left == nullptr) {
				Node* temp = root->right;
				cout << "Name : " << root->name << endl;
				cout << "Phone Number : " << root->number << endl;
				delete root;
				cout << "Candidate deleted successfully." << endl;
				return temp;
			}
			else if (root->right == nullptr) {
				Node* temp = root->left;
				cout << "Name : " << root->name << endl;
				cout << "Phone Number : " << root->number << endl;
				delete root;
				cout << "Candidate deleted successfully." << endl;
				return temp;
			}

			Node* temp = inorderPre(root->left);
			strcpy_s(root->name, temp->name);
			root->left = deleteNode(root->left, temp->name,temp->password);
		}
		return root;
	}

	void searchNode(Node* root, char* name, char* pass) {
		if (root != nullptr) {
			searchNode(root->left, name, pass);
			if (strcmp(root->name, name) == 0 && strcmp(root->password, pass) == 0) {
				cout << " Name : " << root->name << " , Phone No.: " << root->number << endl;
			}
			searchNode(root->right, name, pass);
		}
	}

	Node* updateNode(Node* root, const char* name) {
		if (root != nullptr) {
			if (strcmp(root->name, name) == 0) {
				char newName[40];
				char newNumber[12];
				char newPass[4];
				char ch;
				cout << "Enter what you want to update name or phone number press 'N' for name and 'P' for  phone number and 'd' for password..";
				cin >> ch;
				while (ch == 'p' || ch == 'P' || ch == 'n' || ch == 'N' || ch == 'd' || ch == 'D') {
					if (ch == 'n' || ch == 'N') {
						cout << "Enter new Name: ";
						cin.ignore();
						cin.getline(newName, 40);
						strcpy_s(root->name, newName);
						break;
					}
					else if (ch == 'p' || ch == 'P') {
						cout << "Enter new Phone no.: ";
						cin.ignore();
						cin.getline(newNumber, 12);
						strcpy_s(root->number, newNumber);
						break;
					}
					else if (ch == 'd' || ch == 'D') {
						cout << "Enter new password.: ";
						cin.ignore();
						cin.getline(newPass, 4);
						strcpy_s(root->password, newPass);
						break;
					}
				}
				cout << "Voter updated successfully." << endl;
				return root;
			}

			root->left = updateNode(root->left, name);
			root->right = updateNode(root->right, name);
		}
		return root;
	}

	void aOrder(Node* root) {
		if (root != nullptr) {
			aOrder(root->left);
			cout << " Name : " << root->name << endl << " Phone No.: " << root->number << endl << " password .: " << root->password  << endl;
			aOrder(root->right);
		}
	}

	void writeBSTToFile(Node* root, ofstream& outFile) {
		if (root == nullptr) {
			return;
		}

		outFile << root->name << "\t" << root->number << "\t" << root->password << "\t" << root->hasVoted << endl;
		writeBSTToFile(root->left, outFile);
		writeBSTToFile(root->right, outFile);
	}

	void LoadBSTFile(ifstream& inFile) {
		root = NULL;
		Node* temproot = NULL;
		// Create a BST and insert data from the file
		while (inFile >> n >> num >> pass >> hvt) {
			temproot = insertNode(n, num, pass, hvt, temproot);
		}
		root = temproot;
	}

public:
	Voter() {
		root = NULL;
	}

	Node* getRoot() {
		return root;
	}

	int getHasVote(Node*root,char*name,char*pass) {
		Node* pp = findVoter(root, name, pass);
		if (pp->hasVoted == 1) {
			return 1;
		}
		else {
			return 0;
		}

	}
	
	void insertVoter() {
		cout << "Enter Voter Name : ";
		cin.ignore();
		cin.getline(n, 40);
		cout << "Enter Voter Mobile Number : ";
		cin.getline(num, 12);
		cout << "Enter Secure password ( Must be 4 characters ): ";
		cin.getline(pass, 4);

		root = insertNode(n, num, pass, 0, root);
	}
	
	void delet() {
		if (root == nullptr) {
			cout << "No voters to delete !" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Enter Exact Name to delete : ";
			cin.ignore();
			cin.getline(n, 40);
			cout << "Enter Exact password : ";
			cin.ignore();
			cin.getline(pass, 4);
			root = deleteNode(root, n, pass);
			_getch();
			system("cls");
		}
	}

	void searchVoter() {
		if (root == nullptr) {
			cout << "\nNo Voters to search !" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Enter name of Voter. : ";
			cin.ignore();
			cin.getline(n, 40);
			cout << "Enter password of Voter. : ";
			cin.ignore();
			cin.getline(pass, 4);
			cout << endl;
			searchNode(root, n, pass);
			_getch();
			system("cls");
		}
	}

	void updateVoter() {
		if (root == nullptr) {
			cout << "\nNo Voters to search !" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Enetr name you want to update !" << endl;
			cout << "Enter Name : ";
			cin.ignore();
			cin.getline(n, 40);
			root = updateNode(root, n);
			_getch();
			system("cls");
		}
	}

	void showAscending() {
		if (root == NULL) {
			cout << "NO Voters to show ! " << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Printing Voters List : " << endl;
			aOrder(root);
			cout << endl;
			_getch();
			system("cls");
		}
	}

	Node* findVoter(Node* root, char* name, char* pass) {
		if (root != nullptr) {
			if (strcmp(root->name, name) == 0 && strcmp(root->password, pass) == 0) {
				return root;
			}

			Node* leftResult = findVoter(root->left, name, pass);
			if (leftResult != nullptr) {
				return leftResult;
			}

			return findVoter(root->right, name, pass);
		}

		return nullptr;
	}

	void saveToFile() {
		ofstream outFile("voter_data.txt");
		if (!outFile.is_open()) {
			cout << "Error opening file for writing." << endl;
			return;
		}

		writeBSTToFile(root, outFile);
		outFile.close();
		cout << "BST data written to file." << endl;
	}

	void getFromFile() {
		ifstream inFile("voter_data.txt");
		if (!inFile.is_open()) {
			cout << "Error opening file for reading." << endl;
			return;
		}

		LoadBSTFile(inFile);
		inFile.close();
	}
};

class Candidate {
protected:
	struct Node{
		char name[40];
		char number[12];
		char password[4];
		int votecount;
		Node* left;
		Node* right;
	};
	Node* root;
	char n[40];
	char num[12];
	char pass[4];
	int vtc;

	Node* insertNode(char* name, char* num, char* password, int vtc, Node* root) {
		if (root == NULL) {
			root = new Node();
			strcpy_s(root->name, name);
			strcpy_s(root->number, num);
			strcpy_s(root->password, password);
			root->votecount = vtc;
			root->left = root->right = NULL;
			return root;
		}
		else if (strcmp(root->name, name) == 0) {
			cout << "Name is Already Present " << endl;
			return NULL;
		}
		else if (strcmp(root->name, name) > 0) {
			root->left = insertNode(name, num, password, vtc, root->left);
		}
		else {
			root->right = insertNode(name, num, password, vtc, root->right);  // Change this line
		}
		return root;
	}

	Node* inorderPre(Node* node) {
		while (node->right != nullptr)
			node = node->right;

		return node;
	}

	Node* deleteNode(Node* root, char* name, char* pass) {
		if (root == nullptr)
		{
			return root;
		}

		if (strcmp(root->name, name) > 0 && strcmp(root->password, pass) > 0)
		{
			root->left = deleteNode(root->left, name, pass);
		}
		else if (strcmp(root->name, name) < 0 && strcmp(root->password, pass) < 0)
		{
			root->right = deleteNode(root->right, name, pass);
		}
		else {
			if (root->left == nullptr) {
				Node* temp = root->right;
				cout << "Name : " << root->name << endl;
				cout << "Phone Number : " << root->number << endl;
				delete root;
				cout << "Candidate deleted successfully." << endl;
				return temp;
			}
			else if (root->right == nullptr) {
				Node* temp = root->left;
				cout << "Name : " << root->name << endl;
				cout << "Phone Number : " << root->number << endl;
				delete root;
				cout << "Candidate deleted successfully." << endl;
				return temp;
			}

			Node* temp = inorderPre(root->left);
			strcpy_s(root->name, temp->name);
			root->left = deleteNode(root->left, temp->name, temp->password);
		}
		return root;
	}

	void searchNode(Node* root, char* name, char* pass) {
		if (root != nullptr) {
			searchNode(root->left, name, pass);
			if (strcmp(root->name, name) == 0 && strcmp(root->password, pass) == 0) {
				cout << " Name : " << root->name << " , Phone No.: " << root->number<< endl;
			}
			searchNode(root->right, name, pass);
		}
	}

	Node* updateNode(Node* root, const char* name) {
		if (root != nullptr) {
			if (strcmp(root->name, name) == 0) {
				char newName[40];
				char newNumber[12];
				char newPass[4];
				char ch;
				cout << "Enter what you want to update name or phone number press 'N' for name and 'P' for  phone number and 'd' for password..";
				cin >> ch;
				while (ch == 'p' || ch == 'P' || ch == 'n' || ch == 'N' || ch == 'd' || ch == 'D') {
					if (ch == 'n' || ch == 'N') {
						cout << "Enter new Name: ";
						cin.ignore();
						cin.getline(newName, 40);
						strcpy_s(root->name, newName);
						break;
					}
					else if (ch == 'p' || ch == 'P') {
						cout << "Enter new Phone no.: ";
						cin.ignore();
						cin.getline(newNumber, 12);
						strcpy_s(root->number, newNumber);
						break;
					}
					else if (ch == 'd' || ch == 'D') {
						cout << "Enter new password.: ";
						cin.ignore();
						cin.getline(newPass, 4);
						strcpy_s(root->password, newPass);
						break;
					}
				}
				cout << "Candidate updated successfully." << endl;
				return root;
			}

			root->left = updateNode(root->left, name);
			root->right = updateNode(root->right, name);
		}
		return root;
	}

	void aOrder(Node* root) {
		if (root != nullptr) {
			aOrder(root->left);
			cout << " Name : " << root->name << endl << " Phone No.: " << root->number << endl << endl;
			aOrder(root->right);
		}
	}

	void displayResults(Node* root) const {
		if (root != nullptr) {
			displayResults(root->left);
			std::cout << root->name << ": " << root->votecount << " votes\n";
			displayResults(root->right);
		}
	}

	void writeBSTToFile(Node* root, ofstream& outFile) {
		if (root == nullptr) {
			return;
		}

		outFile << root->name << "\t" << root->number << "\t" << root->password << "\t" << root->votecount << endl;
		writeBSTToFile(root->left, outFile);
		writeBSTToFile(root->right, outFile);
	}

	void LoadBSTFile(ifstream& inFile) {
		root = NULL;
		Node* temproot = NULL;
		// Create a BST and insert data from the file
		while (inFile >> n >> num >> pass >> vtc) {
			temproot = insertNode(n,num, pass,vtc, temproot);
		}
		root = temproot;
	}

public:

	Candidate() {
		root = nullptr;
	}

	Node* getRoot() {
		return root;
	}

	void showAscending() {
		if (root == NULL) {
			cout << "NO Candidates to show ! " << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Printing Candidates List : " << endl;
			aOrder(root);
			cout << endl;
			_getch();
			system("cls");
		}
	}

	void insertCandidate() {
		cout << "Enter Candidate Name : ";
		cin.ignore();
		cin.getline(n, 40);
		cout << "Enter Candidate Mobile Number : ";
		cin.getline(num, 12);
		cout << "Enter Secure password ( Must be 4 characters ): ";
		cin.getline(pass, 4);

		root = insertNode(n, num, pass, 0, root);
	}

	void deleteCandidate() {
		if (root == nullptr) {
			cout << "No Candidate to delete !" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Enter Exact Name to delete : ";
			cin.ignore();
			cin.getline(n, 40);
			cout << "Enter Exact password : ";
			cin.ignore();
			cin.getline(pass, 4);
			root = deleteNode(root, n, pass);
			_getch();
			system("cls");
		}
	}

	void searchCandidate() {
		if (root == nullptr) {
			cout << "\nNo Candidates to search !" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Enter name of candidate. : ";
			cin.ignore();
			cin.getline(n, 40);
			cout << "Enter password of candidate. : ";
			cin.ignore();
			cin.getline(pass, 4);
			cout << endl;
			searchNode(root, n,pass);
			_getch();
			system("cls");
		}
	}

	void updateCandidate() {
		if (root == nullptr) {
			cout << "\nNo Candidate to Update!" << endl;
			_getch();
			system("cls");
		}
		else {
			cout << "Enetr name you want to update !" << endl;
			cout << "Enter Name : ";
			cin.ignore();
			cin.getline(n, 40);
			root = updateNode(root, n);
			_getch();
			system("cls");
		}
	}

	void displayResults() {
		if (root == nullptr) {
			cout << "\nNo Result to Display !" << endl;
			_getch();
			system("cls");
		}
		else {
			displayResults(root);
			_getch();
			system("cls");
		}
	}

	Node* findCandi(Node* root, char* name) {
		if (root != nullptr) {
			if (strcmp(root->name, name) == 0) {
				return root;
			}

			Node* leftResult = findCandi(root->left, name);
			if (leftResult != nullptr) {
				return leftResult;
			}

			return findCandi(root->right, name);
		}

		return nullptr;
	}

	void saveToFile() {
		ofstream outFile("candidate_data.txt");
		if (!outFile.is_open()) {
			cout << "Error opening file for writing." << endl;
			return;
		}

		writeBSTToFile(root, outFile);
		outFile.close();
		cout << "BST data written to file." << endl;
	}

	void getFromFile() {
		ifstream inFile("candidate_data.txt");
		if (!inFile.is_open()) {
			cout << "Error opening file for reading." << endl;
			return;
		}

		LoadBSTFile(inFile);
		inFile.close();
	}

};


class votingSystem : public Voter, public Candidate{
	Candidate candidates;
	Voter voters;
	char name[40];
	char pass[4];

public:

	void casteVote() {
		cout << "Enter Name : ";
		cin.ignore();
		cin.getline(name, 40);
		cout << "Enter password : ";
		cin.getline(pass, 4);
		int p;
		Voter::Node* voterp = findVoter(voters.getRoot(), name, pass);
		if (voterp == nullptr) {
			cout << "Voter Not Found!" << endl;
		}
		else {
			p = voterp->hasVoted;
			if (p == 1) {
				cout << "Voter has Already Voted" << endl;
			}
			else {
				char cand[40];
				cout << "Enter candidate Name : ";
				cin.getline(cand, 40);
				Candidate::Node* candp = findCandi(candidates.getRoot(), cand);
				if (candp != nullptr) {
					candp->votecount++;
					voterp->hasVoted = 1;
					cout << "Vote Cast Successfully" << endl;
				}
				else {
					cout << "Candidate not Found!" << endl;
				}
			}
		}
		
	}
	
	void voterMenu() {
		while (true) {
		system("cls");
			cout << "\n-----MENU-----\n";
			cout << "1. Register Voter\n";
			cout << "2. Delete Voter\n";
			cout << "3. Search Voter\n";
			cout << "4. Update Update\n";
			cout << "5. Print Voters List\n";
			cout << "6. Return back to main menu\n";
			int choice;
			cout << "Enter Choice :\n";
			cin >> choice;
			cout << "\n";

			switch (choice) {
			case 1:
				voters.insertVoter();
				_getch();
				system("cls");
				break;
			case 2:
				voters.delet();
				break;
			case 3:
				voters.searchVoter();
				break;
			case 4:
				voters.updateVoter();
				break;
			case 5:
				voters.showAscending();
				break;
			case 6:
				menu();
				break;
			default:
				cout << "Enter Correct Number ! " << endl;
				_getch();
			}
		}
	}

	void candidateMenu() {
		while (true) {
		system("cls");
			cout << "\n-----MENU-----\n";
			cout << "1. Register candidate\n";
			cout << "2. Delete candidate\n";
			cout << "3. Search candidate\n";
			cout << "4. Update candidate\n";
			cout << "5. Print candidates List\n";
			cout << "6. Return back to main menu\n";
			int choice;
			cout << "Enter Choice :\n";
			cin >> choice;
			cout << "\n";

			switch (choice) {
			case 1:
				candidates.insertCandidate();
				_getch();
				system("cls");
				break;
			case 2:
				candidates.deleteCandidate();
				break;
			case 3:
				candidates.searchCandidate();
				break;
			case 4:
				candidates.updateCandidate();
				break;
			case 5:
				candidates.showAscending();
				break;
			case 6:
				menu();
				break;
			default:
				cout << "Enter Correct Number ! " << endl;
				_getch();
			}
		}
	}

	void dataStore() {
		voters.saveToFile();
		candidates.saveToFile();
	}

	void dataGetters() {
		voters.getFromFile();
		candidates.getFromFile();
	}

	void password() {
		int i = 0;
		char ch, st[21], ch1[21] = { "pass" };
		cout << "\n\t\tEnter Password : ";
		while (1)
		{
			ch = _getch();
			if (ch == 13)
			{
				st[i] = '\0';
				break;
			}
			else if (ch == 8 && i > 0)
			{
				i--;
				cout << "\b \b";
			}
			else
			{
				cout << "*";
				st[i] = ch;
				i++;
			}
		}
		for (i = 0; st[i] == ch1[i] && st[i] != '\0' && ch1[i] != '\0'; i++);
		if (st[i] == '\0' && ch1[i] == '\0')
		{
			cout << endl;
			candidates.displayResults();
		}
		else
		{
			cout << "\n\n\t\tWrong Password.\n\n\t\ttry again.....\n";
			_getch();
			system("cls");
			menu();
		}
	}

	void menu() {
		char p;
		while (true) {
			system("cls");
			cout << "******************* Welcome to Your Online Voting Platform *******************" << endl;
			cout << "\nPress '1' For Voters Module.\n";
			cout << "\nPress '2' For candidates Module.\n";
			cout << "\npress '3' To Cast a Vote \n";
			cout << "\npress '4' To Display Votes Result \n";
			cout << "\npress '5' Exit Program \n\n";
			cout << "Enter Choice :";
			cin >> p;
			if (p == '1') {
				voterMenu();
			}
			else if (p == '2') {
				candidateMenu();
			}
			else if (p == '3') {
				casteVote();
				_getch();
				menu();
			}
			else if (p == '4') {
				password();
			}
			else if (p == '5') {
				dataStore();
				exit(0);
			}
			else {
				cout << "Wrong Choice Try Again..........." << endl;
				continue;
			}
				_getch();
		}
	}
};


int main() {
	votingSystem s;
	s.dataGetters();
	s.menu();
}