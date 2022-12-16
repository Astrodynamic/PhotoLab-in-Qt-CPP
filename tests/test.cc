#include <gtest/gtest.h>

#include <QDebug>

#include "model.h"

constexpr double error = 1e-1;

TEST(Grayscale, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-bw-average.png");

  QImage result(mdl.Grayscale(img_1));

  for (int i = 0; i < result.width(); ++i) {
    for (int j = 0; j < result.height(); ++j) {
      ASSERT_NEAR(img_2.pixelColor(i, j).redF(), result.pixelColor(i, j).redF(),
                  error);
      ASSERT_NEAR(img_2.pixelColor(i, j).greenF(),
                  result.pixelColor(i, j).greenF(), error);
      ASSERT_NEAR(img_2.pixelColor(i, j).blueF(),
                  result.pixelColor(i, j).blueF(), error);
    }
  }
}

TEST(Negative, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-negative.png");

  QImage result(mdl.Negative(img_1));

  for (int i = 0; i < result.width(); ++i) {
    for (int j = 0; j < result.height(); ++j) {
      ASSERT_NEAR(img_2.pixelColor(i, j).redF(), result.pixelColor(i, j).redF(),
                  error);
      ASSERT_NEAR(img_2.pixelColor(i, j).greenF(),
                  result.pixelColor(i, j).greenF(), error);
      ASSERT_NEAR(img_2.pixelColor(i, j).blueF(),
                  result.pixelColor(i, j).blueF(), error);
    }
  }
}

TEST(Emboss, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-ebmoss.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.Emboss(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 206).blueF(),
              result.pixelColor(98, 206).blueF(), error);
}

TEST(Sharpen, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-sharpen.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.Sharpen(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 206).blueF(),
              result.pixelColor(98, 206).blueF(), error);
}

TEST(BoxBlur, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-box-blur.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.BoxBlur(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 13).blueF(),
              result.pixelColor(98, 13).blueF(), error);
}

TEST(Gaussian, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-gaussian-blur.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.Gaussian(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 13).blueF(),
              result.pixelColor(98, 13).blueF(), error);
}

TEST(Laplacian, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-outline.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.Laplacian(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 13).blueF(),
              result.pixelColor(98, 13).blueF(), error);
}

TEST(SobelLeft, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-sobel-left.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.SobelLeft(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 13).blueF(),
              result.pixelColor(98, 13).blueF(), error);
}

TEST(SobelRight, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-sobel-right.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.SobelRight(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 39).blueF(),
              result.pixelColor(98, 39).blueF(), error);
}

TEST(SobelFull, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-sobel-left-and-right.png");

  QImage gray_img(mdl.Grayscale(img_1));
  QImage result(mdl.SobelFull(gray_img));

  ASSERT_NEAR(img_2.pixelColor(3, 10).redF(), result.pixelColor(3, 10).redF(),
              error);
  ASSERT_NEAR(img_2.pixelColor(41, 57).greenF(),
              result.pixelColor(41, 57).greenF(), error);
  ASSERT_NEAR(img_2.pixelColor(98, 39).blueF(),
              result.pixelColor(98, 39).blueF(), error);
}

TEST(CustomFilter, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-outline.png");

  static std::vector<std::vector<double>> mat{
      {-1.f, -1.f, -1.f}, {-1.f, +8.f, -1.f}, {-1.f, -1.f, -1.f}};

  QImage result_1(mdl.CustomFilter(img_1, mat, 3, 3));
  QImage result_2(mdl.Laplacian(img_1));

  for (int i = 0; i < result_1.width(); ++i) {
    for (int j = 0; j < result_1.height(); ++j) {
      ASSERT_NEAR(result_1.pixelColor(i, j).redF(),
                  result_2.pixelColor(i, j).redF(), error);
      ASSERT_NEAR(result_1.pixelColor(i, j).greenF(),
                  result_2.pixelColor(i, j).greenF(), error);
      ASSERT_NEAR(result_1.pixelColor(i, j).blueF(),
                  result_2.pixelColor(i, j).blueF(), error);
    }
  }
}

TEST(Brightness, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");
  QImage img_2(":/sample-outline.png");

  QImage result_1(mdl.Brightness(img_1, -100));
  QImage result_2(mdl.Brightness(img_2, 100));

  ASSERT_GE(img_1.pixelColor(0, 0).lightness(),
            result_1.pixelColor(0, 0).lightness());
  ASSERT_LE(img_2.pixelColor(0, 0).lightness(),
            result_2.pixelColor(0, 0).lightness());
}

TEST(Contrast, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");

  QImage result_1(mdl.Contrast(img_1, -100));

  int img1_min = 255;
  int img1_max = 0;
  int res1_min = 255;
  int res1_max = 0;

  for (int i = 0; i < result_1.width(); ++i) {
    for (int j = 0; j < result_1.height(); ++j) {
      img1_min = std::min(img1_min, img_1.pixelColor(i, j).lightness());
      img1_max = std::max(img1_max, img_1.pixelColor(i, j).lightness());
      res1_min = std::min(res1_min, result_1.pixelColor(i, j).lightness());
      res1_max = std::max(res1_max, result_1.pixelColor(i, j).lightness());
    }
  }

  ASSERT_LE(img1_min, res1_min);
  ASSERT_GE(img1_max, res1_max);
}

TEST(HSL, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");

  QImage result_1(mdl.ChangeByHSL(img_1, QColor::fromHsl(60, 10, 90)));

  ASSERT_NE(img_1.pixelColor(0, 0).saturation(),
            result_1.pixelColor(0, 0).saturation());
  ASSERT_NE(img_1.pixelColor(0, 0).lightness(),
            result_1.pixelColor(0, 0).lightness());
}

TEST(HSV, test_1) {
  s21::Model mdl;

  QImage img_1(":/sample.png");

  QImage result_1(mdl.ChangeByHSL(img_1, QColor::fromHsv(120, 10, 90)));

  ASSERT_NE(img_1.pixelColor(0, 0).saturation(),
            result_1.pixelColor(0, 0).saturation());
  ASSERT_NE(img_1.pixelColor(0, 0).value(), result_1.pixelColor(0, 0).value());
}
