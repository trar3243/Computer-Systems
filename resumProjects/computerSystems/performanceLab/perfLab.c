#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int main(int argc, char ** argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

class Filter * readFilter(string filename)
{
    ifstream input(filename.c_str());

    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) 
    {
        for (int j=0; j < size; j++) 
        {
            int value;
            input >> value;
            filter -> set(i,j,value);
        }
    }
    return filter;
}



















double applyFilter(class Filter *filter, cs1300bmp *input, cs1300bmp *output)
{
    long long cycStart, cycStop;

    cycStart = rdtscll();

    output -> width = input -> width;
    output -> height = input -> height;
    
    unsigned char divisor = filter -> getDivisor(); 
    bool check; 
    if (divisor == 1)
    {
        check = 1;
    }
    else
    {
        check = 0; 
    }
    
    char filterArray[9];

    filterArray[0] = filter -> get(0,0);
    filterArray[1] = filter -> get(0,1);
    filterArray[2] = filter -> get(0,2);
    filterArray[3] = filter -> get(1,0);
    filterArray[4] = filter -> get(1,1);
    filterArray[5] = filter -> get(1,2);
    filterArray[6] = filter -> get(2,0);
    filterArray[7] = filter -> get(2,1);
    filterArray[8] = filter -> get(2,2);

    
    unsigned char saveVal4;
    unsigned char saveVal3;
    unsigned char saveVal2;  
    unsigned char saveVal; 
    short heightMin1 = input -> height -1;
    short widthMin1 = input -> width - 1; 
    short temp;
    short col; 
    short row; 
    unsigned char plane; 
    //#pragma omp parallel for
    for(plane = 0; plane < 3; plane++) 
    {
        for(row = 1; row < heightMin1 - 1; row = row + 2) 
        {
            for(col = 1; col < widthMin1 - 1; col = col + 2) 
            {
                temp = (input -> color[plane][row - 1][col - 1] * filterArray[0]) + (input -> color[plane][row - 1][col] * filterArray[1]) + (input -> color[plane][row - 1][col+1] * filterArray[2])+ 
                (input -> color[plane][row][col- 1] * filterArray[3])+ (input -> color[plane][row][col] * filterArray[4])+ (input -> color[plane][row][col+1] * filterArray[5]) + 
                (input -> color[plane][row+1][col- 1] * filterArray[6])+ (input -> color[plane][row+1][col] * filterArray[7])+ (input -> color[plane][row+1][col+1] * filterArray[8]);
                if (temp < 0)
                {
                    saveVal = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal = 255; 
                }
                else if (check)
                {
                    saveVal = temp;
                }
                else
                {
                    saveVal = (temp / divisor);
                }
                

                temp = (input -> color[plane][row - 1][col] * filterArray[0])+ (input -> color[plane][row - 1][col + 1] * filterArray[1])+ (input -> color[plane][row - 1][col+2] 
                * filterArray[2]) + (input -> color[plane][row][col] * filterArray[3])+ (input -> color[plane][row][col + 1] * filterArray[4])+ (input -> color[plane][row][col + 2] * filterArray[5])+ 
                (input -> color[plane][row+1][col] * filterArray[6])+ (input -> color[plane][row+1][col + 1] * filterArray[7])  + (input -> color[plane][row+1][col + 2] * filterArray[8]);
                if (temp < 0)
                {
                    saveVal2 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal2 = 255; 
                }
                else if (check)
                {
                    saveVal2 = temp;
                }
                else 
                {
                    saveVal2 = (temp / divisor);
                }

                temp = (input -> color[plane][row ][col - 1] * filterArray[0]) + (input -> color[plane][row ][col] * filterArray[1]) + (input -> color[plane][row][col+1] * filterArray[2])+ 
                (input -> color[plane][row + 1][col- 1] * filterArray[3])+ (input -> color[plane][row + 1][col] * filterArray[4])+ (input -> color[plane][row + 1][col+1] * filterArray[5]) + 
                (input -> color[plane][row+2][col- 1] * filterArray[6])+ (input -> color[plane][row+2][col] * filterArray[7])+ (input -> color[plane][row+2][col+1] * filterArray[8]);
                if (temp < 0)
                {
                    saveVal3 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal3 = 255; 
                }
                else if (check)
                {
                    saveVal3 = temp;
                }
                else
                {
                    saveVal3 = (temp / divisor); 
                }

                temp = (input -> color[plane][row ][col] * filterArray[0])+ (input -> color[plane][row ][col + 1] * filterArray[1])+ (input -> color[plane][row ][col+2] 
                * filterArray[2]) + (input -> color[plane][row + 1][col] * filterArray[3])+ (input -> color[plane][row + 1][col + 1] * filterArray[4])+ (input -> color[plane][row + 1][col + 2] * filterArray[5])+ 
                (input -> color[plane][row+2][col] * filterArray[6])+ (input -> color[plane][row+2][col + 1] * filterArray[7])  + (input -> color[plane][row+2][col + 2] * filterArray[8]);
                if (temp < 0)
                {
                    saveVal4 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal4 = 255; 
                }
                else if (check)
                {
                    saveVal4 = temp;
                }
                else
                {
                    saveVal4 = (temp / divisor);
                }

        

                output -> color[plane][row][col] = saveVal; 
                output -> color[plane][row][col + 1] = saveVal2; 
                output -> color[plane][row + 1][col] = saveVal3; 
                output -> color[plane][row + 1][col + 1] = saveVal4; 
            }
            for(; col < widthMin1; col = col + 1) 
            {
                temp = 
                (input -> color[plane][row - 1][col - 1] 
                * filterArray[0])
                + 
                (input -> color[plane][row - 1][col] 
                * filterArray[1])
                + 
                (input -> color[plane][row - 1][col+1] 
                * filterArray[2])
                + 
                (input -> color[plane][row][col- 1] 
                * filterArray[3])
                + 
                (input -> color[plane][row][col] 
                * filterArray[4])
                + 
                (input -> color[plane][row][col+1] 
                * filterArray[5])
                + 
                (input -> color[plane][row+1][col- 1] 
                * filterArray[6])
                + 
                (input -> color[plane][row+1][col] 
                * filterArray[7])
                + 
                (input -> color[plane][row+1][col+1] 
                * filterArray[8]);
                if (temp < 0)
                {
                    saveVal3 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal3 = 255; 
                }
                else if (check)
                {
                    saveVal3 = temp;
                }
                else
                {
                    saveVal3 = (temp / divisor);
                }

                temp = 
                (input -> color[plane][row ][col - 1] 
                * filterArray[0])
                + 
                (input -> color[plane][row ][col] 
                * filterArray[1])
                + 
                (input -> color[plane][row ][col+1] 
                * filterArray[2])
                + 
                (input -> color[plane][row + 1][col- 1] 
                * filterArray[3])
                + 
                (input -> color[plane][row + 1][col] 
                * filterArray[4])
                + 
                (input -> color[plane][row + 1][col+1] 
                * filterArray[5])
                + 
                (input -> color[plane][row+2][col- 1] 
                * filterArray[6])
                + 
                (input -> color[plane][row+2][col] 
                * filterArray[7])
                + 
                (input -> color[plane][row+2][col+1] 
                * filterArray[8]);
                if (temp < 0)
                {
                    saveVal4 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal4 = 255; 
                }
                else if (check)
                {
                    saveVal4 = temp;
                }
                else
                {
                    saveVal4 = (temp / divisor);
                }

                

                
                output -> color[plane][row][col] = saveVal3; 
                output -> color[plane][row + 1][col] = saveVal4; 
            }
        }
        for(; row < heightMin1 ; row = row + 1) 
        {
            for(col = 1; col < widthMin1 - 1; col = col + 2) 
            {

                temp = 
                (input -> color[plane][row - 1][col - 1] 
                * filterArray[0])
                + 
                (input -> color[plane][row - 1][col] 
                * filterArray[1])
                + 
                (input -> color[plane][row - 1][col+1] 
                * filterArray[2])
                + 
                (input -> color[plane][row][col- 1] 
                * filterArray[3])
                + 
                (input -> color[plane][row][col] 
                * filterArray[4])
                + 
                (input -> color[plane][row][col+1] 
                * filterArray[5])
                + 
                (input -> color[plane][row+1][col- 1] 
                * filterArray[6])
                + 
                (input -> color[plane][row+1][col] 
                * filterArray[7])
                + 
                (input -> color[plane][row+1][col+1] 
                * filterArray[8]);
                if (temp < 0)
                {
                    saveVal3 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal3 = 255; 
                }
                else if (check)
                {
                    saveVal3 = temp;
                }
                else
                {
                    saveVal3 = (temp / divisor);
                }


                temp = 
                (input -> color[plane][row - 1][col] 
                * filterArray[0])
                + 
                (input -> color[plane][row - 1][col + 1] 
                * filterArray[1])
                + 
                (input -> color[plane][row - 1][col+2] 
                * filterArray[2])
                + 
                (input -> color[plane][row][col] 
                * filterArray[3])
                + 
                (input -> color[plane][row][col + 1] 
                * filterArray[4])
                + 
                (input -> color[plane][row][col + 2] 
                * filterArray[5])
                + 
                (input -> color[plane][row+1][col] 
                * filterArray[6])
                + 
                (input -> color[plane][row+1][col + 1] 
                * filterArray[7])
                + 
                (input -> color[plane][row+1][col + 2] 
                * filterArray[8]);
                if (temp < 0)
                {
                    saveVal4 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal4 = 255; 
                }
                else if (check)
                {
                    saveVal4 = temp;
                }
                else
                {
                    saveVal4 = (temp / divisor);
                }

                

                

                output -> color[plane][row][col] = saveVal3; 
                output -> color[plane][row][col + 1] = saveVal4; 
            }
            for(; col < widthMin1; col = col + 1) 
            {
                temp = 
                (input -> color[plane][row - 1][col - 1] 
                * filterArray[0])
                + 
                (input -> color[plane][row - 1][col] 
                * filterArray[1])
                + 
                (input -> color[plane][row - 1][col+1] 
                * filterArray[2])
                + 
                (input -> color[plane][row][col- 1] 
                * filterArray[3])
                + 
                (input -> color[plane][row][col] 
                * filterArray[4])
                + 
                (input -> color[plane][row][col+1] 
                * filterArray[5])
                + 
                (input -> color[plane][row+1][col- 1] 
                * filterArray[6])
                + 
                (input -> color[plane][row+1][col] 
                * filterArray[7])
                + 
                (input -> color[plane][row+1][col+1] 
                * filterArray[8]);
                if (temp < 0)
                {
                    saveVal4 = 0;
                }
                else if (temp > (255 * divisor))
                {
                    saveVal4 = 255; 
                }
                else if (check)
                {
                    saveVal4 = temp;
                }
                else
                {
                    saveVal4 = (temp / divisor);
                }

                output -> color[plane][row][col] = saveVal4; 
            }
        }
    }

    cycStop = rdtscll();
    double diff = cycStop - cycStart;
    double diffPerPixel = diff / (output -> width * output -> height);
    fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
    diff, diff / (output -> width * output -> height));

    return diffPerPixel;
}