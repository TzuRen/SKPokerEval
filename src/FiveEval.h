// SKPokerEval
//
// Copyright 2010 Kenneth J. Shackleton
//
// This program gives you software freedom; you can copy, convey, propagate,
// redistribute and/or modify this program under the terms of the GNU General
// Public License (GPL) as published by the Free Software Foundation (FSF),
// either version 3 of the License, or (at your option) any later version of
// the GPL published by the FSF.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program in a file in the top-level directory called "GPLv3". If
// not, see http://www.gnu.org/licenses/.

#ifndef SKPOKEREVAL_FIVEEVAL_H
#define SKPOKEREVAL_FIVEEVAL_H

#include <array>
#include <cstdint>
#include "Constants.h"

class FiveEval {
 public:
  constexpr FiveEval();
  ~FiveEval() = default;
  // Get the rank of a hand comprising five cards, each represented by an
  // integer from 0 (resp. Ace of Spades) to 51 (resp. Two of Clubs) inclusive.
  // The higher the rank the better the hand. Two hands of equal rank tie.
  constexpr uint16_t GetRank(int, int, int, int, int) const;
  // Get the rank of a hand comprising seven cards, each represented by an
  // integer from 0 (resp. Ace of Spades) to 51 (resp. Two of Clubs) inclusive.
  // The higher the rank the better the hand. Two hands of equal rank tie.
  constexpr uint16_t GetRank(int, int, int, int, int, int, int) const;

 private:
  std::array<uint16_t, MAX_FIVE_NONFLUSH_KEY_INT + 1> mRankPtr = {};
  std::array<uint16_t, MAX_FIVE_FLUSH_KEY_INT + 1> mFlushRankPtr = {};
  std::array<uint32_t, kDeckSize> mDeckcardsFace = {};
  std::array<uint16_t, kDeckSize> mDeckcardsFlush = {};
  std::array<uint16_t, kDeckSize> mDeckcardsSuit = {};
};

constexpr FiveEval::FiveEval() {
  uint32_t const face[kNumberOfFaces] = {kSixFive,   kSevenFive, kEightFive,
                                         kNineFive,  kTenFive,   kJackFive,
                                         kQueenFive, kKingFive,  kAceFive};
  uint32_t const face_flush[kNumberOfFaces] = {
      SIX_FLUSH,  SEVEN_FLUSH, EIGHT_FLUSH, NINE_FLUSH, TEN_FLUSH,
      JACK_FLUSH, QUEEN_FLUSH, KING_FLUSH,  ACE_FLUSH};

  for (int n = 0; n < kNumberOfFaces; ++n) {
    int const N = n << 2;
    mDeckcardsSuit[N] = kSpade;
    mDeckcardsSuit[N + 1] = kHeart;
    mDeckcardsSuit[N + 2] = kDiamond;
    mDeckcardsSuit[N + 3] = kClub;

    mDeckcardsFace[N] = face[8 - n];
    mDeckcardsFace[N + 1] = face[8 - n];
    mDeckcardsFace[N + 2] = face[8 - n];
    mDeckcardsFace[N + 3] = face[8 - n];

    mDeckcardsFlush[N] = (short unsigned)face_flush[8 - n];
    mDeckcardsFlush[N + 1] = (short unsigned)face_flush[8 - n];
    mDeckcardsFlush[N + 2] = (short unsigned)face_flush[8 - n];
    mDeckcardsFlush[N + 3] = (short unsigned)face_flush[8 - n];
  }

  // n increments as rank.
  short unsigned n = 1;

  // High card.
  for (int i = 5; i < kNumberOfFaces; ++i) {
    for (int j = 3; j < i; ++j) {
      for (int k = 2; k < j; ++k) {
        for (int l = 1; l < k; ++l) {
          // No straights.
          for (int m = 0; m < l && !(i - m == 4 || (i == 8 && j == 3)); ++m) {
            mRankPtr[face[i] + face[j] + face[k] + face[l] + face[m]] = n++;
          }
        }
      }
    }
  }

  // Pair.
  for (int i = 0; i < kNumberOfFaces; ++i) {
    for (int j = 2; j < kNumberOfFaces; ++j) {
      for (int k = 1; k < j; ++k) {
        for (int l = 0; l < k; ++l) {
          if (i != j && i != k && i != l) {
            mRankPtr[(face[i] << 1) + face[j] + face[k] + face[l]] = n++;
          }
        }
      }
    }
  }

  // Two pair.
  for (int i = 1; i < kNumberOfFaces; ++i) {
    for (int j = 0; j < i; ++j) {
      for (int k = 0; k < kNumberOfFaces; ++k) {
        // No full-houses.
        if (k != i && k != j) {
          mRankPtr[(face[i] << 1) + (face[j] << 1) + face[k]] = n++;
        }
      }
    }
  }

  // Triple.
  for (int i = 0; i < kNumberOfFaces; ++i) {
    for (int j = 1; j < kNumberOfFaces; ++j) {
      for (int k = 0; k < j; ++k) {
        // No quads.
        if (i != j && i != k) {
          mRankPtr[(3 * face[i]) + face[j] + face[k]] = n++;
        }
      }
    }
  }

  // Low straight non-flush.
  mRankPtr[face[8] + face[0] + face[1] + face[2] + face[3]] = n++;

  // Usual straight non-flush.
  for (int i = 0; i < kNumberOfFaces - 4; ++i) {
    mRankPtr[face[i] + face[i + 1] + face[i + 2] + face[i + 3] + face[i + 4]] =
        n++;
  }

  // Full house.
  for (int i = 0; i < kNumberOfFaces; ++i) {
    for (int j = 0; j < kNumberOfFaces; ++j) {
      if (i != j) {
        mRankPtr[(3 * face[i]) + (face[j] << 1)] = n++;
      }
    }
  }

  // Flush not a straight.
  for (int i = 5; i < kNumberOfFaces; ++i) {
    for (int j = 3; j < i; ++j) {
      for (int k = 2; k < j; ++k) {
        for (int l = 1; l < k; ++l) {
          for (int m = 0; m < l; ++m) {
            if (!(i - m == 4 || (i == 8 && j == 3))) {
              mFlushRankPtr[face_flush[i] | face_flush[j] | face_flush[k] |
                            face_flush[l] | face_flush[m]] = n++;
            }
          }
        }
      }
    }
  }

  // Quad.
  for (int i = 0; i < kNumberOfFaces; ++i) {
    for (int j = 0; j < kNumberOfFaces; ++j) {
      if (i != j) {
        mRankPtr[(face[i] << 2) + face[j]] = n++;
      }
    }
  }

  // Low straight flush.
  mFlushRankPtr[face_flush[0] | face_flush[1] | face_flush[2] | face_flush[3] |
                face_flush[8]] = n++;

  // Usual straight flush.
  for (int i = 0; i < kNumberOfFaces - 4; ++i) {
    mFlushRankPtr[face_flush[i] | face_flush[i + 1] | face_flush[i + 2] |
                  face_flush[i + 3] | face_flush[i + 4]] = n++;
  }
}

