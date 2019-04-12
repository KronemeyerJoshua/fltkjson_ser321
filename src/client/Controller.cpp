#include "Controller.hpp"
#include "MessageGui.hpp"
#include "stubclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Check_Browser.H>
#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <vector>

/**
 * Copyright (c) 2019 Tim Lindquist, Joshua Kronemeyer
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ FLTK client UI for Message management.
 * This class extends the Gui component class MessageGui and demonstrates
 * sample control functions that respond to button clicks drop-down selects.
 * This software is meant to run on Linux and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering,
 *                       IAFSE, ASU at the Polytechnic campus
 * @author Kronemyer, Joshua (jkroneme@asu.edu)
 * @file    Controller.cpp
 * @date    March, 2019
 **/

/** ClickedX is one of the callbacks for GUI controls.
 * Callbacks need to be static functions. But, static functions
 * cannot directly access instance data. This program uses "userdata"
 * to get around that by passing the instance to the callback
 * function. The callback then accesses whatever GUI control object
 * that it needs for implementing its functionality.
 */

/**
 * @brief      Constructs SampleStudentClient and sets up callback for fltk buttons
 *
 * @param[in]  name  userId passed to client
 */

SampleStudentClient::SampleStudentClient(const char *name, std::string host, std::string user) : MessageGui(name)
{
    sendButt->callback(ClickedSend, (void *)this);
    getButt->callback(ClickedGet, (void *)this);
    deleteButt->callback(ClickedDelete, (void *)this);
    replyButt->callback(ClickedReply, (void *)this);
    headerFCB->callback(SelectedHeader, (void *)this);
    headerFCB->when(FL_WHEN_CHANGED);
    hostId = host;
    userId = user;
    // See const in Controller.hpp
    callback(ClickedX);
}


void SampleStudentClient::ClickedSend(Fl_Widget *w, void *userdata) {
    // Basic Static GUI Element Initilization
    SampleStudentClient *anInstance = (SampleStudentClient *)userdata;
    Fl_Multiline_Input *messageFMI = anInstance->messageFMI;
    Fl_Input *dateFI = anInstance->dateFI;
    Fl_Input *subjectFI = anInstance->subjectFI;
    Fl_Input *toFI = anInstance->toFI;
    Fl_Input *fromFI = anInstance->fromFI;
    Fl_Check_Browser *headers = anInstance->headerFCB;
    std::string userId = anInstance->userId;
    std::ostringstream stringBuilder;
    jsonrpc::HttpClient hc(anInstance->hostId);
    StubClient sc(hc, jsonrpc::JSONRPC_CLIENT_V2);
    sc.login(userId);

    stringBuilder << fromFI->value() << " " << dateFI->value();
    Json::Value msgDetails;
    msgDetails["date"] = dateFI->value();
    msgDetails["message"] = messageFMI->value();
    msgDetails["messageFrom"] = fromFI->value();
    msgDetails["messageTo"] = toFI->value();
    msgDetails["subject"] = subjectFI->value();

    //std::cout << msg. << std::endl;

    sc.sendMessage(msgDetails, stringBuilder.str());
}

/**
 * @brief      Exits Program
 *
 * @param      w         ftlk
 * @param      userdata  The userdata
 */
void SampleStudentClient::ClickedX(Fl_Widget *w, void *userdata)
{
    exit(1);
}


/**
 * @brief      ListenerAction for Reply Button
 *
 * @param      w         fltk Widget
 * @param      userdata  The userdata
 */
