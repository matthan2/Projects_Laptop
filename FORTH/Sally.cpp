// File: Sally.cpp
//
// CMSC 341 Spring 2017 Project 2
//
// Implementation of member functions of Sally Forth interpreter
//

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std;

#include "Sally.h"


// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
	m_kind = kind;
	m_value = val;
	m_text = txt;
}


// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
	m_kind = kind;
	m_value = val;
	m_dothis = fptr;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
	istrm(input_stream)  // use member initializer to bind reference
{

	symtab["DUMP"] = SymTabEntry(KEYWORD, 0, &doDUMP);

	symtab["+"] = SymTabEntry(KEYWORD, 0, &doPlus);
	symtab["-"] = SymTabEntry(KEYWORD, 0, &doMinus);
	symtab["*"] = SymTabEntry(KEYWORD, 0, &doTimes);
	symtab["/"] = SymTabEntry(KEYWORD, 0, &doDivide);
	symtab["%"] = SymTabEntry(KEYWORD, 0, &doMod);
	symtab["NEG"] = SymTabEntry(KEYWORD, 0, &doNEG);

	symtab["."] = SymTabEntry(KEYWORD, 0, &doDot);
	symtab["SP"] = SymTabEntry(KEYWORD, 0, &doSP);
	symtab["CR"] = SymTabEntry(KEYWORD, 0, &doCR);
	
	symtab[">"] = SymTabEntry(KEYWORD, 0, &doGreater);
	symtab[">="] = SymTabEntry(KEYWORD, 0, &doGreaterEqu);
	symtab["<"] = SymTabEntry(KEYWORD, 0, &doLesser);
	symtab["<="] = SymTabEntry(KEYWORD, 0, &doLesserEqu);
	symtab["=="] = SymTabEntry(KEYWORD, 0, &doEqu);
	symtab["!="] = SymTabEntry(KEYWORD, 0, &doNotEqu);

	symtab["DUP"] = SymTabEntry(KEYWORD, 0, &doDUP);
	symtab["DROP"] = SymTabEntry(KEYWORD, 0, &doDROP);
	symtab["SWAP"] = SymTabEntry(KEYWORD, 0, &doSWAP);
	symtab["ROT"] = SymTabEntry(KEYWORD, 0, &doROT);

	symtab["SET"] = SymTabEntry(KEYWORD, 0, &doSET);
	symtab["@"] = SymTabEntry(KEYWORD, 0, &doAT);
	symtab["!"] = SymTabEntry(KEYWORD, 0, &doExclaim);

	symtab["AND"] = SymTabEntry(KEYWORD, 0, &doAND);
	symtab["OR"] = SymTabEntry(KEYWORD, 0, &doOR);
	symtab["NOT"] = SymTabEntry(KEYWORD, 0, &doNOT);

	symtab["IFTHEN"] = SymTabEntry(KEYWORD, 0, &doIFTHEN);
	symtab["ELSE"] = SymTabEntry(KEYWORD, 0, &doELSE);
	symtab["ENDIF"] = SymTabEntry(KEYWORD, 0, &doENDIF);

	symtab["DO"] = SymTabEntry(KEYWORD, 0, &doDO);
	symtab["UNTIL"] = SymTabEntry(KEYWORD, 0, &doUNTIL);
}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
	string line;     // single line of input
	int pos;         // current position in the line
	int len;         // # of char in current token
	long int n;      // int value of token
	char *endPtr;    // used with strtol()


	while (true) {    // keep reading until empty line read or eof

					  // get one line from standard in
					  //
		getline(istrm, line);

		// if "normal" empty line encountered, return to mainLoop
		//
		if (line.empty() && !istrm.eof()) {
			return true;
		}

		// if eof encountered, return to mainLoop, but say no more
		// input available
		//
		if (istrm.eof()) {
			return false;
		}


		// Process line read

		pos = 0;                      // start from the beginning

									  // skip over initial spaces & tabs
									  //
		while (line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t')) {
			pos++;
		}

		// Keep going until end of line
		//
		while (line[pos] != '\0') {

			// is it a comment?? skip rest of line.
			//
			if (line[pos] == '/' && line[pos + 1] == '/') break;

			// is it a string literal? 
			//
			if (line[pos] == '.' && line[pos + 1] == '"') {

				pos += 2;  // skip over the ."
				len = 0;   // track length of literal

						   // look for matching quote or end of line
						   //
				while (line[pos + len] != '\0' && line[pos + len] != '"') {
					len++;
				}

				// make new string with characters from
				// line[pos] to line[pos+len-1]
				string literal(line, pos, len);  // copy from pos for len chars

												 // Add to token list
												 //
				tkBuffer.push_back(Token(STRING, 0, literal));

				// Different update if end reached or " found
				//
				if (line[pos + len] == '\0') {
					pos = pos + len;
				}
				else {
					pos = pos + len + 1;
				}

			}
			else {  // otherwise "normal" token

				len = 0;  // track length of token

						  // line[pos] should be an non-white space character
						  // look for end of line or space or tab
						  //
				while (line[pos + len] != '\0' && line[pos + len] != ' ' && line[pos + len] != '\t') {
					len++;
				}

				string literal(line, pos, len);   // copy form pos for len chars
				pos = pos + len;

				// Try to convert to a number
				//
				n = strtol(literal.c_str(), &endPtr, 10);

				if (*endPtr == '\0') {
					tkBuffer.push_back(Token(INTEGER, n, literal));
				}
				else {
					tkBuffer.push_back(Token(UNKNOWN, 0, literal));
				}
			}

			// skip over trailing spaces & tabs
			//
			while (line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t')) {
				pos++;
			}

		}
	}
}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
	Token tk;
	bool more = true;

	while (more && tkBuffer.empty()) {
		more = fillBuffer();
	}

	if (!more && tkBuffer.empty()) {
		throw EOProgram("End of Program");
	}

	tk = tkBuffer.front();
	tkBuffer.pop_front();
	return tk;
}


// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {

	Token tk;
	map<string, SymTabEntry>::iterator it;

	try {
		while (1) {
			tk = nextToken();

			if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

				// if INTEGER or STRING just push onto stack
				params.push(tk);

			}
			else {
				it = symtab.find(tk.m_text);

				if (it == symtab.end()) {   // not in symtab

					params.push(tk);

				}
				else if (it->second.m_kind == KEYWORD) {

					// invoke the function for this operation
					//
						it->second.m_dothis(this);

				}
				else if (it->second.m_kind == VARIABLE) {

					// variables are pushed as tokens
					//
					tk.m_kind = VARIABLE;
					params.push(tk);

				}
				else {

					// default action
					//
					params.push(tk);

				}
			}
		}

	}
	catch (EOProgram& e) {

		cerr << "End of Program\n";
		if (params.size() == 0) {
			cerr << "Parameter stack empty.\n";
		}
		else {
			cerr << "Parameter stack has " << params.size() << " token(s).\n";
		}

	}
	catch (out_of_range& e) {

		cerr << "Parameter stack underflow??\n";

	}
	catch (...) {

		cerr << "Unexpected exception caught\n";

	}
}

// -------------------------------------------------------


void Sally::doPlus(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for +.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value + p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}


void Sally::doMinus(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for -.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value - p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}


void Sally::doTimes(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for *.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value * p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}


void Sally::doDivide(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for /.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value / p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}


void Sally::doMod(Sally *Sptr) {
	Token p1, p2;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for %.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	int answer = p2.m_value % p1.m_value;
	Sptr->params.push(Token(INTEGER, answer, ""));
}


void Sally::doNEG(Sally *Sptr) {
	Token p;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for NEG.");
	}
	p = Sptr->params.top();
	Sptr->params.pop();
	Sptr->params.push(Token(INTEGER, -p.m_value, ""));
}


void Sally::doDot(Sally *Sptr) {

	Token p;
	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameter for .");
	}

	p = Sptr->params.top();
	Sptr->params.pop();

	if (p.m_kind == INTEGER) {
		cout << p.m_value;
	}
	else {
		cout << p.m_text;
	}
}


void Sally::doSP(Sally *Sptr) {
	cout << " ";
}


void Sally::doCR(Sally *Sptr) {
	cout << endl;
}

void Sally::doGreater(Sally * Sptr)
{
	Token p1, p2;
	int answer = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for >.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	if (p2.m_value > p1.m_value)
	{
		answer = 1;
	}
	else
	{
		answer = 0;
	}


	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doGreaterEqu(Sally * Sptr)
{
	Token p1, p2;
	int answer =0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for >=.");
	}
	p1 = Sptr->params.top();

	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	if (p2.m_value >= p1.m_value)
		{
			answer = 1;
		}
		else
		{
			answer = 0;
		}

		Sptr->params.push(Token(INTEGER, answer, ""));
	
}

