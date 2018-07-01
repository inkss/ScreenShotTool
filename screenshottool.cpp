#include "screenshottool.h"
#include "ui_screenshottool.h"

#include <QDebug>
#include <QSettings>
#include <QTranslator>

/*
 * 画图原理
 * 1\首先在全屏幕设置一个透明画布
 * 2\然后在透明画布上绘制矩形
 * 3\对画布上的矩形区域截图
 * 4\保存截图到文件夹或剪切板
 * 修正
 * 1\全屏截屏，同时生成一个暗色图片
 * 2\设置全屏画布，然后将暗色全屏图片显示到画布
 * 3\在暗色全屏图片上画矩形，矩形内显示亮色图片
 * 4\对矩形区域截图
 * 5\保存截图到文件夹或剪切板
 * */

ScreenShotTool::ScreenShotTool(QWidget *parent) :
    QWidget(parent)
{
    QWidget * xparent = new QWidget;        //设置一个空的父对象，从而达到掩藏任务栏图标的目的
    setParent(xparent);

    this->setWindowFlags(Qt::Dialog|Qt::WindowCloseButtonHint|Qt::WindowStaysOnTopHint);
    this->setWindowTitle(tr("设置"));
    this->setWindowIcon(QIcon(":/ss.ico"));
    initTray();                             //托盘显示
    this->setFixedSize(this->size());
}

ScreenShotTool::~ScreenShotTool() {}

void ScreenShotTool::ss_start()             //开始截屏
{
    QScreen *screen = QGuiApplication::primaryScreen();
    fullPixmap = screen->grabWindow(0);
    screenCanvas=new Canvas(0);             //创建画布
    screenCanvas->setbgPixmap(fullPixmap);  //传递全屏背景图片
}

void ScreenShotTool::initTray()             //初始化托盘
{
    m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setIcon(QIcon(":/ss.ico")); //托盘图标

    exitAction=new QAction(tr("退出"),this);
    QMenu *trayMenu=new QMenu(this);
    trayMenu->addAction(exitAction);
    m_systemTray->setContextMenu(trayMenu);
    m_systemTray->show();

    connect(m_systemTray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(slt_clickTray(QSystemTrayIcon::ActivationReason)));
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(slt_exitAction()));
}

void ScreenShotTool::slt_clickTray(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason) {
        case QSystemTrayIcon::Trigger:
            //单击托盘图标,显示菜单
            ss_start();
            break;
        case QSystemTrayIcon::DoubleClick:
            //双击托盘图标
            //双击后进行截图
            this->show();
            break;
        default:
            break;
    }
}

void ScreenShotTool::slt_exitAction()
{
    closeFlag=true;
    this->close();
    QApplication::quit();       //程序退出
}

void ScreenShotTool::closeEvent(QCloseEvent *event)
{
    if(closeFlag==true) {
        event->accept();
    } else {
        this->hide();
        event->ignore();
    }
}

bool ScreenShotTool::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    return false;               //该函数一定要返回false，不然程序会直接崩溃
}
