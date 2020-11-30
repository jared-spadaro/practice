//   Modifications by Jared Spadaro
//   October 14, 2013
//   CPE103 with Professor Buckalew


import java.awt.*;
import java.awt.event.*;
import java.applet.Applet;
import java.util.Iterator;
import javax.swing.*;

public class ColorTetrisDriver extends Applet {
   
   //number of different colors allowed in the game -
   //if changed, must also change paint method
   public final int numColors = 4;  
   
   //number of rows displayed 
   public final int numRows = 8;
   
   //number of stacks
   public final int numCols = 6;
   
   // block size in pixels
   private final int blkSize = 50;
   
   //stacks that store the color blocks
   public Stack stacks[] = new Stack[numCols];
   
   //color and location of the next block
   private int nextColor, nextColumn;
   
   //column to be swapped from
   private int colMarker = 0;

   //inner class that does the display
   ColorTetrisCanvas grid;
   
   //buttons that swap this stack's top with left or right tops
   private JButton left, right;
   private JPanel dirPanel;
   
   //buttons that move the stack marker
   private JButton leftS, rightS;
   private JPanel dirPanelS;
   
   //buttons that move the incoming cube
   private JButton leftC, rightC;
   private JPanel dirPanelC;

   private JPanel gamePanel;
   
   //this listener object responds to timer events
   private TimerActionListener timerListener;
   
   //this listener object responds to button events
   private ButtonActionListener buttonListener;
   
   // this method sets up the canvas and starts it off
   public void init() {
      System.out.println("ColorTetris started"); // goes to console 
      timerListener = new TimerActionListener();
      buttonListener = new ButtonActionListener();
       
      //initialize the stacks with random colors
      // pushes one block onto each stack
      for (int i=0; i<numCols; i++) {
         stacks[i] = new Stack();
         // a color is an int from 0 to numColors-1
         int color = (int) (Math.random()*1000.0)%(numColors);
         stacks[i].push(new Integer(color));
      }
        
      // the gamePanel is the panel that contains the game interfaces, including
      // the buttons and output display
      gamePanel = new JPanel();
      // Y_AXIS layout places components from top to bottom, in order of adding
      gamePanel.setLayout(new BoxLayout(gamePanel, BoxLayout.Y_AXIS));
      
      // first place the playing grid
      // this object is the output of game, the canvas on which blocks are painted
      grid = new ColorTetrisCanvas(numRows, numCols, numColors);
      // adding it first places it at the top of the gamePanel
      gamePanel.add(grid);
       
      // place the incoming cube control buttons 
      // quotes are what will appear on button
      leftC = new JButton("<C");
      // the listener is triggered when the button is clicked
      leftC.addActionListener(buttonListener);
      rightC = new JButton("C>");
      rightC.addActionListener(buttonListener);
      
      // dirPanelC contains these two buttons, laid out from left to right
      dirPanelC = new JPanel();
      dirPanelC.setLayout(new BoxLayout(dirPanelC, BoxLayout.X_AXIS));
      dirPanelC.add(leftC);
      dirPanelC.add(rightC);
      // add dirPanelC to gamePanel just below the output canvas
      gamePanel.add(dirPanelC);

      //stack top swap buttons
      left = new JButton("<");
      left.addActionListener(buttonListener);
      right = new JButton(">");
      right.addActionListener(buttonListener);

      // dirPanel contains the stack top swap buttons
      dirPanel = new JPanel();
      dirPanel.setLayout(new BoxLayout(dirPanel, BoxLayout.X_AXIS));
      dirPanel.add(left);
      dirPanel.add(right);
      // add dirPanel just below cube control buttons
      gamePanel.add(dirPanel);

      // the stack marker control buttons
      leftS = new JButton("<<");
      leftS.addActionListener(buttonListener);
      rightS = new JButton(">>");
      rightS.addActionListener(buttonListener);
      
      // dirPanelS contains the marker control buttons
      dirPanelS = new JPanel();
      dirPanelS.setLayout(new BoxLayout(dirPanelS, BoxLayout.X_AXIS));
      dirPanelS.add(leftS);
      dirPanelS.add(rightS);
      // add below top swap buttons
      gamePanel.add(dirPanelS);

      // now add the game panel to the applet
      add(gamePanel);
      
      // start the timer to go off every 3 seconds
      javax.swing.Timer timer = new javax.swing.Timer(3000, timerListener);  // goes off in 2 seconds
      timer.start();
   }
   
