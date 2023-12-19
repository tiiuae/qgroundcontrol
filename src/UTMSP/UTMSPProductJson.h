/****************************************************************************
 *
 * (c) 2023 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QMap>
#include <QVector>

class UTMSPProductJson {
public:
    QString utmspName;
    QString utmspLogoUrl;
    QString utmspSupportUrl;
    QString utmspDocumentationUrl;
    QString baseUrl;
    QMap<QString, QString> availableScopes;
    QVector<QJsonObject> availableServices;

    void parseJson(const QString &jsonFilePath);
};
