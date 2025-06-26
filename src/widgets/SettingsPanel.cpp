#include "../../include/widgets/SettingsPanel.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

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

    //Food
    QGroupBox* foodSettingsBox = new QGroupBox("Food Settings");
    QHBoxLayout* foodCordLayout = new QHBoxLayout();
    QVBoxLayout* foodLayout = new QVBoxLayout();
    
    QSpinBox* xFoodCord = new QSpinBox;
    QSpinBox* yFoodCord = new QSpinBox;

    xFoodCord->setRange(0, 400);
    yFoodCord->setRange(0, 400);
    xFoodCord->setValue(0);
    yFoodCord->setValue(0);

    foodCordLayout->addWidget(xFoodCord);
    foodCordLayout->addWidget(yFoodCord);

    addFoodButton = new QPushButton("Add Food");

    foodLayout->addLayout(foodCordLayout);
    foodLayout->addWidget(addFoodButton);

    connect(addFoodButton, &QPushButton::clicked, [this, xFoodCord, yFoodCord]{
        onAddFoodButtonClicked(xFoodCord->value(), yFoodCord->value());
        qDebug() << xFoodCord->value() << " " << yFoodCord->value();
    });

    foodSettingsBox->setLayout(foodLayout);
    mainLayout->addWidget(foodSettingsBox);

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
    antCountSlider->setValue(count);
}

void SettingsPanel::updateSimulationSpeed(qreal speed)
{
    speedSlider->setValue(static_cast<int>(speed));
}

void SettingsPanel::onAddFoodButtonClicked(int x, int y)
{
    emit addFood(QPointF(x, y));
}
