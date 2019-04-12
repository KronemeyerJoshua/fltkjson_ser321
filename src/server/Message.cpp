#include "Message.hpp"
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <fstream>
#include <iostream>
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
 * This class creates Gui components for a UI to manage messages.
 * This software is meant to run on Linux, and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering, IAFSE
 *                       ASU at the Polytechnic campus
 * @author Joshua Kronemeyer (jkroneme@asu.edu)
 * @file    Message.cpp
 * @date    March, 2019
 * @license See above
 **/


/**
 * @brief      Constructs the Message.
 *
 * @param[in]  name  userId
 */
Message::Message()
{
	// Setup our root JSON from file and grab current user
    std::ifstream jsonfile("src/server/messages.json", std::ifstream::binary);
    Json::Reader reader;
    bool success = reader.parse(jsonfile, root, false);
    jsonfile.close();
    if (!success)
    {
        std::cout << reader.getFormattedErrorMessages();
    }
}


/**
 * @brief      Gets the headers from userId.
 *
 * @return     The headers from userId.
 */
Json::Value Message::getMessageFromHeaders()
{   
    headers.clear();
    for (int i = 0; i < root[userId].size(); i++)
    {
        headers.append(root[userId].getMemberNames()[i]);
    }
    return headers;
}


/**
 * @brief      Gets the message.
 *
 * @param[in]  header  The header
 *
 * @return     The message.
 */
Json::Value Message::getMessage(std::string header)
{
    Json::Value msg = root[userId][header];
    return msg;
}

/**
 * @brief      Delete's Message from Json
 *
 * @param[in]  header  The header
 *
 * @return     Successful deletion bool
 */
bool Message::deleteMessage(std::string header) {
	Json::Value s = root[userId].removeMember(header);
	std::ofstream jsonfile("src/server/messages.json");
    jsonfile << root;
	if (s.size())
		return true;
	return false;
}

bool Message::sendMessage(Json::Value msg, std::string header) {
    root[msg["messageTo"].asCString()][header].append(msg);
    Json::StyledStreamWriter ssw(" ");
    std::ofstream jsonOutFile("src/server/messages.json", std::ofstream::binary);
    ssw.write(jsonOutFile, root);

    return true;
}


void Message::setUser(std::string name) {
    userId = name;
}

/**
 * @brief      Gets the body.
 *
 * @return     The body.
 */
const char *Message::getBody()
{
	return cMsg[0]["message"].asCString();
}

/**
 * @brief      Gets the subject.
 *
 * @return     The subject.
 */
const char *Message::getSubject()
{
	return cMsg[0]["subject"].asCString();
}

/**
 * @brief      Gets the date.
 *
 * @return     The date.
 */
const char *Message::getDate()
{
	return cMsg[0]["date"].asCString();
}

/**
 * @brief      Gets message to.
 *
 * @return     To.
 */
const char *Message::getTo()
{
	return cMsg[0]["messageTo"].asCString();
}

/**
 * @brief      Gets message from.
 *
 * @return     message from.
 */
const char *Message::getFrom()
{
	return cMsg[0]["messageFrom"].asCString();
}