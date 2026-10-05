//https://www.youtube.com/watch?v=UTVg7wzMWQc&t=4832s
struct Sieve
{
  ll n;
  vector<ll> f,primes;
  Sieve(ll n=1):n(n),f(n+1) 
  {
    f[0]=f[1]=-1;
    for(ll i=2; i<=n; i++)
    {
      if(f[i]) continue;
      primes.emplace_back(i);
      f[i] = i;
      for(ll j=i*i; j<=n; j+=i)
      {
        if(!f[j]) f[j]=i;
      }
    }
  }

  bool isPrime(ll x)
  {
    return f[x] == x;
  }
  vector<ll> factorList(ll x)
  {
    vector<ll> res;
    while(x!=1)
    {
      res.emplace_back(f[x]);
      x /= f[x];
    }
  return res;
  }

  vector<pair<ll,ll>> factor(ll x)
  {
    vector<ll> fl = factorList(x);
    if(fl.size()==0) return {};
    vector<P> res(1,P(fl[0],0));
    for(ll p : fl)
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