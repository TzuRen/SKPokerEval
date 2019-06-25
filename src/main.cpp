#include "Constants.h"
#include "SevenEval.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <set>

namespace {

constexpr char ranks[] = "AKQJT9876";
constexpr char suits[] = "shdc";

std::string ToString(int hand) {
  if (hand >= kDeckSize)
    return {'?', '?'};
  return {ranks[hand / kNumberOfSuits], suits[hand % kNumberOfSuits]};
}

template <size_t N>
std::string ToString(const std::array<int, N>& hands) {
  std::string result;
  result.reserve(N * 2);
  for (size_t i = 0; i < N; ++i) {
    result.push_back(ranks[hands[i] / kNumberOfSuits]);
    result.push_back(suits[hands[i] % kNumberOfSuits]);
  }

  return result;
}

using Hand = std::array<int, 2>;

template <size_t N>
class Equity {
 public:
  Equity() = default;
  Equity(Hand hand) : hand_(std::move(hand)) {}

  void AddWin() { ++results_[1]; }

  void AddLoss() { ++results_[0]; }

  void AddTie(size_t num_tied) { ++results_[num_tied]; }

  const Hand& hand() const { return hand_; }
  const auto& results() const { return results_; }

  double ToDouble() const {
    static constexpr std::array<double, N + 1> kFractions = [] {
      std::array<double, N + 1> fractions = {};
      for (size_t i = 1; i <= N; ++i)
        fractions[i] = 1.0 / i;
      return fractions;
    }();

    return std::inner_product(results_.begin(), results_.end(),
                              kFractions.begin(), 0.0) /
           static_cast<double>(
               std::accumulate(results_.begin(), results_.end(), 0));
  }

 private:
  Hand hand_ = {};
  std::array<size_t, N + 1> results_ = {};
};

template <size_t N>
struct Result {
 public:
  using Equities = std::array<Equity<N>, N>;
  Result(const std::array<Hand, N>& hands) {
    for (size_t i = 0; i < N; ++i)
      equities_[i] = Equity<N>(hands[i]);
  }

  void AddRanks(const std::array<uint16_t, N>& ranks) {
    uint16_t best_rank = 0;
    size_t num_best_ranks = 0;
    for (auto rank : ranks) {
      if (rank < best_rank)
        continue;

      if (rank > best_rank) {
        best_rank = rank;
        num_best_ranks = 1;
        continue;
      }

      ++num_best_ranks;
    }

    for (size_t i = 0; i < N; ++i) {
      ranks[i] == best_rank ? equities_[i].AddTie(num_best_ranks)
                            : equities_[i].AddLoss();
    }
  }

  const Equities& equities() const { return equities_; }

 private:
  Equities equities_;
};

template <size_t N>
std::ostream& operator<<(std::ostream& out, const Result<N>& result) {
  for (const auto& equity : result.equities())
    out << ToString(equity.hand()) << ": " << equity.ToDouble()
        << ",\twins: " << equity.results()[1]
        << ",\tties: " << equity.results()[2] << '\n';
  return out;
}

template <size_t N>
void CanonicalizeSuits(std::array<Hand, N>* hands) {
  std::array<int, 4> suits;
  suits.fill(-1);
  int suit_count = 0;
  for (auto& hand : *hands) {
    for (auto& card : hand) {
      auto suit = card % kNumberOfSuits;
      if (suits[suit] == -1)
        suits[suit] = suit_count++;
      card = card - suit + suits[suit];
    }
  }
}

template <size_t I, size_t N>
constexpr int GetBegin(int prev, const std::array<int, N>& board) {
  if constexpr (I < N)
    return board[I];

  if constexpr (I == N)
    return 0;

  return prev + 1;
}

template <size_t I, size_t N>
constexpr int GetEnd(const std::array<int, N>& board) {
  if constexpr (I < N)
    return board[I] + 1;

  return kDeckSize;
}

template <size_t N, size_t M = 0, size_t D = 0>
constexpr Result<N> ComputeEquities(const std::array<Hand, N>& hands,
                                    const std::array<int, M>& board = {},
                                    const std::array<int, D>& dead = {}) {
  static_assert(M < 5);

  Result<N> result(hands);
  std::array<uint16_t, N> ranks;

  std::bitset<kDeckSize> used;
  for (const auto& hand : hands)
    for (const auto& card : hand)
      used[card] = 1;

  for (int d : dead)
    used[d] = 1;

  for (int c0 = GetBegin<0>(0, board); c0 < GetEnd<0>(board); ++c0) {
    if (used[c0])
      continue;
    for (int c1 = GetBegin<1>(c0, board); c1 < GetEnd<1>(board); ++c1) {
      if (used[c1])
        continue;
      for (int c2 = GetBegin<2>(c1, board); c2 < GetEnd<2>(board); ++c2) {
        if (used[c2])
          continue;
        for (int c3 = GetBegin<3>(c2, board); c3 < GetEnd<3>(board); ++c3) {
          if (used[c3])
            continue;
          for (int c4 = GetBegin<4>(c3, board); c4 < GetEnd<4>(board); ++c4) {
            if (used[c4])
              continue;

            for (size_t i = 0; i < N; ++i)
              ranks[i] = SevenEval::GetRank(hands[i][0], hands[i][1], c0, c1,
                                            c2, c3, c4);
            result.AddRanks(ranks);
          }
        }
      }
    }
  }

  return result;
}

}  // namespace

int main() {
  std::array<Hand, 2> hands;
  hands[0] = {kKd, kQd};
  hands[1] = {kJd, kTd};

  std::array<int, 3> board = {k9d, k8d, k7d};
  std::cout << ComputeEquities(hands, board);
}
