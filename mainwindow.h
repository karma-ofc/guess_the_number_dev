#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

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
    void on_pushButtonStartGame_clicked();
    void resetToStartMenu();
    void on_pushButtonShowRecords_clicked();
    void on_pushButtonResetRecords_clicked();
    // Другие методы, если нужны

private:
    Ui::MainWindow *ui;
    int targetNumber;
    int minValue = 1;
    int maxValue = 100;
    QStringList guessHistory;
    QStringListModel *model;
    bool isDarkTheme = false;
    QTranslator translator;
    bool isEnglish = false;

    // Новые члены для работы с базой данных
    QSqlDatabase db;
    int attemptCount; // количество попыток в текущей игре

    void startNewGame();
    void updateHistory();
    void provideHint(int guess, bool isLower);
    void setDarkTheme(bool enabled);
    void switchLanguage(bool toEnglish);

    // Методы для работы с базой данных рекордов
    void initDatabase();
    void insertRecord(const QString &playerName, int attempts);
    void showRecords();
};

#endif // MAINWINDOW_H
