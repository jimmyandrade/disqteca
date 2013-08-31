#include <fstream>

#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <Phonon/MediaObject>
#include <Phonon/VideoWidget>
#include <QSplitter>
#include <QTime>
#include <QSplashScreen>
#include <QPixmap>
#include <QUrl>

#include "disqteca.h"
#include "ui_disqteca.h"

void disqteca::sourceChanged(const Phonon::MediaSource &source)
{
    ui->Mixteca->selectRow(sources.indexOf(source));
    ui->andamento->setText("00:00");
    setWindowTitle("disqteca" +  metaInformationResolver->currentSource().fileName());
}

void disqteca::tick(qint64 time)
{
    QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

    ui->andamento->setText(displayTime.toString("mm:ss"));
}

void disqteca::aboutToFinish()
{
    int index = sources.indexOf(mediaObject->currentSource()) + 1;
    if (sources.size() > index) {
        mediaObject->enqueue(sources.at(index));
    }
}

disqteca::disqteca(QWidget *parent) : QMainWindow(parent), ui(new Ui::disqteca) {

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    videoPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    videoWidget = new Phonon::VideoWidget();
    videoWidget->setGeometry(0, 0, 1920, 1080);
    videoWidget->setMinimumWidth(320);
    videoWidget->setMinimumHeight(240);

    mediaObject = new Phonon::MediaObject(this);
    metaInformationResolver = new Phonon::MediaObject(this);

    mediaObject->setTickInterval(1000);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(metaInformationResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(metaStateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    // Nunca referenciar nenhum objeto da UI antes dessa linha
    ui->setupUi(this);

    // Liga objetos de busca, volume e os widgets de áudio e video
    ui->seekSlider->setMediaObject(mediaObject);
    ui->volumeSlider->setAudioOutput(audioOutput);
    Phonon::createPath(mediaObject, audioOutput);
    Phonon::createPath(mediaObject, videoWidget);

    DivisorVideoMixteca = new QSplitter;
    DivisorVideoMixteca->addWidget(videoWidget);
    DivisorVideoMixteca->addWidget(ui->Mixteca);

    QVBoxLayout *DivisorCentral = new QVBoxLayout;
    DivisorCentral->addWidget(DivisorVideoMixteca);
    DivisorCentral->addWidget(ui->controlesWidget);

    QWidget *Central = new QWidget;
    Central->setLayout(DivisorCentral);

    setCentralWidget(Central);

    QStringList Cabecalhos;
    Cabecalhos << tr("Titulo") << tr("Artista") << tr("Disco") << tr("Ano");

    ui->Mixteca->setHorizontalHeaderLabels(Cabecalhos);
    ui->sairAction->setShortcuts(QKeySequence::Quit);

}

disqteca::~disqteca() {
    delete ui;
}

void disqteca::sobre() {

    QString Titulo("sobre o disqteca");
    QString Texto("disqteca, um player desenvolvido"
                  "para o TP1 da disciplina de Projeto Assistido por Computador.\n"
                  "\n"
                  "Equipe:\n"
                  "Altierres Washington\n"
                  "Marco Aurelio\n"
                  "Paulo H. Andrade Mota C.\n"
                  "Renan Nogueira");
    QMessageBox::about(this, Titulo, Texto);

}

void disqteca::on_actionSobre_o_disqteca_triggered() {
    sobre();
}

void disqteca::on_actionSobre_o_qt_triggered() {
    QMessageBox::aboutQt(this, "sobre o qt");
}

void disqteca::abrir() {
    QStringList files = QFileDialog::getOpenFileNames(this, tr("escolha os arquivos de musica e video"),
        QDesktopServices::storageLocation(QDesktopServices::MusicLocation));

    if (files.isEmpty())
        return;

    int index = sources.size();
    foreach (QString string, files) {
            Phonon::MediaSource source(string);

        sources.append(source);
    }
    if (!sources.isEmpty())
        metaInformationResolver->setCurrentSource(sources.at(index));

    mediaObject->play();
}

void disqteca::on_action_abrir_triggered() {
    abrir();
}

void disqteca::on_sairAction_triggered() {
    this->close();
}

void disqteca::telaCheia() {

    if(isFullScreen()) {
        showNormal();
        ui->Mixteca->show();
        ui->menubar->setVisible(true);
        ui->telaCheiaAction->setChecked(false);
    }
    else {
        showFullScreen();
        ui->Mixteca->hide();
        ui->menubar->setVisible(false);
        ui->telaCheiaAction->setChecked(true);
    }

}

void disqteca::on_telaCheiaAction_triggered() {
    telaCheia();
}

void disqteca::alternaMenus() {

    if(this->ui->menubar->isVisible()) {
        this->ui->menubar->setVisible(false);
    }
    else {
        this->ui->menubar->setVisible(true);
    }

}

void disqteca::stateChanged(Phonon::State newState, Phonon::State /* oldState */) {

    QPixmap PlayPixmap(":/disqteca/resources/icons/dark/appbar.control.play.png");
    QIcon PlayIcon(PlayPixmap);

    QPixmap PausePixmap(":/disqteca/resources/icons/dark/appbar.control.pause.png");
    QIcon PauseIcon(PausePixmap);

    switch (newState) {
        case Phonon::ErrorState:
            if (mediaObject->errorType() == Phonon::FatalError) {
                QMessageBox::warning(this, tr("Fatal Error"),
                mediaObject->errorString());
            } else {
                QMessageBox::warning(this, tr("Error"),
                mediaObject->errorString());
            }
            break;
//![9]
//![10]
        case Phonon::PlayingState:
                ui->playAction->setChecked(true);
                ui->stopAction->setEnabled(true);
                ui->playToolbarButton->setChecked(false);
                ui->playToolbarButton->setIcon(PauseIcon);
                break;
        case Phonon::StoppedState:
                ui->playAction->setChecked(false);
                ui->stopAction->setEnabled(false);
                ui->playToolbarButton->setChecked(true);
                ui->andamento->setText("00:00");
                ui->playToolbarButton->setIcon(PlayIcon);
                break;
        case Phonon::PausedState:
                ui->playAction->setChecked(false);
                ui->stopAction->setEnabled(true);
                ui->playAction->setEnabled(true);
                ui->playToolbarButton->setChecked(true);
                ui->playToolbarButton->setIcon(PlayIcon);
                break;
//![10]
        case Phonon::BufferingState:
                break;
        default:
            ;
    }
}

void disqteca::tableClicked(int row, int /* column */)
{
    bool wasPlaying = mediaObject->state() == Phonon::PlayingState;

    mediaObject->stop();
    mediaObject->clearQueue();

    if (row >= sources.size())
        return;

    mediaObject->setCurrentSource(sources[row]);

    if (wasPlaying) {
        mediaObject->play();
    }
    else {
        mediaObject->stop();
    }
}

void disqteca::on_Mixteca_cellPressed(int row, int column) {
    tableClicked(row, column);
}

void disqteca::on_playAction_triggered()
{
    if(ui->playAction->isChecked()) {
        mediaObject->play();
    }
    else {
        mediaObject->pause();
    }
}

void disqteca::metaStateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    if (newState == Phonon::ErrorState) {
        QMessageBox::warning(this, tr("Error opening files"),
            metaInformationResolver->errorString());
        while (!sources.isEmpty() &&
               !(sources.takeLast() == metaInformationResolver->currentSource())) {}  /* loop */;
        return;
    }

    if (newState != Phonon::StoppedState && newState != Phonon::PausedState)
        return;

    if (metaInformationResolver->currentSource().type() == Phonon::MediaSource::Invalid)
            return;

    QMap<QString, QString> metaData = metaInformationResolver->metaData();

    QString title = metaData.value("TITLE");
    if (title == "")
        title = metaInformationResolver->currentSource().fileName();

    QTableWidgetItem *titleItem = new QTableWidgetItem(title);
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *artistItem = new QTableWidgetItem(metaData.value("ARTIST"));
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *albumItem = new QTableWidgetItem(metaData.value("ALBUM"));
    albumItem->setFlags(albumItem->flags() ^ Qt::ItemIsEditable);
    QTableWidgetItem *yearItem = new QTableWidgetItem(metaData.value("DATE"));
    yearItem->setFlags(yearItem->flags() ^ Qt::ItemIsEditable);
//![14]

    int currentRow = ui->Mixteca->rowCount();
    ui->Mixteca->insertRow(currentRow);
    ui->Mixteca->setItem(currentRow, 0, titleItem);
    ui->Mixteca->setItem(currentRow, 1, artistItem);
    ui->Mixteca->setItem(currentRow, 2, albumItem);
    ui->Mixteca->setItem(currentRow, 3, yearItem);

//![15]
    if (ui->Mixteca->selectedItems().isEmpty()) {
        ui->Mixteca->selectRow(0);
        mediaObject->setCurrentSource(metaInformationResolver->currentSource());
    }

    Phonon::MediaSource source = metaInformationResolver->currentSource();
    int index = sources.indexOf(metaInformationResolver->currentSource()) + 1;
    if (sources.size() > index) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    }
    else {
        ui->Mixteca->resizeColumnsToContents();
        if (ui->Mixteca->columnWidth(0) > 300)
            ui->Mixteca->setColumnWidth(0, 300);
    }
}

