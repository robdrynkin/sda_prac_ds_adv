#include "hit.h"

#include <memory>
#include <optional>

#include <torch/script.h>


namespace NModels {

    class TDummyHitModel : public IHitModel {
    public:
        TDummyHitModel(const std::string&) { }

        std::vector<float> GetVector(const TFeatures& features) override {
            auto t = torch::randn({10});
            std::vector<float> vec(t.data_ptr<float>(), t.data_ptr<float>() + t.numel());
            return vec;
        }
    };

    IHitModelPtr CreateDummyHitModel(const std::string &path) {
        return std::make_shared<TDummyHitModel>(path);
    }

}
