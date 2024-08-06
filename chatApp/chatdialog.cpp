#include "chatdialog.h"
#include "ui_chatdialog.h"

chatDialog::chatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatDialog),m_state(ChatUIMode::ChatMode), m_mode(ChatUIMode::ChatMode), is_loading(false)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()|Qt::FramelessWindowHint);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->add_btn->SetState("normal","hover","press");
    ui->add_btn->setProperty("state", "normal");
    ui->search_box->SetMaxLength(15);
    QAction *searchAction = new QAction(ui->search_box);
    searchAction->setIcon(QIcon(":/resourse/search.png"));
    ui->search_box->addAction(searchAction, QLineEdit::LeadingPosition);
    ui->search_box->setPlaceholderText(QStringLiteral("Search..."));

    QAction *clearAction = new QAction(ui->search_box);
    clearAction->setIcon(QIcon(":/resourse/close_transparent.png"));
    ui->search_box->addAction(clearAction, QLineEdit::TrailingPosition);
    connect(ui->search_box, &QLineEdit::textChanged, [clearAction](const QString &text)
        {
        if(!text.isEmpty())
        {
            clearAction->setIcon(QIcon(":/resourse/close_search.png"));
        }
        else
            {
            clearAction->setIcon(QIcon(":/resourse/close_transparent.png"));
        }
    });
    connect(clearAction, &QAction::triggered,[this, clearAction]{
        ui->search_box->clear();
        clearAction->setIcon(QIcon(":/resourse/close_transparent.png"));
        ui->search_box->clearFocus();
        showSearch(false);
    });
    ui->search_box->SetMaxLength(15);
    showSearch(false);
    connect(ui->chatting_friends_list, &ChattingFriendsList::sigLoadingChatFriends, this, &chatDialog::slotLoadingChatFriends);
    addChatFriend();
    QPixmap pixmap(":/resourse/head_1.jpg");
    ui->side_avat_lb->setPixmap(pixmap);
    QPixmap scaledPixmap = pixmap.scaled(ui->side_avat_lb->size(), Qt::KeepAspectRatio);
    ui->side_avat_lb->setPixmap(scaledPixmap);
    ui->side_avat_lb->setScaledContents(true);

    ui->side_chat_wd->setProperty("state", "normal");
    ui->side_contact_wd->setProperty("state", "normal");
    ui->side_chat_wd->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    ui->side_contact_wd->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    AddLBGroup(ui->side_chat_wd);
    AddLBGroup(ui->side_contact_wd);

    connect(ui->side_chat_wd,&StateWidget::clicked,this, &chatDialog::SlotSideChat);
    connect(ui->side_contact_wd,&StateWidget::clicked,this, &chatDialog::SlotSideContact);

    connect(ui->search_box,&QLineEdit::textChanged,this, &chatDialog::slotTextChanged);
    this->installEventFilter(this);
    ui->side_chat_wd->SetSelected(true);
    ui->search_candidates_list->SetSearchBox(ui->search_box);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_friend_apply, this, &chatDialog::slot_apply_friend);
}

chatDialog::~chatDialog()
{
    delete ui;
}

void chatDialog::addChatFriend()
{
    std::vector<QString> names= {"C++","Python","Rust","Pytorch","Tensorflow"};
    std::vector<QString> heads= {
        ":/resourse/head_1.jpg",
        ":/resourse/head_2.jpg",
        ":/resourse/head_3.jpg",
        ":/resourse/head_4.jpg",
        ":/resourse/head_5.jpg"
    };
    std::vector<QString> strs= {
        "你妈贵姓",
        "两开花",
        "Keep going!",
        "不宜妄自菲薄",
        "Be sure of yourself!"
    };
    for(int i  =0;i<13;i++)
    {
        int randomValue = QRandomGenerator::global()->bounded(100);
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();


        auto * msgcard = new msgCards();
        msgcard ->SetInfo(names[name_i],heads[head_i],strs[str_i]);
        QListWidgetItem * item = new QListWidgetItem;
        item->setSizeHint(msgcard->sizeHint());
        ui->chatting_friends_list->addItem(item);
        ui->chatting_friends_list->setItemWidget(item, msgcard);
    }
}

void chatDialog::ClearLabelState(StateWidget *lb)
{
    for(auto & ele: _lb_list)
    {
        if(ele==lb)
        {
            continue;
        }
        ele->ClearState();
    }
}

bool chatDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        QMouseEvent * mouseEvent = static_cast<QMouseEvent *>(event);
        handleGlobalMousePress(mouseEvent);
    }
    return QDialog::eventFilter(watched,event);

}

void chatDialog::handleGlobalMousePress(QMouseEvent * event)
{
    if(m_mode!=ChatUIMode::SearchMode)
    {
        return ;
    }
    QPoint posInSearchList = ui->search_candidates_list->mapFromGlobal(event->globalPosition().toPoint());
    if(!ui->search_candidates_list->rect().contains(posInSearchList))
    {
        ui->search_box->clear();
        showSearch(false);
    }
}

void chatDialog::showSearch(bool isSearch)
{
    if(isSearch)
    {
        ui->chatting_friends_list->hide();
        ui->contacts_list->hide();
        ui->search_candidates_list->show();
        m_mode = ChatUIMode::SearchMode;
    }else if(m_state==ChatUIMode::ChatMode)
    {
        ui->chatting_friends_list->show();
        ui->contacts_list->hide();
        ui->search_candidates_list->hide();
        m_mode = ChatUIMode::ChatMode;
    }else if(m_state==ChatUIMode::ContactMode)
    {
        ui->chatting_friends_list->hide();
        ui->contacts_list->show();
        ui->search_candidates_list->hide();
        m_mode = ChatUIMode::ContactMode;
    }

}

void chatDialog::AddLBGroup(StateWidget *lb)
{
    _lb_list.push_back(lb);
}

void chatDialog::slotLoadingChatFriends()
{
    if(is_loading)
    {
        return ;
    }
    is_loading=true;
    LoadingDlg * loading_dlg =  new LoadingDlg(this);
    loading_dlg->setModal(true);
    loading_dlg->show();
    qDebug() << "add new msg cards...";
    addChatFriend();
    loading_dlg->deleteLater();
    is_loading = false;

}

void chatDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        event->ignore();
        return;
    }
    QDialog::keyPressEvent(event);

}

void chatDialog::SlotSideChat()
{
    qDebug() << "side chat clicked, switch to side chat";
    ClearLabelState(ui->side_chat_wd);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    m_state = ChatUIMode::ChatMode;
    showSearch(false);
}

void chatDialog::SlotSideContact()
{
    qDebug() << "side contact clicked, switch to side contact";
    ClearLabelState(ui->side_contact_wd);
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
    m_state=ChatUIMode::ContactMode;
    showSearch(false);
}

void chatDialog::slotTextChanged(const QString &str)
{
    if(!str.isEmpty())
    {
        showSearch(true);
    }
}

void chatDialog::slot_apply_friend(std::shared_ptr<AddFriendApply> apply)
{
    qDebug() << "receive apply friend slot, applyuid is " << apply->_from_uid << " name is "
             << apply->_name << " desc is " << apply->_desc;

    bool b_already = UserMgr::GetInstance()->AlreadyApply(apply->_from_uid);
    if(b_already){
        return;
    }

    // UserMgr::GetInstance()->AddApplyList(std::make_shared<ApplyInfo>(apply));
    // ui->side_contact_lb->ShowRedPoint(true);
    // ui->con_user_list->ShowRedPoint(true);
    ui->friend_apply_page->AddNewApply(apply);
}


