#include "vermazodialog.h"
#include "cartadeckui.h"
#include "ui_vermazodialog.h"

VerMazoDialog::VerMazoDialog(
    ListaCircular<Jugador*> jugadores,
    bool modoFlip,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::VerMazoDialog),
    listaJugadores(jugadores),
    estaFlip(modoFlip),
    escena(nullptr),
    vista(nullptr),
    jugadorSeleccionado(-1)
{
    ui->setupUi(this);

    this->setStyleSheet(
        "QDialog#VerMazoDialog {"
        "background: qlineargradient("
        "x1:0, y1:0, x2:1, y2:1,"
        "stop:0 #638F0A,"
        "stop:1 #800F44"
        ");"
        "}"
        );

    ui->stackedWidget->setCurrentIndex(0);
    cargarJugadores();
    inicializarVistaMazo();
}

//Metodo encargado de inicializar la vista de las cartas que se van encontrar
void VerMazoDialog::inicializarVistaMazo()
{
    escena = new QGraphicsScene(this);
    vista = new QGraphicsView(escena, this);

    vista->setAlignment(Qt::AlignCenter);
    vista->setStyleSheet("background: transparent; border: none;");
    vista->setRenderHint(QPainter::Antialiasing);

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->widgetCartas->layout());

    if(!layout) {
        layout = new QVBoxLayout(ui->widgetCartas);
        ui->widgetCartas->setLayout(layout);
    }

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(vista);
}

//Metodo que permite seleccionar
void VerMazoDialog::cargarJugadores()
{
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui->widgetJugadores->layout());

    if(!layout) {
        layout = new QVBoxLayout(ui->widgetJugadores);
        ui->widgetJugadores->setLayout(layout);
    }

    layout->setAlignment(Qt::AlignTop);

    for(int i = 0; i < listaJugadores.getLongitud(); i++)
    {
        QPushButton* btn = new QPushButton(
            QString::fromStdString(listaJugadores.obtenerEn(i)->getNombre())
            );

        btn->setProperty("indiceJugador", i);

        btn->setMinimumHeight(50);

        btn->setStyleSheet(
            "QPushButton {"
            "background-color: #353b48;"
            "color: white;"
            "border-radius: 10px;"
            "font-size: 16px;"
            "}"
            "QPushButton:hover {"
            "background-color: #40739e;"
            "}"
            );

        connect(btn, &QPushButton::clicked, this, [this, btn]() {
            int indice = btn->property("indiceJugador").toInt();
            mostrarMazoJugador(indice);
        });

        layout->addWidget(btn);
    }
}

//Metodo que permite mostrar el mazo del jugador seleccionado
void VerMazoDialog::mostrarMazoJugador(int indice)
{
    jugadorSeleccionado = indice;

    ui->stackedWidget->setCurrentIndex(1);

    dibujarMazo(listaJugadores.obtenerEn(indice));

    QTimer::singleShot(5000, this, [this]() {
        this->accept();
    });
}

void VerMazoDialog::dibujarMazo(Jugador* jugadorActual)
{
    escena->clear();

    int total = jugadorActual->getMazo()->getLongitud();
    if(total == 0) return;

    double anchoContenedor = vista->viewport()->width();
    if(anchoContenedor < 1241) anchoContenedor = 1241;

    double anchoCarta = 135.0;
    double ideal = (total > 1) ?
                       (anchoContenedor - 30 - anchoCarta) / (total - 1) : 0;

    double separacion = (total > 1) ?
                            qBound(25.0, ideal, 85.0) : 0;

    double anchoTotal = anchoCarta + (total - 1) * separacion;
    double xActual = (anchoContenedor - anchoTotal) / 2.0;

    escena->setSceneRect(0, 0, anchoContenedor, 240);

    for(int i = 0; i < total; ++i)
    {
        Carta carta = jugadorActual->getMazo()->getValor(i);

        QString pathImagen;

        if(!estaFlip)
            pathImagen = QString::fromStdString(
                carta.getAnverso()->getPathImagen());
        else
            pathImagen = QString::fromStdString(
                carta.getReverso()->getPathImagen());

        CartaDeckUI* visual = new CartaDeckUI(i, pathImagen);

        escena->addItem(visual);
        visual->setPos(xActual + (i * separacion), 30);
        visual->setZValue(i);
    }
}

VerMazoDialog::~VerMazoDialog()
{
    delete ui;
}
