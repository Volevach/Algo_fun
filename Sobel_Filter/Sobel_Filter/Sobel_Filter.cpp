// Sobel_Filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SobelOp.h"


int main(int argc, char* argv[])
{
	unsigned char image[MAX_X][MAX_Y];
	unsigned char image_filt[MAX_X][MAX_Y];

	unsigned int size_x;
	unsigned int size_y;
	unsigned int val255;

	SobelOp MySobel = SobelOp();

	bool input_bin = false;
	bool rgb = false;

	char inputfile[150] = "../Data/Input/electronics_grey_bin.pgm";
	char outputfile[150] = "../Data/Output/output.pgm";

	std::ifstream in(inputfile);
	std::ofstream out(outputfile);

	std::string line;

	unsigned int lncnt = 0;

	if (!in)
	{
		printf("Input file not found\n");
		return -1;
	}

	if (!out)
	{
		printf("Output file cannot be created\n");
		return -1;
	}
	std::getline(in, line);
	lncnt++;

	// RGB ASCII
	if (line.compare("P3") == 0)
	{
		rgb = true;
		out << "P2" << std::endl;
	}
	// RGB Bin
	else if (line.compare("P6") == 0)
	{
		input_bin = true;
		rgb = true;
		out << "P2" << std::endl;
	}
	// Grey ASCII
	else if (line.compare("P2") == 0)
	{
		out << "P2" << std::endl;
	}
	// Grey BIN
	else if (line.compare("P5") == 0)
	{
		input_bin = true;
		out << "P2" << std::endl;
	}
	else
	{
		printf("File not supported\n\n");
		return -1;
	}

	std::getline(in, line);
	lncnt++;
	while (line.at(0) == '#')
	{
		std::getline(in, line);
		lncnt++;
	}

	std::istringstream iss(line);
	// get size x, y 
	iss >> size_y;
	iss >> size_x;
	out << line << std::endl;

	// get max val, shoud be 255
	in >> val255;
	lncnt++;
	if (val255 != 255)
	{
		printf("wrong scaling (not 255)\n\n");
	}

	out << 255 << std::endl;
	unsigned int val;

	unsigned int val_r;
	unsigned int val_g;
	unsigned int val_b;
	// read from file

	if (input_bin)
	{
		in.close();
		in.open(inputfile, std::ios::binary);
		char eol = '\n';
		char buff1 = 0;
		while (lncnt > 0)
		{
			in.get(buff1);
			if (buff1 == eol)
			{
				lncnt--;
			}
		}

		for (unsigned int i = 0; i < size_x; i++)
		{
			for (unsigned int j = 0; j < size_y; j++)
			{
				if (rgb)
				{
					unsigned char bbuff[3];
					in.read((char*)(&bbuff), 3);
					val = (unsigned int)
						((0.3  * (float)(bbuff[0]))
							+ (0.59 * (float)(bbuff[1]))
							+ (0.11 * (float)(bbuff[2])));
				}
				else
				{
					unsigned char bbuf;
					in.read((char*)(&bbuf), 1);
					val = bbuf;
				}
				image[i][j] = (unsigned char)(val);

			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < size_x; i++)
		{
			for (unsigned int j = 0; j < size_y; j++)
			{
				if (rgb)
				{
					in >> val_r;
					in >> val_g;
					in >> val_b;
					val = (unsigned int)((0.3  * (float)(val_r)) + (0.59 * (float)(val_g)) + (0.11 * (float)(val_b)));
				}
				else
				{
					in >> val;
				}
				image[i][j] = (unsigned char)(val);
			}
		}
	}

	in.close();
	MySobel.SobelFiltImage(image, image_filt);


	// write back to file 
	if (input_bin)
	{
		for (unsigned int i = 0; i < size_x; i++)
		{
			for (unsigned int j = 0; j < size_y; j++)
			{

			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < size_x; i++)
		{
			for (unsigned int j = 0; j < size_y; j++)
			{
				out << (unsigned int)image_filt[i][j] << std::endl;
			}
		}
	}
	out.close();
	return 0;
}


