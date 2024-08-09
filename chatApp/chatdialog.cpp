#include "chatdialog.h"
#include "ui_chatdialog.h"

chatDialog::chatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatDialog),m_state(ChatUIMode::ChatMode), m_mode(ChatUIMode::ChatMode), is_loading(false), _cur_chat_uid(0)
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
    //连接认证添加好友信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_add_auth_friend, this, &chatDialog::slot_add_auth_friend);

    //链接自己认证回复信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_auth_rsp, this,
            &chatDialog::slot_auth_rsp);
    //
    connect(ui->search_candidates_list, &SearchList::sig_jump_chat_item, this,
            &chatDialog::slot_jump_chat_item);
    // 加载联系人
    connect(ui->contacts_list, &ContactUserList::sig_loading_contact_user, this,
            &chatDialog::slot_loading_contact_user);
}

chatDialog::~chatDialog()
{
    delete ui;
}

void chatDialog::addChatFriend()
{

    auto friend_list = UserMgr::GetInstance()->GetChatListPerPage();
    if(friend_list.empty()==false)
    {
        for(auto & friend_ele: friend_list)
        {
            auto find_iter = _chat_items_added.find(friend_ele->_uid);
            if(find_iter!=_chat_items_added.end())
            {
                continue;
            }
            auto * chat_user_wd =new msgCards();
            auto user_info = std::make_shared<UserInfo>(friend_ele);
            chat_user_wd->SetInfo(user_info);
            QListWidgetItem* item = new QListWidgetItem;
            item->setSizeHint(chat_user_wd->sizeHint());
            ui->chatting_friends_list->addItem(item);
            ui->chatting_friends_list->setItemWidget(item, chat_user_wd);
            _chat_items_added.insert(friend_ele->_uid, item);
        }
        UserMgr::GetInstance()->UpdateChatLoadedCount();
    }
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
        auto user_info = std::make_shared<UserInfo>(0,names[name_i],names[name_i], heads[head_i],0, strs[str_i]);
        msgcard ->SetInfo(user_info);
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
    loadMoreChatUser();
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

void chatDialog::slot_loading_contact_user()
{
    qDebug() << "slot loading contact user";
    if(is_loading){
        return;
    }

    is_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug() << "add new data to list.....";
    loadMoreConUser();
    // 加载完成后关闭对话框
    loadingDialog->deleteLater();

    is_loading = false;
}

void chatDialog::slot_apply_friend(std::shared_ptr<AddFriendApply> apply)
{
    qDebug() << "receive apply friend slot, applyuid is " << apply->_from_uid << " name is "
             << apply->_name << " desc is " << apply->_desc;

    bool b_already = UserMgr::GetInstance()->AlreadyApply(apply->_from_uid);
    if(b_already){
        return;
    }
    std::shared_ptr<ApplyInfo> app = std::make_shared<ApplyInfo>(apply);
    UserMgr::GetInstance()->AddApplyList(app);
    ui->side_contact_wd->ShowRedPoint(true);
    ui->contacts_list->ShowRedPoint(true);
    ui->friend_apply_page->AddNewApply(apply);
}

void chatDialog::slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info)
{
    qDebug() << "receive slot_add_auth__friend uid is " << auth_info->_uid
             << " name is " << auth_info->_name << " nick is " << auth_info->_nick;

    //判断如果已经是好友则跳过
    auto bfriend = UserMgr::GetInstance()->CheckFriendById(auth_info->_uid);
    if(bfriend){
        return;
    }

    UserMgr::GetInstance()->AddFriend(auth_info);

    int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
    int str_i = randomValue % strs.size();
    int head_i = randomValue % heads.size();
    int name_i = randomValue % names.size();

    auto* chat_user_wid = new msgCards();
    auto user_info = std::make_shared<UserInfo>(auth_info);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatting_friends_list->insertItem(0, item);
    ui->chatting_friends_list->setItemWidget(item, chat_user_wid);
    _chat_items_added.insert(auth_info->_uid, item);
}

void chatDialog::slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp)
{
    qDebug() << "receive slot_auth_rsp uid is " << auth_rsp->_uid
             << " name is " << auth_rsp->_name << " nick is " << auth_rsp->_nick;

    //判断如果已经是好友则跳过
    auto bfriend = UserMgr::GetInstance()->CheckFriendById(auth_rsp->_uid);
    if(bfriend){
        return;
    }

    UserMgr::GetInstance()->AddFriend(auth_rsp);
    int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
    int str_i = randomValue % strs.size();
    int head_i = randomValue % heads.size();
    int name_i = randomValue % names.size();

    auto* chat_user_wid = new msgCards();
    auto user_info = std::make_shared<UserInfo>(auth_rsp);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatting_friends_list->insertItem(0, item);
    ui->chatting_friends_list->setItemWidget(item, chat_user_wid);
    _chat_items_added.insert(auth_rsp->_uid, item);
}

