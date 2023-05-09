#include "color_window.h"

#include "./ui_color_window.h"

ColorWindow::ColorWindow(QWidget *parent, ColorModel color_model,
                         std::function<void(QColor, ColorModel)> color_callback,
                         std::function<void()> apply_callback)
    : QDialog(parent),
      ui(new Ui::ColorWindow),
      m_color_model(color_model),
      m_color_callback(color_callback),
      m_apply_callback(apply_callback) {
  ui->setupUi(this);

  setFixedSize(width(), height());

  switch (color_model) {
    case ColorModel::kHSL:
      ui->ll_value_brightness->setText("Lightness");
      break;
    case ColorModel::kHSV:
      ui->ll_value_brightness->setText("Value");
      break;
    default:
      break;
  }
}

ColorWindow::~ColorWindow() { delete ui; }

void ColorWindow::on_sld_hue_valueChanged(int value) {
  ui->sx_hue->setValue(value);
  UpdateColor();
}

void ColorWindow::on_sld_hue_sliderReleased() {
  if (m_color_callback) m_color_callback(m_color, m_color_model);
}

void ColorWindow::on_sld_saturation_valueChanged(int value) {
  ui->sx_saturation->setValue(value);
  UpdateColor();
}

void ColorWindow::on_sld_saturation_sliderReleased() {
  if (m_color_callback) m_color_callback(m_color, m_color_model);
}

void ColorWindow::on_sld_value_brightness_valueChanged(int value) {
  ui->sx_value_brightness->setValue(value);
  UpdateColor();
}

void ColorWindow::on_sld_value_brightness_sliderReleased() {
  if (m_color_callback) m_color_callback(m_color, m_color_model);
}

void ColorWindow::on_sx_hue_valueChanged(int value) {
  ui->sld_hue->setValue(value);
}

void ColorWindow::on_sx_saturation_valueChanged(int value) {
  ui->sld_saturation->setValue(value);
}

void ColorWindow::on_sx_value_brightness_valueChanged(int value) {
  ui->sld_value_brightness->setValue(value);
}

void ColorWindow::on_btn_apply_clicked() {
  if (m_apply_callback) m_apply_callback();
  close();
}

void ColorWindow::UpdateColor() {
  switch (m_color_model) {
    case ColorModel::kHSL:
      m_color = QColor::fromHsl(ui->sld_hue->value() % 360,
                               ui->sld_saturation->value(),
                               ui->sld_value_brightness->value());
      break;
    case ColorModel::kHSV:
      m_color = QColor::fromHsv(ui->sld_hue->value() % 360,
                               ui->sld_saturation->value(),
                               ui->sld_value_brightness->value());
      break;
    default:
      break;
  }
}
