#include <QApplication>
#include <QLoggingCategory>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValueRef>
#include <QJsonArray>
#include <cstdio>
#include <iostream>

const char g_cszUrl[] =
	"http://api.openweathermap.org/data/2.5/weather?q=Rostov-na-Donu&appid=e837b51ac0c6d8779a57b47be693d61c";
int main(int nArgC, char *apszArgV[])
{
	QApplication app(nArgC, apszArgV);
	QTextStream out(stdout), err(stderr);

	QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");

	QString hostName { g_cszUrl };
	QNetworkAccessManager manager;
	manager.connectToHost(hostName);

	QUrl url { hostName };
	QNetworkRequest request(url);

	QNetworkReply *pReply = manager.get(request);
	QEventLoop loop;
	QObject::connect(pReply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	const int cnError = pReply->error();
	if (cnError != 0)
	{
		err << "HTTP error: " << cnError << endl;
		return -1;
	}

	QString resData = (QString)pReply->readAll();
	QString strErrorMsg;

	int nErrorRow, nErrorCol;
	QJsonDocument doc = QJsonDocument::fromJson(resData.toUtf8());

	double temp_max = doc.object()["main"].toObject()["temp_max"].toVariant().toDouble();
	double temp_min = doc.object()["main"].toObject()["temp_min"].toVariant().toDouble();
	int pressure = doc.object()["main"].toObject()["pressure"].toVariant().toInt();
	QString weather = doc.object()["weather"].toArray()[0].toObject()["description"].toVariant().toString();

	std::cout << "Description : " << weather.toStdString() << std::endl;
	std::cout << "Temp max : " << temp_max << std::endl;
	std::cout << "Temp min : " << temp_min << std::endl;
	std::cout << "Pressure : " << pressure << std::endl;
} // main()

