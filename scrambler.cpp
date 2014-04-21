#include "scrambler.h"
#include <math.h>
#include <QDebug>


const QChar Scrambler::alphabet[] = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u',
	'v', 'w', 'x', 'y', 'z', ' '};

const int Scrambler::alphSize = sizeof(Scrambler::alphabet) / sizeof(Scrambler::alphabet[0]);



int Scrambler::GetNum(QChar one)
{
	for (int i = 0; i < alphSize; i++)
		if (one == alphabet[i])
			return i;

	return 0;
}



QString Scrambler::EncryptSingleReshuffle (QString str, int tableLenth)
{
	while ((str.length() % tableLenth) != 0)
		str = str + ' ';

	int bunch = str.length() / tableLenth;

	QString res = "";

	for (int i = 0; i < bunch; i++)
	{
		for (int j = 0; j < str.length(); j += bunch)
			if ((i + j) < str.length())
				res = res + str.at(i+j);
			res += " ";
	}

	return res;
}

QString Scrambler::DecryptSingleReshuffle (QString str, int tableLenth)
{
	QString res = "";

	int bunch = str.length() / (tableLenth + 1);

	for (int i = 0; i < tableLenth; i++)
	{
		for (int j = 0; j < bunch; j++)
			res = res + str.at(((tableLenth + 1) * j) + i);
	}

	return res;
}





QString Scrambler::EncryptSingleReshuffleWithKey (QString str, QString key)
{
	while ((str.length() % key.length()) != 0)
		str = str + " ";

	int bunch = str.length() / key.length();

	int size = key.length();

	QString res = "";
	res = EncryptSingleReshuffle(str, size);
	QString tmp = res;

	int sortArr[size];

	for (int i = 0; i < size; i++)
		sortArr[i] = GetNum(key[i]);

	for (int i = 0; i < size; i++)
	{
		int num = alphSize;
		int pos = 0;
		for (int j = 0; j < size; j++)
			if (num > sortArr[j])
			{
				num = sortArr[j];
				pos = j;
			}
		sortArr[pos] = alphSize;

		for (int j = 0; j < bunch; j++)
			res[(size + 1) * j + i] = tmp.at((size + 1) * j + pos);
	}

	return res;
}

QString Scrambler::DecryptSingleReshuffleWithKey (QString str, QString key)
{
	while ((str.length() % key.length()) != 0)
		str = str + " ";

	int bunch = str.length() / (key.length() + 1);

	int size = key.length();

	QString res = str;
	QString tmp = str;

	int sortArr[size];

	for (int i = 0; i < size; i++)
		sortArr[i] = GetNum(key[i]);

	for (int i = 0; i < size; i++)
	{
		int num = alphSize;
		int pos = 0;
		for (int j = 0; j < size; j++)
			if (num > sortArr[j])
			{
				num = sortArr[j];
				pos = j;
			}
		sortArr[pos] = alphSize;

		for (int j = 0; j < bunch; j++)
			res[(size + 1) * j + pos] = tmp.at((size + 1) * j + i);
	}

	res = DecryptSingleReshuffle(res, size);
	return res;
}




QString Scrambler::EncryptDoubleReshuffle (QString str, int _wkey, int _lkey)
{
	int widht = 1;
	int length = 1;

	int k = 1;
	while ((_wkey / k) >= 10)
	{
		k *= 10;
		widht++;
	}

	k = 1;
	while ((_lkey / k) >= 10)
	{
		k *= 10;
		length++;
	}

	if ((widht * length) < str.length())
		return "";

	while ((widht * length) % str.length() != 0)
		str = str + ' ';

	int wkey[widht];
	for (int i = widht - 1; i >= 0; i--)
	{
		wkey[i] = _wkey % 10;
		_wkey = _wkey / 10;
	}

	int lkey[length];
	for (int i = length - 1; i >= 0; i--)
	{
		lkey[i] = _lkey % 10;
		_lkey = _lkey / 10;
	}


	QString tmp = str;
	QString res = tmp;

	for (int i = 0; i < length; i++)
	{
		int num = 10;
		int pos = 0;
		for (int j = 0; j < length; j++)
			if (num > lkey[j])
			{
				num = lkey[j];
				pos = j;
			}
		lkey[pos] = 10;

		for (int j = 0; j < widht; j++)
			tmp[(length * j) + i] = str.at((length * j) + pos);
	}

	for (int i = 0; i < widht; i++)
	{
		int num = 10;
		int pos = 0;
		for (int j = 0; j < widht; j++)
			if (num > wkey[j])
			{
				num = wkey[j];
				pos = j;
			}
		wkey[pos] = 10;

		for (int j = 0; j < length; j++)
			res[(length * i) + j] = tmp.at((length * pos) + j);
	}

	return res;
}

