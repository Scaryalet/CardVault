#ifndef USERHOME_H
#define USERHOME_H

#include <QMainWindow>
#include "addcard.h"
#include "addset.h"
#include "flowlayout.h"
#include "qcombobox.h"
#include "qlistwidget.h"
#include <QSqlDatabase>
#include <QWidget>
#include <QPainter>
#include <QPushButton>

namespace Ui {
class UserHome;
}


class CustomButton : public QPushButton {
public:
    CustomButton(const QString& text, const QString& imagePath, qreal opacity, const QString& buttonStyleSheet, QWidget* parent = nullptr)
        : QPushButton(text, parent), imagePath(imagePath), buttonOpacity(opacity) {
        setStyleSheet(buttonStyleSheet);
        pixmap.load(imagePath);
        if (pixmap.isNull()) {
            qDebug() << "Failed to load image:" << imagePath;
        }
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPushButton::paintEvent(event);

        if (!pixmap.isNull()) {
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing);

            QPixmap scaledPixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.setOpacity(buttonOpacity); // Set the opacity based on the button's ownership status
            painter.drawPixmap(rect(), scaledPixmap);
        }
    }

private:
    QString imagePath;
    QPixmap pixmap;
    qreal buttonOpacity;
};


class UserHome : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserHome(QWidget *parent = nullptr);
    ~UserHome();
    FlowLayout *flowLayout;
    Set s1;
    QSqlDatabase db;
public slots:

private slots:
    void showFranchiseNames();
    void showUsersSets();
    void clearLayout(QLayout *layout);
    void displayTheCards();
    void userAddCard();
    void userAddSet();
    void handleExit();
    void resetFilter();

private:
    Ui::UserHome *ui;
    QComboBox *setsCombo;
    QListWidget *setsList;
    QComboBox *filterCombo;
    bool cardExistsInAllCards(const QString &cardName);
    bool shouldShowCard(const QSqlQuery &query, const QString &selectedOption);
};

#endif // USERHOME_H
