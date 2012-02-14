#include "infowindow.h"
#include <QMessageBox>
#include <QPushButton>

InfoWindow::InfoWindow()
{
    QPushButton *ok = new QPushButton;
    ok->setMinimumWidth(50);
    ok->setText("Schließen");

    QMessageBox *info = new QMessageBox;
    info->addButton(ok, QMessageBox::ActionRole);

    info->setWindowIcon(QIcon(":/new/image/info.png"));
    info->setText("Dies ist ein Projekt in dem Wahlfach: CPP\n"
                  "von Hans Laser und Andre Kießlich.\n\n"
                  "Projektname: Adress Buch\n\n"
                  "Version: 1.0.0");
    info->setWindowTitle("Info");
    info->show();
}
