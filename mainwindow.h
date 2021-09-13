#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Population;

#include <QMainWindow>
#include <src/SalesmanProblem.h>
#include <QGraphicsScene>
#include <src/SalesmanProblemSolutionProgress.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_buttonSimulate_clicked();

    void on_buttonStep_clicked();

    void on_buttonStepToEnd_clicked();

    void on_buttonStop_clicked();

    void on_entrySteps_editingFinished();

    void on_entryMutation_editingFinished();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;
    QBrush blueBrush {Qt::blue};
    QPen bluePen {Qt::blue, 2};
    std::vector<QGraphicsEllipseItem * > ellipses;
    std::vector<QGraphicsLineItem * > lines;

    SalesmanProblemSolutionProgress solution_progress;

    void DrawCitiesCircularPath(const std::vector<Destination> &cities, const std::vector<int> &city_order);

    void DrawCityPoints(const std::vector<Destination> &cities);

    void RedrawPath();

    void UpdateStepLabel();

    void StartSimulation(int cities_amount, int population_size, double mutate_fraction, int iterations_amount);
};
#endif // MAINWINDOW_H
