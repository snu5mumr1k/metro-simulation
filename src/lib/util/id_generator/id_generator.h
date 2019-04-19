#pragma once

#include <set>

namespace util {
template<typename Tag>
class IdGenerator {
public:
    template<typename TIterator>
    void ResetStorage(TIterator begin, TIterator end) {
        ids_.clear();
        AddMany(begin, end);
    }

    template<typename TIterator>
    void AddMany(TIterator begin, TIterator end) {
        for (auto i = begin; i != end; advance(i, 1)) {
            ids_.insert(i->id());
        }
    }

    int64_t GenerateNewId() {
        const int64_t id = ids_.empty() ? 0 : *ids_.begin() + 1;
        ids_.insert(id);
        return id;
    }

private:
    std::set<int64_t, std::greater<int64_t>> ids_;
};
}  // namespace util