QString Scrambler::DecryptDoubleReshuffle (QString str, int _wkey, int _lkey)
{
	if (str.length() == 0)
		return "";

	int widht = 1;
	int length = 1;

	int k = 1;
	while ((_wkey / k) >= 10)
	{
		k *= 10;
		widht++;
	}

	k = 1;
	while ((_lkey / k) >= 10)
	{
		k *= 10;
		length++;
	}

	while ((widht * length) % str.length() != 0)
		str = str + ' ';

	int wkey[widht];
	for (int i = widht - 1; i >= 0; i--)
	{
		wkey[i] = _wkey % 10;
		_wkey = _wkey / 10;
	}

	int lkey[length];
	for (int i = length - 1; i >= 0; i--)
	{
		lkey[i] = _lkey % 10;
		_lkey = _lkey / 10;
	}


	QString tmp = str;
	QString res = tmp;

	for (int i = 0; i < widht; i++)
	{
		int num = 10;
		int pos = 0;
		for (int j = 0; j < widht; j++)
			if (num > wkey[j])
			{
				num = wkey[j];
				pos = j;
			}
		wkey[pos] = 10;

		for (int j = 0; j < length; j++)
			tmp[(length * pos) + j] = str.at((length * i) + j);
	}

	for (int i = 0; i < length; i++)
	{
		int num = 10;
		int pos = 0;
		for (int j = 0; j < length; j++)
			if (num > lkey[j])
			{
				num = lkey[j];
				pos = j;
			}
		lkey[pos] = 10;

		for (int j = 0; j < widht; j++)
			res[(length * j) + pos] = tmp.at((length * j) + i);
	}

	return res;
}





int Scrambler::Module(int one, int base)
{
	while (one < 0)
		one += base;

	return one % base;
}


QString Scrambler::EncryptCaesar(QString str, int shift)
{
	QString res = "";

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module(GetNum(str.at(i)) + shift, alphSize)];
	}

	return res;
}

QString Scrambler::DecryptCaesar(QString str, int shift)
{
	QString res = "";

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module(GetNum(str.at(i)) - shift, alphSize)];
	}

	return res;
}



QString Scrambler::EncryptGronsfeld(QString str, int _key)
{
	int size = 1;

	int k = 1;
	while ((_key / k) >= 10)
	{
		k *= 10;
		size++;
	}

	qDebug() << " dfg " << size;
	int key[size];
	for (int i = size - 1; i >= 0; i--)
	{
		key[i] = _key % 10;
		_key = _key / 10;
	}

	QString res = "";

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module(GetNum(str.at(i)) + key[i % size], alphSize)];
	}

	return res;
}

QString Scrambler::DecryptGronsfeld(QString str, int _key)
{
	int size = 1;

	int k = 1;
	while ((_key / k) >= 10)
	{
		k *= 10;
		size++;
	}

	int key[size];
	for (int i = size - 1; i >= 0; i--)
	{
		key[i] = _key % 10;
		_key = _key / 10;
	}

	QString res = "";

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module(GetNum(str.at(i)) - key[i % size], alphSize)];
	}

	return res;
}



