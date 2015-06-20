#ifndef MAGAZYNIERWINDOW_H
#define MAGAZYNIERWINDOW_H

#include <QMainWindow>

namespace Ui {
class MagazynierWindow;
}

class MagazynierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MagazynierWindow(QWidget *parent = 0);
    ~MagazynierWindow();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MagazynierWindow *ui;
};

#endif // MAGAZYNIERWINDOW_H
