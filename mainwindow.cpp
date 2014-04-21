#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdexcept>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	lastUsedAlgo = Scrambler::Invalid;

	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushEncrypt_clicked()
{
	if(ui->editSource->text() == ""
			|| ui->editKey->text() == "")
	{
		QMessageBox::critical(this, "Ошибка", "Ключ и исходная строка не должны быть пустыми.", QMessageBox::Ok);
		return;
	}

	switch(selectedAlgo())
	{
		case Scrambler::Caesar:
		{
			bool ok = false;
			int shift = ui->editKey->text().toInt(&ok);
			if(!ok || shift <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен быть положительным целым числом.", QMessageBox::Ok);
				return;
			}
			ui->editEncrypted->setText(Scrambler::EncryptCaesar(ui->editSource->text(), shift));
			lastUsedAlgo = Scrambler::Caesar;
			break;
		}

		case Scrambler::DoubleReshuffle:
		{
			QStringList numbers = ui->editKey->text().split(" ", QString::SkipEmptyParts);
			if(numbers.length() < 2)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен парой положительных целых чисел, разделенных пробелом.", QMessageBox::Ok); // TODO: check if newline needed
				return;
			}
			bool ok_w, ok_l;
			int wkey = numbers.at(0).toInt(&ok_w);
			int lkey = numbers.at(1).toInt(&ok_l);

			if(!ok_l || !ok_w || wkey <= 0 || lkey <=0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен парой положительных целых чисел, разделенных пробелом.", QMessageBox::Ok); // TODO: check if newline needed
				return;
			}
			ui->editEncrypted->setText(Scrambler::EncryptDoubleReshuffle(ui->editSource->text(), wkey, lkey));
			lastUsedAlgo = Scrambler::DoubleReshuffle;
			break;
		}

		case Scrambler::GammaCypher:
		{
			ui->editEncrypted->setText(Scrambler::Gamma::EncryptGamma(ui->editSource->text(), gamma));
			lastUsedAlgo = Scrambler::GammaCypher;
			break;
		}

		case Scrambler::Gronsfeld:
		{
			bool ok  = false;
			int key = ui->editKey->text().toInt(&ok);
			if(!ok || key <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен быть положительным целым числом.", QMessageBox::Ok);
				return;
			}
			ui->editEncrypted->setText(Scrambler::EncryptGronsfeld(ui->editSource->text(), key));
			lastUsedAlgo = Scrambler::Gronsfeld;
			break;
		}

		case Scrambler::ManyAlphabet:
		{
			ui->editEncrypted->setText(Scrambler::EncryptManyAlphabet(ui->editSource->text(), ui->editKey->text()));
			lastUsedAlgo = Scrambler::ManyAlphabet;
			break;
		}

		case Scrambler::SingleReshuffle:
		{
			bool ok = false;
			int key = ui->editKey->text().toInt(&ok);
			if(!ok || key <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен быть положительным целым числом.", QMessageBox::Ok);
				return;
			}
			ui->editEncrypted->setText(Scrambler::EncryptSingleReshuffle(ui->editSource->text(), key));
			lastUsedAlgo = Scrambler::SingleReshuffle;
			break;
		}

		case Scrambler::SingleWithKey:
		{
			ui->editEncrypted->setText(Scrambler::EncryptSingleReshuffleWithKey(ui->editSource->text(), ui->editKey->text()));
			lastUsedAlgo = Scrambler::SingleWithKey;
			break;
		}

		case Scrambler::Invalid: // TODO: review
			QMessageBox::critical(this, "Ошибка", "Алгоритм не был выбран.", QMessageBox::Ok);
			break;

		case Scrambler::ElGamalCypher:
		case Scrambler::Rsa:
		default:
			return;
	}
}

