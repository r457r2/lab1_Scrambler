#include "scrambler.h"


const QChar Scrambler::alphabet[] = {
	'а', 'б', 'в', 'г', 'д', 'е', 'ё',
	'ж', 'з', 'и', 'й', 'к', 'л', 'м',
	'н', 'о', 'п', 'р', 'с', 'т', 'у',
	'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ',
	'ы', 'ь', 'э', 'ю', 'я', ' '};

const int Scrambler::alphSize = sizeof(Scrambler::alphabet) / sizeof(Scrambler::alphabet[0]);



int Scrambler::GetNum(QChar one)
{
	for (int i = 0; i < 34; i++)
		if (one == alphabet[i])
			return i;

	throw Exception();
}

QString Scrambler::SingleReshuffle (QString one, int tableLenth)
{
	QString res = "";

	for (int i = 0; i < tableLenth; i++)
	{
		for (int j = 0; j < one.length(); j += tableLenth)
			if ((i + j) < one.length())
				res = res + one.at(i+j);
		res = res + ' ';
	}

	return res;
}

QString Scrambler::SingleReshuffleWithKey (QString one, QString key)
{
	QString res = "";
	int size = key.length();
	int sortArr[size];

	for (int i = 0; i < size; i++)
		sortArr[i] = GetNum(key[i]);

	for (int i = 0; i < size; i++)
	{
		int num = 35;
		int pos = 0;
		for (int i = 0; i < size; i++)
			if (num > sortArr[i])
			{
				num = sortArr[i];
				pos = i;
			}
		sortArr[pos] = 35;

		for (int j = 0; j < one.length(); j += size)
			if ((j + pos) < one.length())
				res = res + one.at(j + pos);
		res = res + ' ';
	}

	return res;
}

QString Scrambler::DoubleReshuffle (QString one, int widht, int length, int _wkey, int _lkey)
{
	if ((widht * length) < one.length())
		throw Exception();

	int wkey[widht];
	for (int i = widht - 1; i >= 0; i--)
	{
		wkey[i] = _wkey % 10;
		_wkey = _wkey / 10;
	}

	if (((_wkey % 10) != 0) || ((_wkey / 10) != 0))
		throw Exception();


	int lkey[length];
	for (int i = length - 1; i >= 0; i--)
	{
		lkey[i] = _lkey % 10;
		_lkey = _lkey / 10;
	}

	if (((_lkey % 10) != 0) || ((_lkey / 10) != 0))
		throw Exception();

	for (int i = 0; i < widht; i++)
		if ((wkey[i] >= widht) || (wkey[i] = 0))
			throw Exception();

	for (int i = 0; i < length; i++)
		if ((lkey[i] >= length) || (lkey[i] = 0))
			throw Exception();

	QString tmp = "";
	QString res = "";

	for (int i = 0; i < widht; i++)
	{
		int num = widht;
		int pos = 0;
		for (int i = 0; i < widht; i++)
			if (num > wkey[i])
			{
				num = wkey[i];
				pos = i;
			}
		wkey[pos] = widht;

		for (int j = 0; j < one.length(); j += widht)
			if ((j + pos) < one.length())
				tmp = tmp + one.at(j + pos);
	}

	for (int i = 0; i < length; i++)
	{
		int num = length;
		int pos = 0;
		for (int i = 0; i < length; i++)
			if (num > lkey[i])
			{
				num = lkey[i];
				pos = i;
			}
		lkey[pos] = length;

		for (int j = 0; j < tmp.length(); j += length)
			if ((j + pos) < tmp.length())
				res = res + tmp.at(j + pos);
		res = res + ' ';
	}

	return res;
}
