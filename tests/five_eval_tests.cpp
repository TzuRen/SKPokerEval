#include <gtest/gtest.h>
#include <array>
#include <atomic>
#include <climits>
#include "../src/Constants.h"
#include "../src/Deckcards.h"
#include "../src/FiveEval.h"
#include "Parallel.h"

namespace {

std::string to_string(uint8_t card) {
  static constexpr char kRanks[] = "AKQJT9876";
  static constexpr char kSuits[] = "shdc";
  return {kRanks[card / kNumberOfSuits], kSuits[card % kNumberOfSuits]};
}

}  // namespace

class FiveEvalTest : public ::testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
  FiveEval const eval;
};

TEST_F(FiveEvalTest, HighCard) {
  long rank = LONG_MIN;
  for (int i = 5; i < kNumberOfFaces; ++i) {
    int const I = ((kNumberOfFaces - 1 - i) << 2) + 1;  // No flushes.
    for (int j = 3; j < i; ++j) {
      int const J = (kNumberOfFaces - 1 - j) << 2;
      for (int k = 2; k < j; ++k) {
        int const K = (kNumberOfFaces - 1 - k) << 2;
        for (int l = 1; l < k; ++l) {
          int const L = (kNumberOfFaces - 1 - l) << 2;
          for (int m = 0; m < l; ++m) {
            if (i - m == 4 || (i == kNumberOfFaces - 1 && j == 3)) {
              continue;
            }
            int const M = (kNumberOfFaces - 1 - m) << 2;
            int const next_rank = eval.GetRank(I, J, K, L, M);
            ASSERT_GT(next_rank, rank)
                << "Rank " << next_rank << " at " << I << ", " << J << ", " << K
                << ", " << L << ", " << M << " is invalid.";
            rank = next_rank;
          }
        }
      }
    }
  }
}

TEST_F(FiveEvalTest, WorstPairBeatsBestHighCard) {
  // Ace through to Jack inclusive, plus a Nine. No flush.
  int const rank_of_best_high_card = eval.GetRank(kAs, kKs, kQs, kJs, k9h);
  // Pair of Sixes with Nine high.
  int const rank_of_worst_pair = eval.GetRank(k9s, k8s, k7s, k6s, k6h);
  ASSERT_EQ(rank_of_best_high_card + 1, rank_of_worst_pair);
}

TEST_F(FiveEvalTest, Pair) {
  long rank = LONG_MIN;
  for (int i = 0; i < kNumberOfFaces; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    for (int j = 2; j < kNumberOfFaces; ++j) {
      if (j == i) {
        continue;
      }
      int const J = (kNumberOfFaces - 1 - j) << 2;
      for (int k = 1; k < j; ++k) {
        if (k == i) {
          continue;
        }
        int const K = (kNumberOfFaces - 1 - k) << 2;
        for (int l = 0; l < k; ++l) {
          if (l == i) {
            continue;
          }
          int const L = (kNumberOfFaces - 1 - l) << 2;
          int const next_rank = eval.GetRank(I, I + 1, J, K, L);
          ASSERT_GT(next_rank, rank)
              << "Rank " << next_rank << " at " << I << ", " << I + 1 << ", "
              << J << ", " << K << ", " << L << " is invalid.";
          rank = next_rank;
        }
      }
    }
  }
}

TEST_F(FiveEvalTest, WorstTwoPairBeatsBestPair) {
  // Pair of Aces with King, Queen and Jack.
  int const rank_of_best_pair = eval.GetRank(kAs, kAh, kKs, kQs, kJs);
  // Pair of Sevens, Pair of Sixes, Eight high.
  int const rank_of_worst_two_pair = eval.GetRank(k8s, k7s, k7h, k6s, k6h);
  ASSERT_EQ(rank_of_best_pair + 1, rank_of_worst_two_pair);
}

TEST_F(FiveEvalTest, TwoPair) {
  long rank = LONG_MIN;
  for (int i = 1; i < kNumberOfFaces; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    for (int j = 0; j < i; ++j) {
      int const J = (kNumberOfFaces - 1 - j) << 2;
      for (int k = 0; k < kNumberOfFaces; ++k) {
        if (k == i || k == j) {
          continue;
        }
        int const K = (kNumberOfFaces - 1 - k) << 2;
        int const next_rank = eval.GetRank(I, I + 1, J, J + 1, K);
        ASSERT_GT(next_rank, rank)
            << "Rank " << next_rank << " at " << I << ", " << I + 1 << ", " << J
            << ", " << J + 1 << ", " << K << " is invalid.";
        rank = next_rank;
      }
    }
  }
}

