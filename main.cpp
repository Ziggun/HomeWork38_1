#include <QApplication>
#include <QPushButton> // просто кнопка
#include <QPixmap>
#include <iostream>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMediaPlayer>
#include <QSound>

class ImageButton : public QPushButton
{
    Q_OBJECT // обязательный макрос для всех классов и наследников Qjbject
public:
    ImageButton() = default;
    ImageButton (QWidget *parent); // конструктор который принимает указатель на виджет и встраивает его в родитекля, это позволяет встраивать виджеты в сложную иерархию окон
    void paintEvent(QPaintEvent *e) override; // роверка метода
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown(); // здесь мы и будем менять картинку
private:
    QPixmap mCurrentBUttonPixmap;
    QPixmap mButtonDownPixmap; // объявили 3 картинки, отвечают за внешний вид кнопки, в обычном состоянии нажатом и не нажатом
    QPixmap mButtonUpPixmap;
    bool isDown = false; // определение нажата или нет

};

ImageButton::ImageButton(QWidget *parent) {
    setParent(parent); // Реализация методов, передадим туда родителя
    setToolTip("STOP!"); //подсказка в всплывающем виджете при наведении на него мышки
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // фиксированный размер сделали по горизонтали и вертикали.
    mButtonUpPixmap = QPixmap("B://Work//HomeWOrk38_1_QT//files//red-button.jpg");//загружаем картинки, загружаем не нажатую кнопку
    mButtonDownPixmap = QPixmap("B://Work//HomeWOrk38_1_QT//files//images.jfif");
    mCurrentBUttonPixmap = mButtonUpPixmap; // 'это первое что мы увидим
    setGeometry(mCurrentBUttonPixmap.rect()); // меняем размер виджета, при помощи метода rect узнаём размер картинки
    connect(this,&QPushButton::clicked, this,&ImageButton::setDown);// раз они наследники то мы не пишекм qobject, а просто пишем this ,
    // а второй this пишет кто будет получателем события, один сигнал, один слот, один прислал, другой принял
}
void ImageButton::paintEvent(QPaintEvent *e)  // рисуем кнопку
{
    QPainter p(this); //он и рисует объекты и принимает, то на чём он будет рисовать, в данном случае это нащ объект
    p.drawPixmap(e->rect(),mCurrentBUttonPixmap);  // само рисование, в кёррент всегда картинка которую нужно нарисовать сейчас.
}

QSize ImageButton::sizeHint() const
{
    return QSize(100,100); // метод говорит какого размера будет виджет.
}

QSize ImageButton::minimumSizeHint() const
{
    return sizeHint(); // укажем минимальный размер
}

void ImageButton::keyPressEvent(QKeyEvent *e)  // здесь определяем как кнопка реагирует на нажатие
{
    setDown();

}

void ImageButton::setDown() // здесь нужно написать что кнопка меняется на нажатую, и чтобы Qt её перерисовывало
{
    mCurrentBUttonPixmap = mButtonDownPixmap;
    update(); // чтобы он понял, что пора менять кнопку
    QTimer::singleShot(100,this,&ImageButton::setUp); // через 100 милисе сек после нажатия кнопка вернётся в исходное положение.
}

void ImageButton::setUp()
{
    mCurrentBUttonPixmap = mButtonUpPixmap; // и меняем кнопку в другое положение.
    update();
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    ImageButton redButton(nullptr); // раз родитель нулевой казатель то наша кнопка будет главным окном приложения
    QSound sound("B://Work//HomeWOrk38_1_QT//files//cl.wav");
    redButton.setFixedSize(800,800); // размеры кнопки
    redButton.move(1000,400); //двигаем кнопку
    QObject::connect(&redButton, &QPushButton::clicked, [&sound](){
        sound.play();
        std::cout << "clicked" << std::endl;}); // мы проверяем работает ли кнопка
    redButton.show(); // Вызываем как всегда этот метод
    return app.exec();
}
#include "main.moc"
