#include <recti/recti.hpp>
#include <experimental/random>
#include <iostream>
#include <list>
#include <set>

using std::experimental::randint;
using namespace recti;
using std::cout;

int main() {
  auto lst = std::list<rectangle2D<int>>{};

  for (int i = 0; i < 10; ++i) {
    int ii = i * 100;
    for (int j = 0; j < 20; ++j) {
      int jj = j * 100;
      rectangle2D r{interval{ii, ii + randint(50, 110)},
                    interval{jj, jj + randint(50, 110)}};
      lst.push_back(r);
    }
  }

  std::set<rectangle2D<int>> S;  // set of maximal non-overlapped rectangles
  std::list<rectangle2D<int>> L; // list of the removed rectangles

  for (const auto &r : lst) {
    auto search = S.find(r);
    if (search != S.end()) {
      L.push_back(r);
    } else {
      S.insert(r);
    }
  }

  for (const auto &r : S) {
    cout << "  \\draw " << r << ";\n";
  }
  for (const auto &r : L) {
    cout << "  \\draw[color=red] " << r << ";\n";
  }
}