void MainWindow::on_pushDecrypt_clicked()
{
	if(lastUsedAlgo != selectedAlgo())
	{
		std::cout << lastUsedAlgo << ":" << selectedAlgo() << std::endl;
		QMessageBox::critical(this, "Ошибка", "Строка была зашифрована другим алгоритмом.", QMessageBox::Ok);
		return;
	}

	if(ui->editEncrypted->text() == ""
			|| ui->editKey->text() == "")
	{
		QMessageBox::critical(this, "Ошибка", "Ключ и зашифрованная строка не должны быть пустыми.", QMessageBox::Ok);
		return;
	}

	switch(lastUsedAlgo)
	{
		case Scrambler::Caesar:
		{
			bool ok = false;
			int shift = ui->editKey->text().toInt(&ok);
			if(!ok || shift <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен быть положительным целым числом.", QMessageBox::Ok);
				return;
			}
			ui->editSource->setText(Scrambler::DecryptCaesar(ui->editEncrypted->text(), shift));
			break;
		}

		case Scrambler::DoubleReshuffle:
		{
			QStringList numbers = ui->editKey->text().split(" ", QString::SkipEmptyParts);
			if(numbers.length() < 2)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен парой положительных целых чисел, разделенных пробелом.", QMessageBox::Ok);
				return;
			}
			bool ok_w, ok_l;
			int wkey = numbers.at(0).toInt(&ok_w);
			int lkey = numbers.at(1).toInt(&ok_l);
			if(!ok_l || !ok_w || wkey <= 0 || lkey <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен парой положительных целых чисел, разделенных пробелом.", QMessageBox::Ok);
				return;
			}
			ui->editSource->setText(Scrambler::DecryptDoubleReshuffle(ui->editEncrypted->text(), wkey, lkey));
			break;
		}

		case Scrambler::GammaCypher:
		{
			ui->editSource->setText(Scrambler::Gamma::DecryptGamma(ui->editEncrypted->text(), gamma));
			break;
		}

		case Scrambler::Gronsfeld:
		{
			bool ok  = false;
			int key = ui->editKey->text().toInt(&ok);
			if(!ok || key <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен быть положительным целым числом.", QMessageBox::Ok);
				return;
			}
			ui->editSource->setText(Scrambler::DecryptGronsfeld(ui->editEncrypted->text(), key));
			break;
		}

		case Scrambler::ManyAlphabet:
		{
			ui->editSource->setText(Scrambler::DecryptManyAlphabet(ui->editEncrypted->text(), ui->editKey->text()));
			break;
		}

		case Scrambler::SingleReshuffle:
		{
			bool ok = false;
			int key = ui->editKey->text().toInt(&ok);
			if(!ok || key <= 0)
			{
				QMessageBox::critical(this, "Ошибка", "Ключ должен быть положительным целым числом.", QMessageBox::Ok);
				return;
			}
			ui->editSource->setText(Scrambler::DecryptSingleReshuffle(ui->editEncrypted->text(), key));
			break;
		}

		case Scrambler::SingleWithKey:
		{
			ui->editSource->setText(Scrambler::DecryptSingleReshuffleWithKey(ui->editEncrypted->text(), ui->editKey->text()));
			break;
		}

		case Scrambler::Invalid: // shouldn't really happen
			QMessageBox::critical(this, "Ошибка", "Алгоритм не был выбран.", QMessageBox::Ok);
			break;

		case Scrambler::ElGamalCypher:
		case Scrambler::Rsa:
		default:
			return;
	}
}

Scrambler::Algoritm MainWindow::selectedAlgo()
{
	if(ui->rbtnCaesar->isChecked())
		return Scrambler::Caesar;
	else if(ui->rbtnDoubleReshuffle->isChecked())
		return Scrambler::DoubleReshuffle;
	else if(ui->rbtnGamma->isChecked())
		return Scrambler::GammaCypher;
	else if(ui->rbtnGronsfeld->isChecked())
		return Scrambler::Gronsfeld;
	else if(ui->rbtnManyAlph->isChecked())
		return Scrambler::ManyAlphabet;
	else if(ui->rbtnSingleReshuffle->isChecked())
		return Scrambler::SingleReshuffle;
	else if(ui->rbtnSingleWKey)
		return Scrambler::SingleWithKey;
	else
		return Scrambler::Invalid;
}

void MainWindow::on_pushAsymmEncrypt_clicked()
{
	if(ui->editAsymmSource->text() == ""
			|| ui->editAsymmPrivateKey->text() == ""
			|| ui->editAsymmPubKey->text() == "")
	{
		QMessageBox::critical(this, "Ошибка", "Исходная строка и открытый ключ не должны быть пустыми.", QMessageBox::Ok);
		return;
	}

	switch(selectedAsymmAlgo())
	{
	case Scrambler::ElGamalCypher:
	{
		if(ui->editAsymmPrivateKey->text() == "")
		{
			QMessageBox::critical(this, "Ошибка", "Закрытый ключ не должнен быть пустым.", QMessageBox::Ok);
			return;
		}

		QStringList key = ui->editAsymmPubKey->text().split(" ", QString::SkipEmptyParts);
		if(key.length() < 3)
		{
			QMessageBox::critical(this, "Ошибка", "Открытый ключ должен состоять из трех чисел, разделенных пробелом.", QMessageBox::Ok);
			return;
		}

		Scrambler::ElGamal::openKey pubkey(key[0], key[1], key[2]);
		ui->editAsymmEncrypted->setText(Scrambler::ElGamal::EncryptElGamal(ui->editAsymmSource->text(), pubkey));

		lastUsedAlgo = Scrambler::ElGamalCypher;
		break;
	}

	case Scrambler::Rsa:
	{
		QStringList key = ui->editAsymmPubKey->text().split(" ", QString::SkipEmptyParts);
		if(key.length() < 2)
		{
			QMessageBox::critical(this, "Ошибка", "Открытый ключ должен состоять из двух чисел, разделенных пробелом.", QMessageBox::Ok);
			return;
		}

		Scrambler::RSA::openKey pubkey(key[0], key[1]);
		ui->editAsymmEncrypted->setText(Scrambler::RSA::EncryptRSA(ui->editAsymmSource->text(), pubkey));

		lastUsedAlgo = Scrambler::Rsa;
		break;
	}

	case Scrambler::Caesar:
	case Scrambler::Invalid:
	case Scrambler::SingleReshuffle:
	case Scrambler::SingleWithKey:
	case Scrambler::DoubleReshuffle:
	case Scrambler::Gronsfeld:
	case Scrambler::ManyAlphabet:
	case Scrambler::GammaCypher:
		break;
	}
}

