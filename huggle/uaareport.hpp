//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef UAAREPORT_H
#define UAAREPORT_H

#include "definitions.hpp"
// now we need to ensure that python is included first, because it
// simply suck :P
// seriously, Python.h is shitty enough that it requires to be
// included first. Don't believe it? See this:
// http://stackoverflow.com/questions/20300201/why-python-h-of-python-3-2-must-be-included-as-first-together-with-qt4
#ifdef PYTHONENGINE
#include <Python.h>
#endif

#include <QDialog>
#include <QString>
#include <QtXml>
#include <QTimer>
#include <QUrl>
#include "core.hpp"
#include "configuration.hpp"
#include "wikiuser.hpp"
#include "wikipage.hpp"
#include "apiquery.hpp"

namespace Ui
{
    class UAAReport;
}

namespace Huggle
{
    class WikiUser;
    class WikiPage;
    class ApiQuery;
    //! Form to report users to UAA
    class UAAReport : public QDialog
    {
            Q_OBJECT
        public:
            explicit UAAReport(QWidget *parent = 0);
            ~UAAReport();
            //! I don't have much of a clue why this is here lol, but I know the dialog can't be initialised from mainwindow without this
            void setUserForUAA(WikiUser *user);
        private slots:
            void on_pushButton_clicked();
            void on_pushButton_2_clicked();
            void on_pushButton_3_clicked();
            void onTick();
            void onStartOfSearch();
        private:
            //! Function to decide what we are reporting
            void whatToReport();
            //! Check if user is reported
            bool checkIfReported();
            //! Get page contents (reason for this is above)
            void getPageContents();
            //! Function to that allows us to properly insert what we need to insert
            void insertUsername();
            //! Message box, if anything fails
            void failed(QString reason);
            Ui::UAAReport *ui;
            WikiUser *User;
            QString ContentsOfUAA;
            //! Whole contents of UAA page
            QString dr;
            //! String that represents what is in the line edit
            QString OptionalReason;
            //! UAA template
            QString ta;
            //! Reason for report
            QString UAAReportReason;
            //! Pointer to WikiUser
            WikiPage *page;
            //! Pointer to get UAA contents (we don't want replace the page with our content, do we?)
            ApiQuery *qUAApage;
            //! Timer pointer that allows us to do magical things
            QTimer *uT;
            //! Timer that does other magical things
            QTimer *cuT;
            //! Pointer that also gets UAA contents; this time it is used for checking if a user is reported or not
            ApiQuery *qChUAApage;
    };
}

#endif // UAAREPORT_H
