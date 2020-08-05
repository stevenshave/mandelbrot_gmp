std::vector<mpf_class> initialise_mpf_vector(int num){
  std::vector<mpf_class> linspaced;
  linspaced.reserve(num);
  for (int i = 0; i < num; ++i)
        {
            linspaced.push_back (mpf_class(0));
        }
  return linspaced;
};


void linspace_mpf(std::vector<mpf_class>& linspaced, mpf_class start, mpf_class end)
{
  mpf_class delta((end - start) / (linspaced.size() - 1));
  for(int i=0; i < linspaced.size()-1; ++i)
    {
      linspaced[i]=(start + delta * i);
    }
  linspaced[linspaced.size()-1]=end;
  
};



template <class T>
std::vector<T> linspace(T start, T end, int num){
  std::vector<T> linspaced;
  linspaced.reserve(num);

  T delta((end - start) / (num - 1));

  for(int i=0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end);
  return linspaced;
};
