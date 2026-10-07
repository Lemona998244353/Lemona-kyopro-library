template<int MOD>
class static_modint {
    static_assert(MOD >= 2);

private:
    int _v;

public:
    using ModInt = static_modint;

    static_modint() : _v(0) {}

    static_modint(long long x) {
        x %= MOD;
        if (x < 0) x += MOD;
        _v = static_cast<int>(x);
    }

    int val() const {
        return _v;
    }

    static constexpr int mod() {
        return MOD;
    }

    // 呼び出し側が 0 <= x < MOD を保証する
    static ModInt raw(int x) {
        ModInt result;
        result._v = x;
        return result;
    }

    ModInt& operator+=(const ModInt& rhs) {
        long long x = (long long)_v + rhs._v;
        if (x >= MOD) x -= MOD;
        _v = static_cast<int>(x);
        return *this;
    }

    ModInt& operator-=(const ModInt& rhs) {
        _v -= rhs._v;
        if (_v < 0) _v += MOD;
        return *this;
    }

    ModInt& operator*=(const ModInt& rhs) {
        _v = (long long)_v * rhs._v % MOD;
        return *this;
    }

    ModInt pow(long long n) const {
        assert(n >= 0);
        ModInt result = raw(1);
        ModInt base = *this;

        while (n > 0) {
            if (n & 1) result *= base;
            base *= base;
            n >>= 1;
        }
        return result;
    }

    // MOD が素数であることが前提
    ModInt inv() const {
        assert(_v != 0);
        return pow(MOD - 2);
    }

    ModInt& operator/=(const ModInt& rhs) {
        return *this *= rhs.inv();
    }

    ModInt operator-() const {
        return raw(_v == 0 ? 0 : MOD - _v);
    }

    friend ModInt operator+(ModInt lhs, const ModInt& rhs) {
        return lhs += rhs;
    }

    friend ModInt operator-(ModInt lhs, const ModInt& rhs) {
        return lhs -= rhs;
    }

    friend ModInt operator*(ModInt lhs, const ModInt& rhs) {
        return lhs *= rhs;
    }

    friend ModInt operator/(ModInt lhs, const ModInt& rhs) {
        return lhs /= rhs;
    }

    friend bool operator==(const ModInt& lhs, const ModInt& rhs) {
        return lhs._v == rhs._v;
    }

    friend bool operator!=(const ModInt& lhs, const ModInt& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const ModInt& x) {
        return os << x.val();
    }
};

using mint998244353 = static_modint<998244353>;
using mint1000000007 = static_modint<1000000007>;

