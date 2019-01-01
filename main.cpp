#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QStandardPaths>
#include <QtDebug>

#include "sheet.h"
#include "record.h"
#include "sheetcollection.h"
#include "sheetmodel.h"
#include "recordmodel.h"
#include "datamanager.h"
#include "sheetstatus.h"
#include "sheetstatuscollection.h"
#include "sheetstatusmodel.h"

void registerTypes()
{
    qmlRegisterType<SheetStatus>("com.kristou.expense", 1, 0, "SheetStatus");
    qmlRegisterType<SheetStatusModel>("com.kristou.expense", 1, 0, "SheetStatusModel");
    qmlRegisterType<SheetStatusCollection>("com.kristou.expense", 1, 0, "SheetStatusCollection");

    qmlRegisterType<Sheet>("com.kristou.expense", 1, 0, "Sheet");
    qmlRegisterType<SheetModel>("com.kristou.expense", 1, 0, "SheetModel");
    qmlRegisterType<SheetCollection>("com.kristou.expense", 1, 0, "SheetCollection");

    qmlRegisterType<Record>("com.kristou.expense", 1, 0, "Record");
    qmlRegisterType<RecordModel>("com.kristou.expense", 1, 0, "RecordModel");
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    DataManager manager(QStandardPaths::writableLocation(QStandardPaths:: AppDataLocation));

    //Test
    SheetStatusCollection sheetStatusCollection(&manager);
    SheetCollection sheetCollection(&manager);
//    collection.setDataManager(&manager);

    registerTypes();

    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("sheetCollection", QVariant::fromValue(&sheetCollection));
    ctxt->setContextProperty("sheetStatusCollection", QVariant::fromValue(&sheetStatusCollection));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
