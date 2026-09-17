template <class Mint>
class Combination {
private:
    static constexpr int DEFAULT_MAX_N = 510000;

    std::vector<Mint> fact_;
    std::vector<Mint> inv_fact_;

public:
    // 最大値を省略した場合は default_max まで前計算
    Combination() : Combination(DEFAULT_MAX_N) {}

    // 最大値を指定する場合
    explicit Combination(int max_n) {
        build(max_n);
    }

    void build(int max_n) {
        assert(max_n >= 0);

        fact_.resize(max_n + 1);
        inv_fact_.resize(max_n + 1);

        fact_[0] = 1;
        for (int i = 1; i <= max_n; ++i) {
            fact_[i] = fact_[i - 1] * i;
        }

        inv_fact_[max_n] = fact_[max_n].inv();
        for (int i = max_n; i >= 1; --i) {
            inv_fact_[i - 1] = inv_fact_[i] * i;
        }
    }

    Mint C(int n, int r) const {
        if (n < 0 || r < 0 || r > n) return 0;

        assert(n < static_cast<int>(fact_.size()));
        return fact_[n] * inv_fact_[r] * inv_fact_[n - r];
    }

    Mint P(int n, int r) const {
        if (n < 0 || r < 0 || r > n) return 0;

        assert(n < static_cast<int>(fact_.size()));
        return fact_[n] * inv_fact_[n - r];
    }

    Mint factorial(int n) const {
        assert(0 <= n && n < static_cast<int>(fact_.size()));
        return fact_[n];
    }

    Mint inverse_factorial(int n) const {
        assert(0 <= n && n < static_cast<int>(inv_fact_.size()));
        return inv_fact_[n];
    }

    int max_n() const {
        return static_cast<int>(fact_.size()) - 1;
    }
};