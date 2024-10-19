#include "friendinfopage.h"
#include "ui_friendinfopage.h"

#include <QDebug>

FriendInfoPage::FriendInfoPage(QWidget* parent) :
	QWidget(parent),
    ui(new Ui::FriendInfoPage), _user_info(nullptr), _video_dlg(nullptr)
{
	ui->setupUi(this);
	ui->msg_chat->SetState("normal", "hover", "press");
	ui->video_chat->SetState("normal", "hover", "press");
	ui->voice_chat->SetState("normal", "hover", "press");
    connect(ui->video_chat, &ClickedBtn::clicked, this, &FriendInfoPage::slotOpenVideoCallDlg);
	qDebug() << "FriendInfoPage Created;";
}

FriendInfoPage::~FriendInfoPage()
{
	qDebug() << "FriendInfoPage deleted;";
	delete ui;
}

void FriendInfoPage::SetInfo(std::shared_ptr<UserInfo> user_info)
{
	_user_info = user_info;
	// 加载图片
	QPixmap pixmap(user_info->_icon);

	// 设置图片自动缩放
	ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	ui->icon_lb->setScaledContents(true);

	ui->name_lb->setText(user_info->_name);
	ui->nick_lb->setText(user_info->_nick);
	ui->bak_lb->setText(user_info->_nick);
}

void FriendInfoPage::on_msg_chat_clicked()
{
	qDebug() << "msg chat btn clicked";
	emit sig_jump_chat_item(_user_info);
}

void FriendInfoPage::slotOpenVideoCallDlg()
{
    auto videoDevices = QMediaDevices::videoInputs().empty();
    auto audioDevices = QMediaDevices::audioInputs().empty();
    if(videoDevices&&audioDevices)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("未检测到音频和视频设备，请添加后再试"));
        msgBox.exec();
        return ;
    }
    if (_video_dlg == nullptr)
    {
        _video_dlg = new VideoCallingDialog();
        connect(_video_dlg, &QDialog::rejected, this, &FriendInfoPage::slotCloseVideoCallDlg);
        _video_dlg->show();
        _video_dlg->raise();
        _video_dlg->activateWindow();
        return;
    }
    _video_dlg->show();
    _video_dlg->raise();
    _video_dlg->activateWindow();

}
void FriendInfoPage::slotCloseVideoCallDlg()
{
    if (_video_dlg)
    {
        delete _video_dlg;
        _video_dlg = nullptr;
    }
}
