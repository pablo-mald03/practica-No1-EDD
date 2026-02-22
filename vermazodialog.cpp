#include "vermazodialog.h"
#include "cartadeckui.h"
#include "ui_vermazodialog.h"
#include"qdebug.h"

VerMazoDialog::VerMazoDialog(
    ListaCircular<Jugador*> &jugadores,
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

    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setDragMode(QGraphicsView::ScrollHandDrag);

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
    QHBoxLayout* layout =
        qobject_cast<QHBoxLayout*>(ui->scrollAreaWidgetContents->layout());

    if (!layout) {
        qDebug() << "ERROR: scrollAreaWidgetContents no tiene layout";
        return;
    }

    layout->setAlignment(Qt::AlignLeft);
    layout->setSpacing(20);

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    for (int i = 0; i < listaJugadores.getLongitud(); i++)
    {
        if(listaJugadores.getActual() == listaJugadores.obtenerEn(i)){
            continue;
        }

        QPushButton* btn = new QPushButton(
            QString::fromStdString(
                listaJugadores.obtenerConstanteEn(i)->getNombre()
                )
            );

        btn->setFixedSize(160, 160);

        connect(btn, &QPushButton::clicked, this, [this, i]() {
            mostrarMazoJugador(i);
        });

        layout->addWidget(btn);
    }

    layout->addStretch();
}

//Metodo que permite mostrar el mazo del jugador seleccionado
void VerMazoDialog::mostrarMazoJugador(int indice)
{
    jugadorSeleccionado = indice;
    ui->stackedWidget->setCurrentIndex(1);
    Jugador* jugador = listaJugadores.obtenerConstanteEn(indice);
    dibujarMazo(jugador);

    QTimer::singleShot(5000, this, [this]() {
        this->accept();
    });
}

void VerMazoDialog::dibujarMazo(Jugador* jugadorActual)
{
    escena->clear();

    int total = jugadorActual->getMazo()->getLongitud();
    if(total == 0) return;

    const double anchoCarta = 100.0;
    const double altoCarta  = 150.0;
    const double separacion = 30.0;

    double anchoTotal = (anchoCarta * total) +
                        (separacion * (total - 1));

    escena->setSceneRect(0, 0, anchoTotal + 40, 190);

    this->ui->label_2->setText("Cartas del " + QString::fromStdString(jugadorActual->getNombre()));
    for(int i = 0; i < total; ++i)
    {
        Carta carta = jugadorActual->getMazo()->getValor(i);

        QString pathImagen = !estaFlip
                                 ? QString::fromStdString(carta.getAnverso()->getPathImagen())
                                 : QString::fromStdString(carta.getReverso()->getPathImagen());

        CartaDeckUI* visual = new CartaDeckUI(i, pathImagen);

        visual->setScale(0.75);

        escena->addItem(visual);
        visual->setPos(20 + i * (anchoCarta + separacion), 20);
        visual->setZValue(i);
    }
}

VerMazoDialog::~VerMazoDialog()
{
    delete ui;
}
