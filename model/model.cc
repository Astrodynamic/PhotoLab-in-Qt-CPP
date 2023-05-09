#include "model.h"

namespace PLab {

QImage Model::Grayscale(const QImage &img) {
  if (!img.isNull()) {
    QImage res(img);
    for (int x = 0; x < res.width(); ++x) {
      for (int y = 0; y < res.height(); ++y) {
        int gray = qGray(res.pixel(x, y));
        res.setPixel(x, y, qRgb(gray, gray, gray));
      }
    }
    return res;
  }
  return img;
}

QImage Model::Negative(const QImage &img) {
  if (!img.isNull()) {
    QImage res(img);
    for (int x = 0; x < res.width(); ++x) {
      for (int y = 0; y < res.height(); ++y) {
        QColor color = res.pixelColor(x, y);
        color.setRgb(255 - color.red(), 255 - color.green(),
                     255 - color.blue());
        res.setPixel(x, y, color.rgba());
      }
    }
    return res;
  }
  return img;
}

QImage Model::Toning(const QImage &img) {
  if (!img.isNull()) {
    QImage res(img);
    QColor c1 = QColorDialog::getColor();
    for (int x = 0; x < res.width(); ++x) {
      for (int y = 0; y < res.height(); ++y) {
        QColor c2 = res.pixelColor(x, y);
        int R = c1.red() + c2.red();
        int G = c1.green() + c2.green();
        int B = c1.blue() + c2.blue();

        if (R > 255) R = 255;
        if (G > 255) G = 255;
        if (B > 255) B = 255;

        c2.setRgb(R, G, B);
        res.setPixel(x, y, c2.rgba());
      }
    }
    return res;
  }
  return img;
}

QImage Model::Emboss(const QImage &img) {
  static std::vector<std::vector<double>> mat{
      {-2, -1, +0}, {-1, +1, +1}, {+0, +1, +2}};

  return Convolution(img, mat, 3, 3);
}

QImage Model::Sharpen(const QImage &img) {
  static std::vector<std::vector<double>> mat{
      {+0, -1, +0}, {-1, +4, -1}, {+0, -1, +0}};

  return (Addition(Convolution(img, mat, 3, 3), img));
}

QImage Model::BoxBlur(const QImage &img) {
  double value = 1.f / 9.f;
  static std::vector<std::vector<double>> mat{
      {value, value, value}, {value, value, value}, {value, value, value}};

  return Convolution(img, mat, 3, 3);
}

QImage Model::Gaussian(const QImage &img) {
  double v1 = 1.f / 16.f;
  double v2 = 2.f / 16.f;
  double v3 = 4.f / 16.f;
  static std::vector<std::vector<double>> mat{
      {v1, v2, v1}, {v2, v3, v2}, {v1, v2, v1}};

  return Convolution(img, mat, 3, 3);
}

QImage Model::Laplacian(const QImage &img) {
  static std::vector<std::vector<double>> mat{
      {-1.f, -1.f, -1.f}, {-1.f, +8.f, -1.f}, {-1.f, -1.f, -1.f}};

  return Convolution(img, mat, 3, 3);
}

QImage Model::SobelLeft(const QImage &img) {
  static std::vector<std::vector<double>> mat{
      {+1.f, +0.f, -1.f}, {+2.f, +0.f, -2.f}, {+1.f, +0.f, -1.f}};

  return Convolution(img, mat, 3, 3);
}

QImage Model::SobelRight(const QImage &img) {
  static std::vector<std::vector<double>> mat{
      {-1.f, +0.f, +1.f}, {-2.f, +0.f, +2.f}, {-1.f, +0.f, +1.f}};

  return Convolution(img, mat, 3, 3);
}

QImage Model::SobelFull(const QImage &img) {
  static std::vector<std::vector<double>> mat1{
      {+1.f, +0.f, -1.f}, {+2.f, +0.f, -2.f}, {+1.f, +0.f, -1.f}};

  static std::vector<std::vector<double>> mat2 = {
      {-1.f, +0.f, +1.f}, {-2.f, +0.f, +2.f}, {-1.f, +0.f, +1.f}};

  return Addition(Convolution(img, mat1, 3, 3), Convolution(img, mat2, 3, 3));
}

QImage Model::CustomFilter(const QImage &img,
                           const std::vector<std::vector<double>> &mat, int row,
                           int col) {
  return Convolution(img, mat, row, col);
}

QImage Model::Brightness(const QImage &img, int value) {
  QImage img_copy(img);
  for (int i = 0; i < img.width(); i++) {
    for (int j = 0; j < img.height(); j++) {
      QRgb color = img.pixel(i, j);
      img_copy.setPixel(i, j,
                        qRgb(SaturateCastToUnsignedInt(qRed(color) + value),
                             SaturateCastToUnsignedInt(qGreen(color) + value),
                             SaturateCastToUnsignedInt(qBlue(color) + value)));
    }
  }
  return img_copy;
}

QImage Model::Contrast(const QImage &img, int contrast) {
  QImage img_copy(img);
  for (int i = 0; i < img.width(); i++) {
    for (int j = 0; j < img.height(); j++) {
      QRgb color = img.pixel(i, j);
      double factor = (259.0 * (contrast + 255)) / (255.0 * (259 - contrast));
      img_copy.setPixel(
          i, j,
          qRgb(SaturateCastToUnsignedInt(factor * (qRed(color) - 128) + 128),
               SaturateCastToUnsignedInt(factor * (qGreen(color) - 128) + 128),
               SaturateCastToUnsignedInt(factor * (qBlue(color) - 128) + 128)));
    }
  }
  return img_copy;
}

QImage Model::ChangeByHSL(const QImage &img, QColor color) {
  QImage img_copy(img);
  for (int i = 0; i < img_copy.width(); i++) {
    for (int j = 0; j < img_copy.height(); j++) {
      QColor pixel_color = img_copy.pixelColor(i, j);
      pixel_color.toHsl();
      pixel_color.setHsl(
          pixel_color.hue() + color.hue(),
          SaturateCastToUnsignedInt(pixel_color.saturation() *
                                    (color.saturation() / 160.0)),
          SaturateCastToUnsignedInt(pixel_color.lightness() *
                                    (color.lightness() / 150.0)));
      img_copy.setPixelColor(i, j, pixel_color);
    }
  }
  return img_copy;
}

QImage Model::ChangeByHSV(const QImage &img, QColor color) {
  QImage img_copy(img);
  for (int i = 0; i < img_copy.width(); i++) {
    for (int j = 0; j < img_copy.height(); j++) {
      QColor pixel_color = img_copy.pixelColor(i, j);
      pixel_color.toHsv();
      pixel_color.setHsv(
          pixel_color.hue() + color.hue(),
          SaturateCastToUnsignedInt(pixel_color.saturation() *
                                    (color.saturation() / 160.0)),
          SaturateCastToUnsignedInt(pixel_color.value() *
                                    (color.value() / 150.0)));
      img_copy.setPixelColor(i, j, pixel_color);
    }
  }
  return img_copy;
}

QImage Model::Convolution(const QImage &img,
                          std::vector<std::vector<double>> mat, int m, int n) {
  QImage uimg(img);
  QColor color;
  int R, G, B, X, Y;
  for (int i = 0; i < img.width(); ++i) {
    for (int j = 0; j < img.height(); ++j) {
      R = 0;
      G = 0;
      B = 0;
      for (int p = -m / 2; p <= m / 2; ++p) {
        for (int q = -n / 2; q <= n / 2; ++q) {
          if (((i + p) < 0) || ((i + p) >= img.width())) {
            X = i - p;
          } else {
            X = i + p;
          }

          if (((j + q) < 0) || ((j + q) >= img.height())) {
            Y = j - q;
          } else {
            Y = j + q;
          }

          color = img.pixelColor(X, Y);

          R += static_cast<int>(color.red() * mat[m / 2 + p][n / 2 + q]);
          G += static_cast<int>(color.green() * mat[m / 2 + p][n / 2 + q]);
          B += static_cast<int>(color.blue() * mat[m / 2 + p][n / 2 + q]);
        }
      }
      R = qBound(0, R, 255);
      G = qBound(0, G, 255);
      B = qBound(0, B, 255);

      uimg.setPixel(i, j, qRgb(R, G, B));
    }
  }
  return uimg;
}

QImage Model::Addition(const QImage &img_1, const QImage &img_2) {
  QImage result(img_1);
  if (img_1.width() == img_2.width() && img_1.height() == img_2.height()) {
    for (int i = 0; i < result.width(); ++i) {
      for (int j = 0; j < result.height(); ++j) {
        QColor c_1 = img_1.pixelColor(i, j);
        QColor c_2 = img_2.pixelColor(i, j);

        int R = qBound(0, c_1.red() + c_2.red(), 255);
        int G = qBound(0, c_1.green() + c_2.green(), 255);
        int B = qBound(0, c_1.blue() + c_2.blue(), 255);

        result.setPixel(i, j, qRgb(R, G, B));
      }
    }
  }
  return result;
}

}  // namespace PLab
