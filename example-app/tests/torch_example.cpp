#include <gtest/gtest.h>

#include <torch/torch.h>

TEST(TorchExample, TensorBasics) {
    auto t1 = torch::ones({1, 2, 3});
    EXPECT_EQ(t1.size(0), 1);
    EXPECT_EQ(t1.size(1), 2);
    EXPECT_EQ(t1.size(2), 3);

    auto t2 = t1.sum(1);
    EXPECT_EQ(t2.size(0), 1);
    EXPECT_EQ(t2.size(1), 3);

    auto t2Accessor = t2.accessor<float,2>();
    for (int i = 0; i < 1; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_EQ(t2Accessor[i][j], 2);
        }
    }
}

TEST(TorchExample, FromBlob) {
    std::vector<float> arr{1, 2, 3, 4, 5, 6};
    auto t = torch::from_blob((void*)arr.data(), {2, 3});

    EXPECT_EQ(t.size(0), 2);
    EXPECT_EQ(t.size(1), 3);

    auto tAccessor = t.accessor<float,2>();
    EXPECT_EQ(tAccessor[0][0], 1);
    EXPECT_EQ(tAccessor[0][1], 2);
    EXPECT_EQ(tAccessor[0][2], 3);
    EXPECT_EQ(tAccessor[1][0], 4);
    EXPECT_EQ(tAccessor[1][1], 5);
    EXPECT_EQ(tAccessor[1][2], 6);
}
