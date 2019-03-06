#include "conexionbbdd.h"
#include <QDebug>
#include <QtSql>
#include <QUuid>
#include <QSqlQuery>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>


ConexionBBDD::ConexionBBDD()
{

}
void ConexionBBDD::Conectar()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("aviones");
    db.setUserName("usuario");
    db.setPassword("usuario");
    bool ok = db.open();

    if (ok)
    {
        qDebug() << "Conectado OK";

    } else {
        qDebug() << db.lastError();
    } // end if
}



QString ConexionBBDD::DevolverVuelos()
{
    QSqlQuery qu;
    qu.setForwardOnly(true);
    if (!qu.exec("SELECT * FROM public.vuelos"))return QString();

      QJsonDocument  json;
      QJsonArray     recordsArray;

      while(qu.next())
      {
         QJsonObject recordObject;
            for(int x=0; x < qu.record().count(); x++)
            {
            recordObject.insert( qu.record().fieldName(x),QJsonValue::fromVariant(qu.value(x)) );
            }
         recordsArray.push_back(recordObject);
      }
      json.setArray(recordsArray);

      QString doc=json.toJson(QJsonDocument::Compact);


      return doc;
    }




















