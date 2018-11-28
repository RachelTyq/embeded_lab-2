

#include <iostream>
#include <string>
#include<fstream>
#include <math.h>
using namespace std;
char hexstr[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
string invert_seq(string str)
{
	string opstr = "";
	for (int i = str.length() - 1; i >= 0; i--)
	{
		opstr += str[i];
	}
	return opstr;
}
int bin_to_dec(string str, int len)
{
	int output = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '1')
			output += pow(2, i);
	}
	return output;
}
string bin_to_HEX(string str, int len)
{
	int index = 0;
	string output = "";
	for (int i = 0; i < len ; i=i+4)
	{
		index = 0;
		if (str[i]=='1')
	    	index += pow(2, i);
		if (str[i+1] == '1')
			index += pow(2, i+1);
		if (str[i+2] == '1')
			index += pow(2, i+2);
		if (str[i+3] == '1')
			index += pow(2, i+3);
		output += hexstr[index];
	}
	output = invert_seq(output);
	return output;
}
void decode_mem_access(string a)
{
	string rn = a.substr(16, 4);
	string rd = a.substr(12, 4);
	string addr = a.substr(0, 12);
	int rnintex = bin_to_dec(rn, 4);
	int rdintex = bin_to_dec(rd, 4);
	int addrintex = bin_to_dec(addr, 12);
	if (a[20] == '1')
	{
		cout << "LDR  ";
	}
	else
	{
		cout << "STR  ";
	}
	cout << "R" << rdintex << ",[";
	cout << "R" << rnintex;
	if (a[24] == '0'){
		cout << "]";
	}

	if (a[25] == '0'&&addrintex != 0)
	{
		cout << ",";
		if (a[23] == '0')
			cout << "-";
		cout << "#" << addrintex;
	}
	else if (addrintex != 0)
	{
		cout << ",";
		if (a[23] == '0')
			cout << "-";
		cout<<"R" << addrintex;
	}
	if (a[24] == '1')
		cout << "]";

}
void decode_operate(string a)
{
	string opcode = a.substr(21, 4);
	string rn = a.substr(16, 4);
	string rd = a.substr(12, 4);
	string op2 = a.substr(0, 12);
	int rnintex = bin_to_dec(rn, 4);
	int rdintex = bin_to_dec(rd, 4);
	int op2intex = bin_to_dec(op2, 12);
	bool intexn = true;
	bool intexd = true;
	if (opcode == "0000")
		cout << "AND  ";
	if (opcode == "0010")
		cout << "ADD  ";
	if (opcode == "0101")
	{
		cout << "CMP  ";
		intexd = false;
	}
	if (opcode == "1011")
	{
		cout << "MOV  ";
		intexn = false;
	}
	if (opcode == "0011")
		cout << "ORR  ";
	if (intexd)
	{
		if (rdintex==14)
			cout << "LR"<< ",";
		else if (rdintex==15)
			cout << "PC" << ",";
		else
		cout << "R" << rdintex << ",";
	}
	if (intexn)
	{
		if (rnintex == 14)
			cout << "LR" << ",";
		else if (rnintex == 15)
			cout << "PC" << ",";
		else
		cout << "R" << rnintex << ",";
	}
	if (a[25] == '1')
	{
		cout << "#" << op2intex;
	}
	else
	{
		if (op2intex == 14)
			cout << "LR" ;
		else if (op2intex == 15)
			cout << "PC" ;
		else
		cout << "R" << op2intex;
	}

}
void decode_mul(string a)
{
	cout << "MUL  ";
	string rd = a.substr(16, 4);
	string rm = a.substr(0, 4);
	string rs = a.substr(8, 4);
	int rmintex = bin_to_dec(rm, 4);
	int rdintex = bin_to_dec(rd, 4);
	int rsintex = bin_to_dec(rs, 4);
	cout << "R" << rdintex << ",";
	cout << "R" << rmintex << ",";
	cout << "R" << rsintex;
}
void decode_mrs(string a)
{
	string rd=a.substr(12,4);
	int rdintex = bin_to_dec(rd, 4);
	cout << "MRS  ";
	if (rdintex != 15)
	{
		cout << "R" << rdintex<<",";
	}
	else { cout << "false,Rd can not be PC!"; }
	if (a[22] == '0')
		cout << "CPSR";
	else
		cout << "SPSR";

}
void decode_swi(string a)
{
	string label = a.substr(0, 24);
	int labelintex = bin_to_dec(label, 24);
	string label16 = bin_to_HEX(label, 24);
	cout << "SWI  ";
	//cout  << label16;
	cout << labelintex;
}
void decode_branch(string a)
{
	string label = a.substr(0, 24);
	//int labelintex = bin_to_dec(label, 24);
	string label16 = bin_to_HEX(label, 24);
	if (a[24] == '0')
	{
		cout << "B  ";
	}
	else
		cout << "BL  ";
	cout << "#"<<label16;

}
void classification(string line)
{
	string a = invert_seq(line);
	if (line.substr(4, 5) == "00010" && line.substr(10, 6) == "001111" && line.substr(20, 12) == "000000000000") {
		decode_mrs(a);
	}
	else if (line.substr(4, 4) == "1111"){
		decode_swi(a);
	}
	else if (line.substr(4, 3) == "101") {
		decode_branch(a);
	}
	else if (line.substr(4, 7) == "0000000" && line.substr(24, 4) == "1001") {
		decode_mul(a);
	}
	else if (line.substr(4, 2) == "00") {
		decode_operate(a);
	}
	else if (line.substr(4, 2) == "01") {
		decode_mem_access(a);
	}
	else {
		cout << "Fails!" << endl;
	}
}
void openfiles()
{
	ifstream in("arm.txt");
	string str;
	while (!in.eof())
	{
		getline(in, str);
		classification(str);
		cout << endl;
	}
	in.close();
}
int main()
{
	openfiles();
	return 0;
}
