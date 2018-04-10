//
// Created by Nikolay Yakovets on 2018-02-01.
//

#ifndef QS_SIMPLEESTIMATOR_H
#define QS_SIMPLEESTIMATOR_H

#include "Estimator.h"
#include "SimpleGraph.h"

#include <unordered_map>
#include <unordered_set>

class PairHasher {
public:
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U> &x) const {
        return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
    }
};

class SimpleEstimator : public Estimator {

    std::shared_ptr<SimpleGraph> graph;

    std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::vector<uint32_t>>> vertexIndexByLabel;
    std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::vector<uint32_t>>> vertexIndexByLabelReverse;
    std::unordered_map<uint32_t, std::vector<uint32_t>> outVertexByLabel;
    std::unordered_map<uint32_t, std::vector<uint32_t>> inVertexByLabel;

    void unpackQueryTree(std::vector<std::pair<uint32_t, bool>> *path, RPQTree *q);

    void generateSampleIds(uint32_t maxId, std::vector<uint32_t> *sampleIds, uint32_t n);

    double generateSampling(std::vector<uint32_t> *from, std::vector<uint32_t> *to, uint32_t sampleSize);

    double indexBasedJoinSampling(std::unordered_map<uint32_t, std::vector<uint32_t>> *index,
                                  std::vector<uint32_t> *from, std::vector<uint32_t> *to,
                                  uint32_t sampleSize);

public:

    explicit SimpleEstimator(std::shared_ptr<SimpleGraph> &g);

    ~SimpleEstimator() = default;

    void prepare() override;

    cardStat estimate(RPQTree *q) override;

    cardStat estimate_aux(std::vector<std::pair<uint32_t, bool>> path);
};

#endif //QS_SIMPLEESTIMATOR_H
