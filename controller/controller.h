#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  QImage Grayscale(const QImage &img) { return model_.Grayscale(img); }
  QImage Negative(const QImage &img) { return model_.Negative(img); }
  QImage Toning(const QImage &img) { return model_.Toning(img); }
  QImage Emboss(const QImage &img) { return model_.Emboss(img); }
  QImage Sharpen(const QImage &img) { return model_.Sharpen(img); }
  QImage BoxBlur(const QImage &img) { return model_.BoxBlur(img); }
  QImage Gaussian(const QImage &img) { return model_.Gaussian(img); }
  QImage Laplacian(const QImage &img) { return model_.Laplacian(img); }
  QImage SobelLeft(const QImage &img) { return model_.SobelLeft(img); }
  QImage SobelRight(const QImage &img) { return model_.SobelRight(img); }
  QImage SobelFull(const QImage &img) { return model_.SobelFull(img); }
  QImage CustomFilter(const QImage &img,
                      const std::vector<std::vector<double>> &mat, int row,
                      int col) {
    return model_.CustomFilter(img, mat, row, col);
  }
  QImage Brightness(const QImage &img, int value) {
    return model_.Brightness(img, value);
  }
  QImage Contrast(const QImage &img, int percent) {
    return model_.Contrast(img, percent);
  }
  QImage ChangeByHSL(const QImage &img, QColor color) {
    return model_.ChangeByHSL(img, color);
  }
  QImage ChangeByHSV(const QImage &img, QColor color) {
    return model_.ChangeByHSV(img, color);
  }

 private:
  Model model_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
