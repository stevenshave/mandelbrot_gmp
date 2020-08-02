# include <iostream>
#include <gmpxx.h>
#include <vector>
#include <array>
#include <iomanip>
#include "linspace.hpp"
#include <array>
using namespace std;





int main(){
  //Set up position, resolution, etc...
  const uint8_t MAXITER=80;
  const uint64_t PRECISION = 64;
  mpf_set_default_prec(PRECISION);
  const int32_t RESOLUTIONX=1024, RESOLUTIONY=768;

  mpf_class x(1.75), y(0);

  mpf_class begin_x_length(3);
  mpf_class begin_y_length(2);


  // Zoom rates
  mpf_class zoom_rate(0.99);
  uint64_t zoom_step = 750;
  mpf_class zoom_multiplier(0);
  mpf_pow_ui(zoom_multiplier.get_mpf_t(), zoom_rate.get_mpf_t(), zoom_step);
  mp_exp_t exp=1;
  //std::cout<<"Zoom Multiplier = "<<zoom_multiplier.get_str(exp,10,100)<<","<<exp<<"\n";
  //std::cout<<"Zoom Multiplier = "<<std::setprecision(50)<<zoom_multiplier<<"\n";
  mpf_class new_x_length(begin_x_length*zoom_multiplier);
  mpf_class new_y_length(begin_y_length*zoom_multiplier);

  mpf_class zoomed_xmin((x-new_x_length/2.0)), zoomed_xmax(x+new_x_length/2.0), zoomed_ymin(y-new_y_length/2.0), zoomed_ymax(y+new_y_length/2.0);
  

  vector<mpf_class> xcoords=linspace_mpf(zoomed_xmin,  zoomed_xmax, RESOLUTIONX);
  vector<mpf_class> ycoords=linspace_mpf(zoomed_ymin,  zoomed_ymax, RESOLUTIONX);
  std::cerr<<zoomed_xmin<<","<<zoomed_xmax<<","<<zoomed_ymin<<","<<zoomed_xmax<<"\n";
  std::array<std::array<uint8_t,RESOLUTIONY>,RESOLUTIONX> data={};

  mpf_class nreal(0), real(0), imag(0), p1(0), p2(0), p3(0), xcoord(0), ycoord(0);
  uint8_t n;
  for(uint32_t i =0;i<RESOLUTIONX; i++){
    for(uint32_t j =0 ; j<RESOLUTIONY;j++){

      //std::cerr<<static_cast<int>(j)<<" - ";
      n=0;
      real=imag=p3=0;
      xcoord=xcoords[i];
      ycoord=ycoords[j];
      while(p3<4.0&& n<MAXITER){
      
      p2=imag * imag;
      p2=p2 + xcoord;
      nreal=real * real;
      nreal=nreal-p2;
      p1=real * 2;
      p2=p1 * imag;
      imag=p2 + ycoord;
      real=nreal;
      p1=real * real;
      p2=imag * imag;
      p3=p1 + p2;
      ++n;
      }
      data[i][j]=n;
      //std::cerr<<static_cast<int>(n)<<"\n";
      // nreal=0;
      // real=0;
      // imag=0;
      // n=0;
      // while(n<MAXITER && (real*real+imag*imag)<4.0){
      //   nreal=(real*real)-(imag*imag)+xcoords[i];
      //   imag=2*real*imag+ycoords[j];
      //   real=nreal;
      //   ++n;
      // }
      // data[i][j]=n;
    }
  }
}