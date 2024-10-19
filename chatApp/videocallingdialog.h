#ifndef VIDEOCALLINGDIALOG_H
#define VIDEOCALLINGDIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraDevice>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QMessageBox>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QTimer>
namespace Ui {
class VideoCallingDialog;
}

class VideoCallingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VideoCallingDialog(QWidget *parent = nullptr);
    ~VideoCallingDialog();
// protected:
    // void showEvent(QShowEvent *ev) override;
private slots:
    void on_toggle_audio_btn_toggled(bool checked);
    void on_toggle_video_btn_toggled(bool checked);
    void on_hang_up_clicked();

private:
    Ui::VideoCallingDialog *ui;
    QList<QCameraDevice> _cameras;
    QList<QAudioDevice> _audios;
    QCamera *_camera;
    QMediaCaptureSession *_captureSession;
    QVideoWidget *_videoWidget;
    bool is_hang_up;
    bool is_video_on;
    bool is_audio_on;
    int _avatarSize;
private:
    void adjustAvatarPos(QWidget*, QLabel *, bool);


};

#endif // VIDEOCALLINGDIALOG_H
