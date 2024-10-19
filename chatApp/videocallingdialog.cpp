#include "videocallingdialog.h"
#include "ui_videocallingdialog.h"


VideoCallingDialog::VideoCallingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VideoCallingDialog), is_hang_up(false), is_video_on(false), is_audio_on(true),
    _camera(nullptr), _captureSession(new QMediaCaptureSession(this))

{
    setFixedSize(420,680);
    ui->setupUi(this);
    auto * manager = new QMediaDevices(this);
    _cameras = QMediaDevices::videoInputs();
    _audios = QMediaDevices::audioInputs();
    ui->local_video->hide();
    ui->remote_video->setFixedSize(400,560);
    ui->remote_avatar->move(200,280);
    QPixmap avtar_pxmap(":/duckduckgo-logo-png-19.png");
    ui->toggle_video_btn->setCheckable(true);
    // ui->toggle_video_btn->t
    ui->toggle_audio_btn->setCheckable(true);
    connect(manager, &QMediaDevices::videoInputsChanged, this,[this](){
        _cameras = QMediaDevices::videoInputs();
    }); //实时检测USB，
    connect(manager, &QMediaDevices::audioInputsChanged, this,[this](){
        _cameras = QMediaDevices::videoInputs();
    }); //实时检测USB，
    ui->toggle_audio_btn->toggle();
    ui->remote_avatar->setPixmap(avtar_pxmap.scaled(ui->remote_avatar->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->hang_up->SetIcon(":/resourse/hang-up-svgrepo-com.svg");
    ui->hang_up->setStyleSheet("#hang_up{ background: #a90e0e; border: 2px solid #a90e0e; border-radius:40px;}");
    ui->toggle_audio_btn->SetIcon(":/resourse/microphone-svgrepo-com.svg");
    ui->toggle_video_btn->SetIcon(":/resourse/video-slash-svgrepo-com.svg");
}

VideoCallingDialog::~VideoCallingDialog()
{
    if(_camera)
    {
        _camera->stop();
        delete _camera;
        _camera=nullptr;
    }
    delete _captureSession;
    // delete _videoWidget;
    delete ui;
}

// void VideoCallingDialog::showEvent(QShowEvent *ev)
// {

// }
void VideoCallingDialog::on_toggle_audio_btn_toggled(bool checked)
{
    is_audio_on = checked;
    if(is_audio_on)
    {
        if(_audios.empty())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("未检测到音频设备，请添加后再试"));
            msgBox.exec();
            ui->toggle_audio_btn->setChecked(!checked);
            is_audio_on = !is_audio_on;
            return ;
        }
        ui->toggle_audio_btn->SetIcon(":/resourse/microphone-svgrepo-com.svg");
        return ;
    }
    ui->toggle_audio_btn->SetIcon(":/resourse/microphone-off-svgrepo-com.svg");
}

void VideoCallingDialog::on_toggle_video_btn_toggled(bool checked)
{

    is_video_on = checked;
    if(is_video_on)
    {
        if(_cameras.empty())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("未检测到视频设备，请添加后再试"));
            is_video_on = !is_video_on;
            msgBox.exec();
            ui->toggle_video_btn->setChecked(!checked);
            return ;
        }
        ui->toggle_video_btn->SetIcon(":/resourse/video-svgrepo-com.svg");
        if(!_cameras.isEmpty())
        {
            _videoWidget = new QVideoWidget(ui->local_video);
            QTimer::singleShot(100, this, [this](){_videoWidget->setFixedSize(ui->local_video->size());});
            QCameraDevice cameraDevice = _cameras.first();
            _camera = new QCamera(cameraDevice, this);
            _captureSession->setCamera(_camera);
            _captureSession->setVideoOutput(_videoWidget);
            _camera->start();
        }
        // adjustAvatarPos(ui->local_video,ui->local_avatar,true);
        // adjustAvatarPos(ui->remote_video,ui->remote_avatar,true);
        ui->local_video->show();
        ui->local_avatar->hide();
        ui->local_video->setFixedSize(400,560);
        ui->remote_video->setFixedSize(400,560);
        setFixedSize(840,680);
        if(ui->local_avatar->pixmap().isNull())
            ui->local_avatar->setPixmap(QPixmap(":/resourse/icon.png").scaled(ui->local_avatar->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
        return ;
    }
    // if(_camera)
    // {
    //     _camera->stop();
    //     delete _camera;
    //     _camera = nullptr;
    // }
    // adjustAvatarPos(ui->local_video,ui->local_avatar,false);
    // adjustAvatarPos(ui->remote_video,ui->remote_avatar,false);
    ui->local_video->hide();
    ui->local_avatar->hide();
    setFixedSize(420,680);
    ui->remote_video->setFixedSize(400,560);
    ui->toggle_video_btn->SetIcon(":/resourse/video-slash-svgrepo-com.svg");
}
void VideoCallingDialog::on_hang_up_clicked()
{
    is_hang_up = true;
    emit QDialog::rejected();
}

void VideoCallingDialog::adjustAvatarPos(QWidget *videoWidget, QLabel * avatarLabel, bool videoOn)
{
    _avatarSize = videoOn?50:160;
    avatarLabel->setFixedSize(_avatarSize, _avatarSize);

    if (videoOn)
    {
        // 当视频打开时，将头像放置在视频窗口的左下角
        QRect videoGeometry = videoWidget->geometry();
        int x = videoGeometry.x() + 10;  // 左下角留10px的边距
        int y = videoGeometry.y() + videoGeometry.height() - _avatarSize - 10;  // 下边留10px的边距
        avatarLabel->move(x, y);
    }
    else
    {
        int x = videoWidget->width()/2;
        int y = videoWidget->height()/2;
        // 当视频关闭时，将头像恢复到原来的位置
        avatarLabel->move(x, y);  // 恢复到原始位置，假设为窗口的左上角
    }

    avatarLabel->raise();  // 确保头像显示在上层
}

