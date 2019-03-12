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
    }
}



QString ConexionBBDD::DevolverVuelos()
{
    QSqlQuery qu;
    qu.setForwardOnly(true);









          bool firstline = true;
          qu.setForwardOnly(true);
          if(qu.exec("SELECT idvuelo,nombrecompania,nombredestino,numeropuerta,horavuelo,informacionvuelo FROM public.vuelos join companias using (idcompania)join puertas using (idpuerta)join destinos using(iddestino);"))
          {
              QString answer = "{\"vuelos\":[";
              while(qu.next())
                  {
                      if(firstline){firstline = false;}else {answer += ",";}

                      answer += "{";
                      for(int x=0; x < qu.record().count(); ++x)
                      {
                          if(x != 0){answer += ",";}
                          answer += "\""+qu.record().fieldName(x) +"\":\""+ qu.value(x).toString()+"\"";
                      }
                      answer += "}";
                  }
              answer += "]}";
              return answer;
          }

}




























