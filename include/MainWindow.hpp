#pragma once

#include <QObject>
#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>

#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "widgets/SettingsPanel.hpp"

#include "model/AntColonyModel.hpp"

#include "graphics/CustomView.hpp"
#include "graphics/SimulationVisualizer.hpp"
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
    void setupGraphics();
    void initSimulator();
    void connectSignals();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    QLabel* foodCollected;

    QGraphicsScene* scene;
    CustomView* view;
    SimulationVisualizer* visualizer;

    AntColonyModel* antColonyModel;
    // AntField* antField;
    SettingsPanel* settingsPanel;
    AntSimulator* antSimulator;
    QThread* simulationThread;
};
