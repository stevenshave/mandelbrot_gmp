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


int main(){
  //Set up position, resolution, etc...
  const uint8_t MAXITER=80;
  const uint64_t PRECISION = 400;
  mpf_set_default_prec(PRECISION);
  //const int32_t RESOLUTIONX=1024, RESOLUTIONY=768;
  const int32_t RESOLUTIONX=3840, RESOLUTIONY=2160;
  //const int32_t RESOLUTIONX=1920, RESOLUTIONY=1080;
  //const int32_t RESOLUTIONX=110, RESOLUTIONY=100;
  const int32_t NUM_FRAMES=5;
  ofstream fout;
  gzFile outfile = gzopen("file.bin", "wb");

  auto data=std::array<std::array<uint8_t,RESOLUTIONY>,RESOLUTIONX>();
  mpf_class x(0.3602404434376143632361252444495453084826), y(-0.64131306106480317486037501517930206);

  mpf_class begin_x_length(3);
  mpf_class begin_y_length(2);
  vector<mpf_class> xcoords=initialise_mpf_vector(RESOLUTIONX);
  vector<mpf_class> ycoords=initialise_mpf_vector(RESOLUTIONY);


  // Zoom rates
  mpf_class zoom_rate(0.4);
  //mpf_class zoom_rate(0.99);
  uint64_t zoom_step = 1;
  //uint64_t zoom_step = 750;
  mpf_class zoom_multiplier(0);
  
  for(int frame=0;frame<NUM_FRAMES;++frame){
    mpf_pow_ui(zoom_multiplier.get_mpf_t(), zoom_rate.get_mpf_t(), zoom_step+frame);

    mpf_class new_x_length(begin_x_length*zoom_multiplier);
    mpf_class new_y_length(begin_y_length*zoom_multiplier);

    mpf_class zoomed_xmin((x-new_x_length/2.0)), zoomed_xmax(x+new_x_length/2.0), zoomed_ymin(y-new_y_length/2.0), zoomed_ymax(y+new_y_length/2.0);


    linspace_mpf(xcoords, zoomed_xmin, zoomed_xmax);
    linspace_mpf(ycoords, zoomed_ymin,  zoomed_ymax);
    std::cerr<<zoomed_xmin<<","<<zoomed_xmax<<","<<zoomed_ymin<<","<<zoomed_xmax<<"\n";

    mpf_class nreal(0), real(0), imag(0), p1(0), p2(0), p3(0), xcoord(0), ycoord(0);


    int counter=0;
    uint8_t n;
    #pragma omp parallel for private(nreal, real, imag, p1, p2, p3, xcoord, ycoord, n) schedule(dynamic, 32)
    for(uint32_t i =0;i<RESOLUTIONX; i++){
      for(uint32_t j =0 ; j<RESOLUTIONY;j++){
        xcoord=xcoords[i];
        ycoord=ycoords[j];
        mpf_set_ui(real.get_mpf_t(),0);
        mpf_set_ui(imag.get_mpf_t(), 0);
        mpf_set_ui(p3.get_mpf_t(), 0);
        n=0;
        while(n<MAXITER && p3<4.0){
          mpf_mul(p2.get_mpf_t(),imag.get_mpf_t(), imag.get_mpf_t());
          mpf_add(p2.get_mpf_t(), p2.get_mpf_t(), xcoord.get_mpf_t());
          mpf_mul(nreal.get_mpf_t(), real.get_mpf_t(), real.get_mpf_t());
          mpf_sub(nreal.get_mpf_t(), nreal.get_mpf_t(), p2.get_mpf_t());
          mpf_mul_ui(p1.get_mpf_t(), real.get_mpf_t(), 2);
          mpf_mul(p2.get_mpf_t(), p1.get_mpf_t(), imag.get_mpf_t());
          mpf_add(imag.get_mpf_t(), p2.get_mpf_t(), ycoord.get_mpf_t());
          mpf_set(real.get_mpf_t(), nreal.get_mpf_t());
          mpf_mul(p1.get_mpf_t(), real.get_mpf_t(), real.get_mpf_t());
          mpf_mul(p2.get_mpf_t(), imag.get_mpf_t(), imag.get_mpf_t());
          mpf_add(p3.get_mpf_t(), p1.get_mpf_t(), p2.get_mpf_t());
          ++n;
        }
      data[i][j]=n;
      }

    }
    std::cerr<<"Done frame # "<<frame<<"\n";
    gzwrite(outfile, &data, RESOLUTIONX*RESOLUTIONY);

  }
  gzclose(outfile);
}