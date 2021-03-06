#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <item.h>
#include <QVector>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    int getRandomInt(int min, int max);
    QString getRandomDouble(double min, double max, int len);
    Ui::MainWindow* ui;
    QVector<Item*> itemList;
};

#endif // MAINWINDOW_H
