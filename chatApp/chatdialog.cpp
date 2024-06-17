#include "chatdialog.h"
#include "ui_chatdialog.h"

chatDialog::chatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatDialog),m_state(ChatUIMode::ChatMode), m_mode(ChatUIMode::ChatMode), is_loading(false)
{
    ui->setupUi(this);
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
    showSearch(false);
    connect(ui->chatting_friends_list, &ChattingFriendsList::sigLoadingChatFriends, this, &chatDialog::slotLoadingChatFriends);
    addChatFriend();
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

void chatDialog::slotLoadingChatFriends()
{
    if(is_loading)
    {
        return ;
    }
    is_loading=true;
    loadingDialog * loading_dlg =  new loadingDialog(this);
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
