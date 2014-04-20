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

		struct openKey
		{
			mpz_class moduleP;
			mpz_class baseG;
			mpz_class baseY;
		} ok;

		ElGamal(QString _P, QString _G, QString _X);

		static QString EncryptElGamal (QString str, openKey key);
		static QString DecryptElGamal (QString str, openKey key, mpz_class secretKey);

	protected:
		static mpz_class IntPow(mpz_class one, mpz_class two);
	};

	//RSA тоже пока не работает
	class RSA
	{

	};

protected:
	static int GetNum(QChar one);
	static int Module (int one, int base);
};

#endif // SCRAMBLER_H
