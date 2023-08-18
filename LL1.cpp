//Karam issa 20200585
//Beybars Abaza 20200715
//Jude Hamdan 20200856
//Aws almahasneh 20200388





#include<iostream>
#include<string>
#include<stack>

using namespace std;
/*
LL(1) Parsing:
Here the 1st L represents that the scanning of the Input will be done from Left to Right manner
and the second L shows that in this parsing technique we are going to use Left most Derivation Tree.
And finally, the 1 represents the number of look-ahead, which means how many symbols are you going to
see when you want to make a decision.
*/

/*
step 1: hardcode teh grammar appropriately into the productionSet without left recursion
Step 2: Calculate First() and Follow() for all non-terminals.
Step 3: calculate each production rule and fill the parsing table
step 4: parsing program in a function to cehck if a given input string is accepted or not

*/

//Each non termincal vocabulary literal(character) is represented by one UpperCase letter [A-Z]
//each terminal vocabulary literal(cahrater) is represented by one lowerCase Letter[a-z]
//LHS and RHS of each production Rule will be separated by a "=" symbol instead of "->"
//program assumes there will be no blank space within a production rule string and left recursion is avoided in all input productions
//epsilon will be represented using the '#'


//grammar:
//A->aBc
//B->bB|b

//functions
void firstOf(char[], char);
void followOf(char[], char);
void firstFollow(char[], char);
void addToResultSet(char[], char);
bool noEpsilonInFollow(char[]);
void findParsingTable();
bool epsilonSearch(char[]);
void getRules(string[], char);
int findPos(char);
int findPosVn(char);
void parsingProg(string);
int global_i = 0;
int global_j = 0;
const int  numberOfProductionRules = 3;
//grammer is hard coded into the 2-D array
char productionSet[10][10] = { "A=aBa", "B=bB", "B=c" };
char nonTerminalChar[3] = { 'A', 'B' };
char terminalChar[4] = { 'a', 'b', 'c' };
char first[5][5];
char follow[5][5];

string parsingTable[10][10];

string a[5];

stack<char> st;

int main() {

	cout << "LL(1) Parser to calculate the first and follow sets of a given grammar, calculate and fill the parsing table, and parsing program to check if language is accepted or not when teh parsing is complete " << endl;


	cout <<endl<< endl << "Grammar: " << endl;
	cout << "A->aBa" << endl;
	cout << "B->bB|c" << endl;


	cout << endl << endl;

	//to calculate the first functions of the Vn
	for (int i = 0; nonTerminalChar[i] != '\0'; i++) {
		//loop through each Vn character and find its first set, after that add the set to the corresponding row in the first2d array
		//first parameter is a 1d array at index i, and the corresponding nonTerminalChar
		firstOf(first[i], nonTerminalChar[i]);
	}

	//printing out the first array to show the first set calculated for each non termianl character
	for (int i = 0; i < 2; i++) {
		cout << "The first of " << nonTerminalChar[i] << ": {";
		for (int j = 0; j < 2; j++) {
			cout << first[i][j] << " ";
		}
		cout << " }" << endl;
	}
	cout << endl;
	//------------------------------------------------------------------------------first done


	for (int i = 0; nonTerminalChar[i] != '\0'; i++) {
		//loop through each Vn character and find its folow set, after that add the set to the corresponding row in the follow2d array
		//first parameter is a 1d array at index i, and the corresponding nonTerminalChar
		followOf(follow[i], nonTerminalChar[i]);
	}

	//printing out the follow array to show the follow set calculated for each non termianl character
	for (int i = 0; i < 2; i++) {
		cout << "The follow of " << nonTerminalChar[i] << ": {";
		for (int j = 0; j < 2; j++) {
			cout << follow[i][j] << " ";
		}
		cout << " }" << endl;
	}
	cout << endl;

	//------------------------------------------------------------------------------follow done
	findParsingTable();//call this function to fill the parsing table
	cout << "Parsing Table" << endl;
	cout << "\ta\tb\tc\t$" << endl;
	cout << "-----------------------------------" << endl;
	for (int i = 0; i < numberOfProductionRules; i++) {
		if (i > 0) {
			if (productionSet[i][0] ==  productionSet[i - 1][0])break;
		}
		cout << productionSet[i][0] << "| ";
		
		for (int j = 0; j < 10; j++) {
			if (parsingTable[i][j].empty()) {
				cout << "\t";
			}
			else {
				cout << "\t" << parsingTable[i][j];
			}
		}
		cout << endl;
	}

	//------------------------------------------------------------------------------Parsing table calculated and printed

	string usrInput;
	cout << endl;
	cout << "Please enter a string to check if it is accepeted: ";
	cin >> usrInput;

	parsingProg(usrInput);
	//------------------------------------------------------------------------------Parsing is complete
	return 0;
}


