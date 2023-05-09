#ifndef PHOTOLAB_MODEL_MODEL_H_
#define PHOTOLAB_MODEL_MODEL_H_

#include <QColorDialog>
#include <QImage>
#include <QLabel>
#include <vector>

namespace PLab {

class Model {
 public:
  Model() = default;
  ~Model() = default;

  QImage Grayscale(const QImage &img);
  QImage Negative(const QImage &img);
  QImage Toning(const QImage &img);
  QImage Emboss(const QImage &img);
  QImage Sharpen(const QImage &img);
  QImage BoxBlur(const QImage &img);
  QImage Gaussian(const QImage &img);
  QImage Laplacian(const QImage &img);
  QImage SobelLeft(const QImage &img);
  QImage SobelRight(const QImage &img);
  QImage SobelFull(const QImage &img);
  QImage CustomFilter(const QImage &img,
                      const std::vector<std::vector<double>> &mat, int row,
                      int col);
  QImage Brightness(const QImage &img, int value);
  QImage Contrast(const QImage &img, int percent);
  QImage ChangeByHSL(const QImage &img, QColor color);
  QImage ChangeByHSV(const QImage &img, QColor color);

 private:
  QImage Convolution(const QImage &img, std::vector<std::vector<double>> mat,
                     int m, int n);
  QImage Addition(const QImage &img_1, const QImage &img_2);
  static unsigned char SaturateCastToUnsignedInt(int value) {
    if (value >= 0 && value <= 255) return static_cast<unsigned char>(value);
    if (value < 0) return 0;
    return 255;
  }
};

}  // namespace PLab

#endif  // PHOTOLAB_MODEL_MODEL_H_
