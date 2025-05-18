#pragma once

#include <QObject>
#include <QMainWindow>

#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void initUI();

};
