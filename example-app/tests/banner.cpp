#include <gtest/gtest.h>

#include "../src/models/banner.h"


TEST(DummyBannerModelTest, Empty) {
    auto model = NModels::CreateDummyBannerModel("");

    auto bannerIds = model->GetBanners(std::vector<float>(10, 0), 5);
    EXPECT_TRUE(bannerIds.empty());
}

TEST(DummyBannerModelTest, BadShape) {
    auto model = NModels::CreateDummyBannerModel("");

    EXPECT_THROW(
        model->GetBanners(std::vector<float>(5, 0), 5),
        std::runtime_error
    );
}

TEST(DummyBannerModelTest, BannersCount) {
    auto model = NModels::CreateDummyBannerModel("");
    model->UpdateVectors({1, 2, 3, 4}, {});

    auto bannerIds = model->GetBanners(std::vector<float>(10, 1), 3);
    EXPECT_EQ(bannerIds.size(), 3);
}
