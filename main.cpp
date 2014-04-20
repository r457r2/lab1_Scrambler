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

	QString str("abcdiefg");
	qDebug() << "Originl = "  << str;

	int key1 = 21;
	int key2 = 1243;

	str = Scrambler::EncryptDoubleReshuffle(str, key1, key2);
	qDebug() << "Encrypt = "  << str;

	qDebug() << "Decrypt = " << Scrambler::DecryptDoubleReshuffle(str, key1, key2);
	return a.exec();
}
