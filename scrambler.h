#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include <QString>
#include <QChar>
#include <stdexcept>
#include "gmpxx.h"

class Scrambler
{
public:

	enum Algoritm
	{
		Invalid,
		SingleReshuffle,
		SingleWithKey,
		DoubleReshuffle,
		Caesar,
		Gronsfeld,
		ManyAlphabet,
		GammaCypher,
		ElGamalCypher,
		Rsa
	};


	static const QChar alphabet[];
	static const int alphSize;

//методы
	//шифры перестановок, не реализую Магические квадраты
	//одиночная перестановка
	static QString EncryptSingleReshuffle (QString str, int tableLenth);
	static QString DecryptSingleReshuffle (QString str, int tableLenth);

	//одиночная перестановка с ключом
	static QString EncryptSingleReshuffleWithKey (QString str, QString key);
	static QString DecryptSingleReshuffleWithKey (QString str, QString key);

	//двойная перестановка
	static QString EncryptDoubleReshuffle (QString str, int _wkey, int _lkey);
	static QString DecryptDoubleReshuffle (QString str, int _wkey, int _lkey);




	//шифр простой замены, не реализую Полибианский квадрат
	//шифр Цезаря
	static QString EncryptCaesar (QString str, int shift);
	static QString DecryptCaesar (QString str, int shift);


	//шифры сложной замены
	//шифр Гронсвельда
	static QString EncryptGronsfeld (QString str, int key);
	static QString DecryptGronsfeld (QString str, int key);

	//многоалфавитная замена
	static QString EncryptManyAlphabet (QString str, QString key);
	static QString DecryptManyAlphabet (QString str, QString key);

	//гаммирование
	class Gamma
	{
	public:
		int gammaSize;
		int* gamma;

		Gamma();
		Gamma(Gamma& unused)
		{
			throw std::runtime_error("should not be called");
		}
		~Gamma();

		static QString EncryptGamma(QString str, Gamma& key);
		static QString DecryptGamma(QString str, Gamma& key);
	};

	//ассиметричные шифры
	//Эль Гамаля пока не работает
	class ElGamal
	{
	public:
		class Exception{};

		mpz_class secretKeyX;

		class openKey
		{
		public:
			mpz_class moduleP;
			mpz_class baseG;
			mpz_class baseY;

			openKey(){};
			openKey(QString _P, QString _G, QString _X)
			{
				mpz_class X;
				X = _X.toStdString();

				moduleP = _P.toStdString();
				baseG = _G.toStdString();

				if ((moduleP <= baseG) || (moduleP <= X))
					throw Exception();

				mpz_class tmp;
				tmp = IntPow(baseG, X);

				baseY = tmp % moduleP;
			}

			QString toQString()
			{
				QString result = "";

				result = moduleP.get_str().c_str() + ' ';
				result += baseG.get_str().c_str()+ ' ';
				result += baseY.get_str().c_str();

				return result;
			}
		};

		openKey ok;

		ElGamal(QString _P, QString _G, QString _X);

		QString getSecretKeyStr()
		{
			QString result = secretKeyX.get_str().c_str();
			return result;
		}

		static QString EncryptElGamal (QString str, openKey key);
		static QString DecryptElGamal (QString str, openKey key, QString _secretKey);

	protected:
		static mpz_class IntPow(mpz_class one, mpz_class two);
	};

	//RSA тоже пока не работает
	class RSA
	{
	public:
		struct openKey
		{
			mpz_class d;
			mpz_class N;
		} ok;

		struct closedKey
		{
			mpz_class e;
			mpz_class M;
		} ck;

		RSA(QString _p, QString _q);

		static QString EncryptRSA();
		static QString DecryptRSA();
//		1.	Получатель выбирает 2 больших простых целых числа p и q,
//		на основе которых вычисляет N=pq; M=(p-1)(q-1).
//		2.	Получатель выбирает целое случайное число d, которое является взаимопростым
//			со значением М, и вычисляет значение е из условия ed=1(mod M).
//		3.	d и N публикуются как открытый ключ, е и М являются закрытым ключом.
//		4.	Если S –сообщение и его длина: 1<Len(S)<N, то зашифровать этот текст можно
//			как S’=Sd(mod N), то есть шифруется открытым ключом.
//		5.	Получатель расшифровывает с помощью закрытого ключа: S=S’e(mod N).

	};

protected:
	static int GetNum(QChar one);
	static int Module (int one, int base);
};

#endif // SCRAMBLER_H