QString Scrambler::EncryptManyAlphabet(QString str, QString key)
{
	QString res = "";
	int size = key.length();
	int sortArr[size];

	for (int i = 0; i < size; i++)
		sortArr[i] = GetNum(key[i]);

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module((GetNum(str.at(i)) + sortArr[i % size]), alphSize)];
	}

	return res;
}

QString Scrambler::DecryptManyAlphabet(QString str, QString key)
{
	QString res = "";
	int size = key.length();
	int sortArr[size];

	for (int i = 0; i < size; i++)
		sortArr[i] = GetNum(key[i]);

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module((GetNum(str.at(i)) - sortArr[i % size]), alphSize)];
	}

	return res;
}



Scrambler::Gamma::Gamma ()
{
	gammaSize = 64 / sizeof(alphabet[0]);
	gamma = new int[gammaSize];

	for (int i = 0; i < gammaSize; i++)
		gamma[i] = qrand();
}

Scrambler::Gamma::~Gamma ()
{
	delete gamma;
}

QString Scrambler::Gamma::EncryptGamma(QString str, Gamma& key)
{
	QString res = "";

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module((GetNum(str.at(i)) + key.gamma[i % key.gammaSize]), alphSize)];
	}

	return res;
}

QString Scrambler::Gamma::DecryptGamma(QString str, Gamma& key)
{
	QString res = "";

	for (int i = 0; i < str.length(); i++)
	{
		res = res + alphabet[Module((GetNum(str.at(i)) - key.gamma[i % key.gammaSize]), alphSize)];

	}

	return res;
}


bool Scrambler::isSimple(mpz_class one)
{
	for (int i = 2; i < one; i++)
	{
		if ((one % i) == 0)
			return false;
	}
	return true;
}


mpz_class Scrambler::IntPow(mpz_class one, mpz_class two)
{
	mpz_class res("1");

	while (two != 0)
	{
		res *= one;
		two--;
	}

	return res;
}



Scrambler::ElGamal::ElGamal(QString _P, QString _G, QString _X)
{
	mpz_class moduleP;
	moduleP = _P.toStdString();

	if (!isSimple(moduleP))
		throw Exception();

	mpz_class baseG;
	baseG = _G.toStdString();
	secretKeyX = _X.toStdString();

	if ((moduleP <= baseG) || (moduleP <= secretKeyX))
		throw Exception();

	mpz_class tmp;
	tmp = IntPow(baseG, secretKeyX);

	mpz_class baseY;
	baseY = tmp % moduleP;
	QString _Y = baseY.get_str().c_str();

	openKey tmpok(_P, _G, _Y);
	ok = tmpok;
}

QString Scrambler::ElGamal::EncryptElGamal(QString str, openKey key)
{
	QString result = "";

	gmp_randclass rand(gmp_randinit_default);
	mpz_class sessionKeyK;
	sessionKeyK = rand.get_z_range(key.moduleP - 1);
	sessionKeyK = sessionKeyK + 1;

	while ((sessionKeyK <= 0) || (sessionKeyK >= key.moduleP))
		sessionKeyK = qrand();

	for (int i = 0; i < str.length(); i++)
	{
		int num = GetNum(str.at(i));

		mpz_class a = (IntPow(key.baseG, sessionKeyK) % key.moduleP);
		long int aa = a.get_ui();
		result.append(reinterpret_cast<QChar*>(&aa), sizeof(aa)/sizeof(QChar));

		mpz_class b = ((IntPow(key.baseY, sessionKeyK) * num) % key.moduleP);
		long int bb = b.get_ui();
		result.append(reinterpret_cast<QChar*>(&bb), sizeof(bb)/sizeof(QChar));
	}
	return result;
}

