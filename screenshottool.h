#ifndef SCREENSHOTTOOL_H
#define SCREENSHOTTOOL_H

/*
 * Author:qiuzhiqian
 * Email:xia_mengliang@163.com
 * Github:https://github.com/qiuzhiqian
 * Date:2017.07.23
 **/

#include <QWidget>
#include <QDialog>
#include <QScreen>
#include <QPixmap>
#include <QMouseEvent>
#include <QDesktopWidget>

#include <QSystemTrayIcon>

#include <QMenu>

#include "canvas.h"

#include <QAbstractNativeEventFilter>


class ScreenShotTool : public QWidget,public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit ScreenShotTool(QWidget *parent = 0);
    ~ScreenShotTool();

    void initTray();                //初始化托盘
    void ss_start();                //开始截图

    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:

    Canvas *screenCanvas;
    QPixmap fullPixmap;
    QSystemTrayIcon *m_systemTray;  //系统托盘
    QAction *exitAction;
    void closeEvent( QCloseEvent * event );     //重写退出
    bool closeFlag=false;

signals:
    void appQuit();

private slots:
    void slt_clickTray(QSystemTrayIcon::ActivationReason reason);
    void slt_exitAction();
};

#endif // SCREENSHOTTOOL_H