void SampleStudentClient::ClickedReply(Fl_Widget *w, void *userdata)
{
    // Basic Static GUI Element Initilization
    SampleStudentClient *anInstance = (SampleStudentClient *)userdata;
    Fl_Multiline_Input *messageFMI = anInstance->messageFMI;
    Fl_Input *dateFI = anInstance->dateFI;
    Fl_Input *subjectFI = anInstance->subjectFI;
    Fl_Input *toFI = anInstance->toFI;
    Fl_Input *fromFI = anInstance->fromFI;
    Fl_Check_Browser *headers = anInstance->headerFCB;

    // Values we require for grabbing message data
    int which = headers->value();
    std::ostringstream stringBuilder;
    std::string userId = anInstance->userId;
    jsonrpc::HttpClient hc(anInstance->hostId);
    StubClient sc(hc, jsonrpc::JSONRPC_CLIENT_V2);
    sc.login(userId);
    /*
    * !IMPORTANT!
    * There is a bug with ftlk, the call headers->value doesn't return the checked element, but the SELECTED element
    * Which means setting a box to "checked" in code can cause FL_Check_Browser->value to equal 0, but FL_Check_Browser->nchecked() to equal one
    * It will not update until the user has SELECTED an element, this appears to only occur at the start of the program and can cause it to crash if not dealt with
    * The code here assumes the user has booted the client and is attempting to reply to the first email after pressing "get"
    */
    if (which == 0 && headers->nchecked() == 1)
    {
        which = 1;
    }
    if (headers->nitems() > 0 && headers->nchecked()) // Uhh... We have data, yeah?
    {
        // Get our selected message and current time
        Json::Value cMsg = sc.getMessage(headers->text(which));
        auto aClk = std::chrono::system_clock::now();
        auto aTime = std::chrono::system_clock::to_time_t(aClk);
        std::string aDateStr(ctime(&aTime));
        // the conversion to string adds a new line at the end of the string. Trim it.
        std::string trimmed(trimMe(aDateStr));

        toFI->value(cMsg[0]["messageFrom"].asCString());
        fromFI->value(cMsg[0]["messageTo"].asCString());
        // Update our GUI with reply information
        dateFI->value(trimmed.c_str());
        stringBuilder << "RE: " << cMsg[0]["subject"].asCString();
        subjectFI->value(stringBuilder.str().c_str());
        stringBuilder.clear();
        stringBuilder.str("");
        stringBuilder << "\n\n\n-------------------------------------------------\n" << "To: " << cMsg[0]["messageTo"].asCString() << "\t\tFrom: " << cMsg[0]["messageFrom"].asCString() << "\t\tDate:" << cMsg[0]["date"].asCString() << "\n" << cMsg[0]["message"].asCString();
        messageFMI->value((stringBuilder.str()).c_str());
    }

}

/**
 * @brief      ListenerAction for Get Button
 *
 * @param      w         fltk Widget
 * @param      userdata  The userdata
 */
void SampleStudentClient::ClickedGet(Fl_Widget *w, void *userdata)
{
    // Basic Static GUI Element Initilization
    SampleStudentClient *anInstance = (SampleStudentClient *)userdata;
    std::cout << "You clicked Get" << std::endl;
    Fl_Multiline_Input *messageFMI = anInstance->messageFMI;
    Fl_Input *dateFI = anInstance->dateFI;
    Fl_Input *subjectFI = anInstance->subjectFI;
    Fl_Input *toFI = anInstance->toFI;
    Fl_Input *fromFI = anInstance->fromFI;
    Fl_Check_Browser *headers = anInstance->headerFCB;
    std::string userId = anInstance->userId;

    // clear all existing entries from the list of message headers
    headers->clear();
    jsonrpc::HttpClient hc(anInstance->hostId);
    StubClient sc(hc, jsonrpc::JSONRPC_CLIENT_V2);
    sc.login(userId);
    // Request headers
    //Message msg(userId);
    //std::vector<std::string> hdrs = msg.getMessageFromHeaders();
    Json::Value hdrs = sc.getMessageFromHeaders();
    // Populate our GUI
    for (Json::Value::const_iterator it = hdrs.begin(); it != hdrs.end(); it++)
    {
        headers->add(hdrs[it.key().asInt()].asCString());
    }
    headers->checked(1, 1);
    Json::Value cMsg = sc.getMessage(hdrs[0].asString());
    messageFMI->value(cMsg[0]["message"].asCString());
    toFI->value(cMsg[0]["messageTo"].asCString());
    fromFI->value(cMsg[0]["messageFrom"].asCString());
    dateFI->value(cMsg[0]["date"].asCString());
    subjectFI->value(cMsg[0]["subject"].asCString());
}


/**
 * @brief      ListenerAction for Delete Button
 *
 * @param      w         fltk Widget
 * @param      userdata  The userdata
 */
