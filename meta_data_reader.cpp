// Ahmad Alkurdy
//Date: 6/12/2016
// program would read meta-data from binary file and orgnize the results into binary files files
// after analysis them into catagories 


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

// function to read the data from the binary file and sore the data in the dynamic arrays

void datareader(fstream &binInput, int &tempretureflag, int &salinityflag, int &heightflag
	, int numRecords, int *salarr, int *heightarr, int *temparr); 

// function to write the data from the dynamic arrays into the files 
void dataWriter(int &tempretureflag, int &salinityflag, int &heightflag
	, int &numRecords, int *salarr, int *heightarr, int *temparr);

//	argc: argument counter tells the number f perameter the main expecting
//  argv:argument vector (array of charecter pointers)
int main(int argc, char* argv[])
{
	// declare input and output files and extra output file for the binary file

	
	//declare variables to hold the binary numbers that are read from the input file
	int tempretureflag = 0;
	int salinityflag = 0;
	int heightflag = 0;
	int numRecords = 0;
	string fileName;
	fstream binInput;
	int *temparr; // pointer for the tempreture dynamic array
	
	int *salarr;// pointer for the salinity dynamic array
	
	int *heightarr;// pointer for the height dynamic arrays
	fstream input;
	
	


	// if we have two peramter in the argument then the operation will happen
	if (argc == 2)
	{
		input.open("data.in", ios::in|ios::binary);
		if(!input)
		{
			cout << "Error: no file is found" << endl;
		}
		
		//read the information from the binary file and take data of the size of int (four numbers)
		// and store it in the variables 
		input.read((char*) &tempretureflag, sizeof(int));
		input.read((char*) &salinityflag, sizeof(int));
		input.read((char*) &heightflag, sizeof(int));
		input.read((char*) &numRecords, sizeof(int));
		numRecords = numRecords;

		//declaring dynamic arrays

	   temparr = new int[numRecords];
	   salarr = new int [numRecords];
	   heightarr = new int [numRecords];

		// we call both functions to do their job
		datareader(input, tempretureflag, salinityflag, heightflag,numRecords,salarr, heightarr, temparr); 
		
		dataWriter(tempretureflag, salinityflag, heightflag, numRecords,salarr, heightarr, temparr); 

		// reading the data into the arrays
		
	
		return 0;


	}
	else {
		cout << "Error" << endl;
	}
	delete [] temparr;
	delete [] salarr;
	delete [] heightarr;
	return 0;

}

void datareader(fstream &input, int &tempretureflag, int &salinityflag, int &heightflag
	, int numRecords, int *salarr, int *heightarr, int *temparr)
{
	int salinity = 0;
	int height = 0;
	int temp = 0;

	//logic if statments to read the header of the file and recognize how the data will be orgnized
	// to be read in the three dynamic arrays we have
	if (tempretureflag == 1 && salinityflag == 1 && heightflag == 1)
		{
			for(int i=0 ; i < numRecords ; i++)
			{
			input.read((char*) &temp, sizeof(int));
			temparr[i] = temp;
			input.read((char*) &salinity, sizeof(int));
			salarr[i] = salinity;
			input.read((char*) &height, sizeof (int));
			heightarr[i] = height;
			}
		}
		
		if (tempretureflag == 0 && salinityflag == 1 && heightflag == 1)
		{
			for(int i = 0; i < numRecords; i++)
			{
			input.read((char*) &salinity , sizeof(int));
			salarr[i] = salinity;
			input.read((char*) &height, sizeof(int));
			heightarr[i] = height;
			
			
			}
			
		}
		if (tempretureflag == 0 && salinityflag == 0 && heightflag == 1)
		{
			for(int i = 0; i < numRecords; i++)
			{
			
			input.read((char*) &height, sizeof(int));
			heightarr[i] = height;
			}
		}
		if (tempretureflag == 1 && salinityflag == 0 && heightflag == 0)
		{
			for(int i = 0; i < numRecords; i++)
			{
			input.read((char*) &temp, sizeof(int));
			temparr[i] = temp;
			
			
			}
		}
		if (tempretureflag == 1 && salinityflag == 1 && heightflag == 0)
		{
			for(int i = 0; i < numRecords; i++)
			{
			input.read((char*) &temp, sizeof(int));
			temparr[i] = temp;
			input.read((char*) &salinity, sizeof(int));
			salarr[i] = salinity;
			
			}

		}
		if (tempretureflag == 0 && salinityflag == 1 && heightflag == 0)
		{
			for(int i = 0; i < numRecords; i++)
			{
							
			
			input.read((char*) &salinity, sizeof(int));
			salarr[i] = salinity;
			
			}

			if (tempretureflag == 0 && salinityflag == 0 && heightflag == 0)
			{
				cout << "Error: no data was found" << endl;
			}
		}
	
}
void dataWriter(int &tempretureflag, int &salinityflag, int &heightflag
	, int &numRecords, int *salarr, int *heightarr, int *temparr)
{
	stringstream num;
	num << numRecords;
	string file;
	//if statments to write the data into binary-output files according to the header of the file
	// if 1 then we build a file and output its array into binary file
	
	if(tempretureflag == 1)
	{
		
			ofstream outputtempbin;
			outputtempbin.open("OutputTemp.in",ios :: out| ios :: binary);
			file = "Tempreture" + num.str() + ".txt";

				for(int i = 0; i < numRecords; i++)
			{
				int temp = 0;
				temp = temparr[i]; 
				outputtempbin.write((char*) &temp, sizeof(int));

				
			}		
	}
		

		if(heightflag == 1)
		{	
			ofstream outputheightbin;
			outputheightbin.open("OutputHeight.in", ios :: out| ios:: binary);
			
			file = "Hieght" + num.str() + ".txt";
			
			for(int i = 0; i < numRecords; i++)
				
			{
				int height = 0;
				height = heightarr[i]; 
				outputheightbin.write((char*) &height, sizeof(int));

				
			}			
		}	
		
		if(salinityflag == 1)
		{
		    
			ofstream outputsalbin;
			outputsalbin.open("outputsalbin.in", ios :: out|ios::binary);
		
			
			file = "Salinity" + num.str() +".txt";

			for(int i = 0; i < numRecords; i++)
			{
				int salinity = 0;
				salinity = salarr[i]; 
				outputsalbin.write((char*) &salinity, sizeof(int));

				
			}		
		}	
		
		
}

