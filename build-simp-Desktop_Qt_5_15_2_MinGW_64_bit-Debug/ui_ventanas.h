/********************************************************************************
** Form generated from reading UI file 'ventanas.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANAS_H
#define UI_VENTANAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ventanas
{
public:
    QWidget *centralwidget;
    QWidget *Game_window;
    QGraphicsView *graphicsView;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ventanas)
    {
        if (ventanas->objectName().isEmpty())
            ventanas->setObjectName(QString::fromUtf8("ventanas"));
        ventanas->resize(800, 600);
        centralwidget = new QWidget(ventanas);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Game_window = new QWidget(centralwidget);
        Game_window->setObjectName(QString::fromUtf8("Game_window"));
        Game_window->setGeometry(QRect(19, 49, 451, 351));
        graphicsView = new QGraphicsView(Game_window);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 110, 256, 192));
        label = new QLabel(Game_window);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 49, 16));
        label_2 = new QLabel(Game_window);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 60, 49, 16));
        label_3 = new QLabel(Game_window);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(200, 60, 49, 16));
        ventanas->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ventanas);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ventanas->setMenuBar(menubar);
        statusbar = new QStatusBar(ventanas);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ventanas->setStatusBar(statusbar);

        retranslateUi(ventanas);

        QMetaObject::connectSlotsByName(ventanas);
    } // setupUi

    void retranslateUi(QMainWindow *ventanas)
    {
        ventanas->setWindowTitle(QCoreApplication::translate("ventanas", "ventanas", nullptr));
        label->setText(QCoreApplication::translate("ventanas", "vidas:", nullptr));
        label_2->setText(QCoreApplication::translate("ventanas", "puntos: ", nullptr));
        label_3->setText(QCoreApplication::translate("ventanas", "nivel:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ventanas: public Ui_ventanas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANAS_H
