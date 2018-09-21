// albert - a simple application launcher for linux
// Copyright (C) 2014-2017 Manuel Schneider

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QStringList>
#include <QVariant>
#include <QSqlQuery>
#include "history.h"


Core::History::History(QObject *parent) : QObject(parent) {
    QSqlQuery query("SELECT input "
                    "FROM activation a JOIN  query q ON a.query_id = q.id "
                    "GROUP BY input  "
                    "ORDER BY max(timestamp) DESC;");
    while (query.next())
        lines_.append(query.value(0).toString());

    currentLine_ = -1; // This means historymode is not active
}


/** ***************************************************************************/
void Core::History::add(QString str) {
    if (!str.isEmpty()){
        if (lines_.contains(str))
            lines_.removeAll(str); // Remove dups
        lines_.prepend(str);
    }
}


/** ***************************************************************************/
QString Core::History::next() {
    if (currentLine_+1 < static_cast<int>(lines_.size())
            && static_cast<int>(lines_.size())!=0 ) {
        ++currentLine_;
        return lines_[currentLine_];
    } else return QString();
}


/** ***************************************************************************/
QString Core::History::prev() {
    if (0 < currentLine_) {
        --currentLine_;
        return lines_[currentLine_];
    } else return QString();
}


/** ***************************************************************************/
void Core::History::resetIterator() {
    currentLine_ = -1;
}
