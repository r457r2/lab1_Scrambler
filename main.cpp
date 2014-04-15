#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "scrambler.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();


	QString str("aaaaa");
	qDebug() << "Originl = "  << str;

	Scrambler::Gamma one;

	str = Scrambler::Gamma::EncryptGamma(str, one);
	qDebug() << "Encrypt = "  << str;

	qDebug() << "Decrypt = " << Scrambler::Gamma::DecryptGamma(str, one);
	return a.exec();
}
