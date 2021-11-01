#include <gtest/gtest.h>

#include "../src/models/hit.h"


TEST(DummyHitModelTest, Dim) {
    auto model = NModels::CreateDummyHitModel("");
    auto vec = model->GetVector({});
    EXPECT_EQ(vec.size(), 10);
}