constexpr short unsigned FiveEval::GetRank(int const card_one,
                                           int const card_two,
                                           int const card_three,
                                           int const card_four,
                                           int const card_five) const {
  if ((mDeckcardsSuit[card_one] == mDeckcardsSuit[card_two]) &&
      (mDeckcardsSuit[card_one] == mDeckcardsSuit[card_three]) &&
      (mDeckcardsSuit[card_one] == mDeckcardsSuit[card_four]) &&
      (mDeckcardsSuit[card_one] == mDeckcardsSuit[card_five])) {
    return mFlushRankPtr[mDeckcardsFlush[card_one] | mDeckcardsFlush[card_two] |
                         mDeckcardsFlush[card_three] |
                         mDeckcardsFlush[card_four] |
                         mDeckcardsFlush[card_five]];
  }
  return mRankPtr[mDeckcardsFace[card_one] + mDeckcardsFace[card_two] +
                  mDeckcardsFace[card_three] + mDeckcardsFace[card_four] +
                  mDeckcardsFace[card_five]];
}

constexpr uint16_t FiveEval::GetRank(int const card_one,
                                     int const card_two,
                                     int const card_three,
                                     int const card_four,
                                     int const card_five,
                                     int const card_six,
                                     int const card_seven) const {
  int const seven_cards[7] = {card_one,  card_two, card_three, card_four,
                              card_five, card_six, card_seven};
  int temp[5] = {};

  uint16_t best_rank_so_far = 0, current_rank = 0;
  int m = 0;

  for (int i = 1; i < 7; ++i) {
    for (int j = 0; j < i; ++j) {
      m = 0;
      for (int k = 0; k < 7; ++k) {
        if (k != i && k != j) {
          temp[m++] = seven_cards[k];
        }
      }
      current_rank = GetRank(temp[0], temp[1], temp[2], temp[3], temp[4]);
      if (best_rank_so_far < current_rank) {
        best_rank_so_far = current_rank;
      }
    }
  }
  return best_rank_so_far;
}

#endif  // SKPOKEREVAL_FIVEEVAL_H
