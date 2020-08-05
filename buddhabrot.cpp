# include <iostream>
#include <gmpxx.h>
#include <vector>
#include <array>
#include <iomanip>
#include "linspace.hpp"
#include <array>
#include <fstream>
#include "zlib.h"
using namespace std;


#include <random>


int main(){
  gzFile outfile = gzopen("buddhabrot.bin", "wb");

    const uint64_t NUMRAYS=10000000000;
    const uint32_t MAXITER=10;
    const int32_t RESOLUTIONX=1024, RESOLUTIONY=768;
    //const int64_t RESOLUTIONX=3840, RESOLUTIONY=2160;
    //const int32_t RESOLUTIONX=1920, RESOLUTIONY=1080;
    //const int32_t RESOLUTIONX=110, RESOLUTIONY=100;

    double xmin=-4.5;
    double xmax=3;
    double ymin=-3.5;
    double ymax=3.5;

    
    std::random_device rd;
    std::mt19937 mt_x(rd());
    std::mt19937 mt_y(rd());
    std::uniform_real_distribution<double> rndx(xmin, xmax);
    std::uniform_real_distribution<double> rndy(ymin, ymax);


    auto const xcoords=linspace(static_cast<double>(-2.5),static_cast<double>(1),RESOLUTIONX);
    auto const ycoords=linspace(static_cast<double>(-1.5),static_cast<double>(1.5),RESOLUTIONY);
    double x, y;

    auto image=std::array<std::array<uint64_t,RESOLUTIONY>,RESOLUTIONX>();
    double deltax=((xmax - xmin) / static_cast<double>(RESOLUTIONX - 1));
    double deltay=((ymax - ymin) / static_cast<double>(RESOLUTIONY - 1));

    double real,nreal,imag,creal,cimag;
    unsigned int n;
    for(uint64_t iter=0;iter<NUMRAYS;++iter){
        x=rndx(mt_x);
        y=rndx(mt_y);
        
        real=0;
        nreal=0;
        imag=0;
        creal=x;
        cimag=y;
        n=0;
        while (n<MAXITER){
            nreal = real*real - imag*imag + creal;
            imag = 2* real*imag + cimag;
            real = nreal;
            if (real * real + imag * imag > 4.0){
                break;
            }
            ++n;
            if(real<=xmax && real>=xmin && imag<=ymax && imag>=ymin){
            image[static_cast<int>((real-xmin)/deltax)][static_cast<int>((imag-ymin)/deltay)]+=1;
            }else{break;}
        }
    }
    gzwrite(outfile, &image, sizeof(image));

    gzclose(outfile);



}