/*Parsing program takes in an input string and checks wether it is accepted or not by checking the production rules in
the parsing table*/
void parsingProg(string buffer)
{
	//Push the end delimeter into the stack
	st.push('$');
	//Push the starting symbol into the stack
	st.push(productionSet[0][0]);
	//Add end delimeter to the end of the input string
	buffer = buffer += '$';
	//Keep looping while both stack and buffer have not reached the end delimeter
	while (st.top() != '$' && buffer != "$")
	{ //Check if stack top is a Vt
		if (st.top() >= 'a' && st.top() <= 'z')
		{	//Given the stack top is a Vt check if it matches the first character in the buffer
			if (buffer[0] == st.top())
			{
				//If it does match Vt=Vt pop the stack and erase the first character in the buffer string
				st.pop();
				buffer.erase(0, 1);

			}
			else {
				//Else the stack top is a vt and it does not match the first character in the buffer then language is not accepted
				cout << "Parsing is complete language is not accepted as the Vts do not match" << endl;
				break;
			}
		}
		//Check if stack top is a Vn
		else if (st.top() >= 'A' && st.top() <= 'Z')
		{ //Given it is a Vn check if the character at the start of the buffer coinciding with the Vn gives a prod rule in parsing table
			if (!parsingTable[findPosVn(st.top())][findPos(buffer[0])].empty())
			{//Save the appropriate production in the string temp
				string temp = parsingTable[findPosVn(st.top())][findPos(buffer[0])];
				if (temp == "#")
				{
					//If the production rule gives Epsilon pop the Vn from the stack
					st.pop();
				}
				else
				{
					//Else if the production rule exists and does not give epsilon pop the Vn from the stack
					st.pop();

					for (int i = temp.length() - 1; i >= 0; i--)
					{
						//Push the characters of the production rule on the right hand side into the stack from right to left
						st.push(temp[i]);
					}
				}
			}
			else {//If no relationship is found then the language is not accepted

				if ((parsingTable[findPosVn(st.top())][findPos(buffer[0])].empty()))
				{
					cout << "Parsing is complete language is not accepted as no relationship was found in the parsing table" << endl;
					break;
				}
			}
		}
	}

	if (st.top() == '$' && buffer == "$")
		cout << "Parsing is complete language is accepted" << endl;

}






//will get and store all availbe production rules from the productionSet 2d array and fill them in the string a so we can insert them into the parsing table
//will get and store all availbe production rules from the productionSet 2d array and fill them in the string a so we can insert them into the parsing table
void  getRules(string a[], char c) {
	int index = 0;
	for (int i = 0; i < numberOfProductionRules; i++) {
		//keep  looping to find production rule with X on the LHS, as the productionSet array is 2d, LHS will always be in the first column so 
		if (productionSet[i][0] == c) {
			string n = "";
			for (int j = 2; productionSet[i][j] != '\0'; j++) {
				n = n + productionSet[i][j];
			}
			a[index] = n;
			index++;
		}


	}

}


//given a character c(Vt) it will return teh column index
int findPos(char c) {
	switch (c) {
	case 'a': return 0;
	case 'b': return 1;
	case 'c': return 2;
	case '$': return 4;
	}

}

int findPosVn(char c)
{
	switch (c)
	{
	case 'A': return 0;
	case 'B': return 1;
	}
}


void findParsingTable() {
	string a[5];
	for (int n = 0; n < strlen(nonTerminalChar); n++) {
		for (int i = 0; first[n][i] != '\0'; i++) {
			for (int j = 0; follow[n][j] != '\0'; j++) {
				if ((first[n][i] == follow[n][j]) || (epsilonSearch(first[n]))) {
					//similarty is found at row n we add epilon through the elements of the follow OR epsilon found in teh first array 

					for (int k = 0; follow[n][k] != '\0'; k++) {
						parsingTable[n][findPos(follow[n][k])] = "#";
					}

				}
				else {//not simimlar it will go through to the RHS through the elemetns of teh first
					//looop thoruhg the elemetns of the firstoF(elemlnt)
					for (int x = 0; first[n][x] != '\0'; x++) {
						//get rules will fill the array of a wiht all the possible prdouction rules for every given vn
						getRules(a, productionSet[n][0]);
						parsingTable[n][findPos(first[n][x])] = a[x];
					}
				}
			}
		}
	}

}
//fucntion if firstOf(A) = # and if so remove # from the result array and call teh firstOf(next element)
bool noEpsilonInFollow(char Result[]) {
	for (int i = 0; Result[i] != '\0'; i++) {
		if (Result[i] == '#') {
			Result[i] = '\0';
			return false;

		}
	}
	return true;
}

//searches for epsilon in a given array
bool epsilonSearch(char Result[]) {
	for (int i = 0; Result[i] != '\0'; i++) {
		if (Result[i] == '#') {
			return true;

		}

	}
	return false;
}