void disqteca::on_stopAction_triggered() {
    mediaObject->stop();
}

void disqteca::on_rewindAction_triggered() {
    qint64 Tempo = mediaObject->currentTime()-4000;
    mediaObject->seek(Tempo);
}

void disqteca::on_forwardAction_triggered() {
    qint64 Tempo = mediaObject->currentTime()+4000;
    mediaObject->seek(Tempo);
}

void disqteca::on_previousAction_triggered() {
    if(sources.indexOf(mediaObject->currentSource()) == 0) {
        tableClicked(0, 0);
        return;
    }
    int MusicaAnterior = sources.indexOf(mediaObject->currentSource());
    --MusicaAnterior;
    tableClicked(MusicaAnterior, MusicaAnterior);
}

void disqteca::on_nextAction_triggered() {

    if(sources.indexOf(mediaObject->currentSource()) == sources.size()-1) {
        tableClicked(0, 0);
        return;
    }

    int ProximaMusica = sources.indexOf(mediaObject->currentSource());
    ++ProximaMusica;
    tableClicked(ProximaMusica, ProximaMusica);

}

void disqteca::on_saveAction_triggered() {

    QString NomeArquivo = QFileDialog::getSaveFileName(this, "salvar mixteca", ".", tr("Mixtecas (*.mix.txt)"));
    if(NomeArquivo.isEmpty()) {
        return;
    }

    std::ofstream out(NomeArquivo.toStdString().c_str());

    for ( int i=0; i < sources.size(); ++i) {
        QString aux = sources[i].fileName();
        out << aux.toStdString() << std::endl;
    }

    out.close();

}

