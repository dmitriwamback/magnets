//
// Created by Dmitri on 2026-11-16.
//

#include "Model.h"

void Model::Step(float deltaTime) {

}

void Model::Populate(Magnet &magnet) {
    magnets.push_back(magnet);
}

std::vector<Magnet> Model::Magnets() {
    return magnets;
}
