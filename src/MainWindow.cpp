#include "MainWindow.hpp"

#include <QThread>
#include <QMutexLocker>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), antColonyModel(new AntColonyModel())
{
    resize(AppSettings::instance().windowSize());

    init();

    AppSettings::instance().loadSettingsState(settingsPanel);
    AppSettings::instance().loadSplitterState("SceneSettingsSplitter", splitter);
    AppSettings::instance().loadModelData(antColonyModel);
    AppSettings::instance().loadSimulationState(antSimulator);
    QMetaObject::invokeMethod(antSimulator, "restore", 
                              Qt::QueuedConnection);
    visualizer->updateVisualization();
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

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 1, 1);

    view = new CustomView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setDragMode(QGraphicsView::NoDrag);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    view->scale(400, 400);

    visualizer = new SimulationVisualizer(scene, antColonyModel, this);

    leftLayout->addWidget(view);

    foodCollected  = new QLabel("Food collected: 0", view);
    foodCollected->setStyleSheet("color: white;");
    foodCollected->move(10, 10);
    foodCollected->raise();

    settingsPanel = new SettingsPanel();

    splitter = new QSplitter(Qt::Horizontal);
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
    connect(settingsPanel, &SettingsPanel::simulationSpeedChanged, antSimulator, &AntSimulator::setSimulationSpeed);

    connect(settingsPanel, &SettingsPanel::startSimulation, antSimulator, &AntSimulator::start);
    connect(settingsPanel, &SettingsPanel::pauseSimulation, antSimulator, &AntSimulator::pause);
    connect(settingsPanel, &SettingsPanel::resumeSimulation, antSimulator, &AntSimulator::resume);
    connect(settingsPanel, &SettingsPanel::resetSimulation, antSimulator, &AntSimulator::reset);

    connect(antSimulator, &AntSimulator::updateData, visualizer, &SimulationVisualizer::updateVisualization);
    connect(settingsPanel, &SettingsPanel::addFood, [this](const QPointF& pos) {
        if (!antColonyModel) return;
        antColonyModel->addFood(pos);
        if (visualizer) visualizer->updateVisualization();
    });
    connect(view, &CustomView::foodAddRequest, [this](const QPointF& pos) {
        if (!antColonyModel) return;
        antColonyModel->addFood(pos);
        if (visualizer) visualizer->updateVisualization();
    });
    connect(view, &QGraphicsView::customContextMenuRequested, [this](const QPoint&) {
        view->resetTransform();
        view->scale(400, 400);
    });

    connect(antSimulator, &AntSimulator::updateCollectedFood, foodCollected, [this](int count){
        foodCollected->setText(QString("Food collected: %1").arg(count));
    });
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    AppSettings::instance().saveModelData(antColonyModel);
    AppSettings::instance().saveSimulationState(antSimulator);
    AppSettings::instance().saveSettingsState(settingsPanel);
    AppSettings::instance().saveSplitterState("SceneSettingsSplitter", splitter);
    AppSettings::instance().setWindowSize(size());

    if (simulationThread && simulationThread->isRunning())
    {
        simulationThread->quit();
        simulationThread->wait(1000);
    }

    QMainWindow::closeEvent(event);
}
