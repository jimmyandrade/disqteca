#include "disqteca.h"
#include "ui_disqteca.h"

disqteca::disqteca(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::disqteca)
{
    ui->setupUi(this);
}

disqteca::~disqteca()
{
    delete ui;
}
