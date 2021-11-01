#pragma once

#include <cinttypes>
#include <optional>

#include "utils.h"

namespace NModels {
    struct IBannerModel {
        virtual void UpdateVectors(std::vector<uint64_t> bannerIds, const TFeatures& features) = 0;
        virtual std::vector<uint64_t> GetBanners(const std::vector<float>& hitVector, uint32_t topK) const = 0;
        virtual void Reset() = 0;
    };
    using IBannerModelPtr = std::shared_ptr<IBannerModel>;

    IBannerModelPtr CreateDummyBannerModel(const std::string& path);
}
