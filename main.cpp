#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QSound>

class ImageButton : public QPushButton
{
    Q_OBJECT
public:
    ImageButton() = default;
    ImageButton (QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentBUttonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
    bool isDown = false;

};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent);
    setToolTip("STOP!");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mButtonUpPixmap = QPixmap("B://Work//HomeWOrk38_1_QT//files//red-button.jpg");
    mButtonDownPixmap = QPixmap("B://Work//HomeWOrk38_1_QT//files//images.jfif");
    mCurrentBUttonPixmap = mButtonUpPixmap;
    setGeometry(mCurrentBUttonPixmap.rect());
    connect(this,&QPushButton::clicked, this,&ImageButton::setDown);
}
void ImageButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.drawPixmap(e->rect(),mCurrentBUttonPixmap);
}

QSize ImageButton::sizeHint() const
{
    return QSize(100,100);
}

QSize ImageButton::minimumSizeHint() const
{
    return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e)
{
    setDown();

}

void ImageButton::setDown()
{
    mCurrentBUttonPixmap = mButtonDownPixmap;
    update();
    QTimer::singleShot(100,this,&ImageButton::setUp);
}

void ImageButton::setUp()
{
    mCurrentBUttonPixmap = mButtonUpPixmap;
    update();
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ImageButton redButton(nullptr);
    QSound sound("B://Work//HomeWOrk38_1_QT//files//cl.wav");
    redButton.setFixedSize(800,800);
    redButton.move(1000,400);
    QObject::connect(&redButton, &QPushButton::clicked, [&sound](){
        sound.play();
        std::cout << "clicked" << std::endl;});
    redButton.show();
    return app.exec();
}
#include "main.moc"
