#include "statusbar.h"
#include "gamedialog.h"

namespace game {

StatusBar::StatusBar(GameDialog* dialog) : plasmaEnergy(100), barrierEnergy(0), gd(dialog), plasmaDrained(false)
{}

void StatusBar::buildBrush(){
    // determine location for status bar
    statusBar = QRect(0, gd->SCALEDHEIGHT, gd->SCALEDWIDTH, gd->STATUSBARHEIGHT);

    // build for the main status bar
    QLinearGradient statusBarBrush(0, gd->SCALEDHEIGHT, 0, gd->SCALEDHEIGHT + gd->STATUSBARHEIGHT);
    statusBarBrush.setColorAt(0.05, QColor::fromRgb(10, 10, 10));
    statusBarBrush.setColorAt(0.2, QColor::fromRgb(100, 100, 100));
    statusBarBrush.setColorAt(0.5, QColor::fromRgb(120, 120, 120));
    statusBarBrush.setColorAt(0.8, QColor::fromRgb(100, 100, 100));
    this->statusBarBrush = statusBarBrush;


    // determine the dimension of the energy bar
    int barWidth = static_cast<int>(gd->SCALEDWIDTH*0.175);
    int barHeight = static_cast<int>(gd->STATUSBARHEIGHT*0.6);

    // build the energy bar container
    containerOuter = QRect(0, 0, barWidth*1.1, barHeight*1.3);
    containerInner = QRect(containerOuter.width() - barWidth,
                           (containerOuter.height() - barHeight) / 2,
                           barWidth, barHeight);

    // determine location for plasma bar
    plasmaBar = QRect(gd->SCALEDWIDTH*0.80, gd->SCALEDHEIGHT + gd->STATUSBARHEIGHT*0.3,
                      gd->SCALEDWIDTH*0.175, gd->STATUSBARHEIGHT*0.6);

    // build brush for the plasma bar
    QLinearGradient plasmabarBrush(0, gd->SCALEDHEIGHT, 0, gd->SCALEDHEIGHT + gd->STATUSBARHEIGHT);
    plasmabarBrush.setColorAt(0.2, QColor::fromRgb(0, 0, 180));
    plasmabarBrush.setColorAt(0.4, QColor::fromRgb(0, 0, 250));
    plasmabarBrush.setColorAt(0.6, QColor::fromRgb(0, 0, 250));
    plasmabarBrush.setColorAt(0.8, QColor::fromRgb(0, 0, 180));
    this->plasmaBarBrush = plasmabarBrush;

    // determine location for barrier bar
    barrierBar = QRect(gd->SCALEDWIDTH*0.55, gd->SCALEDHEIGHT + gd->STATUSBARHEIGHT*0.3,
                       gd->SCALEDWIDTH*0.175, gd->STATUSBARHEIGHT*0.6);

    // build brush for the barrier bar
    QLinearGradient barrierbarBrush(0, gd->SCALEDHEIGHT, 0, gd->SCALEDHEIGHT + gd->STATUSBARHEIGHT);
    barrierbarBrush.setColorAt(0.2, QColor::fromRgb(180, 0, 0));
    barrierbarBrush.setColorAt(0.4, QColor::fromRgb(250, 0, 0));
    barrierbarBrush.setColorAt(0.6, QColor::fromRgb(250, 0, 0));
    barrierbarBrush.setColorAt(0.8, QColor::fromRgb(180, 0, 0));
    this->barrierBarBrush = barrierbarBrush;
}

void StatusBar::draw(QPainter* p){
    p->setPen(Qt::NoPen);

    //////////////////////////////////////////
    //////      STATUS BAR BACKGROUND
    //////////////////////////////////////////
    // first draw the background of status bar
    p->setBrush(statusBarBrush);
    p->drawRect(statusBar);


    //////////////////////////////////////////
    //////      PLASMA BAR
    //////////////////////////////////////////
    // draw the container for plasma bar
    containerInner.moveTo(plasmaBar.x(), plasmaBar.y());
    containerOuter.moveTo(containerInner.x() - (containerOuter.width() - containerInner.width()),
                          plasmaBar.y() - (containerOuter.height() - containerInner.height()) / 2);
    p->setBrush(QColor::fromRgb(96, 80, 43));
    p->drawRect(containerOuter);
    p->setBrush(QColor::fromRgb(45, 40, 26));
    p->drawRect(containerInner);

    // draw the plasma Bar, with scaling of the plasma energy
    p->setBrush(plasmaBarBrush);
    p->drawRect(plasmaBar.x(), plasmaBar.y(),
                plasmaBar.width() * plasmaEnergy / 100.0, plasmaBar.height());

    // if plasma bar is fully drained, draw a transparent rect represent it cannot be used currently
    // OR if barrier energy bar is active. (since only one cursor can be active at any given time)
    if(plasmaDrained || barrierEnergy > 0)
        p->fillRect(containerOuter, QBrush(QColor(0, 0, 0, 128)));


    //////////////////////////////////////////
    //////      BARRiER BAR
    //////////////////////////////////////////
    // draw the container for barrier bar
    containerInner.moveTo(barrierBar.x(), barrierBar.y());
    containerOuter.moveTo(containerInner.x() - (containerOuter.width() - containerInner.width()),
                          barrierBar.y() - (containerOuter.height() - containerInner.height()) / 2);
    p->setBrush(QColor::fromRgb(96, 80, 43));
    p->drawRect(containerOuter);
    p->setBrush(QColor::fromRgb(45, 40, 26));
    p->drawRect(containerInner);

    // draw the barrier Bar, with scaling of the plasma energy
    p->setBrush(barrierBarBrush);
    p->drawRect(barrierBar.x(), barrierBar.y(),
                barrierBar.width() * barrierEnergy / 100.0, barrierBar.height());

    // if barrier bar is fully drained, draw a transparent rect represent it cannot be used currently
    if(barrierEnergy <= 0)
        p->fillRect(containerOuter, QBrush(QColor(0, 0, 0, 128)));

    //////////////////////////////////////////
    //////      CURRENT SCORE
    //////////////////////////////////////////
    p->setPen(Qt::white);
    QFont f("monospace");
    f.setStyleHint(QFont::TypeWriter);
    f.setFamily("courier");
    f.setPointSize(static_cast<int>(gd->STATUSBARHEIGHT * 0.5));

    p->setFont(f);
    p->drawText(gd->SCALEDWIDTH*0.05, gd->SCALEDHEIGHT + gd->STATUSBARHEIGHT*0.8, QString::number(gd->gameScore));

    //    // print keyboard hint
    //    p->drawText(5, line_height, "[F1] Toggle Cheat | [C] Change Cursor | [P] Pause/Resume | [-/+] Goto Prev/Next Stage");

    //    // print spaceship x, y
    //    str = "Spaceship [X:";
    //    str += QString::number(ship->get_x());
    //    str += " Y:";
    //    str += QString::number(ship->get_y()) + "]";
    //    p->drawText(20, line_height * 2, str);

}

void StatusBar::update(){

}
}
