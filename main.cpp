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

	QString str("abcdiefg hjklmnop");
	qDebug() << "Originl = "  << str;

	Scrambler::ElGamal one("29", "15", "4");

	str = Scrambler::ElGamal::EncryptElGamal(str, one.ok);
	qDebug() << "Encrypt = "  << str;

	qDebug() << "Decrypt = " << Scrambler::ElGamal::DecryptElGamal(str, one.ok, one.secretKeyX);
	return a.exec();
}
