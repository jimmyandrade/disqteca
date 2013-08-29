/********************************************************************************
** Form generated from reading UI file 'disqteca.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISQTECA_H
#define UI_DISQTECA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_disqteca
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *disqteca)
    {
        if (disqteca->objectName().isEmpty())
            disqteca->setObjectName(QString::fromUtf8("disqteca"));
        disqteca->resize(431, 480);
        disqteca->setMinimumSize(QSize(320, 480));
        disqteca->setMaximumSize(QSize(1024, 768));
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica-Light"));
        font.setPointSize(11);
        disqteca->setFont(font);
        disqteca->setStyleSheet(QString::fromUtf8("* {\n"
"background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(255, 147, 0), stop: 1 rgb(242, 44, 103));\n"
"}"));
        centralwidget = new QWidget(disqteca);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        disqteca->setCentralWidget(centralwidget);
        menubar = new QMenuBar(disqteca);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 431, 25));
        menubar->setFont(font);
        disqteca->setMenuBar(menubar);
        statusbar = new QStatusBar(disqteca);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        disqteca->setStatusBar(statusbar);

        retranslateUi(disqteca);

        QMetaObject::connectSlotsByName(disqteca);
    } // setupUi

    void retranslateUi(QMainWindow *disqteca)
    {
        disqteca->setWindowTitle(QApplication::translate("disqteca", "MainWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class disqteca: public Ui_disqteca {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISQTECA_H
