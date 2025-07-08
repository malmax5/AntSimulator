#pragma once

#include <QObject>
#include <QMainWindow>

#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "widgets/SettingsPanel.hpp"

#include "model/AntColonyModel.hpp"

#include "AntField.hpp"
#include "AntSimulator.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void init();

private:
    void initUI();
    void initSimulator();
    void connectSignals();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    AntColonyModel* antColonyModel;
    AntField* antField;
    SettingsPanel* settingsPanel;
    AntSimulator* antSimulator;
    QThread* simulationThread;
};