void Sally::doLesser(Sally * Sptr)
{
	Token p1, p2;
	int answer = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for <");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	if (p2.m_value < p1.m_value)
	{
		answer = 1;
	}
	else
	{
		answer = 0;
	}


	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doLesserEqu(Sally * Sptr)
{
	Token p1, p2;
	int answer = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for <=.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	if (p2.m_value <= p1.m_value)
	{
		answer = 1;
	}
	else
	{
		answer = 0;
	}


	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doEqu(Sally * Sptr)
{
	Token p1, p2;
	int answer = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for ==.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	if (p2.m_value == p1.m_value)
	{
		answer = 1;
	}
	else
	{
		answer = 0;
	}

	
	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doNotEqu(Sally * Sptr)
{
	Token p1, p2;
	int answer = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for !=.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	if (p2.m_value != p1.m_value)
	{
		answer = 1;
	}
	else
	{
		answer = 0;
	}



	Sptr->params.push(Token(INTEGER, answer, ""));
}

void Sally::doDUP(Sally * Sptr)
{
	Token p1;
	int num;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameters for DUP.");
	}
	p1 = Sptr->params.top();
	Sptr->params.pop();
	num = p1.m_value;

	Sptr->params.push(Token(INTEGER, num, ""));
	Sptr->params.push(Token(INTEGER, num, ""));
}

void Sally::doDROP(Sally * Sptr)
{

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need one parameters for DROP.");
	}
	Sptr->params.pop();
}

void Sally::doSWAP(Sally * Sptr)
{
	Token p1, p2;
	int num1, num2;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for SWAP.");
	}

	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();

	num1 = p1.m_value;
	num2 = p2.m_value;

	Sptr->params.push(Token(INTEGER, num1, ""));
	Sptr->params.push(Token(INTEGER, num2, ""));
}

void Sally::doROT(Sally * Sptr)
{
	Token p1, p2, p3;
	int num1, num2, num3;
	if (Sptr->params.size() < 3) {
		throw out_of_range("Need three parameters for ROT.");
	}

	p1 = Sptr->params.top();
	Sptr->params.pop();
	p2 = Sptr->params.top();
	Sptr->params.pop();
	p3 = Sptr->params.top();
	Sptr->params.pop();

	num1 = p3.m_value;
	num2 = p1.m_value;
	num3 = p2.m_value;

	Sptr->params.push(Token(INTEGER, num3, ""));
	Sptr->params.push(Token(INTEGER, num2, ""));
	Sptr->params.push(Token(INTEGER, num1, ""));
}

void Sally::doSET(Sally * Sptr)
{
	Token varName, varNum;
	string def;
	int value;
	map<string, SymTabEntry>::iterator it;


	SymTabEntry s1;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for SET.");
	}


	varName = Sptr->params.top();
	Sptr->params.pop(); //variable name
	if (!isalpha(varName.m_text[0]))
	{
		cout << "Not a string" << endl;
	}
	else
	{


		def = varName.m_text;


		varNum = Sptr->params.top();
		Sptr->params.pop();	// its value

		if (varNum.m_kind != INTEGER)
		{
			cout << "Not an Integer." << endl;
		}
		else
		{


			value = varNum.m_value;


			it = Sptr->symtab.find(def);



			//cant find duplicate == Good
			if (it != Sptr->symtab.end())
			{
				cout << "Bad parameters, duplicate variable." << endl;

			}
			else
			{




				s1.m_value = varNum.m_value;
				s1.m_kind = VARIABLE;
				//Sptr->symtab[def].m_value = value;
															// map<char, int> first;
							//  first['a'] = 10;
				Sptr->symtab[def] = s1; //adds to symtable
			}
		}
	}
}

void Sally::doAT(Sally * Sptr)
{
	Token potCopy;
	int value;
	string name;
	map<string, SymTabEntry>::iterator it;

	if (Sptr->params.size() < 1) {
		throw out_of_range("Need a parameters for @.");
	}

	potCopy = Sptr->params.top();
	Sptr->params.pop();		//variable name
	name = potCopy.m_text;
	it = Sptr->symtab.find(name);
	if (potCopy.m_kind == INTEGER)
	{
		cout << "this is the wrong set up" << endl;
	}
	else
	{


		if (it != Sptr->symtab.end()) //|| //(!isdigit(value)))
		{
			value = Sptr->symtab[name].m_value;

			Sptr->params.push(Token(INTEGER, value, ""));
		}
		else
		{
			cout << "no such varible" << endl;
		}
	}
}

