#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scrambler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private slots:
	void on_pushEncrypt_clicked();
	void on_pushDecrypt_clicked();
	void on_pushAsymmEncrypt_clicked();
	void on_pushAsymmDecrypt_clicked();
	void on_pushGenKey_clicked();

private:
	Ui::MainWindow *ui;
	Scrambler::Algoritm lastUsedAlgo;
	Scrambler::Gamma gamma;

	Scrambler::Algoritm selectedAlgo();
	Scrambler::Algoritm selectedAsymmAlgo();

};

#endif // MAINWINDOW_H
