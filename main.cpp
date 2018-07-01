#include "screenshottool.h"
#include <QApplication>
#include <QGuiApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //防止窗体全部掩藏后意外退出
    //否则在截图完成之后，全部隐藏会造成程序退出
    a.setQuitOnLastWindowClosed(false);

    ScreenShotTool w;
    w.hide();

    a.installNativeEventFilter(&w);

    return a.exec();
}
