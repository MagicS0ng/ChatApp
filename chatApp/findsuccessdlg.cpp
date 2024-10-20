#include "applyfriend.h"
#include "findsuccessdlg.h"
#include "ui_findsuccessdlg.h"

FindSuccessDlg::FindSuccessDlg(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindSuccessDlg), _parent(parent)
{
    ui->setupUi(this);
    setWindowTitle("Add");
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    QString app_path = QCoreApplication::applicationDirPath();
    QString pix_map = QDir::toNativeSeparators(app_path+ QDir::separator()+"static"+QDir::separator()+"head_1.jpg");
    QPixmap pxMap(pix_map);
    pxMap = pxMap.scaled(ui->head_lb->size(), Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->head_lb->setPixmap(pxMap);
    ui->add_friend_btn->SetState("normal", "hover","press");
    this->setModal(true);
}

FindSuccessDlg::~FindSuccessDlg()
{
    qDebug() << "FindSuccessDlg destruct";
    delete ui;
}

void FindSuccessDlg::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    ui->name_lb->setText(si->_name);
    _si = si;
}

void FindSuccessDlg::on_add_friend_btn_clicked()
{
    qDebug() << "find success";
    this->hide();
    auto applyFriend = new ApplyFriend(_parent);
    applyFriend->SetSearchInfo(_si);
    applyFriend->setModal(true);
    applyFriend->show();
}

