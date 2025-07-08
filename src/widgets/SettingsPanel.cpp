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

    antCountSpinBox = new QSpinBox();
    antCountSpinBox->setRange(1, 1000);
    antCountSpinBox->setValue(100);

    QSlider* antCountSlider = new QSlider(Qt::Horizontal);
    antCountSlider->setRange(1, 1000);
    antCountSlider->setValue(100);
    
    antLayout->addWidget(new QLabel("Ant count: "));
    antLayout->addWidget(antCountSpinBox);
    antLayout->addWidget(antCountSlider);

    QObject::connect(antCountSpinBox, &QSpinBox::valueChanged, this, &SettingsPanel::antCountChanged);
    QObject::connect(antCountSlider, &QSlider::valueChanged, antCountSpinBox, &QSpinBox::setValue);

    antSettingsBox->setLayout(antLayout);
    mainLayout->addWidget(antSettingsBox);

    //Food
    QGroupBox* foodSettingsBox = new QGroupBox("Food Settings");
    QHBoxLayout* foodCordLayout = new QHBoxLayout();
    QVBoxLayout* foodLayout = new QVBoxLayout();
    
    QSpinBox* xFoodCord = new QSpinBox;
    QSpinBox* yFoodCord = new QSpinBox;

    xFoodCord->setRange(0, 1000);
    yFoodCord->setRange(0, 1000);
    xFoodCord->setValue(0);
    yFoodCord->setValue(0);

    foodCordLayout->addWidget(xFoodCord);
    foodCordLayout->addWidget(yFoodCord);

    addFoodButton = new QPushButton("Add Food");

    foodLayout->addLayout(foodCordLayout);
    foodLayout->addWidget(addFoodButton);

    connect(addFoodButton, &QPushButton::clicked, [this, xFoodCord, yFoodCord]{
        onAddFoodButtonClicked(xFoodCord->value(), yFoodCord->value());
    });

    foodSettingsBox->setLayout(foodLayout);
    mainLayout->addWidget(foodSettingsBox);

    // Speed
    QGroupBox* speedSettingsBox = new QGroupBox("Speed Settings");
    QVBoxLayout* speedLayout = new QVBoxLayout();

    speedSpinBox = new QSpinBox();
    speedSpinBox->setRange(1, 10);
    speedSpinBox->setValue(1);

    QSlider* speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setRange(1, 10);
    speedSlider->setValue(1);
    speedLayout->addWidget(new QLabel("Simulation Speed: "));
    speedLayout->addWidget(speedSpinBox);
    speedLayout->addWidget(speedSlider);

    QObject::connect(speedSpinBox, &QSpinBox::valueChanged, this, &SettingsPanel::simulationSpeedChanged);
    QObject::connect(speedSlider, &QSlider::valueChanged, speedSpinBox, &QSpinBox::setValue);

    speedSettingsBox->setLayout(speedLayout);
    mainLayout->addWidget(speedSettingsBox);

    //Simulation
    QHBoxLayout* controlLayout = new QHBoxLayout();

    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    resumeButton = new QPushButton("Resume");
    resetButton = new QPushButton("Reset");

    controlLayout->addWidget(startButton);
    controlLayout->addWidget(pauseButton);
    controlLayout->addWidget(resumeButton);
    controlLayout->addWidget(resetButton);

    QObject::connect(startButton, &QPushButton::clicked, this, &SettingsPanel::startSimulation);
    QObject::connect(pauseButton, &QPushButton::clicked, this, &SettingsPanel::pauseSimulation);
    QObject::connect(resumeButton, &QPushButton::clicked, this, &SettingsPanel::resumeSimulation);
    QObject::connect(resetButton, &QPushButton::clicked, this, &SettingsPanel::resetSimulation);

    mainLayout->addLayout(controlLayout);
}

void SettingsPanel::updateAntCount(int count)
{
    antCountSpinBox->setValue(count);
}

void SettingsPanel::updateSimulationSpeed(qreal speed)
{
    speedSpinBox->setValue(static_cast<int>(speed));
}

void SettingsPanel::onAddFoodButtonClicked(int x, int y)
{
    emit addFood(QPointF(x, y));
}