void MainWindow::on_pushAsymmDecrypt_clicked()
{
	if(lastUsedAlgo != selectedAsymmAlgo())
	{
		QMessageBox::critical(this, "Ошибка", "Строка была зашифрована другим алгоритмом.", QMessageBox::Ok);
		return;
	}

	switch(lastUsedAlgo)
	{
	case Scrambler::ElGamalCypher:
	{
		if(ui->editAsymmEncrypted->text() == ""
				|| ui->editAsymmPrivateKey->text() == ""
				|| ui->editAsymmPubKey->text() == "")
		{
			QMessageBox::critical(this, "Ошибка", "Зашифрованная строка и ключи не должны быть пустыми.", QMessageBox::Ok);
			return;
		}

		QStringList key = ui->editAsymmPubKey->text().split(" ", QString::SkipEmptyParts);
		if(key.length() < 3)
		{
			QMessageBox::critical(this, "Ошибка", "Открытый ключ должен состоять из трех чисел, разделенных пробелом.", QMessageBox::Ok);
			return;
		}

		Scrambler::ElGamal::openKey pubkey(key[0], key[1], key[2]);
		ui->editAsymmSource->setText(Scrambler::ElGamal::DecryptElGamal(ui->editAsymmEncrypted->text(), pubkey, ui->editAsymmPrivateKey->text()));
		break;
	}

	case Scrambler::Rsa:
	{
		if(ui->editAsymmEncrypted->text() == ""
				|| ui->editAsymmPrivateKey->text() == "")
		{
			QMessageBox::critical(this, "Ошибка", "Зашифрованная строка и закрытый ключ не должны быть пустыми.", QMessageBox::Ok);
			return;
		}

		QStringList key = ui->editAsymmPrivateKey->text().split(" ", QString::SkipEmptyParts);
		if(key.length() < 2)
		{
			QMessageBox::critical(this, "Ошибка", "Закрытый ключ должен состоять из двух чисел, разделенных пробелом.", QMessageBox::Ok);
			return;
		}

		Scrambler::RSA::closedKey privatekey(key[0], key[1]);
		ui->editAsymmSource->setText(Scrambler::RSA::DecryptRSA(ui->editAsymmEncrypted->text(), privatekey));
		break;
	}

	case Scrambler::Caesar:
	case Scrambler::Invalid:
	case Scrambler::SingleReshuffle:
	case Scrambler::SingleWithKey:
	case Scrambler::DoubleReshuffle:
	case Scrambler::Gronsfeld:
	case Scrambler::ManyAlphabet:
	case Scrambler::GammaCypher:
		break;
	}
}

Scrambler::Algoritm MainWindow::selectedAsymmAlgo()
{
	if(ui->rbtnElGamal->isChecked())
		return Scrambler::ElGamalCypher;
	else if(ui->rbtnRsa->isChecked())
		return Scrambler::Rsa;
	return Scrambler::Invalid;
}

void MainWindow::on_pushGenKey_clicked()
{
	if(selectedAsymmAlgo() == Scrambler::ElGamalCypher)
	{
		if(ui->editKeySeed->text() == "")
		{
			QMessageBox::critical(this, "Ошибка", "Строка генерации не должна быть пустой.", QMessageBox::Ok);
			return;
		}

		QStringList seed = ui->editKeySeed->text().split(" ", QString::SkipEmptyParts);
		if(seed.length() < 3)
		{
			QMessageBox::critical(this, "Ошибка", "Строка генерации должна содержать три положительных целых числа.", QMessageBox::Ok);
			return;
		}

		try
		{
			Scrambler::ElGamal el(seed[0], seed[1], seed[2]);
			ui->editAsymmPubKey->setText(el.ok.toQString());
			ui->editAsymmPrivateKey->setText(el.getSecretKeyStr());
		}
		catch(Scrambler::ElGamal::Exception e)
		{
			QMessageBox::critical(this, "Ошибка", "Первое число должно быть простым.", QMessageBox::Ok);
			return;
		}
	}
	else if(selectedAsymmAlgo() == Scrambler::Rsa)
	{
		if(ui->editKeySeed->text() == "")
		{
			QMessageBox::critical(this, "Ошибка", "Строка генерации не должна быть пустой.", QMessageBox::Ok);
			return;
		}

		try
		{
			QStringList seed = ui->editKeySeed->text().split(" ", QString::SkipEmptyParts);
			if(seed.length() < 2)
			{
				QMessageBox::critical(this, "Ошибка", "Строка генерации должна содержать два положительных целых числа.", QMessageBox::Ok);
				return;
			}

			Scrambler::RSA rsa(seed[0], seed[1]);
			ui->editAsymmPrivateKey->setText(rsa.ck.toQString());
			ui->editAsymmPubKey->setText(rsa.ok.toQString());
		}
		catch(Scrambler::RSA::Exception e)
		{
			QMessageBox::critical(this, "Ошибка", "Что-то пошло не так.", QMessageBox::Ok);
			return;
		}
	}
}
