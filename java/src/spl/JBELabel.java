/*
 * @(#)JBELabel.java   3.01.1 07/30/14
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

package spl;

import graphics.GLabel;
import java.awt.Color;
import java.awt.Font;
import javax.swing.JComponent;
import javax.swing.JLabel;

public class JBELabel extends GLabel {
   public JBELabel(String label) {
      super(label);
      jlabel = null;
   }

   public JComponent getInteractor() {
      if (jlabel == null) {
         jlabel = new JLabel(getLabel());
         jlabel.setFont(getFont());
         jlabel.setForeground(getColor());
      }
      return jlabel;
   }

   public void setFont(Font font) {
      super.setFont(font);
      if (jlabel != null) jlabel.setFont(font);
   }

   public void setColor(Color color) {
      super.setColor(color);
      if (jlabel != null) jlabel.setForeground(color);
   }

   private JLabel jlabel;
}
