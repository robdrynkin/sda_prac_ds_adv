#include <gtest/gtest.h>

#include "../src/models/banner.h"
#include "../src/models/hit.h"
#include "../src/service/service.h"


TEST(ServiceTest, Empty) {
    auto service = NService::CreateService(
        NModels::CreateDummyBannerModel(""),
        NModels::CreateDummyHitModel("")
    );

    auto bannerIds = service->GetBanners({}, 5);
    EXPECT_EQ(bannerIds.size(), 0);
}

TEST(ServiceTest, BannersCount) {
    auto service = NService::CreateService(
            NModels::CreateDummyBannerModel(""),
            NModels::CreateDummyHitModel("")
    );
    service->UpdateVectors({1, 2, 3, 4}, {});

    auto bannerIds = service->GetBanners({}, 3);
    EXPECT_EQ(bannerIds.size(), 3);
}
