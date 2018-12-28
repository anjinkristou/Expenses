#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QStandardPaths>

#include "sheet.h"
#include "record.h"
#include "sheetcollection.h"
#include "sheetmodel.h"
#include "recordmodel.h"
#include "datamanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    DataManager manager(QStandardPaths::writableLocation(QStandardPaths:: AppDataLocation));


    //Test
    SheetCollection collection(&manager);
//    collection.setDataManager(&manager);

    qmlRegisterType<Sheet>("com.kristou.expense", 1, 0, "Sheet");
    qmlRegisterType<SheetModel>("com.kristou.expense", 1, 0, "SheetModel");
    qmlRegisterType<SheetCollection>("com.kristou.expense", 1, 0, "SheetCollection");
    qmlRegisterType<Record>("com.kristou.expense", 1, 0, "Record");
    qmlRegisterType<RecordModel>("com.kristou.expense", 1, 0, "RecordModel");

    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("sheetCollection", QVariant::fromValue(&collection));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