   // this object is triggered whenever a button is clicked
   private class ButtonActionListener implements ActionListener {
      public void actionPerformed(ActionEvent event) {
          
         // find out which button was clicked 
         Object source = event.getSource();
         
         // left marker button was clicked
         if (source == leftS) {
            // shift column marker left
            shiftColumnMarkerLeft();
         }
         
         // right marker button was clicked
         else if (source == rightS) {
            // shift column marker right
            shiftColumnMarkerRight();
         }
         
         // left swap button was clicked
         else if (source == left) {
            // swap tops of this and left stack (EVEN if left stack is empty!)
            // YOUR CODE HERE
	    //Make sure the column marker isn't on the far left stack
	      if(colMarker > 0) {
		//Case for if the current stack is empty
		if(stacks[colMarker].height()==0) {
		  Integer x = new Integer(0);
		  x = (Integer)stacks[colMarker-1].pop(); //Store top of left stack in x
		  stacks[colMarker].push(x);              //Add x to top of current stack
	        }
	        //Case for if the left stack is empty
		else if(stacks[colMarker-1].height()==0) {
		  Integer x = new Integer(0);
		  x = (Integer)stacks[colMarker].pop();  //Store top of current stack in x
		  stacks[colMarker-1].push(x);           //Add x to top of left stack
		}
		//Case for if the neither stacks are empty
		else {
		  Integer x1 = new Integer(0);
		  Integer x2 = new Integer(0);
		  x1 = (Integer)stacks[colMarker].pop();  //Store top of current stack in x1
		  x2 = (Integer)stacks[colMarker-1].pop();//Store top of left stack in x2
		  stacks[colMarker].push(x2);             //Add x2 to current stack
		  stacks[colMarker-1].push(x1);           //Add x1 to left stack
	        }
	     }
	     else {
	       //do nothing (no stack to the left)
	     }
         }
         
         // right swap button was clicked
         else if (source == right) {
            // swap tops of this and right stack
            // YOUR CODE HERE
	    //Make sure that the column marker isn't on the far right stack
	    if(colMarker < numCols-1) {
	      //Case for if current stack is empty
	      if(stacks[colMarker].height()==0) {
		Integer x = new Integer(0);
		x = (Integer)stacks[colMarker+1].pop(); //Store top of right stack in x
		stacks[colMarker].push(x);              //Add x to the current stack
	      }
	      //Case for if the right stack is empty
	      else if(stacks[colMarker+1].height()==0) {
	        Integer x = new Integer(0);
		x = (Integer)stacks[colMarker].pop();  //Store top of current stack in x
		stacks[colMarker+1].push(x);           //Add x to the right stack
	      }
	      //Case for if neither stacks are empty
	      else {
	        Integer x1 = new Integer(0);
		Integer x2 = new Integer(0);
		x1 = (Integer)stacks[colMarker].pop();  //Store top of current stack in x1
		x2 = (Integer)stacks[colMarker+1].pop();//Store top of right stack in x2
		stacks[colMarker].push(x2);             //Add x2 to current stack
		stacks[colMarker+1].push(x1);           //Add x1 to right stack
	      }
           }
           else {
	     //do nothing (no stack to the right)
           }
         }
         
         else if (source == leftC) {
            // move incoming cube left
            if (nextColumn > 0) {
               nextColumn--;
            }
         }
         else if (source == rightC) {
            // move incoming cube right
            if (nextColumn < numCols-1) {
               nextColumn++;
            }
         }
         removeCombos();
         grid.paint(grid.getGraphics());
      } 
      
      public void shiftColumnMarkerLeft() {
         if (colMarker > 0) colMarker--;
         else colMarker = 0;
      }
        
      public void shiftColumnMarkerRight() {
         if (colMarker < numCols-1) colMarker++;
         else colMarker = numCols-1;
      }
   }
   
