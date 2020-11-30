#include "data.h"
#include "cast.h"
#include "commandline.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "strcmp.h"



int strcmp(char const s1[],char const s2[])
{
   int i;
   for(i=0;s1[i]!='\0'&&s2[i]!='\0';i++)
   {
      if(s1[i]!=s2[i])
      {
         if(s1[i]<s2[i])
         {
            return -1;
         } 
         else
         {
 	    return 1;
         }
      }
   }
   return 0;
}
	      
		  
		  

int flag_finder (char * cmdline[],char flag[],int num_args)
{
   int i;
   
   for(i=0;i<num_args;i++)
   {
      if(strcmp(cmdline[i],flag)==0)
      {
	 return i;
      }
   }
   return 0;
}



double convert_double(char const input[],double default_value)
{
   double ret_value;
   int converted;
   converted = sscanf(input,"%lf",&ret_value);
   if(converted == 1)
   {
      return ret_value;
   }
   return default_value;
}



void flag_checker (char *cmdline[],double flag[],int flag_index,int size)
{
   int i;
   int temp;
   for(i=0;i<size;i++)
   {
      flag[i] = convert_double(cmdline[flag_index+(i+1)],flag[i]);
	  
	  
      if(convert_double(cmdline[flag_index+(i+1)],0)==0)
      {
	 i=size;
      }
   }
}
	  


FILE * open_file(char const name[])
{
   FILE * file = fopen(name,"r");
   if(file == NULL)
   {
      printf("Usage: a.out <filename> [-eye x y z] [-view min_x max_x min_y max_y width height] [-light x y z r g b] [-ambient r g b]\n");
      exit(1);
   }
   return file;
}




void read_and_print(FILE * input,FILE * output,int cmd_arg,char * cmdline[])
{
   int result;
   int num_spheres_read=0;
   double center_x,center_y,center_z;
   double radius;
   double sphr_r,sphr_g,sphr_b;
   double ambient,diffuse,specular,roughness;
   struct sphere reading_sphere;
   
   
   struct sphere spheres[10000];
   
   
   double eye_x=0;
   double eye_y=0;
   double eye_z=-14;
  
   double min_x=-10;
   double max_x=10;
   double min_y=-7.5;
   double max_y=7.5;
   double width=1024;
   double height=768;
   
   double light_x=-100;
   double light_y=100;
   double light_z=-100;
   
   double light_r=1.5;
   double light_g=1.5;
   double light_b=1.5;
   
   double ambient_r=1.0;
   double ambient_g=1.0;
   double ambient_b=1.0;
   
   
   char eye_flag[] = "-eye";
   char view_flag[] = "-view";
   char light_flag[] = "-light";
   char ambient_flag[] = "-ambient";
   int index_eye = flag_finder(cmdline,eye_flag,cmd_arg);
   int index_view = flag_finder(cmdline,view_flag,cmd_arg);
   int index_light = flag_finder(cmdline,light_flag,cmd_arg);
   int index_ambient = flag_finder(cmdline,ambient_flag,cmd_arg);
	
   if(index_eye!=0)
   {
      	   
           eye_x = convert_double(cmdline[index_eye+1],eye_x);
	   eye_y = convert_double(cmdline[index_eye+2],eye_y);
	   eye_z = convert_double(cmdline[index_eye+3],eye_z);
   }
	
   if(index_view!=0)
   {
	   min_x = convert_double(cmdline[index_view+1],min_x);
	   max_x = convert_double(cmdline[index_view+2],max_x);
	   min_y = convert_double(cmdline[index_view+3],min_y);
           max_y = convert_double(cmdline[index_view+4],max_y);
	   width = convert_double(cmdline[index_view+5],width);
	   height = convert_double(cmdline[index_view+6],height);
   }
	
   if(index_light!=0)
   {
	   light_x = convert_double(cmdline[index_light+1],light_x);
	   light_y = convert_double(cmdline[index_light+2],light_y);
	   light_z = convert_double(cmdline[index_light+3],light_z);
	   light_r = convert_double(cmdline[index_light+4],light_r);
	   light_g = convert_double(cmdline[index_light+5],light_g);
	   light_b = convert_double(cmdline[index_light+6],light_b);
   }
	
   if(index_ambient!=0)
   {
	   ambient_r = convert_double(cmdline[index_ambient+1],ambient_r);
	   ambient_g = convert_double(cmdline[index_ambient+2],ambient_g);
	   ambient_b = convert_double(cmdline[index_ambient+3],ambient_b);
   }
	

    struct point eye = create_point(eye_x,eye_y,eye_z);
   
    struct point light_origin = create_point(light_x,light_y,light_z);
    struct color light_color = create_color(light_r,light_g,light_b);
    struct light l = create_light(light_origin,light_color);
   
    struct color ambient_light = create_color(ambient_r,ambient_g,ambient_b);


   if(cmd_arg<=1 || cmd_arg>24)
   {
      printf("Usage: a.out <filename> [-eye x y z] [-view min_x max_x min_y max_y width height] [-light x y z r g b] [-ambient r g b]\n");
      exit(1);
   }
   
   while(result!=EOF&&num_spheres_read<10000)
   {
      result=fscanf(input,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
      &center_x,&center_y,&center_z,&radius,&sphr_r,&sphr_g,&sphr_b,&ambient,&diffuse,&specular,&roughness);
	  
      reading_sphere = create_sphere(create_point(center_x,center_y,center_z),radius,
      create_color(sphr_r,sphr_g,sphr_b),create_finish(ambient,diffuse,specular,roughness));
    
      spheres[num_spheres_read] = reading_sphere;
	  
      num_spheres_read++;
   }
    
   cast_all_rays(min_x,max_x,min_y,max_y,width,height,eye,spheres,num_spheres_read,ambient_light,l,output);
   
}
	  
	  
	  
	  
	  
	  