#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonGuess_clicked();
    void on_pushButtonReset_clicked();

private:
    Ui::MainWindow *ui;
    int targetNumber;
    QStringList guessHistory;
    QStringListModel *model;

    void startNewGame();
    void updateHistory();
};

#endif
