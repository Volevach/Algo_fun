// Sobel_Filter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SobelOp.h"


int main(int argc, char* argv[])
{
    unsigned char image_r[MAX_X][MAX_Y];
    unsigned char image_g[MAX_X][MAX_Y];
    unsigned char image_b[MAX_X][MAX_Y];

    unsigned int size_x;
    unsigned int size_y;
    unsigned int val255;
    
    bool input_bin = false;
    bool rgb = false;

    std::ifstream in("../Data/Input/electronics.ppm");
    std::ofstream out("../Data/Output/output.ppm");

    std::string line;
    
    if(!in)
    {
        printf("Input file not found\n");
        return -1;
    }

    if(!out)
    {
        printf("Output file cannot be created\n");
        return -1;
    }

    std::getline(in, line);
    // RGB ASCII

    if(line.compare("P3") == 0)
    {
        rgb = true;
    }
    // RGB Bin
    else if(line.compare("P6") == 0)
    {
        input_bin = true;
        rgb = true;
    }
    // Grey ASCII
    else if(line.compare("P2") == 0)
    {

    }
    // Grey BIN
    else if(line.compare("P5") == 0)
    {
        input_bin = true;
    }
    else
    {
        printf("File not supported\n\n");
        return -1;
    }
    out << line << std::endl;

    std::getline(in, line);
    while(line.at(0) == '#')
    {
        std::getline(in, line);
    }
    std::istringstream iss(line);
    // get size x, y 
    //std::getline(in, line);
    iss >> size_y;
    iss >> size_x;
    out << line << std::endl;

    // get max val, shoud be 255
    in >> val255;
    if(val255 != 255)
    {
        printf("wrong scaling (not 255)\n\n");
    }

    out << 255 << std::endl;
    unsigned int val;
    // read from file
    if(rgb)
    {
        if(input_bin)
        {
            for(unsigned int i = 0; i < size_x; i++)
            {
                for(unsigned int j = 0; j < size_y; j++)
                {

                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < size_x; i++)
            {
                for(unsigned int j = 0; j < size_y; j++)
                {
                    
                    in >> val;
                    image_r[i][j] = (unsigned char)(val);
                    
                    in >> val;
                    image_g[i][j] = (unsigned char)(val);
                    
                    in >> val;
                    image_b[i][j] = (unsigned char)(val);
                }
            }
        }
    }

    // write bacl to file 
    if(rgb)
    {
        if(input_bin)
        {
            for(unsigned int i = 0; i < size_x; i++)
            {
                for(unsigned int j = 0; j < size_y; j++)
                {
                }
            }
        }
        else
        {
            for(unsigned int i = 0; i < size_x; i++)
            {
                for(unsigned int j = 0; j < size_y; j++)
                {
                    out << (unsigned int)image_r[i][j] << std::endl;
                    out << (unsigned int)image_g[i][j] << std::endl;
                    out << (unsigned int)image_b[i][j] << std::endl;
                }
            }
        }
    }

	return 0;
}