/*
	Rules for follow computaion

		1)Place $ in followOf(starting symbol)
		2)If A->aB, followOf(B) = follow(A)
		3)If a->aBC, then
			if # is in firstof(C),then
				followof(B) =(firstOf(C)-{#}) U followOf(A)
			else
				followOf(B) = firstOf(C)



*/
void followOf(char Result[], char c)
{
	//1)Place $ in followOf(starting symbol)
	if (productionSet[0][0] == c)addToResultSet(Result, '$');
	//loop through each production Rules
	for (global_i = 0; global_i < numberOfProductionRules; global_i++)
	{
		//loop through the end of each production starting from the first elemetn in the RHS
		for (global_j = 2; global_j < strlen(productionSet[global_i]); global_j++)
		{
			//reach the Vn we are calculating the followOf function
			if (productionSet[global_i][global_j] == c)
			{
				//call the first function to find the follow
				if (productionSet[global_i][global_j + 1] != '\0')
					firstFollow(Result, productionSet[global_i][global_j + 1]);

				//recurively call the follow of until calculating the follow result array
				if (productionSet[global_i][global_j + 1] == '\0' && c != productionSet[global_i][0])
					followOf(Result, productionSet[global_i][0]);
			}
		}
	}
}
void firstFollow(char Result[], char c)
{
	int k;

	if (!(isupper(c)))addToResultSet(Result, c);

	for (k = 0; k < numberOfProductionRules; k++)
	{
		if (productionSet[k][0] == c)
		{
			if (productionSet[k][2] == '$') followOf(Result, productionSet[global_i][0]);
			else if (!(isupper(productionSet[k][2]))) addToResultSet(Result, productionSet[k][2]);
			else firstFollow(Result, productionSet[k][2]);
		}
	}
	//checker to see if epsilon was added to the follow set, and if so it will call the firstFollow function to the next element int the production rule
	int g = 1;
	while (!noEpsilonInFollow(Result)) {

		firstFollow(Result, productionSet[k][2 + g]);
		g++;
	}


}

/*
Rules for First Computation


	1)If x is terminal, then firstOf(x) = {x}
	2)If x->#, then add # to the firstOf(x)- # is epsilon
	3)if X is a non terminal and X->ABC then
		firstOf(X) = firstOf(A)
			If firstOf(A) containes #, then
				firstOf(X) = (firstOf(A) - {#}) U firstOf(BC)
*/



//computer the elements in firstOf(c) and write them in result Array 
void firstOf(char Result[], char c) {
	int i, j, k;
	char tempResult[20];
	int epsilonFlag;
	tempResult[0] = '\0';
	Result[0] = '\0';


	//if x is terminal, firstOf(X) = {x}
	//The isupper() function in C++ checks if the given character is a uppercase character or not.
	if (!(isupper(c)))
	{
		addToResultSet(Result, c);
		return;
	}


	//if X is non terminal Read each production
	for (i = 0; i < numberOfProductionRules; i++) {
		//keep  looping to find production rule with X on the LHS, as the productionSet array is 2d, LHS will always be in the first column so 
		if (productionSet[i][0] == c) {

			//check if x = # is a production rule, and then add #(epsilon) to firstOf(X)
			//array prodcution set
			//  0	1	2	3	4	5	6	7	8	9
			// LHS  =   RHS
			//so the RHS will always be the in the second column of the array

			if (productionSet[i][2] == '#')
				addToResultSet(Result, '#');

			//\\if X is a non-terminal and x->Y1 Y2, then add a to the first
			//\\if for some i, a is in firstOf(Y1), and e is in all of  of firstOf(Y1), firstOf(Y2),..., firstOf(Yi-1)
			else {
				//start counter at RHS
				j = 2;

				while (productionSet[i][j] != '\0') {
					epsilonFlag = 0;
					//keep calling first of RHS adn put results in a temp array called tempResult
					firstOf(tempResult, productionSet[i][j]);

					//as long as tempResult has characters add them to the original resulat array passed throught the parameter
					for (k = 0; tempResult[k] != '\0'; k++)
						addToResultSet(Result, tempResult[k]);
					//if when calling firstOF and we got # in tempResult then no we need to stop, by activating an exit flag
					for (k = 0; tempResult[k] != '\0'; k++)
						if (tempResult[k] == '#') {
							epsilonFlag = 1;
							break;
						}


					//if epsilon found, no need to check next elementin the particaular production rule

					if (!epsilonFlag)
						break;


					j++;
				}
				//exited teh while loop



			}

			//end of else statement
		}
	}

	return;
}


//this function adds the coputed element to result set wihtout duplication (multiple inclusion of elements)





void addToResultSet(char Result[], char element) {
	int i;
	for (i = 0; Result[i] != '\0'; i++)
		//if the element is found
		if (Result[i] == element) {
			return;
		}
	Result[i] = element;
	Result[i + 1] = '\0';

}
