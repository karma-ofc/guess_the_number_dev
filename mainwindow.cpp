#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStyleFactory>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QTranslator>
#include <QFile>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStringListModel(this))
    , attemptCount(0)  // Счётчик попыток
{
    ui->setupUi(this);
    ui->listViewHistory->setModel(model);
    // Кнопка смены темы
    connect(ui->pushButtonToggleTheme, &QPushButton::clicked, this, [=]() {
        setDarkTheme(!isDarkTheme);
        ui->pushButtonStartGame->setStyleSheet("");
        ui->pushButtonStartGame->setFixedSize(500, 40);
    });

    // Кнопка переключения языка (только в главном меню)
    connect(ui->pushButtonToggleLanguage, &QPushButton::clicked, this, [=]() {
        isEnglish = !isEnglish;
        switchLanguage(isEnglish);
    });

    setDarkTheme(true);

    // Скрываем игровые элементы до старта
    ui->pushButtonGuess->setVisible(false);
    ui->pushButtonReset->setVisible(false);
    ui->lineEditInput->setVisible(false);
    ui->labelInstruction->setVisible(false);
    ui->labelFeedback->setVisible(false);
    ui->labelDivisibility->setVisible(false);
    ui->listViewHistory->setVisible(false);
    // Подключаем базу данных
    initDatabase();
}

MainWindow::~MainWindow()
{
    if (db.isOpen())
        db.close();
    delete ui;
}

// 📌 Инициализация базы данных SQLite
void MainWindow::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("records.db");

    if (!db.open()) {
        qDebug() << "Ошибка открытия базы данных:" << db.lastError().text();
        return;
    }

    // Создаём таблицу `records`, если она ещё не существует
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS records ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "playerName TEXT, "
               "attempts INTEGER)");
}

// 📌 Запуск новой игры
void MainWindow::on_pushButtonStartGame_clicked()
{
    bool okMin, okMax;
    int min = ui->lineEditMin->text().toInt(&okMin);
    int max = ui->lineEditMax->text().toInt(&okMax);

    if (!okMin || !okMax || min >= max) {
        QMessageBox::warning(this, tr("Некорректный диапазон"),
                             tr("Введите два разных числа, где первое меньше второго."));
        return;
    }

    minValue = min;
    maxValue = max;
    attemptCount = 0;  // Сбрасываем количество попыток

    // Скрываем ненужные элементы
    ui->lineEditMin->setVisible(false);
    ui->lineEditMax->setVisible(false);
    ui->labelMin->setVisible(false);
    ui->labelMax->setVisible(false);
    ui->pushButtonStartGame->setVisible(false);
    ui->pushButtonToggleTheme->setVisible(false);
    ui->pushButtonToggleLanguage->setVisible(false); // Скрываем язык в игровом режиме
    ui->pushButtonShowRecords->setVisible(false);
    ui->pushButtonResetRecords->setVisible(false);
    // Показываем игровые элементы
    ui->pushButtonGuess->setVisible(true);
    ui->pushButtonReset->setVisible(true);
    ui->lineEditInput->setVisible(true);
    ui->labelInstruction->setVisible(true);
    ui->labelFeedback->setVisible(true);
    ui->labelDivisibility->setVisible(true);
    ui->listViewHistory->setVisible(true);

    startNewGame();
}

void MainWindow::startNewGame()
{
    targetNumber = QRandomGenerator::global()->bounded(minValue, maxValue + 1);
    guessHistory.clear();
    updateHistory();
    ui->labelFeedback->setText(tr("Введите вашу первую догадку"));
    ui->labelDivisibility->clear();
    ui->lineEditInput->clear();
    ui->lineEditInput->setFocus();
}

void MainWindow::updateHistory()
{
    model->setStringList(guessHistory);
}

void MainWindow::on_pushButtonGuess_clicked()
{
    bool ok;
    int guess = ui->lineEditInput->text().toInt(&ok);
    attemptCount++;  // Увеличиваем счётчик попыток

    if (!ok || guess < minValue || guess > maxValue) {
        QMessageBox::warning(this, tr("Ошибка ввода"),
                             tr("Введите целое число от %1 до %2")
                                 .arg(minValue).arg(maxValue));
        return;
    }

    guessHistory.append(tr("Попытка: %1").arg(guess));
    updateHistory();

    if (guess < targetNumber) {
        ui->labelFeedback->setText(tr("Загаданное число больше"));
    } else if (guess > targetNumber) {
        ui->labelFeedback->setText(tr("Загаданное число меньше"));
    } else {
        // 🏆 Игра окончена – записываем рекорд
        insertRecord("Player", attemptCount);
        ui->labelFeedback->setText(tr("🎉 Вы угадали число за %1 попыток!").arg(attemptCount));
        ui->labelDivisibility->setText(tr("Игра завершена"));
    }

    ui->lineEditInput->clear();
}

