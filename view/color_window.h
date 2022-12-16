#ifndef SRC_VIEW_COLOR_WINDOW_H_
#define SRC_VIEW_COLOR_WINDOW_H_

#include <QDialog>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui {
class ColorWindow;
}
QT_END_NAMESPACE

class ColorWindow : public QDialog {
  Q_OBJECT

 public:
  enum ColorModel { kHSL, kHSV };

  explicit ColorWindow(
      QWidget *parent = nullptr, ColorModel color_model = ColorModel::kHSL,
      std::function<void(QColor, ColorModel)> color_callback = nullptr,
      std::function<void()> apply_callback = nullptr);
  ~ColorWindow() override;

 private slots:
  void on_sld_hue_valueChanged(int value);
  void on_sld_hue_sliderReleased();
  void on_sld_saturation_valueChanged(int value);
  void on_sld_saturation_sliderReleased();
  void on_sld_value_brightness_valueChanged(int value);
  void on_sld_value_brightness_sliderReleased();
  void on_sx_hue_valueChanged(int value);
  void on_sx_saturation_valueChanged(int value);
  void on_sx_value_brightness_valueChanged(int value);
  void on_btn_apply_clicked();

 private:
  void UpdateColor();

  Ui::ColorWindow *ui;
  ColorModel color_model_;
  QColor color_;
  std::function<void(QColor, ColorModel)> color_callback_;
  std::function<void()> apply_callback_;
};

#endif  // SRC_VIEW_COLOR_WINDOW_H_
