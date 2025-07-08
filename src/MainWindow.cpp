#include "MainWindow.hpp"

#include <QThread>
#include <QMutexLocker>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), antColonyModel(new AntColonyModel())
{
    init();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    initUI();
    initSimulator();
    connectSignals();
}

void MainWindow::initUI()
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    QWidget* leftPanel = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    antField = new AntField(antColonyModel);
    leftLayout->addWidget(antField);

    settingsPanel = new SettingsPanel();

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftPanel);
    splitter->addWidget(settingsPanel);

    mainLayout->addWidget(splitter);
}

void MainWindow::initSimulator()
{
    simulationThread = new QThread(this);
    antSimulator = new AntSimulator(antColonyModel);

    antSimulator->moveToThread(simulationThread);

    connect(simulationThread, &QThread::finished, antSimulator, &QObject::deleteLater);
    connect(simulationThread, &QThread::finished, simulationThread, &QThread::deleteLater);

    simulationThread->start();
}

void MainWindow::connectSignals()
{
    connect(settingsPanel, &SettingsPanel::antCountChanged, antSimulator, &AntSimulator::setAntCount);

    connect(settingsPanel, &SettingsPanel::startSimulation, antSimulator, &AntSimulator::start);
    connect(settingsPanel, &SettingsPanel::pauseSimulation, antSimulator, &AntSimulator::pause);
    connect(settingsPanel, &SettingsPanel::resumeSimulation, antSimulator, &AntSimulator::resume);
    connect(settingsPanel, &SettingsPanel::resetSimulation, antSimulator, &AntSimulator::reset);

    connect(antSimulator, &AntSimulator::updateData, antField, &AntField::redraw);
    connect(settingsPanel, &SettingsPanel::addFood, antField, &AntField::addFood);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (simulationThread && simulationThread->isRunning())
    {
        simulationThread->quit();
        simulationThread->wait(1000);
    }

    QMainWindow::closeEvent(event);
}
