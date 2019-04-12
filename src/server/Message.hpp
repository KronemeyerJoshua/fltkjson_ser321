#ifndef Message_H
#define Message_H

#include <vector>
#include <string>
#include <jsoncpp/json/value.h>
#include "MessageLibrary.hpp" // Just to show it compiles

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
 * This class creates Gui components for a UI to manage messages.
 * This software is meant to run on Linux, and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering, IAFSE
 *                       ASU at the Polytechnic campus
 * @author Joshua Kronemeyer (jkroneme@asu.edu)
 * @file    Message.hpp
 * @date    March, 2019
 * @license See above
 **/


/**
 * @brief      Class for message.
 */
class Message {
public:
	std::string userId;
	Message();
    Json::Value getMessageFromHeaders();
    Json::Value getMessage(std::string header);
    bool deleteMessage(std::string header);
    bool sendMessage(Json::Value message, std::string header);
    Json::Value headers;
    void setUser(std::string name);
    const char* getBody();
    const char* getSubject();
    const char* getDate();
    const char* getTo();
    const char* getFrom();

private:
	Json::Value root;
	Json::Value cMsg;

};
#endif