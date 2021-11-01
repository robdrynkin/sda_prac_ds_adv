#pragma once

#include <cinttypes>
#include <optional>

#include "utils.h"

namespace NModels {
    struct IHitModel {
        virtual std::vector<float> GetVector(const TFeatures& features) = 0;
    };
    using IHitModelPtr = std::shared_ptr<IHitModel>;

    IHitModelPtr CreateDummyHitModel(const std::string& path);
}
