#include <QApplication>

#include "view.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  PLab::View window;
  window.show();
  return app.exec();
}
