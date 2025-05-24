#include "mainwindow.h" // Será criado a seguir
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Visualizador Gráfico 2D");
    w.show();
    return a.exec();
}
