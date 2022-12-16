#ifndef SRC_VIEW_CUSTOM_FILTER_H_
#define SRC_VIEW_CUSTOM_FILTER_H_

#include <QDialog>

namespace Ui {
class CustomFilter;
}

namespace s21 {

class CustomFilter : public QDialog {
  Q_OBJECT

 public:
  explicit CustomFilter(QWidget *parent = nullptr);
  ~CustomFilter();

 signals:
  void GetFilterMatrix(std::vector<std::vector<double>> mat, int row, int col);

 private slots:
  void on_cb_width_currentTextChanged(const QString &value);
  void on_cb_height_currentTextChanged(const QString &value);

  void on_dbb_press_accepted();

 protected:
  void resizeEvent(QResizeEvent *event);

 private:
  Ui::CustomFilter *ui;

  void ChangeSizeTable(int row, int col);
};

}  // namespace s21

#endif  // SRC_VIEW_CUSTOM_FILTER_H_
