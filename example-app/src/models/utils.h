#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>


namespace NModels {
    using TFeature = std::vector<std::vector<float>>;
    using TFeatures = std::unordered_map<std::string, TFeature>;

    struct IModel {
        virtual TFeature Forward(const TFeatures& input) = 0;
    };
    using IModelPtr = std::shared_ptr<IModel>;
}
