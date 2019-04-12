#ifndef MessageGUI_H
#define MessageGUI_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Check_Browser.H>

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
 * @file    MessageGui.hpp
 * @date    March, 2019
 * @license See above
 **/


/**
 * @brief      Definitions for our GUI
 */
class MessageGui: public Fl_Window {
	protected:
   /**
    * fromFI is the Fl_Input labelled from, identifying who the message is from.
    */
   Fl_Input * fromFI;

   /**
    * toIC is the Fl_Input labelled to, identifying who the message is to
    */
   Fl_Input * toFI;

   /**
    * subjectFI is the Fl_Input labeled subject, identifying the message subject
    */
   Fl_Input * subjectFI;

   /**
    * dateFI is the Fl_Input labeled date, identifying the message creation date.
    */
   Fl_Input *dateFI;

   /**
    * messageFMI is the Fl_Multiline_Input below subject and date for displaying
    * or entering the message text.
    */
   Fl_Multiline_Input *messageFMI;

   /**
    * getButt is the Fl_Button labelled Get
    * When the user clicks Get, the list of message headers on the left is refreshed.
    */
   Fl_Button * getButt;

   /**
    * deleteButt is the Fl_Button labeled Delete.
    * When the user clicks Delete, the currently displayed message is removed from the
    * message library and its header is removed from the list of message headers.
    */
   Fl_Button *deleteButt;

   /**
    * replyButt is the Fl_Button labeled Reply
    * When the user clicks Reply, the fields on the right side
    * change from a mode of displaying the contents of a message to creating a new
    * message.
    */
   Fl_Button *replyButt;

   /**
    * sendButt is the Fl_Button labeled Send.
    * Clicking this button should cause the library to add a new message from the
    * contents of the fields on the right side of the display
    */
   Fl_Button *sendButt;

   /**
    * exportButt is the Fl_Button labeled Export.
    * This button should cause the library to be serialized to Json and saved in the
    * messages.json file in the projects base directory.
    */
   Fl_Button * exportButt;

   /**
    * headerFCB is the Fl_Check_Browser on the left side of the window.
    * This area is for displaying the message headers.
    */
   Fl_Check_Browser *headerFCB;
   
public:
   MessageGui(const char * name = 0);
};
#endif