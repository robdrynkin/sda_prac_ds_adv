#include "service.h"

#include <string>
#include <vector>

namespace NService {
    class TService: public IService{
    public:
        TService(NModels::IBannerModelPtr bannerModel, NModels::IHitModelPtr hitModel)
            : BannerModel(bannerModel)
            , HitModel(hitModel)
        { }

        void UpdateVectors(std::vector<uint64_t> bannerIds, const NModels::TFeatures& bannersFeatures) override {
            BannerModel->UpdateVectors(bannerIds, bannersFeatures);
        }
        std::vector<uint64_t> GetBanners(const NModels::TFeatures& hitFeatures, uint32_t topK) override {
            auto hitVector = HitModel->GetVector(hitFeatures);
            return BannerModel->GetBanners(hitVector, topK);
        }

        void Reset() override {
            BannerModel->Reset();
        }

    private:
        NModels::IBannerModelPtr BannerModel;
        NModels::IHitModelPtr HitModel;
    };

    IServicePtr CreateService(NModels::IBannerModelPtr bannerModel, NModels::IHitModelPtr hitModel) {
        return std::make_shared<TService>(bannerModel, hitModel);
    }
}
