/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelInstruction;
    QLineEdit *lineEditInput;
    QPushButton *pushButtonGuess;
    QPushButton *pushButtonReset;
    QLabel *labelFeedback;
    QListView *listViewHistory;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 300);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        labelInstruction = new QLabel(centralwidget);
        labelInstruction->setObjectName("labelInstruction");
        labelInstruction->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelInstruction);

        lineEditInput = new QLineEdit(centralwidget);
        lineEditInput->setObjectName("lineEditInput");

        verticalLayout->addWidget(lineEditInput);

        pushButtonGuess = new QPushButton(centralwidget);
        pushButtonGuess->setObjectName("pushButtonGuess");

        verticalLayout->addWidget(pushButtonGuess);

        pushButtonReset = new QPushButton(centralwidget);
        pushButtonReset->setObjectName("pushButtonReset");

        verticalLayout->addWidget(pushButtonReset);

        labelFeedback = new QLabel(centralwidget);
        labelFeedback->setObjectName("labelFeedback");
        labelFeedback->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelFeedback);

        listViewHistory = new QListView(centralwidget);
        listViewHistory->setObjectName("listViewHistory");

        verticalLayout->addWidget(listViewHistory);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\230\320\263\321\200\320\260: \320\243\320\263\320\260\320\264\320\260\320\271 \321\207\320\270\321\201\320\273\320\276", nullptr));
        labelInstruction->setText(QCoreApplication::translate("MainWindow", "\320\243\320\263\320\260\320\264\320\260\320\271\321\202\320\265 \321\207\320\270\321\201\320\273\320\276 \320\276\321\202 1 \320\264\320\276 100:", nullptr));
        pushButtonGuess->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214 \320\270\320\263\321\200\321\203", nullptr));
        labelFeedback->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
