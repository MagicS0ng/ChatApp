#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
class SearchInfo
{
public:
    SearchInfo(int uid, QString name, QString nick, QString des, int gender);
    int _uid;
    QString _name;
    QString _nick;
    QString _desc;
    int _gender;
};

#endif // USERDATA_H
