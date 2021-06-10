#include <recti/recti.hpp>
// #include <random>
#include <iostream>
#include <list>
#include <set>

// using std::randint;
using namespace recti;
using std::cout;

auto main() -> int {
  auto lst = std::list<rectangle<int>>{};

  for (int i = 0; i < 10; ++i) {
    int ii = i * 100;
    for (int j = 0; j < 20; ++j) {
      int jj = j * 100;
      // auto xx = interval{ii, ii + randint(50, 110)};
      // auto yy = interval{jj, jj + randint(50, 110)};
      auto xx = interval{ii, ii + std::rand() % 100};
      auto yy = interval{jj, jj + std::rand() % 100};
      auto r = rectangle { xx, yy };
      lst.push_back(r);
    }
  }

  std::set<rectangle<int>> S;  // set of maximal non-overlapped rectangles
  std::list<rectangle<int>> L; // list of the removed rectangles

  for (const auto &r : lst) {
    auto search = S.find(r);
    if (search != S.end()) {
      L.push_back(r);
    } else {
      S.insert(r);
    }
  }

  // for (const auto &r : S) {
  //   cout << "  \\draw " << r << ";\n";
  // }
  // for (const auto &r : L) {
  //   cout << "  \\draw[color=red] " << r << ";\n";
  // }
}