QString Scrambler::ElGamal::DecryptElGamal(QString str, openKey key, QString _secretKey)
{
	QString result = "";

	mpz_class secretKey;
	secretKey = _secretKey.toStdString();

	int lisize = sizeof(long int) / sizeof(QChar);
	int df = lisize * 2;

for (int i = 0; i < str.length(); i += df)
	{
		QChar aarr[lisize];
		for (int j = 0; j < lisize; j++)
			aarr[j] = str.at(i + j);
		long int a = *(reinterpret_cast<long int*>(aarr));

		QChar barr[lisize];
		for (int j = 0; j < lisize; j++)
			barr[j] = str.at(i + lisize + j);
		long int b = *(reinterpret_cast<long int*>(barr));

		mpz_class tmp;
		tmp = a;
		mpz_class My = ((IntPow(tmp, (key.moduleP - 1 - secretKey)) * b) % key.moduleP);
		long int M = My.get_si();
		result += alphabet[M];
	}
	return result;
}



mpz_class Scrambler::RSA::checkNOD(mpz_class max, mpz_class min)
{
	mpz_class tmp;
	while (max != min)
	{
		tmp = max - min;
		if (min > tmp)
		{
			max = min;
			min = tmp;
		}
		else
			max = tmp;
	}
	return max;
}

Scrambler::RSA::RSA(QString _p, QString _q)
{
	mpz_class p;
	p = _p.toStdString();

	mpz_class q;
	q = _q.toStdString();

	if ((p < 0) || (q < 0))
		throw Exception();

	if ((!isSimple(p)) || (!isSimple(q)))
		throw Exception();

	mpz_class N;
	N = p * q;

	mpz_class fN;
	fN = (p - 1) * (q - 1);

	gmp_randclass rand(gmp_randinit_default);
	mpz_class e;
	while (true)
	{
		e = rand.get_z_range(fN - 1);
		e = e + 1;
		if (checkNOD(fN, e) == 1)
			break;
	}

	QString publicE = e.get_str().c_str();
	QString moduleN = N.get_str().c_str();
	openKey tmpok(publicE, moduleN);
	ok = tmpok;

	mpz_class tmp(fN + 1);
	mpz_class d;
	while (true)
	{
		if ((tmp % e) == 0)
		{
			d = tmp / e;
			break;
		}
		tmp += fN;
	}

	QString secretD = d.get_str().c_str();
	closedKey tmpck(secretD, moduleN);
	ck = tmpck;
}

//		1.	Получатель выбирает 2 больших простых целых числа p и q,
//		на основе которых вычисляет N=pq; M=(p-1)(q-1).
//		2.	Получатель выбирает целое случайное число d, которое является взаимопростым
//			со значением М, и вычисляет значение е из условия ed=1(mod M).
//		3.	e и N публикуются как открытый ключ, d и N являются закрытым ключом.
//		4.	Если S –сообщение и его длина: 1<Len(S)<N, то зашифровать этот текст можно
//			как S’=S^e(mod N), то есть шифруется открытым ключом.
//		5.	Получатель расшифровывает с помощью закрытого ключа: S=S’^d(mod N).

QString Scrambler::RSA::EncryptRSA(QString str, openKey key)
{
	QString result = "";

	for (int i = 0; i < str.length(); i++)
	{
		int num = GetNum(str.at(i));

		mpz_class a = (IntPow(num, key.publicE) % key.moduleN);
		long int aa = a.get_ui();
		result.append(reinterpret_cast<QChar*>(&aa), sizeof(aa)/sizeof(QChar));
	}
	return result;
}

QString Scrambler::RSA::DecryptRSA(QString str, closedKey key)
{
	QString result = "";

	int lisize = sizeof(long int) / sizeof(QChar);

for (int i = 0; i < str.length(); i += lisize)
	{
		QChar aarr[lisize];
		for (int j = 0; j < lisize; j++)
			aarr[j] = str.at(i + j);
		long int a = *(reinterpret_cast<long int*>(aarr));

		mpz_class tmp;
		tmp = a;
		mpz_class My = ((IntPow(a, key.secretD)) % key.moduleN);
		long int M = My.get_si();
		result += alphabet[M];
	}
	return result;
}

