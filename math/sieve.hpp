//https://www.youtube.com/watch?v=UTVg7wzMWQc&t=4832s
struct Sieve
{
  int n;
  vector<int> f,primes;
  Sieve(int n=1):n(n),f(n+1) 
  {
    f[0]=f[1]=-1;
    for(int i=2; i<=n; i++)
    {
      if(f[i]) continue;
      primes.emplace_back(i);
      f[i] = i;
      for(int j=i*i; j<=n; j+=i)
      {
        if(!f[j]) f[j]=i;
      }
    }
  }

  bool isPrime(int x)
  {
    return f[x] == x;
  }
  vector<int> factorList(int x)
  {
    vector<int> res;
    while(x!=1)
    {
      res.emplace_back(f[x]);
      x /= f[x];
    }
  return res;
  }

  vector<pair<int,int>> factor(int x)
  {
    vector<int> fl = factorList(x);
    if(fl.size()==0) return {};
    vector<P> res(1,P(fl[0],0));
    for(int p : fl)
    {
      if(res.back().first==p)
      {
        res.back().second++;
      } else
      {
        res.emplace_back(p,1);
      }
    }
    return res;
  }
};