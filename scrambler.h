#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include <QString>
#include <QChar>

class Scrambler
{
public:
	static const QChar alphabet[];
	static const int alphSize;
	class Exception{};

	static int GetNum(QChar one);

	//шифры перестановок, не реализую Магические квадраты
	static QString SingleReshuffle (QString one, int tableLenth);
	static QString SingleReshuffleWithKey (QString one, QString key);
	static QString DoubleReshuffle (QString one, int widht, int length, int _wkey, int _lkey);

	//шифр простой замены, не реализую Полибианский квадрат
	static QString Caesar (QString one, int shift);

	//шифры сложной замены
	static QString Gronsfeld (QString one, int key);
	static QString ManyAlphabet (QString one, QString key);
	static QString XOR (QString one);
};

#endif // SCRAMBLER_H