   // this object is triggered when the timer goes off
   private class TimerActionListener implements ActionListener {
      public void actionPerformed(ActionEvent event) {
          
         // push the hanging cube onto its column 
         stacks[nextColumn].push(new Integer(nextColor));
          
         // generate randomly the next cube's column and color
         nextColor = (int) (Math.random()*1000.0)%(numColors);
         nextColumn = (int) (Math.random()*1000.0)%(numCols);
                   
         // remove any combos there may be
         removeCombos();
         
         // update output screen
         grid.paint(grid.getGraphics());
      }
   }        
    
   public void removeCombos() {
      // check for 3 in a row horizontally and remove them
      //YOUR CODE HERE
      int i;
      //Go through loop 4 times to compare columns(0,1,2)/(1,2,3)/(2,3,4)/(3,4,5)
      for(i=0;i<numCols-2;i++) { 
        //Check to make sure that none of the stacks are empty	  
	if(stacks[i].height()>0&&stacks[i+1].height()>0&&stacks[i+2].height()>0) {
          //Check to see if there are 3 consecutive colors by calling peek for each stack and comparing with the equals method
          if((stacks[i].peek().equals(stacks[i+1].peek()))&&(stacks[i+1].peek().equals(stacks[i+2].peek()))) {
	    //If there are 3 consecutive colors, remove them 
	    stacks[i].pop();
            stacks[i+1].pop();
	    stacks[i+2].pop();
	  }
        }
      }
   }
    
   class ColorTetrisCanvas extends Canvas {
      // this class paints the output window 
      int rows, cols;
      int numColors;
       
      // the constructor sets it up
      ColorTetrisCanvas(int r, int c, int nc) {
         rows = r;
         cols = c;
         numColors = nc;
         // width of window needs one extra pixel to draw the column marker
         // height of window needs two extra rows
         // top one for incoming block and next one for space
         setSize(cols*blkSize+1, (rows+2)*blkSize);
         setBackground(Color.white);
      }
       
      // this method paints the output window
      public void paint(Graphics g) {
         
         Integer stackColor;
         
         // these three lines just fill the whole window with white
         setBackground(Color.white);
         g.setColor(Color.white);
         // parameters are upper left coordinates of rectangle and
         // width and height of the rectangle
         // upper left corner of window is 0,0
         g.fillRect(0, 0, cols*blkSize + 1, (rows+2) * blkSize);
           
         boolean done = false;
         for (int j=0; j<cols; j++) {
            if (stacks[j].height() >= rows-1) {
               // a stack has exceeded the limit
               done = true;
            }   
         }
         if (done == false) {
            // draw the next block to fall   
            setBlockColor(g, nextColor);
            g.fillRect(nextColumn*blkSize, 0, blkSize, blkSize);
              
            // now draw the stacks
	    //YOUR CODE HERE
            for (int j=0; j<cols; j++) {
               if (stacks[j].height()==0) {}
               else {
                 int i = 0;
		 int k;
		 //Create iterator for stack
		 Iterator itr = stacks[j].iterator();
		 //First stack color will come from top of stack
		 stackColor = (Integer) stacks[j].peek();
                 setBlockColor(g, stackColor);
		 g.fillRect(j*blkSize, i*blkSize + 2*blkSize, blkSize, blkSize);
                 i++;
		 //Move iterator forward so as not to re-paint the top stack
                 itr.next();  
                   //Run through loop for every item stack has (excluding top item)
		   for(k=1;k<stacks[j].height();k++) {
		     //Store stack's next color in stackColor
		     stackColor = (Integer) itr.next();
		     setBlockColor(g, stackColor);     
		     g.fillRect(j*blkSize, i*blkSize + 2*blkSize, blkSize, blkSize);
                     i++;
		   }
                }
             }
         }
         
         // draw the column marker
         // it's two rows down from the top
         g.setColor(Color.black);
         g.drawRect(colMarker*blkSize, blkSize*2, blkSize, rows*blkSize);
      }
      
      // sets color state
      private void setBlockColor(Graphics g, int color) {
         switch (color) {
            case 0: g.setColor(Color.blue); break;
            case 1: g.setColor(Color.red); break;
            case 2: g.setColor(Color.green); break;
            case 3: g.setColor(Color.cyan); break;
        }
      }
   }
}
