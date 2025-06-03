#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    initUI();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUI()
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    QWidget* leftPanel = new QWidget();
    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    QLabel* antField = new QLabel();
    antField->setText("antField");
    leftLayout->addWidget(antField);

    SettingsPanel* settingsPanel = new SettingsPanel();

    QSplitter* splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftPanel);
    splitter->addWidget(settingsPanel);

    mainLayout->addWidget(splitter);
}