void disqteca::on_openAction_triggered(QString NomeArquivo) {

    if(NomeArquivo.size() < 1) {

        QString Arquivo = QFileDialog::getOpenFileName(this, tr("selecione uma mixteca"), QDesktopServices::storageLocation(QDesktopServices::MusicLocation), "Mixtecas (*.mix.txt)");

        if(Arquivo.size()<1) {
            return;
        }

        else {
            NomeArquivo = Arquivo;
        }

    }

    std::ifstream in(NomeArquivo.toStdString().c_str());

    int index = sources.size();

    if(!in.is_open()) {
        QMessageBox::critical(this, "arquivo inválido", "nao conseguimos abrir o arquivo " + NomeArquivo + ". ele deve estar protegido ou outra pessoa ou programa deve estar usando-o.");
        return;
    }

    //PlaylistsRecentes = NomeArquivo;

    QString Aux;

    while (!in.eof()) {

        std::string Musica;

        std::getline(in, Musica);
        Aux = QString::fromStdString(Musica);

        Phonon::MediaSource Fonte(Aux);
        sources.append(Fonte);

    }

    if (!sources.isEmpty()) {
        metaInformationResolver->setCurrentSource(sources.at(index));
    }

    mediaObject->play();
}

void disqteca::on_playToolbarButton_clicked() {

    if(mediaObject->state() == Phonon::PlayingState) {
        mediaObject->pause();
    }
    else {
        mediaObject->play();
    }

}

void disqteca::on_previousButton_clicked()
{
    ui->previousAction->trigger();
}



void disqteca::on_nextButton_clicked()
{
    ui->nextAction->trigger();
}

void disqteca::on_helpAction_triggered() {
    QUrl ManualQUrl = QUrl("index.html");

    QDesktopServices::openUrl(ManualQUrl);
}
