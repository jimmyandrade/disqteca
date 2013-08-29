#ifndef DISQTECA_H
#define DISQTECA_H

#include <QMainWindow>

namespace Ui {
class disqteca;
}

class disqteca : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit disqteca(QWidget *parent = 0);
    ~disqteca();
    
private:
    Ui::disqteca *ui;
};

#endif // DISQTECA_H
