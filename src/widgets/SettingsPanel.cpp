#include "../../include/widgets/SettingsPanel.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QPushButton>

SettingsPanel::SettingsPanel(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Ant
    QGroupBox* antSettingsBox = new QGroupBox("Ant Settings");
    QVBoxLayout* antLayout = new QVBoxLayout();

    antCountSlider = new QSlider(Qt::Horizontal);
    antCountSlider->setRange(1, 1000);
    antCountSlider->setValue(100);
    antLayout->addWidget(new QLabel("Ant count: "));
    antLayout->addWidget(antCountSlider);

    QObject::connect(antCountSlider, &QSlider::valueChanged, this, &SettingsPanel::antCountChanged);

    antSettingsBox->setLayout(antLayout);
    mainLayout->addWidget(antSettingsBox);

    // Speed
    QGroupBox* speedSettingsBox = new QGroupBox("Speed Settings");
    QVBoxLayout* speedLayout = new QVBoxLayout();

    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setRange(1, 10);
    speedSlider->setValue(1);
    speedLayout->addWidget(new QLabel("Simulation Speed: "));
    speedLayout->addWidget(speedSlider);

    QObject::connect(speedSlider, &QSlider::valueChanged, [this](int value){
        emit simulationSpeedChanged(value / 1.0);
    });

    speedSettingsBox->setLayout(speedLayout);
    mainLayout->addWidget(speedSettingsBox);

    //Simulation
    QHBoxLayout* controlLayout = new QHBoxLayout();

    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    resetButton = new QPushButton("Reset");

    controlLayout->addWidget(startButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(resetButton);

    QObject::connect(startButton, &QPushButton::clicked, this, &SettingsPanel::startSimulation);
    QObject::connect(pauseButton, &QPushButton::clicked, this, &SettingsPanel::pauseSimulation);
    QObject::connect(resetButton, &QPushButton::clicked, this, &SettingsPanel::resetSimulation);

    mainLayout->addLayout(controlLayout);
}

void SettingsPanel::updateAntCount(int count)
{
    
}

void SettingsPanel::updateSimulationSpeed(qreal speed)
{
    
}

void SettingsPanel::onAddFoodButtonClicked()
{
    
}
