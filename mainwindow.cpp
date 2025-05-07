#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStringListModel(this))
{
    ui->setupUi(this);
    ui->listViewHistory->setModel(model);
    startNewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame()
{
    targetNumber = QRandomGenerator::global()->bounded(1, 101); // 1 to 100
    guessHistory.clear();
    updateHistory();
    ui->labelFeedback->clear();
    ui->lineEditInput->clear();
}

void MainWindow::updateHistory()
{
    model->setStringList(guessHistory);
}

void MainWindow::on_pushButtonGuess_clicked()
{
    bool ok;
    int guess = ui->lineEditInput->text().toInt(&ok);
    if (!ok || guess < 1 || guess > 100) {
        QMessageBox::warning(this, "Неверный ввод", "Введите число от 1 до 100.");
        return;
    }

    guessHistory.append(QString::number(guess));
    updateHistory();

    if (guess < targetNumber) {
        ui->labelFeedback->setText("Загаданное число больше.");
    } else if (guess > targetNumber) {
        ui->labelFeedback->setText("Загаданное число меньше.");
    } else {
        ui->labelFeedback->setText("Поздравляем! Вы угадали!");
    }

    ui->lineEditInput->clear();
}

void MainWindow::on_pushButtonReset_clicked()
{
    startNewGame();
}
