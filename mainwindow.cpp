#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QDoubleValidator>

#include <iostream>
#include "src/genetic_algorithm/Population.h"
#include "src/genetic_algorithm/Creature.h"
#include "src/SalesmanProblem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->displayWidget->setScene(scene);

//    test values
    ui->entrySteps->setText("100");
    ui->entryCities->setText("20");
    ui->entryPopulation->setText("50");
    ui->entryMutation->setText("0.1");

    auto * validator_int = new QIntValidator(0, 1000000, this);
    auto * validator_double = new QDoubleValidator(0.0, 1.0, 2, this);

    ui->entrySteps->setValidator(validator_int);
    ui->entryCities->setValidator(validator_int);
    ui->entryPopulation->setValidator(validator_int);
    ui->entryMutation->setValidator(validator_double);

    on_buttonStop_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RedrawPath() {
    scene->clear();

    const std::vector<Destination> &cities = solution_progress.GetProblem().GetCities();
    DrawCitiesCircularPath(cities, solution_progress.GetBestSolution());
    DrawCityPoints(cities);
}

void MainWindow::DrawCitiesCircularPath(const std::vector<Destination> &cities, const std::vector<int> &city_order) {
    lines.clear();
    lines.resize(cities.size());

    int line_i = 0;
    auto city_iter = city_order.begin();
    Destination prev_city{};
    Destination cur_city = cities[*city_iter];
    std::advance(city_iter, 1);
    while (city_iter != city_order.end()) {
        prev_city = cur_city;
        cur_city = cities[*city_iter];

        lines[line_i++] = scene->addLine(
                prev_city.x, prev_city.y,
                cur_city.x, cur_city.y,
                bluePen);

        std::advance(city_iter, 1);
    }

    auto &first_city = cities[*city_order.begin()];
    lines.emplace_back(scene->addLine(
            first_city.x, first_city.y,
            cur_city.x, cur_city.y,
            bluePen));
}

void MainWindow::DrawCityPoints(const std::vector<Destination> &cities) {
    ellipses.clear();
    ellipses.resize(cities.size());

    double circle_radius = 5;

    int ellipse_i = 0;
    for (auto &city : cities) {
        ellipses[ellipse_i++] = scene->addEllipse(
                city.x - circle_radius, city.y - circle_radius,
                circle_radius * 2, circle_radius * 2,
                bluePen, blueBrush);
    }
}

void MainWindow::StartSimulation(
        int cities_amount,
        int population_size,
        double mutate_fraction,
        int iterations_amount) {

    ui->entryCities->setEnabled(false);
    ui->entryPopulation->setEnabled(false);
    ui->buttonSimulate->setText("Restart simulation");

    ui->buttonStep->setEnabled(true);
    ui->buttonStepToEnd->setEnabled(true);
    ui->buttonStop->setEnabled(true);


    std::shared_ptr<SalesmanProblem> problem = SalesmanProblem::CreateRandomCities(
            -250, 250,
            -250, 250,
            cities_amount);

    std::shared_ptr<Population> population = Population::CreateRandomPopulation(
            population_size,
            cities_amount,
            dynamic_pointer_cast<OptimizationProblem>(problem),
            mutate_fraction);


    solution_progress = {problem, population, iterations_amount};
}

void MainWindow::UpdateStepLabel() {
    if (solution_progress.IsStarted()) {
        ui->labelCurrentStep->setText(
                "Best score:\n"
                + QString::number(solution_progress.GetPopulation().GetBestScore())
                + "\niter "
                + QString::number(solution_progress.GetCurrentIteration())
                + "/"
                + QString::number(solution_progress.GetFinalIteration()));
    } else {
        ui->labelCurrentStep->setText("Simulation\nnot started");
    }
}

void MainWindow::on_buttonSimulate_clicked()
{
    int cities_amount;
    int population_size;
    double mutate_fraction;
    int iterations_amount;
    try {
        cities_amount = std::stoi(ui->entryCities->text().toStdString());
        population_size = std::stoi(ui->entryPopulation->text().toStdString());
        mutate_fraction = std::stod(ui->entryMutation->text().toStdString());
        iterations_amount = std::stoi(ui->entrySteps->text().toStdString());
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        return;
    }

    StartSimulation(cities_amount, population_size, mutate_fraction, iterations_amount);

    RedrawPath();
    UpdateStepLabel();
}


void MainWindow::on_buttonStep_clicked()
{
    try {
        solution_progress.Iterate();
        UpdateStepLabel();

    } catch (std::runtime_error &err) {
        std::cout << err.what() << std::endl;
        return;
    }

    RedrawPath();
}


void MainWindow::on_buttonStepToEnd_clicked()
{
    while (solution_progress.GetCurrentIteration() < solution_progress.GetFinalIteration()) {
        solution_progress.Iterate();
    }
    RedrawPath();
    UpdateStepLabel();
}


void MainWindow::on_buttonStop_clicked()
{
    ui->entryCities->setEnabled(true);
    ui->entryPopulation->setEnabled(true);

    ui->buttonSimulate->setText("Setup simulation");

    ui->buttonStep->setEnabled(false);
    ui->buttonStepToEnd->setEnabled(false);
    ui->buttonStop->setEnabled(false);

    solution_progress = {};
    UpdateStepLabel();
}


void MainWindow::on_entrySteps_editingFinished()
{
    if (!solution_progress.IsStarted()) return;

    try {
        int iterations_amount = std::stoi(ui->entrySteps->text().toStdString());
        solution_progress.SetFinalIteration(iterations_amount);
        UpdateStepLabel();
        
    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }
}


void MainWindow::on_entryMutation_editingFinished()
{
    if (!solution_progress.IsStarted()) return;

    try {
        double mutate_fraction = std::stod(ui->entryMutation->text().toStdString());
        solution_progress.GetPopulation().SetMutationFraction(mutate_fraction);
        UpdateStepLabel();

    } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }
}

