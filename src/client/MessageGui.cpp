#include "MessageGui.hpp"
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

using namespace std;

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
 * @file    MessageGui.cpp
 * @date    March, 2019
 * @license See above
 **/
   

/**
 * @brief      Constructs the GUI
 *
 * @param[in]  name  userId
 */
MessageGui::MessageGui(const char * name) : Fl_Window(965,400,name) {
      begin();
      // create the list of message headers on the left side of the GUI
      headerFCB = new Fl_Check_Browser(25,75,345,300,"");

      toFI = new Fl_Input(400, 75, 245, 25,"To");
      fromFI = new Fl_Input(705, 75, 245, 25,"From");

      subjectFI = new Fl_Input(430, 125, 250, 25, "Subject");
      dateFI = new Fl_Input(730, 125, 220, 25, "Date");

      messageFMI = new Fl_Multiline_Input(415, 175, 525, 200,"Msg");
      // tell the message multiline to word wrap. 1=on 0=off
      messageFMI->wrap(1);
      
      // create the buttons across the top of the UI
      getButt = new Fl_Button(60,25,100,25,"Get");
      deleteButt = new Fl_Button(180,25,100,25,"Delete");
      replyButt = new Fl_Button(300,25,100,25,"Reply");
      sendButt = new Fl_Button(420,25,100,25,"Send");
      exportButt = new Fl_Button(540,25,100,25,"Export");

      end();
      show();
   }