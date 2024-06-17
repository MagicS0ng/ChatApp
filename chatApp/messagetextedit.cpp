#include "messagetextedit.h"

MessageTextEdit::MessageTextEdit(QWidget *parent):QTextEdit(parent)
{
    this->setMaximumHeight(60);
}
MessageTextEdit::~MessageTextEdit()
{

}
QVector<MsgInfo> MessageTextEdit::getMsgList()
{
    m_getMsgList.clear();
    QString doc =this->document()->toPlainText();
    QString text = "";
    int indexUrl = 0;
    int count = m_msgList.size();
    for(int idx= 0;idx<doc.size();idx++)
    {
        if(doc[idx]==QChar::ObjectReplacementCharacter)
        {
            if(!text.isEmpty())
            {
                QPixmap pix;
                insertMsgList(m_getMsgList, "text", text, pix);
                text.clear();
            }
            while(indexUrl<count)
            {
                MsgInfo msg = m_msgList[indexUrl];
                if(this->document()->toHtml().contains(msg.contents, Qt::CaseSensitive))
                {
                    indexUrl++;
                    m_getMsgList.append(msg);
                    break;
                }
                indexUrl++;
            }
        }
        else
        {
            text.append(doc[idx]);

        }
    }
    if(!text.isEmpty())
    {
        QPixmap pix;
        insertMsgList(m_getMsgList, "text", text,pix);
    }
    m_msgList.clear();
    return m_getMsgList;
}

void MessageTextEdit::insertFileFromUrl(const QStringList &urls)
{
    if(urls.isEmpty())
    {
        return ;
    }
    foreach (QString url, urls) {
        if(isImage(url))
        {
            insertImages(url);
        }
        else
        {
            insertTextFile(url);
        }
    }
}

void MessageTextEdit::dragEnterEvent(QDragEnterEvent *ev)
{
    if(ev->source()==this)
        ev->ignore();
    else
        ev->accept();
}

void MessageTextEdit::dropEvent(QDropEvent *ev)
{
    insertFromMimeData(ev->mimeData());
    ev->accept();
}

void MessageTextEdit::keyPressEvent(QKeyEvent *e)
{
    if((e->key()==Qt::Key_Enter||e->key()==Qt::Key_Return)&&!(e->modifiers()&Qt::ShiftModifier))
    {
        emit send();
        return ;
    }
    QTextEdit::keyPressEvent(e);
}

void MessageTextEdit::insertImages(const QString &url)
{
    QImage image(url);
    if(image.width()>120||image.height()>80)
    {
        if(image.width()>image.height())
        {
            image = image.scaledToHeight(120,Qt::SmoothTransformation);
        }            else
        {
            image = image.scaledToHeight(80, Qt::SmoothTransformation);
        }
    }
    QTextCursor cursor = this->textCursor();
    cursor.insertImage(image, url);
    insertMsgList(m_msgList,"image", url, QPixmap::fromImage(image));
}

void MessageTextEdit::insertTextFile(const QString &url)
{
    QFileInfo fileInfo(url);
    if(fileInfo.isDir())
    {
        QMessageBox::information(this, "However, ","one file is allowd once");
        return;
    }
    if(fileInfo.size()>100*1024*1024)
    {
        QMessageBox::information(this, "However, ","file more than 100 MB is not allowed to send");
        return;
    }
    QPixmap pix = getFileIconPixmap(url);
    QTextCursor cursor = this->textCursor();
    cursor.insertImage(pix.toImage(),url);
    insertMsgList(m_msgList, "file", url,pix);
}

bool MessageTextEdit::canInsertFromMimeData(const QMimeData *source) const
{
    return QTextEdit::canInsertFromMimeData(source);
}

void MessageTextEdit::insertFromMimeData(const QMimeData *source)
{
    QStringList urls = getUrl(source->text());
    if(urls.isEmpty())
    {
        return ;
    }
    foreach (QString url, urls)
    {
        if(isImage(url))
            insertImages(url);
        else
            insertTextFile(url);
    }

}

bool MessageTextEdit::isImage(QString url)
{
    QString imageFormat = "bmp,jpg,png,tif,git,pcx,tga,exif,fpx,svg,psd,cdr,pcd,dxf,ufo,eps,ai,raw,wmf,webp";
    QStringList imageFormatList = imageFormat.split(",");
    QFileInfo fileInfo(url);
    QString suffix = fileInfo.suffix();
    if(imageFormatList.contains(suffix, Qt::CaseInsensitive))
    {
        return true;
    }
    return false;
}

void MessageTextEdit::insertMsgList(QVector<MsgInfo> &list, QString flag, QString text, QPixmap pix)
{
    MsgInfo msg;
    msg.msgFlag=flag;
    msg.contents = text;
    msg.pixMap = pix;
    list.append(msg);
}

QStringList MessageTextEdit::getUrl(QString text)
{
    QStringList urls;
    if(text.isEmpty())
        return urls;
    QStringList list = text.split("\n");
    foreach(QString url, list)
    {
        if(!url.isEmpty())
        {
            QStringList str = url.split("///");
            if(str.size()>=2)
            {
                urls.append(str.at(1));
            }
        }
    }
    return urls;
}

QPixmap MessageTextEdit::getFileIconPixmap(const QString &url)
{
    QFileIconProvider provider;
    QFileInfo fileinfo(url);
    QIcon icon = provider.icon(fileinfo);
    QString strFileSize = getFileSize(fileinfo.size());
    QFont font(QString("宋体"), 10, QFont::Normal, false);
    QFontMetrics fontMetrx(font);
    QSize textSize = fontMetrx.size(Qt::TextSingleLine, fileinfo.fileName());
    QSize fileSize = fontMetrx.size(Qt::TextSingleLine, strFileSize);
    int maxWidth = textSize.width()>fileSize.width()?textSize.width():fileSize.width();
    QPixmap pix(50 + maxWidth + 10, 50);
    pix.fill();
    QPainter painter;
    painter.begin(&pix);
    QRect rect(0,0,50,50);
    painter.drawPixmap(rect, icon.pixmap(40,40));
    painter.setPen(Qt::black);
    QRect rectText(50+10,3,textSize.width(), textSize.height());
    painter.drawText(rectText, fileinfo.fileName());
    QRect rectFile(50+10, textSize.height()+5, fileSize.width(), fileSize.height());
    painter.drawText(rectFile, strFileSize);
    painter.end();
    return pix;

}

QString MessageTextEdit::getFileSize(qint64 size)
{
    QString unit;
    double num;
    if(size < 1024)
    {
        num = size;
        unit = "B";
    }
    else if(size < 1024*1024)
    {
        num = size / 1024.0;
        unit = "KB";
    }
    else if(size < 1024*1024*1024)
    {
        num = size / 1024.0 / 1024.0;
        unit = "MB";
    }
    else
    {
        num = size / 1024.0/1024.0/1024.0;
        unit = "GB";
    }
    return QString::number(num,'f',2) + " " + unit;
}
void MessageTextEdit::textEditChanged()
{

}
