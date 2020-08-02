
std::vector<mpf_class> linspace_mpf(mpf_class start, mpf_class end, int num)
{

  std::vector<mpf_class> linspaced;

  if (num == 0) { return linspaced; }
  if (num == 1) 
    {
      linspaced.push_back(start);
      return linspaced;
    }

  mpf_class delta((end - start) / (num - 1));

  for(int i=0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end); // I want to ensure that start and end
                            // are exactly the same as the input
  return linspaced;
};

