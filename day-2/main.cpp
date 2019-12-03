#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

std::vector<int> value;
const int halt = 99;

//-----------------------------------------------------------------------------

void get_values()
{
	int a;
	std::ifstream infile("input-modified.txt");
	while (infile >> a){
		value.push_back(a);
		if (infile.peek() == ',')
			infile.ignore();
	}
	return;
}

//-----------------------------------------------------------------------------

int execute_opcode(int opcode, int v1, int v2)
{
int result = 0;
switch (opcode) {
	case 1:
		result = v1 + v2;
		break;
	case 2:
		result = v1 * v2;
		break;
}
return result;
}

//-----------------------------------------------------------------------------

void calculate()
{
	for (int i = 0; i <= value.size(); i+=4) {
		if (value[i] != halt) {
			//saving write position in temp variable 
			//in case overwritten
			int write_pos = value[i+3];
			//write to position given by 3rd integer
			//result of operation of opcode given by 0th integer, 
			//on operands given by 1st and 2nd integers
			value[write_pos] = 
				execute_opcode(value[i],
					       value[value[i+1]],
					       value[value[i+2]]);
		}
		else
			return;
	}
}

//-----------------------------------------------------------------------------
	
int main()
{
	get_values();
	calculate();
	std::cout << "Value at position 0: " << value[0] << '\n';
	return 0;
}