TEST_F(FiveEvalTest, WorstTripleBeatsBestBestTwoPair) {
  // Pair of Aces, Pair of Kings, Queen high.
  int const rank_of_best_two_pair = eval.GetRank(kAs, kAh, kKs, kKh, kQs);
  // Triple Sixes, Eight high.
  int const rank_of_worst_triple = eval.GetRank(k8s, k7s, k6s, k6h, k6d);
  ASSERT_EQ(rank_of_best_two_pair + 1, rank_of_worst_triple);
}

TEST_F(FiveEvalTest, Triple) {
  long rank = LONG_MIN;
  for (int i = 0; i < kNumberOfFaces; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    for (int j = 1; j < kNumberOfFaces; ++j) {
      if (j == i) {
        continue;
      }
      int const J = (kNumberOfFaces - 1 - j) << 2;
      for (int k = 0; k < j; ++k) {
        if (k == i) {
          continue;
        }
        int const K = (kNumberOfFaces - 1 - k) << 2;
        int const next_rank = eval.GetRank(I, I + 1, I + 2, J, K);
        ASSERT_GT(next_rank, rank)
            << "Rank " << next_rank << " at " << I << ", " << I + 1 << ", "
            << I + 2 << ", " << J << ", " << K << " is invalid.";
        rank = next_rank;
      }
    }
  }
}

TEST_F(FiveEvalTest, WorstStraightBeatsBestTripe) {
  // Triple Aces, King, Queen.
  int const rank_of_best_triple = eval.GetRank(kAs, kAh, kAd, kKs, kQs);
  // Straight, Ace low.
  int const rank_of_worst_straight = eval.GetRank(kAh, k9s, k8s, k7s, k6s);
  ASSERT_EQ(rank_of_best_triple + 1, rank_of_worst_straight);
}

TEST_F(FiveEvalTest, Straight) {
  int rank = eval.GetRank(kAh, k9s, k8s, k7s, k6s);  // Straight, Ace low.
  for (int i = 0; i < kNumberOfFaces - 4; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    int const next_rank = eval.GetRank(I - 15, I - 12, I - 8, I - 4, I);
    ASSERT_GT(next_rank, rank)
        << "Rank " << next_rank << " at " << to_string(I - 15) << ", "
        << to_string(I - 12) << ", " << to_string(I - 8) << ", "
        << to_string(I - 4) << ", " << to_string(I) << " is invalid.";
    rank = next_rank;
  }
}

TEST_F(FiveEvalTest, WorstFullHouseBeatsBestStraight) {
  // Straight Ace high.
  int const rank_of_best_straight = eval.GetRank(kAh, kKs, kQs, kJs, kTs);
  // Triple Sixes, Pair Sevens.
  int const rank_of_worst_full_house = eval.GetRank(k7s, k7h, k6s, k6h, k6d);
  ASSERT_EQ(rank_of_best_straight + 1, rank_of_worst_full_house);
}

TEST_F(FiveEvalTest, FullHouse) {
  long rank = LONG_MIN;
  for (int i = 0; i < kNumberOfFaces; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    for (int j = 0; j < kNumberOfFaces; ++j) {
      if (j == i) {
        continue;
      }
      int const J = (kNumberOfFaces - 1 - j) << 2;
      int const next_rank = eval.GetRank(I, I + 1, I + 2, J, J + 1);
      ASSERT_GT(next_rank, rank)
          << "Rank " << next_rank << " at " << I << ", " << I + 1 << ", "
          << I + 2 << ", " << J << ", " << J + 1 << " is invalid.";
      rank = next_rank;
    }
  }
}

TEST_F(FiveEvalTest, WorstFlushBeatsBestFullHouse) {
  // Triple Aces, Pair Kings.
  int const rank_of_best_full_house = eval.GetRank(kAs, kAh, kAd, kKs, kKh);
  // Jack, Nine, Eight, Seven, Six.
  int const rank_of_worst_flush = eval.GetRank(kJs, k9s, k8s, k7s, k6s);
  ASSERT_EQ(rank_of_best_full_house + 1, rank_of_worst_flush);
}

TEST_F(FiveEvalTest, Flush) {
  long rank = LONG_MIN;
  for (int i = 5; i < kNumberOfFaces; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    for (int j = 3; j < i; ++j) {
      int const J = (kNumberOfFaces - 1 - j) << 2;
      for (int k = 2; k < j; ++k) {
        int const K = (kNumberOfFaces - 1 - k) << 2;
        for (int l = 1; l < k; ++l) {
          int const L = (kNumberOfFaces - 1 - l) << 2;
          for (int m = 0; m < l; ++m) {
            if (i - m == 4 || (i == kNumberOfFaces - 1 && j == 3)) {
              continue;
            }
            int const M = (kNumberOfFaces - 1 - m) << 2;
            int const next_rank = eval.GetRank(I, J, K, L, M);
            ASSERT_GT(next_rank, rank)
                << "Rank " << next_rank << " at " << I << ", " << J << ", " << K
                << ", " << L << ", " << M << " is invalid.";
            rank = next_rank;
          }
        }
      }
    }
  }
}

