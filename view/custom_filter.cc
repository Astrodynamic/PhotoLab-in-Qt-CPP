#include "custom_filter.h"

#include <QDoubleSpinBox>

#include "ui_custom_filter.h"

namespace s21 {
CustomFilter::CustomFilter(QWidget *parent)
    : QDialog(parent), ui(new Ui::CustomFilter) {
  ui->setupUi(this);

  int row = ui->cb_width->currentText().toInt();
  int col = ui->cb_height->currentText().toInt();

  ChangeSizeTable(row, col);
}

CustomFilter::~CustomFilter() { delete ui; }

void CustomFilter::on_cb_width_currentTextChanged(const QString &value) {
  int row = value.toInt();
  int col = ui->cb_height->currentText().toInt();

  ChangeSizeTable(row, col);
}

void CustomFilter::on_cb_height_currentTextChanged(const QString &value) {
  int row = ui->cb_width->currentText().toInt();
  int col = value.toInt();

  ChangeSizeTable(row, col);
}

void CustomFilter::resizeEvent(QResizeEvent *event) {
  for (int r = 0; r < ui->tw_table->horizontalHeader()->count(); ++r) {
    ui->tw_table->verticalHeader()->setSectionResizeMode(r,
                                                         QHeaderView::Stretch);

    for (int c = 0; c < ui->tw_table->horizontalHeader()->count(); ++c) {
      ui->tw_table->horizontalHeader()->setSectionResizeMode(
          c, QHeaderView::Stretch);
    }
  }
}

void CustomFilter::ChangeSizeTable(int row, int col) {
  ui->tw_table->clear();
  ui->tw_table->setRowCount(row);
  ui->tw_table->setColumnCount(col);

  for (auto r = 0; r < row; ++r) {
    for (auto c = 0; c < col; ++c) {
      QDoubleSpinBox *temp = new QDoubleSpinBox(ui->tw_table);
      temp->setRange(-255.f, +255.f);
      temp->setValue(+0.f);

      temp->setMinimumWidth(50);
      temp->setMinimumHeight(30);

      ui->tw_table->setCellWidget(r, c, temp);
    }
  }
  this->resize(this->geometry().width(), this->geometry().height());
}

void CustomFilter::on_dbb_press_accepted() {
  int row = ui->cb_width->currentText().toInt();
  int col = ui->cb_height->currentText().toInt();

  std::vector<std::vector<double>> mat(row);

  for (int i = 0; i < row; ++i) {
    mat[i].resize(col);
    for (int j = 0; j < col; ++j) {
      mat[i][j] = qobject_cast<QDoubleSpinBox *>(ui->tw_table->cellWidget(i, j))
                      ->value();
    }
  }
  emit GetFilterMatrix(mat, row, col);
}
}  // namespace s21
