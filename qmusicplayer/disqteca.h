#ifndef DISQTECA_H
#define DISQTECA_H

#include <QList>
#include <QMessageBox>
#include <QMainWindow>
#include <Phonon/MediaSource>
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>
#include <Phonon/VideoPlayer>
#include <QSplitter>
#include <QKeyEvent>
#include <QEvent>

namespace Ui {
    class disqteca;
}

class disqteca : public QMainWindow {
    Q_OBJECT
    
public:

    explicit disqteca(QWidget *parent = 0);

    ~disqteca();

    void sobre();

    void telaCheia();

    void alternaMenus();
    
private slots:

    void aboutToFinish();

    void stateChanged(Phonon::State newState, Phonon::State oldState);

    void tick(qint64 time);

    void sourceChanged(const Phonon::MediaSource &source);

    void tableClicked(int row, int column);

    void metaStateChanged(Phonon::State newState, Phonon::State oldState);

    void on_actionSobre_o_disqteca_triggered();

    void on_actionSobre_o_qt_triggered();

    void abrir();

    void on_action_abrir_triggered();

    void on_sairAction_triggered();

    void on_telaCheiaAction_triggered();

    void on_Mixteca_cellPressed(int row, int column);

    void on_playAction_triggered();

    void on_stopAction_triggered();

    void on_rewindAction_triggered();

    void on_forwardAction_triggered();

    void on_previousAction_triggered();

    void on_nextAction_triggered();

    void on_saveAction_triggered();

    void on_openAction_triggered(QString = "");

    void on_playToolbarButton_clicked();

    void on_previousButton_clicked();

    void on_nextButton_clicked();

    void on_helpAction_triggered();

private:

    /**
     * Interface de usuário do disqteca
     * @brief ui
     */
    Ui::disqteca *ui;

    /**
     * Lista com as fontes de mídia
     * @brief sources
     */
    QList<Phonon::MediaSource> sources;

    /**
     * Representa um objeto de mídia
     * @brief mediaObject
     */
    Phonon::MediaObject *mediaObject;

    /**
     * Lida com os metadados da música ou do vídeo
     * @brief metaInformationResolver
     */
    Phonon::MediaObject *metaInformationResolver;

    /**
     * Divisor vertical que permite ajustar tamanho da tela de vídeo e da mixteca
     * @brief LayoutPrincipal
     */
    QSplitter *DivisorVideoMixteca;

    /**
     * Representa a saída de áudio da aplicação
     * @brief audioOutput
     */
    Phonon::AudioOutput *audioOutput;

    /**
     * Representa a saída de vídeo da aplicação
     * @brief videoOutput
     */
    Phonon::VideoPlayer *videoPlayer;

    /**
     * Widget para execução do video
     * @brief videoWidget
     */
    Phonon::VideoWidget *videoWidget;

protected:

    void keyPressEvent(QKeyEvent *e) {
        if(e->key()== Qt::Key_F11 ) {
            telaCheia();
        }
        if(e->key()==Qt::Key_Alt) {
            alternaMenus();
        }
    }

};

#endif // DISQTECA_H
