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

    std::ifstream in("../Data/Input/electronics_grey.pgm");
    std::ofstream out("../Data/Output/output.pgm");

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
        out << "P2" << std::endl;
    }
    // RGB Bin
    else if(line.compare("P6") == 0)
    {
        input_bin = true;
        rgb = true;
        out << "P2" << std::endl;
    }
    // Grey ASCII
    else if(line.compare("P2") == 0)
    {
        out << "P2" << std::endl;
    }
    // Grey BIN
    else if(line.compare("P5") == 0)
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

    unsigned int val_r;
    unsigned int val_g;
    unsigned int val_b;
    // read from file

    if(input_bin)
    {
        for(unsigned int i = 0; i < size_x; i++)
        {
            for(unsigned int j = 0; j < size_y; j++)
            {
                if(rgb)
                {     
                    char buff[3];
                    in.read(buff, 3);
                    val = (unsigned int)
                            ((0.3  * ((float)(buff[0]) + 128.0))
                           + (0.59 * ((float)(buff[1]) + 128.0))
                           + (0.11 * ((float)(buff[2]) + 128.0)));
                }
                else
                {
                    in >> val;
                }
                image[i][j] = (unsigned char)(val);

            }
        }
    }
    else
    {
        for(unsigned int i = 0; i < size_x; i++)
        {
            for(unsigned int j = 0; j < size_y; j++)
            {
                if(rgb)
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

    
    MySobel.SobelFiltImage(image, image_filt);


    // write back to file 
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
                out << (unsigned int)image_filt[i][j] << std::endl;
            }
        }
    }
	return 0;
}