void SampleStudentClient::ClickedDelete(Fl_Widget *w, void *userdata)
{
    // Basic Static GUI Element Initilization
    SampleStudentClient *anInstance = (SampleStudentClient *)userdata;
    Fl_Multiline_Input *messageFMI = anInstance->messageFMI;
    Fl_Input *dateFI = anInstance->dateFI;
    Fl_Input *subjectFI = anInstance->subjectFI;
    Fl_Input *toFI = anInstance->toFI;
    Fl_Input *fromFI = anInstance->fromFI;
    Fl_Check_Browser *headers = anInstance->headerFCB;
    std::string userId = anInstance->userId;
    jsonrpc::HttpClient hc(anInstance->hostId);
    StubClient sc(hc, jsonrpc::JSONRPC_CLIENT_V2);
    sc.login(userId);


    if (headers->nitems() > 0 && headers->nchecked()) // Uhh... We have data, yeah?
    {
        if (sc.deleteMessage(headers->text(headers->value()))) // Delete successful
        {
            // Update GUI
            headers->clear();
            Json::Value hdrs = sc.getMessageFromHeaders();
            for (Json::Value::const_iterator it = hdrs.begin(); it != hdrs.end(); it++)
            {
                headers->add(hdrs[it.key().asInt()].asCString());
            }
            toFI->value("");
            fromFI->value("");
            dateFI->value("");
            subjectFI->value("");
            messageFMI->value("");

        }
    }
}


/**
 * @brief      Trimming for leading \n
 *
 * @param      str   The string
 *
 * @return     Trimmed string
 */
std::string &SampleStudentClient::trimMe (std::string &str)
{
    // right trim
    while (str.length() > 0 && (str[str.length() - 1] == ' ' || str[str.length() - 1] == '\t'
                                || str[str.length() - 1] == '\n' ||  str[str.length() - 1] == '\r'))
    {
        str.erase(str.length () - 1, 1);
    }
    // left trim
    while (str.length () > 0 && (str[0] == ' ' || str[0] == '\t'))
    {
        str.erase(0, 1);
    }
    return str;
}


/**
 * @brief      Updates message data based on new header selection
 *
 * @param      w         fltk widget
 * @param      userdata  The userdata
 */
void SampleStudentClient::SelectedHeader(Fl_Widget *w, void *userdata)
{
    // Basic Static GUI Element Initilization
    SampleStudentClient *anInstance = (SampleStudentClient *)userdata;
    Fl_Multiline_Input *messageFMI = anInstance->messageFMI;
    Fl_Input *dateFI = anInstance->dateFI;
    Fl_Input *subjectFI = anInstance->subjectFI;
    Fl_Input *toFI = anInstance->toFI;
    Fl_Input *fromFI = anInstance->fromFI;
    Fl_Check_Browser *headers = anInstance->headerFCB;
    std::string userId = anInstance->userId;
    jsonrpc::HttpClient hc(anInstance->hostId);
    StubClient sc(hc, jsonrpc::JSONRPC_CLIENT_V2);
    sc.login(userId);
    int which = headers->value();
    // Make sure we have something selected
    if (headers->nchecked())
    {
        // unselect all but the item just selected.
        headers->check_none();
        headers->checked(which, 1);
        // Populate GUI
        Json::Value cMsg = sc.getMessage(headers->text(which));
        messageFMI->value(cMsg[0]["message"].asCString());
        toFI->value(cMsg[0]["messageTo"].asCString());
        fromFI->value(cMsg[0]["messageFrom"].asCString());
        dateFI->value(cMsg[0]["date"].asCString());
        subjectFI->value(cMsg[0]["subject"].asCString());
    }
    else
    {
        toFI->value("");
        fromFI->value("");
        dateFI->value("");
        subjectFI->value("");
        messageFMI->value("");
    }
}


int main(int argc, const char* argv[])
{   std::string port = "8081";
    std::string host = "localhost";
    std::string user = "Joshua.Kronemeyer";
    if (argc > 2) {
        host = argv[1];
        port = argv[2];
        user = argv[3];
    }
    std::ostringstream stringBuilder;
    stringBuilder << "http://" << host << ":" << port;
    std::cout << stringBuilder.str();
    SampleStudentClient cm("Joshua Kronemeyer's Message Browser", stringBuilder.str(), user);

    return (Fl::run());
}