void MainWindow::resetToStartMenu()
{
    // Скрываем игровые элементы
    QList<QWidget*> gameWidgets = {
        ui->pushButtonGuess, ui->pushButtonReset, ui->lineEditInput,
        ui->labelInstruction, ui->labelFeedback, ui->labelDivisibility,
        ui->listViewHistory
    };

    for (auto widget : gameWidgets) {
        widget->setVisible(false);
    }

    // Показываем стартовые элементы
    QList<QWidget*> startWidgets = {
        ui->lineEditMin, ui->lineEditMax, ui->labelMin,
        ui->labelMax, ui->pushButtonStartGame
    };

    for (auto widget : startWidgets) {
        widget->setVisible(true);
    }

    ui->pushButtonToggleTheme->setVisible(true);
    ui->pushButtonToggleLanguage->setVisible(true);
    ui->pushButtonShowRecords->setVisible(true);
    ui->lineEditMin->clear();
    ui->lineEditMax->clear();
}

// 📌 Добавление записи в БД
void MainWindow::insertRecord(const QString &playerName, int attempts)
{
    QSqlQuery query;
    query.prepare("INSERT INTO records (playerName, attempts) VALUES (?, ?)");
    query.addBindValue(playerName);
    query.addBindValue(attempts);

    if (!query.exec()) {
        qDebug() << "Ошибка записи в БД:" << query.lastError().text();
    }
}

// 📌 Отображение лучших результатов
void MainWindow::showRecords()
{
    QSqlQuery query("SELECT playerName, attempts FROM records ORDER BY attempts ASC LIMIT 10");
    QString recordText = tr("Топ рекордов:\n");

    while (query.next()) {
        recordText += query.value(0).toString() + ": " + QString::number(query.value(1).toInt()) + "\n";
    }

    QMessageBox::information(this, tr("Рекорды"), recordText);
}
void MainWindow::setDarkTheme(bool enabled)
{
    isDarkTheme = enabled;
    QPalette palette;
    if (enabled) {
        // Тёмная тема
        palette.setColor(QPalette::Window, QColor(35, 35, 35));
        palette.setColor(QPalette::WindowText, QColor(220, 220, 220));
        palette.setColor(QPalette::Base, QColor(42, 42, 42));
        palette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
        palette.setColor(QPalette::Button, QColor(53, 53, 53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::black);
    } else {
        // Светлая тема (чисто белый фон)
        palette.setColor(QPalette::Window, QColor("#FFFFFF"));  // Белый фон
        palette.setColor(QPalette::WindowText, QColor("#000000"));  // Чёрный текст
        palette.setColor(QPalette::Base, QColor("#FFFFFF"));  // Поля ввода - белые
        palette.setColor(QPalette::AlternateBase, QColor("#F0F0F0"));
        palette.setColor(QPalette::Button, QColor("#E6E6E6"));
        palette.setColor(QPalette::ButtonText, QColor("#000000"));
        palette.setColor(QPalette::Highlight, QColor("#007ACC"));
        palette.setColor(QPalette::HighlightedText, QColor("#FFFFFF"));
    }
    qApp->setPalette(palette);
}

void MainWindow::switchLanguage(bool toEnglish)
{
    qApp->removeTranslator(&translator);
    if (toEnglish) {
        QString translationFile = QCoreApplication::applicationDirPath() + "/translations/app_en.qm";
        if (translator.load(translationFile))
            qApp->installTranslator(&translator);
    }
    ui->retranslateUi(this);
    this->update();
    qApp->processEvents();
}
void MainWindow::on_pushButtonReset_clicked()
{
    resetToStartMenu();
}
void MainWindow::on_pushButtonShowRecords_clicked()
{
    showRecords();
}
void MainWindow::on_pushButtonResetRecords_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Сброс рекордов"),
                                  tr("Вы уверены, что хотите удалить все рекорды?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        if (!query.exec("DELETE FROM records")) {
            qDebug() << "Ошибка очистки базы данных:" << query.lastError().text();
        } else {
            QMessageBox::information(this, tr("Сброс рекордов"), tr("Все рекорды удалены."));
        }
    }
}
