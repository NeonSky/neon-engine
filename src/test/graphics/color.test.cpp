#include "../util.hpp"

#include "../../engine/graphics/color.hpp"
using namespace engine::graphics;

TEST(ColorTest, Constructs1) {
  Color color;
  EXPECT_EQ(color.red(), 0.0F);
  EXPECT_EQ(color.green(), 0.0F);
  EXPECT_EQ(color.blue(), 0.0F);
  EXPECT_EQ(color.alpha(), 1.0F);

  EXPECT_EQ(color.rgb(), (std::array<float, 3>{0.0F, 0.0F, 0.0F}));
  EXPECT_EQ(color.rgba(), (std::array<float, 4>{0.0F, 0.0F, 0.0F, 1.0F}));
}

TEST(ColorTest, Constructs2) {
  Color color(0.1F, 0.3F, 0.7F);
  EXPECT_EQ(color.red(), 0.1F);
  EXPECT_EQ(color.green(), 0.3F);
  EXPECT_EQ(color.blue(), 0.7F);
  EXPECT_EQ(color.alpha(), 1.0F);

  EXPECT_EQ(color.rgb(), (std::array<float, 3>{0.1F, 0.3F, 0.7F}));
  EXPECT_EQ(color.rgba(), (std::array<float, 4>{0.1F, 0.3F, 0.7F, 1.0F}));
}

TEST(ColorTest, Constructs3) {
  Color color(0.4F, 0.2F, 0.6F, 0.1F);
  EXPECT_EQ(color.red(), 0.4F);
  EXPECT_EQ(color.green(), 0.2F);
  EXPECT_EQ(color.blue(), 0.6F);
  EXPECT_EQ(color.alpha(), 0.1F);

  EXPECT_EQ(color.rgb(), (std::array<float, 3>{0.4F, 0.2F, 0.6F}));
  EXPECT_EQ(color.rgba(), (std::array<float, 4>{0.4F, 0.2F, 0.6F, 0.1F}));
}

TEST(ColorTest, Equals1) {
  Color color1(0.4F, 0.2F, 0.6F);
  Color color2(0.4F, 0.2F, 0.6F, 1.0F);

  EXPECT_EQ(color1, color2);
}

TEST(ColorTest, Equals2) {
  Color color1(0.4F, 0.2F, 0.6F);
  Color color2(0.4F, 0.2F, 0.6F, 0.5F);

  EXPECT_NE(color1, color2);
}

TEST(ColorTest, Iterates1) {
  std::array<float, 4> expected{0.4F, 0.2F, 0.6F, 1.0F};
  Color color(std::array<float, 3>{0.4F, 0.2F, 0.6F});

  int i = 0;
  for (auto& comp : color)
    EXPECT_EQ(comp, expected[i++]);
}

TEST(ColorTest, Iterates2) {
  std::array<float, 4> expected{0.4F, 0.2F, 0.6F, 0.1F};
  Color color(expected);

  int i = 0;
  for (auto& comp : color)
    EXPECT_EQ(comp, expected[i++]);
}
