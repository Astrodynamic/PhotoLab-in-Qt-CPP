#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>

#include "../controller/controller.h"
#include "color_window.h"
#include "custom_filter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_act_open_triggered();
  void on_btn_boxblur_clicked();
  void on_btn_emboss_clicked();
  void on_btn_gaussian_clicked();
  void on_btn_grayscale_clicked();
  void on_btn_laplacian_clicked();
  void on_btn_negative_clicked();
  void on_btn_sharpen_clicked();
  void on_btn_sobel_full_clicked();
  void on_btn_sobel_left_clicked();
  void on_btn_sobel_right_clicked();
  void on_btn_toning_clicked();
  void on_btn_custom_clicked();

  void on_cmb_brightness_valueChanged(int value);
  void on_cmb_brightness_sliderReleased();
  void on_btn_brightness_apply_clicked();
  void on_cmb_contrast_valueChanged(int value);
  void on_cmb_contrast_sliderReleased();
  void on_btn_contrast_apply_clicked();
  void on_btn_change_clicked();
  void OnColorWindowValuesChanged(QColor color,
                                  ColorWindow::ColorModel color_model);
  void OnColorWindowAccept();

  void on_btn_clear_filter_clicked();
  void mousePressEvent(QMouseEvent *event) override;

  void on_act_save_triggered();

 private:
  void OnBtnAcceptCustomFilter(const std::vector<std::vector<double>> &mat,
                               int row, int col);

  void ShowOrigImg();
  void ShowFilteredImg();

  QImage orig_img_;
  QImage filtered_image_;
  QImage tmp_image_;

  int brightness_value_ = 0;
  int contrast_value_ = 0;

  Ui::View *ui;
  Controller ctr_;
  CustomFilter custom_filter_;

  bool is_orig_on_screen_ = true;
};

}  // namespace s21

#endif  // SRC_VIEW_VIEW_H_