void Sally::doExclaim(Sally * Sptr)
{
	Token potCopy, numCopy;
	int value;
	string name;
	map<string, SymTabEntry>::iterator it;

	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for !.");
	}

	potCopy = Sptr->params.top();
	Sptr->params.pop();		//variable name
	name = potCopy.m_text;
	it = Sptr->symtab.find(name);
	if (potCopy.m_kind == INTEGER)
	{
		cout << "this is the wrong set up" << endl;
	}
	else
	{


		numCopy = Sptr->params.top();
		Sptr->params.pop();
		value = numCopy.m_value;
		if (numCopy.m_kind != INTEGER)
		{
			cout << "this is the wrong set up" << endl;
		}
		else
		{


			if (it != Sptr->symtab.end())
			{
				Sptr->symtab[name].m_value = value;

			}
			else
			{
				cout << "no entry exists" << endl;
			}
		}
	}
}

void Sally::doAND(Sally * Sptr)
{
	Token sav1, pot2, pot;
	int truth1 = 0;
	int truth2 = 0;
	int realTrue = 0;
	stack <Token> save;
	int count = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for AND.");
	}
	while ((!Sptr->params.empty()) && (count != 2 ))
	{
		sav1 = Sptr->params.top();
		if (sav1.m_kind == INTEGER)
		{
			if (count == 1)
			{
				truth2 = sav1.m_value;
			}
			if (count == 0)
			{
				truth1 = sav1.m_value;
			}
			count++;
		
		}
		if(!sav1.m_kind == INTEGER)
		save.push(sav1);

		Sptr->params.pop();
	}
	while (!save.empty())
	{
		sav1 = save.top();
		Sptr->params.push(sav1);
		save.pop();
	}



	if ((truth1 != 1) && (truth1 != 0))
	{
		cout << "First pop not a boolean" << endl;
	}
	else
	{
		if ((truth2 != 1) && (truth2 != 0))
		{
			cout << "Second pop not a boolean" << endl;
		}
		else
		{


			if ((truth1 == 1)&&(truth2 == 1))
			{
				realTrue = 1;
				
			}
			else
			{
				realTrue = 0;
			
			}
			Sptr->params.push(Token(INTEGER, realTrue, ""));
		}
	}
}

void Sally::doOR(Sally * Sptr)
{
	Token sav1, pot2, pot;
	int truth1 = 0;
	int truth2 = 0;
	int realTrue = 0;
	stack <Token> save;
	int count = 0;
	if (Sptr->params.size() < 2) {
		throw out_of_range("Need two parameters for OR.");
	}
	while ((!Sptr->params.empty()) && (count != 2))
	{
		sav1 = Sptr->params.top();
		if (sav1.m_kind == INTEGER)
		{
			if (count == 1)
			{
				truth2 = sav1.m_value;
			}
			if (count == 0)
			{
				truth1 = sav1.m_value;
			}
			count++;

		}
		if (!sav1.m_kind == INTEGER)
			save.push(sav1);

		Sptr->params.pop();
	}
	while (!save.empty())
	{
		sav1 = save.top();
		Sptr->params.push(sav1);
		save.pop();
	}



	if ((truth1 != 1) && (truth1 != 0))
	{
		cout << "First pop not a boolean" << endl;
	}
	else
	{
		if ((truth2 != 1) && (truth2 != 0))
		{
			cout << "Second pop not a boolean" << endl;
		}
		else
		{


			if ((truth1 == 1) || (truth2 == 1))
			{
				realTrue = 1;

			}
			else
			{
				realTrue = 0;

			}
			Sptr->params.push(Token(INTEGER, realTrue, ""));
		}
	}
}

void Sally::doNOT(Sally * Sptr)
{
	Token sav1, pot2, pot;
	int truth1 = 0;
	int truth2 = 0;
	int realTrue = 0;
	stack <Token> save;
	int count = 0;
	if (Sptr->params.size() < 1) {
		throw out_of_range("Need a parameter for NOT.");
	}
	while ((!Sptr->params.empty()) && (count != 1))
	{
		sav1 = Sptr->params.top();
		if (sav1.m_kind == INTEGER)
		{
			if (count == 1)
			{
				truth2 = sav1.m_value;
			}
			if (count == 0)
			{
				truth1 = sav1.m_value;
			}
			count++;

		}
		if (!sav1.m_kind == INTEGER)
			save.push(sav1);

		Sptr->params.pop();
	}
	while (!save.empty())
	{
		sav1 = save.top();
		Sptr->params.push(sav1);
		save.pop();
	}



	if ((truth1 != 1) && (truth1 != 0))
	{
		cout << "First pop not a boolean" << endl;
	}
	else
	{
		if ((truth2 != 1) && (truth2 != 0))
		{
			cout << "Second pop not a boolean" << endl;
		}
		else
		{


			if ((truth1 != 1) && (truth2 != 1))
			{
				realTrue = 1;

			}
			else
			{
				realTrue = 0;

			}
			Sptr->params.push(Token(INTEGER, realTrue, ""));
		}
	}
}


