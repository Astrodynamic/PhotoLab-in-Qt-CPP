#include "view.h"

#include "./ui_view.h"

namespace PLab {
View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  connect(&custom_filter_, &CustomFilter::GetFilterMatrix, this,
          &View::OnBtnAcceptCustomFilter);
}

View::~View() { delete ui; }

void View::on_act_open_triggered() {
  QString path = QFileDialog::getOpenFileName(
      this, tr("Open bmp"), QDir::currentPath(), tr("bmp(*.bmp)"));
  int width = ui->lbl_image->width();
  int height = ui->lbl_image->height();
  orig_img_ = filtered_image_ =
      QImage(path).scaled(width, height, Qt::KeepAspectRatio);
  ShowOrigImg();
}

void View::on_act_save_triggered() {
  QString file_path = QFileDialog::getSaveFileName(this, "Save Image");
  if (file_path.length()) {
    filtered_image_.save(file_path + ".bmp", "BMP");
  }
}

void View::on_btn_boxblur_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.BoxBlur(filtered_image_);
  } else {
    filtered_image_ = ctr_.BoxBlur(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_emboss_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Emboss(filtered_image_);
  } else {
    filtered_image_ = ctr_.Emboss(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_gaussian_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Gaussian(filtered_image_);
  } else {
    filtered_image_ = ctr_.Gaussian(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_grayscale_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Grayscale(filtered_image_);
  } else {
    filtered_image_ = ctr_.Grayscale(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_laplacian_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Laplacian(filtered_image_);
  } else {
    filtered_image_ = ctr_.Laplacian(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_negative_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Negative(filtered_image_);
  } else {
    filtered_image_ = ctr_.Negative(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_sharpen_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Sharpen(filtered_image_);
  } else {
    filtered_image_ = ctr_.Sharpen(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_sobel_full_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.SobelFull(filtered_image_);
  } else {
    filtered_image_ = ctr_.SobelFull(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_sobel_left_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.SobelLeft(filtered_image_);
  } else {
    filtered_image_ = ctr_.SobelLeft(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_sobel_right_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.SobelRight(filtered_image_);
  } else {
    filtered_image_ = ctr_.SobelRight(orig_img_);
  }
  ShowFilteredImg();
}

void View::on_btn_toning_clicked() {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.Toning(filtered_image_);
  } else {
    filtered_image_ = ctr_.Toning(orig_img_);
  }
  ShowFilteredImg();
}

void View::mousePressEvent(QMouseEvent *event) {
  QWidget::mousePressEvent(event);
  if (!orig_img_.isNull() and !filtered_image_.isNull()) {
    if (event->pos().x() >= ui->lbl_image->pos().x() and
        event->pos().x() <=
            ui->lbl_image->pos().x() + ui->lbl_image->width() and
        event->pos().y() >= ui->lbl_image->pos().y() and
        event->pos().y() <=
            ui->lbl_image->pos().y() + ui->lbl_image->height()) {
      if (is_orig_on_screen_) {
        ShowFilteredImg();
      } else {
        ShowOrigImg();
      }
    }
  }
}

void View::on_btn_custom_clicked() { custom_filter_.exec(); }

void View::OnBtnAcceptCustomFilter(const std::vector<std::vector<double> > &mat,
                                   int row, int col) {
  if (ui->cb_overlay_filters->isChecked()) {
    filtered_image_ = ctr_.CustomFilter(filtered_image_, mat, row, col);
  } else {
    filtered_image_ = ctr_.CustomFilter(orig_img_, mat, row, col);
  }
  ShowFilteredImg();
}

void View::on_cmb_brightness_valueChanged(int value) {
  ui->cmb_contrast->setValue(0);
  brightness_value_ = value;
}

void View::on_cmb_brightness_sliderReleased() {
  if (ui->cb_overlay_filters->isChecked()) {
    tmp_image_ = ctr_.Brightness(filtered_image_, brightness_value_);
  } else {
    tmp_image_ = ctr_.Brightness(orig_img_, brightness_value_);
  }
  ui->lbl_image->setPixmap(QPixmap::fromImage(tmp_image_));
}

void View::on_btn_brightness_apply_clicked() {
  filtered_image_ = tmp_image_;
  ShowFilteredImg();
}

void View::on_cmb_contrast_valueChanged(int value) {
  ui->cmb_brightness->setValue(0);
  contrast_value_ = value;
}

void View::on_cmb_contrast_sliderReleased() {
  if (ui->cb_overlay_filters->isChecked()) {
    tmp_image_ = ctr_.Contrast(filtered_image_, contrast_value_);
  } else {
    tmp_image_ = ctr_.Contrast(orig_img_, contrast_value_);
  }
  ui->lbl_image->setPixmap(QPixmap::fromImage(tmp_image_));
}

void View::on_btn_contrast_apply_clicked() {
  filtered_image_ = tmp_image_;
  ShowFilteredImg();
}

void View::on_btn_change_clicked() {
  tmp_image_ = filtered_image_;

  ColorWindow color_window(
      this,
      static_cast<ColorWindow::ColorModel>(ui->cmb_color_model->currentIndex()),
      std::bind(&View::OnColorWindowValuesChanged, this, std::placeholders::_1,
                std::placeholders::_2),
      std::bind(&View::OnColorWindowAccept, this));
  color_window.exec();
}

void View::OnColorWindowValuesChanged(QColor color,
                                      ColorWindow::ColorModel color_model) {
  switch (color_model) {
    case ColorWindow::ColorModel::kHSL:
      tmp_image_ = ctr_.ChangeByHSL(filtered_image_, color);
      break;
    case ColorWindow::ColorModel::kHSV:
      tmp_image_ = ctr_.ChangeByHSV(filtered_image_, color);
      break;
    default:
      break;
  }
  ui->lbl_image->setPixmap(QPixmap::fromImage(tmp_image_));
}

void View::OnColorWindowAccept() { filtered_image_ = tmp_image_; }

void View::ShowOrigImg() {
  ui->lbl_image->setPixmap(QPixmap::fromImage(orig_img_));
  setStatusTip("Original Image");
  is_orig_on_screen_ = true;

  ui->cmb_brightness->setValue(0);
  ui->cmb_contrast->setValue(0);
}

void View::ShowFilteredImg() {
  ui->lbl_image->setPixmap(QPixmap::fromImage(filtered_image_));
  setStatusTip("Filtered Image");
  is_orig_on_screen_ = false;

  ui->cmb_brightness->setValue(0);
  ui->cmb_contrast->setValue(0);
}

void View::on_btn_clear_filter_clicked() {
  filtered_image_ = orig_img_;
  ShowFilteredImg();
}

}  // namespace PLab
