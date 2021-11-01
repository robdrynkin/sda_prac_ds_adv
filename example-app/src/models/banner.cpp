#include "banner.h"

#include <memory>
#include <vector>
#include <stdexcept>

#include <torch/script.h>


namespace NModels {

    class TDummyBannerModel : public IBannerModel {
    public:
        explicit TDummyBannerModel(const std::string&) {}

        void UpdateVectors(std::vector<uint64_t> bannerIds, const TFeatures&) override {
            for (auto bannerId: bannerIds) {
                Vectors[bannerId] = torch::randn({10});
            }
        }

        std::vector<uint64_t> GetBanners(const std::vector<float>& vec, uint32_t topK) const override {
            if (vec.size() != 10) {
                throw std::runtime_error("Unexpected hit vector dim");
            }
            auto t = torch::from_blob((void*)vec.data(), {static_cast<long long>(vec.size())});
            std::vector<std::pair<float, uint64_t>> similarity;
            for (const auto& [bannerId, bannerVector]: Vectors) {
                similarity.emplace_back((t * bannerVector).sum().item().toFloat(), bannerId);
            }
            std::sort(similarity.begin(), similarity.end());
            std::vector<uint64_t> result;
            for (uint32_t i = 0; i < topK && i < similarity.size(); ++i) {
                result.push_back(similarity[similarity.size() - i - 1].second);
            }
            return result;
        }

        void Reset() override {
            Vectors.clear();
        }

    private:
        std::unordered_map<uint64_t, torch::Tensor> Vectors;
    };


    IBannerModelPtr CreateDummyBannerModel(const std::string& path) {
        return std::make_shared<TDummyBannerModel>(path);
    }

}
