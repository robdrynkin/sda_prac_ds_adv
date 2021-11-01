#pragma once

#include "../models/banner.h"
#include "../models/hit.h"

namespace NService {
    struct IService {
        virtual void UpdateVectors(std::vector<uint64_t> bannerIds, const NModels::TFeatures& bannersFeatures) = 0;
        virtual std::vector<uint64_t> GetBanners(const NModels::TFeatures& hitFeatures, uint32_t topK) = 0;
        virtual void Reset() = 0;
    };
    using IServicePtr = std::shared_ptr<IService>;

    IServicePtr CreateService(NModels::IBannerModelPtr bannerModel, NModels::IHitModelPtr hitModel);
}
