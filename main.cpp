#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "scrambler.h"
#include <iostream>
#include "gmpxx.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	QString str("abcsdf qawde  fgh");
	qDebug() << "Originl = "  << str;

	Scrambler::RSA rr("47", "31");

	str = Scrambler::RSA::EncryptRSA(str, rr.ok);
	qDebug() << "Encrypt = "  << str;

	qDebug() << "Decrypt = " << Scrambler::RSA::DecryptRSA(str, rr.ck);
	return a.exec();
}
