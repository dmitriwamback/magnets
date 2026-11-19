//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_MODEL_H
#define MAGNET_SIMULATOR_MODEL_H
#include <vector>

#include "../object/Magnet.h"

enum class ModelType {
    DIPOLE_MODEL,
    TWO_POLE_MODEL
};

class Model {
public:
    virtual void Step(float deltaTime);
    void Populate(Magnet& magnet);
    std::vector<Magnet> Magnets();

    std::vector<Magnet> magnets;
};


#endif //MAGNET_SIMULATOR_MODEL_H
