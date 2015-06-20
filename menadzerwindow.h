#ifndef MENADZERWINDOW_H
#define MENADZERWINDOW_H

#include <QMainWindow>

namespace Ui {
class MenadzerWindow;
}

class MenadzerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenadzerWindow(QWidget *parent = 0);
    ~MenadzerWindow();

private:
    Ui::MenadzerWindow *ui;
};

#endif // MENADZERWINDOW_H
