#pragma once
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
public slots:
    void slotReboot();

signals:

    void has_won(int i);
private:
    QMediaPlaylist *playlist;
    QMediaPlayer *music;
    static int const EXIT_CODE_REBOOT;
    Ui::MainWindow *ui;

};