TEST_F(FiveEvalTest, WorstQuadBeatsBestFlush) {
  // Ace, King, Queen, Jack, Nine.
  int const rank_of_best_flush = eval.GetRank(kAs, kKs, kQs, kJs, k9s);
  // Quad Sixes, Seven high.
  int const rank_of_worst_quad = eval.GetRank(k7s, k6s, k6h, k6d, k6c);
  ASSERT_EQ(rank_of_best_flush + 1, rank_of_worst_quad);
}

TEST_F(FiveEvalTest, Quad) {
  long rank = LONG_MIN;
  for (int i = 0; i < kNumberOfFaces; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    for (int j = 0; j < kNumberOfFaces; ++j) {
      if (j == i) {
        continue;
      }
      int const J = (kNumberOfFaces - 1 - j) << 2;
      int const next_rank = eval.GetRank(I, I + 1, I + 2, I + 3, J);
      ASSERT_GT(next_rank, rank)
          << "Rank " << next_rank << " at " << I << ", " << I + 1 << ", "
          << I + 2 << ", " << I + 3 << ", " << J << " is invalid.";
      rank = next_rank;
    }
  }
}

TEST_F(FiveEvalTest, WorstStraightFlushBeatsBestQuad) {
  // Quad Aces, King high.
  int const rank_of_best_quad = eval.GetRank(kAs, kAh, kAd, kAc, kKs);
  // Straight flush Ace low.
  int const rank_of_worst_straight_flush =
      eval.GetRank(kAs, k9s, k8s, k7s, k6s);
  ASSERT_EQ(rank_of_best_quad + 1, rank_of_worst_straight_flush);
}

TEST_F(FiveEvalTest, StraightFlush) {
  int rank = eval.GetRank(kAs, k9s, k8s, k7s, k6s);  // Straight flush, Ace low.
  for (int i = 0; i < kNumberOfFaces - 4; ++i) {
    int const I = (kNumberOfFaces - 1 - i) << 2;
    int const next_rank = eval.GetRank(I - 16, I - 12, I - 8, I - 4, I);
    ASSERT_GT(next_rank, rank)
        << "Rank " << next_rank << " at " << I - 16 << ", " << I - 12 << ", "
        << I - 8 << ", " << I - 4 << ", " << I << " is invalid.";
    rank = next_rank;
  }
}

TEST_F(FiveEvalTest, SevenCardHand) {
  std::atomic<long> count(0);
  auto const outer = [&](int const& i) {
    long inner_count = 0;
    uint8_t five[5];
    uint8_t seven[7];
    seven[0] = i;
    for (int j = 5; j < i; ++j) {
      seven[1] = j;
      for (int k = 4; k < j; ++k) {
        seven[2] = k;
        for (int l = 3; l < k; ++l) {
          seven[3] = l;
          for (int m = 2; m < l; ++m) {
            seven[4] = m;
            for (int n = 1; n < m; ++n) {
              seven[5] = n;
              for (int p = 0; p < n; ++p) {
                seven[6] = p;
                int rbf = 0;
                uint8_t v = 0;
                for (uint8_t x = 1; x < 7; ++x) {
                  for (uint8_t y = 0; y < x; ++y) {
                    v = 0;
                    for (uint8_t z = 0; z < 7; ++z) {
                      if (z != x && z != y) {
                        five[v++] = seven[z];
                      }
                    }
                    int const rank = eval.GetRank(five[0], five[1], five[2],
                                                  five[3], five[4]);
                    if (rbf < rank) {
                      rbf = rank;
                    }
                  }
                }
                auto const rbs = eval.GetRank(i, j, k, l, m, n, p);
                ASSERT_EQ(rbf, rbs) << "Rank " << rbs << " at " << i << ", "
                                    << j << ", " << k << ", " << l << ", " << m
                                    << ", " << n << ", " << p << " is invalid.";
                ++inner_count;
              }
            }
          }
        }
      }
    }
    count += inner_count;
  };
  ParallelFor(6, kDeckSize, outer);
  ASSERT_EQ(8347680, count) << "Invalid number of seven card hands tested.";
}