void chatDialog::slot_jump_chat_item(std::shared_ptr<SearchInfo> si)
{
    qDebug() << "slot jump chat item";
    auto find_iter = _chat_items_added.find(si->_uid);
    if(find_iter!=_chat_items_added.end())
    {
        qDebug() << "jump to chat item, uid: " << si->_uid;
        ui->chatting_friends_list->scrollToItem(find_iter.value());
        ui->side_chat_wd->SetSelected(true);
        SetSelectChatItem(si->_uid);
        SetSelectChatPage(si->_uid);
        slot_side_chat();
        return ;
    }
    auto* chat_user_wid = new msgCards();
    auto user_info = std::make_shared<UserInfo>(si);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatting_friends_list->insertItem(0, item);
    ui->chatting_friends_list->setItemWidget(item, chat_user_wid);

    _chat_items_added.insert(si->_uid, item);

    ui->side_chat_wd->SetSelected(true);
    SetSelectChatItem(si->_uid);
    //更新聊天界面信息
    SetSelectChatPage(si->_uid);
    slot_side_chat();
}
void chatDialog::SetSelectChatItem(int uid)
{
    if(ui->chatting_friends_list->count() <= 0){
        return;
    }

    if(uid == 0){
        ui->chatting_friends_list->setCurrentRow(0);
        QListWidgetItem *firstItem = ui->chatting_friends_list->item(0);
        if(!firstItem){
            return;
        }

        //转为widget
        QWidget *widget = ui->chatting_friends_list->itemWidget(firstItem);
        if(!widget){
            return;
        }

        auto con_item = qobject_cast<msgCards*>(widget);
        if(!con_item){
            return;
        }

        _cur_chat_uid = con_item->GetUserInfo()->_uid;

        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        qDebug() << "uid " <<uid<< " not found, set curent row 0";
        ui->chatting_friends_list->setCurrentRow(0);
        return;
    }

    ui->chatting_friends_list->setCurrentItem(find_iter.value());

    _cur_chat_uid = uid;
}

void chatDialog::SetSelectChatPage(int uid)
{
    if( ui->chatting_friends_list->count() <= 0){
        return;
    }

    if (uid == 0) {
        auto item = ui->chatting_friends_list->item(0);
        //转为widget
        QWidget* widget = ui->chatting_friends_list->itemWidget(item);
        if (!widget) {
            return;
        }

        auto con_item = qobject_cast<msgCards*>(widget);
        if (!con_item) {
            return;
        }

        //设置信息
        auto user_info = con_item->GetUserInfo();
        ui->chat_page->SetUserInfo(user_info);
        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        return;
    }

    //转为widget
    QWidget *widget = ui->chatting_friends_list->itemWidget(find_iter.value());
    if(!widget){
        return;
    }

    //判断转化为自定义的widget
    // 对自定义widget进行操作， 将item 转化为基类ListItemBase
    ListBaseItem *customItem = qobject_cast<ListBaseItem*>(widget);
    if(!customItem){
        qDebug()<< "qobject_cast<ListItemBase*>(widget) is nullptr";
        return;
    }

    auto itemType = customItem->GetItemType();
    if(itemType == ListItemType::CHAT_FRIEND_ITEM){
        auto con_item = qobject_cast<msgCards*>(customItem);
        if(!con_item){
            return;
        }

        //设置信息
        auto user_info = con_item->GetUserInfo();
        ui->chat_page->SetUserInfo(user_info);

        return;
    }

}

void chatDialog::loadMoreChatUser()
{
    auto friend_list = UserMgr::GetInstance()->GetChatListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto find_iter = _chat_items_added.find(friend_ele->_uid);
            if(find_iter != _chat_items_added.end()){
                continue;
            }
            auto *chat_user_wid = new msgCards();
            auto user_info = std::make_shared<UserInfo>(friend_ele);
            chat_user_wid->SetInfo(user_info);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->chatting_friends_list->addItem(item);
            ui->chatting_friends_list->setItemWidget(item, chat_user_wid);
            _chat_items_added.insert(friend_ele->_uid, item);
        }

        //更新已加载条目
        UserMgr::GetInstance()->UpdateChatLoadedCount();
    }
}

void chatDialog::loadMoreConUser()
{
    auto friend_list = UserMgr::GetInstance()->GetConListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto *chat_user_wid = new ConUserItem();
            chat_user_wid->SetInfo(friend_ele->_uid,friend_ele->_name,
                                   friend_ele->_icon);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->contacts_list->addItem(item);
            ui->contacts_list->setItemWidget(item, chat_user_wid);
        }

        //更新已加载条目
        UserMgr::GetInstance()->UpdateContactLoadedCount();
    }
}

void chatDialog::slot_side_chat()
{
    qDebug()<< "receive side chat clicked";
    ClearLabelState(ui->side_chat_wd);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    m_state = ChatUIMode::ChatMode;
    showSearch(false);
}


