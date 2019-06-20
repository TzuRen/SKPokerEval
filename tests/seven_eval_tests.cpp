#include <gtest/gtest.h>
#include <atomic>
#include "../src/Constants.h"
#include "../src/FiveEval.h"
#include "../src/SevenEval.h"
#include "Parallel.h"

TEST(SevenEvalTest, CompareWithFiveEval) {
  FiveEval const five_eval;
  auto const to_str = [](int card) {
    static const char kRanks[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6'};
    static const char kSuits[] = {'s', 'h', 'd', 'c'};
    return std::string({kRanks[card / 4], kSuits[card % 4]});
  };
  std::atomic<long> count(0);
  auto const outer = [&](int const& i) {
    long inner_count = 0;
    for (int j = i + 1; j < kDeckSize - 5; ++j) {
      for (int k = j + 1; k < kDeckSize - 4; ++k) {
        for (int l = k + 1; l < kDeckSize - 3; ++l) {
          for (int m = l + 1; m < kDeckSize - 2; ++m) {
            for (int n = m + 1; n < kDeckSize - 1; ++n) {
              for (int p = n + 1; p < kDeckSize; ++p) {
                auto const five_rank = five_eval.GetRank(i, j, k, l, m, n, p);
                auto const seven_rank = SevenEval::GetRank(i, j, k, l, m, n, p);
                ASSERT_EQ(five_rank, seven_rank)
                    << "Ranks at " << to_str(i) << ", " << to_str(j) << ", "
                    << to_str(k) << ", " << to_str(l) << ", " << to_str(m)
                    << ", " << to_str(n) << ", " << to_str(p) << " after "
                    << inner_count << " differ.";
                ++inner_count;
              }
            }
          }
        }
      }
    }
    count += inner_count;
  };
  ParallelFor(0, kDeckSize - 6, outer);
  ASSERT_EQ(8347680, count) << "Invalid number of seven card hands tested.";
}

// static_assert(FiveEval().GetRank(kKh, kJd, kJc, kTs, k9s, k8s, k6s) ==
//                   SevenEval::GetRank(kKh, kJd, kJc, kTs, k9s, k8s, k6s),
//               "");
