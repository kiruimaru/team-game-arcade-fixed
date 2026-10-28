#define main arcadeMain
#include "../game.cpp"
#undef main

#include <cassert>

void resetGamble(int health, int caps) {
  hp = health;
  resources = caps;
  score = 0;
  turn = 1;
}

int main() {
  std::ostringstream output;
  auto *previous = std::cout.rdbuf(output.rdbuf());
  for (int caps = 0; caps < 5; ++caps) {
    resetGamble(100, caps);
    const bool completed = gambleEvent();
    assert(!completed);
    finishTurn(completed);
    assert(resources == caps && score == 0 && turn == 1 && hp == 100);
  }
  bool sawJackpot = false;
  bool sawWin = false;
  bool sawLoss = false;
  bool sawCurse = false;
  for (unsigned int seed = 0; seed < 1000; ++seed) {
    std::srand(seed);
    const int roll = std::rand() % 100;
    std::srand(seed);
    resetGamble(100, 50);
    assert(gambleEvent());
    if (roll < 50) {
      assert(resources == 60 && hp == 100);
      assert(score == (roll == 0 ? 500 : 100));
      sawJackpot = sawJackpot || roll == 0;
      sawWin = sawWin || roll != 0;
    } else {
      assert(resources == 40 && score == 0);
      assert(hp == (roll == 99 ? 70 : 100));
      sawLoss = true;
      sawCurse = sawCurse || roll == 99;
    }
    const int reward = score;
    finishTurn(true);
    assert(score == reward + 10 && turn == 2);

    std::srand(seed);
    resetGamble(1, 5);
    assert(gambleEvent());
    finishTurn(true);
    assert(resources == (roll < 50 ? 6 : 4));
    if (roll == 99) {
      assert(hp == 0 && score == 0 && turn == 1);
    }

    std::srand(seed);
    resetGamble(100, std::numeric_limits<int>::max());
    score = std::numeric_limits<int>::max();
    assert(gambleEvent());
    assert(resources >= 0);
    assert(score == std::numeric_limits<int>::max());
    if (roll < 50) {
      assert(resources == std::numeric_limits<int>::max());
    }
  }
  assert(sawJackpot && sawWin && sawLoss && sawCurse);
  resetGamble(0, 50);
  assert(!gambleEvent());
  assert(resources == 50 && score == 0);
  std::cout.rdbuf(previous);
  std::cout << "Gamble checks passed (1000 seeds and boundary cases).\n";
}
