#include <union_find.hpp>

void UnionFind::Union(std::string p, std::string q) {
  InitParentIfEmpty(p);
  InitParentIfEmpty(q);
  auto rp = Find(parent_[p]);
  auto rq = Find(parent_[q]);
  if (rp == rq) {
    return;
  }
  parent_[rp] = rq;
}

bool UnionFind::IsConnected(std::string p, std::string q) {
  InitParentIfEmpty(p);
  InitParentIfEmpty(q);
  return Find(p) == Find(q);
}

std::string UnionFind::Find(std::string p) {
  InitParentIfEmpty(p);
  if (p != parent_[p]) {
    parent_[p] = Find(parent_[p]);
  }
  return parent_[p];
}

void UnionFind::InitParentIfEmpty(std::string p) {
  if (!parent_.contains(p)) {
    parent_[p] = p;
  }
}
