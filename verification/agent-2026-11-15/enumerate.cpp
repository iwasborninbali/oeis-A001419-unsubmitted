// Independent free-polyomino enumeration and hole count, C++17.
// No OEIS code or third-party polyomino algorithms are used.
// A polyomino is a 4-connected set of occupied closed unit squares.
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
#include <vector>
using Shape = std::vector<uint16_t>;  // packed x*64+y, normalized, sorted
struct ShapeHash {
    size_t operator()(const Shape &v) const {
        uint64_t h = 1469598103934665603ULL;
        for (uint16_t x : v) { h ^= x + 1u; h *= 1099511628211ULL; }
        return size_t(h);
    }
};
static Shape canonical(const std::vector<std::pair<int,int>>& cells) {
    Shape best;
    for (int orientation = 0; orientation < 8; ++orientation) {
        int minx=1000, miny=1000;
        std::vector<std::pair<int,int>> points;
        points.reserve(cells.size());
        for (auto [x,y] : cells) {
            if (orientation & 1) x = -x;                  // reflect
            if (orientation & 2) { int t=x; x=-y; y=t; } // 90 deg
            if (orientation & 4) { x=-x; y=-y; }          // 180 deg
            minx = std::min(minx,x); miny = std::min(miny,y);
            points.emplace_back(x,y);
        }
        Shape candidate;
        candidate.reserve(cells.size());
        for (auto [x,y] : points)
            candidate.push_back(uint16_t((x-minx)*64+(y-miny)));
        std::sort(candidate.begin(),candidate.end());
        if (best.empty() || candidate < best) best = std::move(candidate);
    }
    return best;
}
static bool has_hole(const Shape &shape) {
    int maxx=0,maxy=0;
    for (auto xy:shape) {maxx=std::max(maxx,int(xy/64));maxy=std::max(maxy,int(xy%64));}
    int w=maxx+3,h=maxy+3; // one-cell exterior margin on each side
    std::vector<uint8_t> wall(w*h,0), reached(w*h,0);
    for (auto xy:shape) wall[(int(xy/64)+1)*h+int(xy%64)+1] = 1;
    std::queue<std::pair<int,int>> q;
    reached[0]=1;q.emplace(0,0);
    constexpr int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
    while (!q.empty()) {
        auto [x,y]=q.front();q.pop();
        for (int d=0;d<4;d++) {
            int X=x+dx[d],Y=y+dy[d];
            if (X>=0 && X<w && Y>=0 && Y<h && !wall[X*h+Y] && !reached[X*h+Y]) {
                reached[X*h+Y]=1;q.emplace(X,Y);
            }
        }
    }
    for (int x=0;x<w;x++) for (int y=0;y<h;y++)
        if (!wall[x*h+y] && !reached[x*h+y]) return true;
    return false;
}
int main(int argc,char**argv) {
    const int limit = (argc==2 ? std::stoi(argv[1]) : 14);
    if (limit < 1 || limit > 14) { std::cerr<<"Choose 1..14\n";return 2; }
    // Expected values are control data from OEIS A000105 and A001419,
    // not part of the generation or hole-detection routines.
    constexpr uint64_t expected_total[15]={1,1,1,2,5,12,35,108,369,1285,4655,17073,63600,238591,901971};
    constexpr uint64_t expected_holey[15]={0,0,0,0,0,0,0,1,6,37,195,979,4663,21474,96496};
    std::unordered_set<Shape,ShapeHash> current;
    current.insert(Shape{0});
    auto start=std::chrono::steady_clock::now();
    std::cout<<"n total holey unholey OEIS_total OEIS_holey match\n";
    for (int n=1;n<=limit;n++) {
        uint64_t holes=0;
        for (const Shape &s:current) holes += has_hole(s);
        uint64_t total=current.size();
        bool match=total==expected_total[n] && holes==expected_holey[n];
        std::cout<<n<<' '<<total<<' '<<holes<<' '<<(total-holes)<<' '
                 <<expected_total[n]<<' '<<expected_holey[n]<<' '<<(match?"PASS":"FAIL")<<'\n';
        if (!match) return 1;
        if (n==limit) break;
        std::unordered_set<Shape,ShapeHash> next;
        next.reserve(current.size()*4);
        for (const Shape &s:current) {
            std::vector<std::pair<int,int>> points;
            points.reserve(s.size()+1);
            for (auto xy:s) points.emplace_back(xy/64,xy%64);
            for (auto [x,y]:points) {
                for (auto [dx,dy]:std::array<std::pair<int,int>,4>{{{1,0},{-1,0},{0,1},{0,-1}}}) {
                    auto t=std::make_pair(x+dx,y+dy);
                    if (std::find(points.begin(),points.end(),t)!=points.end()) continue;
                    points.push_back(t);
                    next.insert(canonical(points));
                    points.pop_back();
                }
            }
        }
        current.swap(next);
    }
    auto stop=std::chrono::steady_clock::now();
    std::cout<<"wall_seconds "<<std::chrono::duration<double>(stop-start).count()<<'\n';
    return 0;
}
