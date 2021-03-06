#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 
Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 rotate: create an rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 2 arguments (axis, theta) axis should be x y or z
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing
See the file script for an example of the file format
IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * edges,
                  screen s) {

  FILE *f;
  char line[256];
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");

  color c;
  //clear_screen(s); 
  c.red = MAX_COLOR;
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    //printf(":%s:\n",line);

    //HERE COMES THE FUNCTIONALLITY

    //line
    if( strcmp(line,"line") == 0){
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';

      char * hold;
      hold = strdup(line);
      char * holder;
      holder = NULL;
      char * commands[256];
      int i=0;
      while( (holder = strsep(&hold, " ")) != NULL){
	commands[i] = strdup(holder);
	i++;
      }
      
      add_edge(edges, atoi(commands[0]), atoi(commands[1]), atoi(commands[2]),
	       atoi(commands[3]), atoi(commands[4]), atoi(commands[5]));
    }

    //ident
    if( strcmp(line,"ident") == 0){
      ident(transform);
    }
    
    //scale
    if( strcmp(line,"scale") == 0){
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      
      char * hold;
      hold = strdup(line);
      char * holder;
      holder = NULL;
      char * commands[256];
      int i=0;
      while( (holder = strsep(&hold, " ")) != NULL){
	commands[i] = strdup(holder);
	i++;
      }
      
      struct matrix * h_matrix;
      h_matrix = new_matrix(4,4);
      h_matrix = make_scale(atoi(commands[0]), atoi(commands[1]), atoi(commands[2]));
      matrix_mult(h_matrix, transform); 
    }



    //move
    if( strcmp(line,"move") == 0){
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      
      char * hold;
      hold = strdup(line);
      char * holder;
      holder = NULL;
      char * commands[256];
      int i=0;
      while( (holder = strsep(&hold, " ")) != NULL){
	commands[i] = strdup(holder);
	i++;
      }
      
      struct matrix * h_matrix;
      h_matrix = new_matrix(4,4);
      h_matrix = make_translate(atoi(commands[0]), atoi(commands[1]), atoi(commands[2]));
      matrix_mult(h_matrix, transform); 
    }

    //rotate
    if( strcmp(line,"rotate") == 0){
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      
      char * hold;
      hold = strdup(line);
      char * holder;
      holder = NULL;
      char * commands[256];
      int i=0;
      while( (holder = strsep(&hold, " ")) != NULL){
	commands[i] = strdup(holder);
	i++;
      }

      struct matrix * h_matrix;
      h_matrix = new_matrix(4,4);
      
      if(strcmp(commands[0], "z") == 0){
	h_matrix = make_rotZ(atoi(commands[1]));
      }
      if(strcmp(commands[0], "y") == 0){
	h_matrix = make_rotY(atoi(commands[1]));
      }
      if(strcmp(commands[0], "x") == 0){
	h_matrix = make_rotX(atoi(commands[1]));
      }
      
      matrix_mult(h_matrix, transform); 
    }

    //apply
    if( strcmp(line,"apply") == 0){
      matrix_mult(transform, edges); 
    }

    //display
    if( strcmp(line,"display") == 0){
      clear_screen(s);
      draw_lines(edges, s, c);
      display(s);
      //clear_screen(s);
    }
    
    //save
    if( strcmp(line,"save") == 0){
      fgets(line, 255, f);
      line[strlen(line)-1]='\0';
      
      char * hold;
      hold = strdup(line);
      char * holder;
      holder = NULL;
      char * commands[256];
      int i=0;
      while( (holder = strsep(&hold, " ")) != NULL){
	commands[i] = strdup(holder);
	i++;
      }
      //printf(":%s:\n", commands[0]);
      save_extension(s, commands[0]);
    }

    //quit
    if( strcmp(line,"quit") == 0){
      printf("exiting\n");
      break;
      //exit(0);
    }

  }
  return;
}