/*
IfTHEN false we pop everything up till ELSE
IFTHEN true we head back to the main loop
*/
void Sally::doIFTHEN(Sally * Sptr)
{
	Token p1, p2, t1;
	p2 = Sptr->params.top();
	list<Token> temp;
	list<Token>::iterator it;
	if(Sptr->tkBuffer.empty())
	Sptr->fillTK(Sptr);

	temp = Sptr->tkBuffer;

		if (p2.m_value == 0)
		{
			for (it = temp.begin(); it != temp.end(); it++) //iterate through
			{
				p1 = *it; //position in the loop token
				while (p1.m_text != "ELSE")
				{
					if (Sptr->tkBuffer.empty())
					{
						Sptr->fillTK(Sptr);
					}
					else
					{


						temp.pop_front();
						p1 = temp.front();
					}
				}
				if (p1.m_text == "ELSE")
				{
					temp.pop_front();
					Sptr->tkBuffer = temp;

					break; //hops out
				}
			}

		}



}


/*
At this point if the else conditional came to fruitition, it has already passed it tokens
Now we find ENDIF, throw out all tokens until then, checks for empty buffer
*/
void Sally::doELSE(Sally * Sptr)
{
	Token p1, p2;
	list<Token> temp;
	temp = Sptr->tkBuffer;
	list<Token>::iterator it;
	p2 = Sptr->params.top();

			for (it = temp.begin(); it != temp.end(); it++)
			{
				p1 = *it;
				while (p1.m_text != "ENDIF" && (!temp.empty()))
				{
					
					temp.pop_front();
					if(!temp.empty())
					p1 = temp.front();
					Sptr->tkBuffer = temp;

				}
				while (p1.m_text == "ENDIF" && (!Sptr->tkBuffer.empty()))
				{
					temp.pop_front();
					if(!temp.empty())
					p1 = temp.front();
					if(!Sptr->params.empty())
					Sptr->params.pop();
					Sptr->tkBuffer = temp;

				}
				break;
			}

		
	
}

void Sally::doENDIF(Sally * Sptr)
{
	Token p1;

			if(!Sptr->params.empty())
			Sptr->params.pop();
		

}

void Sally::doDO(Sally * Sptr)
{
	Token p1, p2;
	list<Token> temp1, temp2;
	list<Token>::iterator it;

	while((Sptr->tkBuffer.empty()) || (Sptr->tkBuffer.back().m_text != "UNTIL")) //fill tk
	Sptr->fillTK(Sptr);

	temp1 = Sptr->tkBuffer;

	//it = temp1.begin();
//	p1 = temp1.front();



	
	Sptr->dowhilesave = Sptr->tkBuffer; //save tk

}

void Sally::doUNTIL(Sally * Sptr)
{
	Token p1, p2;
	list<Token> temp1;
	temp1 = Sptr->dowhilesave; //use the saved tokens
	list<Token>::iterator it;

	if (Sptr->params.empty())
	{
			throw out_of_range("A condition is required before UNTIL.");
	}
	else
		p2 = Sptr->params.top();

	if(p2.m_value == 0) //false conditional, keep going
	{
		if (!Sptr->params.empty())
			p2 = Sptr->params.top();
		
		
		Sptr->tkBuffer = temp1;

	}
	if (p2.m_value == 1) //condition has been met, pop the save list
	{
		while (!Sptr->dowhilesave.empty())
		{
			Sptr->dowhilesave.pop_back();
			if (!Sptr->params.empty()) 
				Sptr->params.pop();
		}
	}
}


void Sally::doDUMP(Sally *Sptr) {
	// do whatever for debugging
	

}

void Sally::fillTK(Sally *Sptr)
{
	list<Token> temp1;
	list<Token>::iterator it;
	if (!Sptr->istrm.eof()) //not empty
	{

	Sptr->fillBuffer(); //fills the tkbuffer to hand /n spaces

	}
	//it = Sptr->tkBuffer.begin();
}
