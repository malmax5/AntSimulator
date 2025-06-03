#pragma once

#include <QObject>
#include <QMainWindow>

#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "widgets/SettingsPanel.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void initUI();

};
